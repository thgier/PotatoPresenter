/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <KParts/ReadOnlyPart>
#include <KTextEditor/View>
#include <KTextEditor/MarkInterface>
#include <KActionCollection>

#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QDebug>
#include <QObject>
#include <QTableWidget>
#include <QFileDialog>
#include <QToolButton>
#include <QMessageBox>
#include <QCloseEvent>

#include <functional>

#include "parser.h"
#include "equationcachemanager.h"
#include "cachemanager.h"
#include "slidelistmodel.h"
#include "slidelistdelegate.h"
#include "pdfcreator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setSizes(QList<int>{10000, 10000});
    mEditor = KTextEditor::Editor::instance();
    mDoc = mEditor->createDocument(this);

    mPresentation = std::make_shared<Presentation>();
    mSlideWidget = ui->slideWidget;
    mSlideWidget->setPresentation(mPresentation);

    mViewTextDoc = mDoc->createView(this);
    ui->editor->addWidget(mViewTextDoc);

    // setup Item model
    mSlideModel = new SlideListModel(this);
    mSlideModel->setPresentation(mPresentation);
    ui->pagePreview->setModel(mSlideModel);
    SlideListDelegate *delegate = new SlideListDelegate(this);
    ui->pagePreview->setItemDelegate(delegate);
    ui->pagePreview->setViewMode(QListView::IconMode);
    QItemSelectionModel *selectionModel = ui->pagePreview->selectionModel();

    // setup bar with error messages and couple button
    auto *barTop = new QHBoxLayout(this);
    ui->paint->insertLayout(0, barTop);

    mCoupleButton = new QToolButton(this);
    mCoupleButton->setCheckable(true);
    mCoupleButton->setChecked(true);
    mCoupleButton->setIcon(QIcon::fromTheme("edit-link"));
    mCoupleButton->setToolTip("Couple the Cursor in the Editor and the selection in Slide view");

    mSnappingButton = new QToolButton(this);
    mSnappingButton->setCheckable(true);
    mSnappingButton->setChecked(true);
    mSnappingButton->setIcon(QIcon::fromTheme("snap-nodes-cusp"));
    mSnappingButton->setToolTip("Turn Snapping on/off during Box Geometry manipulation");

    mErrorOutput = new QLabel(this);

    barTop->addWidget(mCoupleButton);
    barTop->addWidget(mSnappingButton);
    barTop->addWidget(mErrorOutput);


    // setup document
    newDocument();

    connect(ui->actionClean_Configurations, &QAction::triggered,
            mPresentation.get(), &Presentation::deleteNotNeededConfigurations);

    connect(selectionModel, &QItemSelectionModel::currentChanged,
            this, [this](const QModelIndex &current){mSlideWidget->setCurrentPage(current.row());});

    connect(mDoc, &KTextEditor::Document::textChanged,
                     this, &MainWindow::fileChanged);
    connect(ui->actionReset_Position, &QAction::triggered,
            this, [this](){mSlideWidget->deleteBoxPosition();
                           fileChanged();});
    connect(ui->actionCreatePDF, &QAction::triggered,
                     this, &MainWindow::exportPDF);
    connect(ui->actionExport_PDF_as, &QAction::triggered,
            this, &MainWindow::exportPDFAs);
    connect(ui->actionExport_PDF_Handout, &QAction::triggered,
            this, &MainWindow::exportPDFHandout);
    connect(ui->actionExport_PDF_Handout_as, &QAction::triggered,
            this, &MainWindow::exportPDFHandoutAs);

    connect(&cacheManager(), &EquationCacheManager::conversionFinished,
            mPresentation.get(), &Presentation::presentationChanged);

    CacheManager<QImage>::instance().setCallback([this](QString){mSlideWidget->update();});
    CacheManager<QSvgRenderer>::instance().setCallback([this](QString){mSlideWidget->update();});

    mErrorOutput->setWordWrap(true);

    auto transformGroup = new QActionGroup(this);
    transformGroup->addAction(ui->actionRotate);
    transformGroup->addAction(ui->actionTranslate);
    ui->actionTranslate->setChecked(true);
    connect(ui->actionRotate, &QAction::triggered,
           this, [this](){mSlideWidget->setTransformationType(TransformationType::rotate);});
    connect(ui->actionTranslate, &QAction::triggered,
            this, [this](){mSlideWidget->setTransformationType(TransformationType::translate);});

    connect(mSlideWidget, &SlideWidget::selectionChanged,
            this, [this](Slide::Ptr slide){
            if(!mCoupleButton->isChecked()) {return ;}
            auto [slideInLine, boxInLine] = mPresentation->findBoxForLine(mViewTextDoc->cursorPosition().line());
            if(slideInLine != slide) {
                mViewTextDoc->setCursorPosition(KTextEditor::Cursor(slide->line(), 0));
                mViewTextDoc->removeSelection();
            }});
    connect(mSlideWidget, &SlideWidget::boxSelectionChanged,
            this, [this](Box::Ptr box){
            if(!mCoupleButton->isChecked()) {return ;}
            auto [slideInLine, boxInLine] = mPresentation->findBoxForLine(mViewTextDoc->cursorPosition().line());
            if(boxInLine != box) {
                mViewTextDoc->setCursorPosition(KTextEditor::Cursor(box->line(), 0));
                mViewTextDoc->removeSelection();
            }});

    connect(ui->actionUndo, &QAction::triggered,
            mSlideWidget, &SlideWidget::undo);
    connect(ui->actionRedo, &QAction::triggered,
            mSlideWidget, &SlideWidget::redo);

    connect(ui->actionSave, &QAction::triggered,
            this, &MainWindow::save);
    connect(ui->actionSave_as, &QAction::triggered,
            this, &MainWindow::saveAs);
    connect(ui->actionOpen, &QAction::triggered,
            this, &MainWindow::openFile);
    connect(ui->actionNew, &QAction::triggered,
            this, &MainWindow::newDocument);

    connect(mSnappingButton, &QToolButton::clicked,
            this, [this](){mSlideWidget->setSnapping(mSnappingButton->isChecked());});
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(!closeDocument()) {
        event->ignore();
        return;
    }
    QMainWindow::closeEvent(event);
}

void MainWindow::fileChanged() {
    if(!mIsModified) {
        setWindowTitle(windowTitleNotSaved());
        mIsModified = true;
    }
    auto iface = qobject_cast<KTextEditor::MarkInterface*>(mDoc);
    iface->clearMarks();
    auto file = QFileInfo(filename()).absolutePath();
    Parser parser{file};
    parser.loadInput(mDoc->text().toUtf8());
    try {
        auto const preamble = parser.readPreamble();
        auto slides = parser.readInput();
        if(!preamble.templateName.isEmpty()) {
            readTemplate(preamble.templateName);
            mPresentation->setTemplate(&mTemplate);
        }
        mPresentation->setSlides(slides);
        mErrorOutput->setText("Conversion succeeded \u2714");
    }  catch (ParserError& error) {
        mErrorOutput->setText("Line " + QString::number(error.line + 1) + ": " + error.message + " \u26A0");
        iface->addMark(error.line, KTextEditor::MarkInterface::MarkTypes::Error);
        return;
    }
    mSlideWidget->updateSlideId();
    mSlideWidget->update();
    auto const index = mSlideModel->index(mSlideWidget->pageNumber());
    ui->pagePreview->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
    ui->pagePreview->scrollTo(index);
}

void MainWindow::readTemplate(QString filename) {
    Parser templateParser{QFileInfo(filename).absolutePath()};
    templateParser.setParseTemplate(true);
    try {
        mTemplate.readTemplateConfig(filename + ".json");
    }  catch (ConfigError& error) {
        throw ParserError{error.errorMessage, 0};
    }

    auto file = QFile(filename + ".txt");
    if(!file.open(QIODevice::ReadOnly)){
        throw ParserError{"Can't open file" + file.fileName(), 0};
    }
    templateParser.loadInput(file.readAll());
    auto const templateSlides = templateParser.readInput();
    mTemplate.setSlides(templateSlides);
}

void MainWindow::setupFileActionsFromKPart() {
    // HACK: Steal actions from the KPart
    deleteShortcutOfKDocAction("file_save");
    deleteShortcutOfKDocAction("file_save_as");
}

void MainWindow::openInputFile(QString filename) {
    auto url = QUrl::fromLocalFile(filename);
    if (!mDoc->openUrl(url)){
        qWarning() << "file not found";
    }
    mDoc->setHighlightingMode("LaTeX");
}

void MainWindow::openFile() {
    if(!closeDocument()) {
        return;
    }
    auto const newFile = QFileDialog::getOpenFileName(this,
        tr("Open File"), filename(), tr("Input Files"));
    if(newFile.isEmpty()){
        return;
    }
    newDocument();
    openInputFile(newFile);
    openJson();
    mPdfFile = "";
    fileChanged();
    setWindowTitle(windowTitle());
    mIsModified = false;
}

void MainWindow::newDocument() {
    if(!closeDocument()) {
        return;
    }
    mDoc = mEditor->createDocument(this);
    mViewTextDoc->deleteLater();
    mViewTextDoc = mDoc->createView(this);
    ui->editor->addWidget(mViewTextDoc);
    connect(mDoc, &KTextEditor::Document::textChanged,
                     this, &MainWindow::fileChanged);
    setupFileActionsFromKPart();
    resetPresentation();
    fileChanged();
    mViewTextDoc->setFocus();
    mDoc->setHighlightingMode("LaTeX");
    mPdfFile = "";

    // couple cursor position and box selection
    mCursorTimer.setSingleShot(true);
    connect(mViewTextDoc, &KTextEditor::View::cursorPositionChanged,
            this, [this](KTextEditor::View *, const KTextEditor::Cursor &){mCursorTimer.start(10);});
    connect(mDoc, &KTextEditor::Document::textChanged,
            this,[this](){mCursorTimer.start(10);});
    connect(&mCursorTimer, &QTimer::timeout,
            this, &MainWindow::updateCursorPosition);
    connect(mPresentation.get(), &Presentation::slideChanged,
            mSlideWidget, [this](int){mSlideWidget->update();});
    setWindowTitle(windowTitle());
    mIsModified = false;
}

bool MainWindow::save() {
    if(!mDoc->documentSave()) {
        return false;
    }
    saveJson();
    ui->statusbar->showMessage(tr("Saved File to  \"%1\".").arg(mDoc->url().toString()), 10000);
    setWindowTitle(windowTitle());
    mIsModified = false;
    return true;
}

bool MainWindow::saveAs(){
    if(!mDoc->documentSaveAs()) {
        return false;
    }
    saveJson();
    fileChanged();
    ui->statusbar->showMessage(tr("Saved File to  \"%1\".").arg(mDoc->url().toString()), 10000);
    setWindowTitle(windowTitle());
    mIsModified = false;
    return true;
}

QString MainWindow::jsonFileName() const {
    if(filename().endsWith(".txt")) {
        return filename().section('.', 0, -2) + ".json";
    }
    return filename() + ".json";
}

void MainWindow::saveJson() {
    mPresentation->saveConfig(jsonFileName());
}

void MainWindow::openJson() {
    if(!QFile::exists(jsonFileName())){
        int ret = QMessageBox::information(this, tr("Failed to open File"), tr("Failed to find %1. Genereate a new empty Configuration File").arg(jsonFileName()),
                                 QMessageBox::Ok);
        switch (ret) {
        case QMessageBox::Ok:
            resetPresentation();
            mPresentation->saveConfig(jsonFileName());
            break;
        }
    }
    mPresentation->loadInput(jsonFileName());
    mSlideWidget->setPresentation(mPresentation);
}

QString MainWindow::filename() const {
    return mDoc->url().toString(QUrl::PreferLocalFile);
}

QString MainWindow::completeBaseName() const {
    auto name = QFileInfo(filename()).completeBaseName();
    if(name.isEmpty()) {
        return "Untitled";
    }
    return name;
}

void MainWindow::resetPresentation() {
    mPresentation = std::make_shared<Presentation>();
    mSlideWidget->setPresentation(mPresentation);
    mSlideModel->setPresentation(mPresentation);
    connect(mPresentation.get(), &Presentation::rebuildNeeded,
            this, &MainWindow::fileChanged);
}

void MainWindow::exportPDF() {
    if(mPdfFile.isEmpty()) {
        exportPDFAs();
        return;
    }
    writePDF();
}

void MainWindow::exportPDFAs() {
    QFileDialog dialog;
    if(mPdfFile.isEmpty()) {
        mPdfFile = getPdfFilename();
    }
    dialog.selectFile(mPdfFile);
    mPdfFile = dialog.getSaveFileName(this, tr("Export PDF"),
                               mPdfFile,
                               tr("pdf (*.pdf)"));
    writePDF();
}

void MainWindow::exportPDFHandout() {
    if(mPdfFileHandout.isEmpty()) {
        exportPDFHandoutAs();
        return;
    }
    writePDFHandout();
}

void MainWindow::exportPDFHandoutAs() {
    QFileDialog dialog;
    if(mPdfFileHandout.isEmpty()) {
        mPdfFileHandout = getPdfFilenameHandout();
    }
    dialog.selectFile(mPdfFileHandout);
    mPdfFileHandout = dialog.getSaveFileName(this, tr("Export PDF Handout"),
                               mPdfFileHandout,
                               tr("pdf (*.pdf)"));
    writePDFHandout();
}

void MainWindow::writePDF() const {
    PDFCreator creator;
    creator.createPdf(mPdfFile, mPresentation);
    ui->statusbar->showMessage(tr("Saved PDF to \"%1\".").arg(mPdfFile), 10000);
}

void MainWindow::writePDFHandout() const {
    PDFCreator creator;
    creator.createPdfHandout(mPdfFileHandout, mPresentation);
    ui->statusbar->showMessage(tr("Saved PDF to \"%1\".").arg(mPdfFileHandout), 10000);
}

QString MainWindow::getConfigFilename(QUrl inputUrl) {
    return inputUrl.toLocalFile().section('.', 0, -2) + ".json";
}

QString MainWindow::getPdfFilename() {
    return mDoc->url().toLocalFile().section('.', 0, -2) + ".pdf";
}

QString MainWindow::getPdfFilenameHandout() {
    return mDoc->url().toLocalFile().section('.', 0, -2) + "_handout.pdf";
}

QAction* MainWindow::deleteShortcutOfKDocAction(const char* name){
    QAction *action = mViewTextDoc->action(name);
    if( action )
       {
            action->setShortcut(QKeySequence());
       }
    return action;
}

void MainWindow::updateCursorPosition() {
    if(!mCoupleButton->isChecked()) {
        return ;
    }
    auto [slide, box] = mPresentation->findBoxForLine(mViewTextDoc->cursorPosition().line());
    if(!slide) {
        return;
    }
    mSlideWidget->setActiveBox(box ? box->id() : QString(), slide->id());
    auto const index = mSlideModel->index(mSlideWidget->pageNumber());
    ui->pagePreview->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
    ui->pagePreview->scrollTo(index);
}

QString MainWindow::applicationName() const {
    return "Potato Presenter";
}

QString MainWindow::windowTitle() const {
    return completeBaseName() + " \u2014 " + applicationName();
}

QString MainWindow::windowTitleNotSaved() const {
    return completeBaseName() + " * \u2014 " + applicationName();
}

bool MainWindow::closeDocument() {
    if(!mIsModified) {
        return true;
    }
    int ret = QMessageBox::information(this, tr("Unsaved changes"), tr("The document %1 has been modified. "
                          "Do you want to save your changes or discard them?").arg(filename()),
                          QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        if(!save()) {
            return false;
        }
        break;
      case QMessageBox::Discard:
        break;
      case QMessageBox::Cancel:
        return false;
      default:
        return false;
    }
    return true;
}
