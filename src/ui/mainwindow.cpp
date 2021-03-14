#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <KTextEditor/View>
#include <KParts/ReadOnlyPart>
#include <KTextEditor/MarkInterface>
#include <KActionCollection>
#include <QProcess>
#include <QDebug>
#include <QObject>
#include <QTableWidget>
#include <QFileDialog>
#include <QToolButton>
#include <QMessageBox>
#include <functional>
#include "parser.h"
#include "equationcachemanager.h"
#include "cachemanager.h"
#include "framelistmodel.h"
#include "framelistdelegate.h"
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
    mFrameWidget = ui->framewidget;
    mFrameWidget->setPresentation(mPresentation);

    mViewTextDoc = mDoc->createView(this);
    ui->editor->addWidget(mViewTextDoc);

    // setup Item model
    mFrameModel = new FrameListModel(this);
    mFrameModel->setPresentation(mPresentation);
    ui->pagePreview->setModel(mFrameModel);
    FrameListDelegate *delegate = new FrameListDelegate(this);
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
    mCoupleButton->setToolTip("Couple the Cursor in the Editor and the selection in Frame view");

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
    fileChanged();
    setupFileActions();

    connect(ui->actionClean_Configurations, &QAction::triggered,
            mPresentation.get(), &Presentation::deleteNotNeededConfigurations);

    connect(selectionModel, &QItemSelectionModel::currentChanged,
            this, [this](const QModelIndex &current){mFrameWidget->setCurrentPage(current.row());});

    connect(mDoc, &KTextEditor::Document::textChanged,
                     this, &MainWindow::fileChanged);
    connect(ui->actionReset_Position, &QAction::triggered,
            this, [this](){mFrameWidget->deleteBoxPosition();
                           fileChanged();});
    connect(ui->actionCreatePDF, &QAction::triggered,
                     this, &MainWindow::exportPDF);
    connect(ui->actionExport_PDF_as, &QAction::triggered,
            this, &MainWindow::exportPDFAs);

    connect(&cacheManager(), &EquationCacheManager::conversionFinished,
            mFrameWidget, QOverload<>::of(&FrameWidget::update));

    CacheManager<QImage>::instance().setCallback([this](QString){mFrameWidget->update();});
    CacheManager<QSvgRenderer>::instance().setCallback([this](QString){mFrameWidget->update();});

    mErrorOutput->setWordWrap(true);

    auto transformGroup = new QActionGroup(this);
    transformGroup->addAction(ui->actionRotate);
    transformGroup->addAction(ui->actionTranslate);
    ui->actionTranslate->setChecked(true);
    connect(ui->actionRotate, &QAction::triggered,
           this, [this](){mFrameWidget->setTransformationType(TransformationType::rotate);});
    connect(ui->actionTranslate, &QAction::triggered,
            this, [this](){mFrameWidget->setTransformationType(TransformationType::translate);});

    connect(mFrameWidget, &FrameWidget::selectionChanged,
            this, [this](Frame::Ptr frame){
            if(!mCoupleButton->isChecked()) {return ;}
            auto [frameInLine, boxInLine] = mPresentation->findBoxForLine(mViewTextDoc->cursorPosition().line());
            if(frameInLine != frame) {
                mViewTextDoc->setCursorPosition(KTextEditor::Cursor(frame->line(), 0));
                mViewTextDoc->removeSelection();
            }});
    connect(mFrameWidget, &FrameWidget::boxSelectionChanged,
            this, [this](Box::Ptr box){
            if(!mCoupleButton->isChecked()) {return ;}
            auto [frameInLine, boxInLine] = mPresentation->findBoxForLine(mViewTextDoc->cursorPosition().line());
            if(boxInLine != box) {
                mViewTextDoc->setCursorPosition(KTextEditor::Cursor(box->line(), 0));
                mViewTextDoc->removeSelection();
            }});

    mCursorTimer.setSingleShot(true);
    connect(mViewTextDoc, &KTextEditor::View::cursorPositionChanged,
            this, [this](KTextEditor::View *, const KTextEditor::Cursor &){mCursorTimer.start(10);});
    connect(mDoc, &KTextEditor::Document::textChanged,
            this,[this](){mCursorTimer.start(10);});
    connect(&mCursorTimer, &QTimer::timeout,
            this, &MainWindow::updateCursor);

    connect(ui->actionUndo, &QAction::triggered,
            mFrameWidget, &FrameWidget::undo);
    connect(ui->actionRedo, &QAction::triggered,
            mFrameWidget, &FrameWidget::redo);

    connect(mPresentation.get(), &Presentation::rebuildNeeded,
            this, &MainWindow::fileChanged);

    connect(mSnappingButton, &QToolButton::clicked,
            this, [this](){mFrameWidget->setSnapping(mSnappingButton->isChecked());});

    mViewTextDoc->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileChanged() {
    auto iface = qobject_cast<KTextEditor::MarkInterface*>(mDoc);
    iface->clearMarks();
    Parser parser{QFileInfo(mFilename).absolutePath()};
    parser.loadInput(mDoc->text().toUtf8());
    try {
        auto const preamble = parser.readPreamble();
        auto frames = parser.readInput();
        if(!preamble.templateName.isEmpty()) {
            readTemplate(preamble.templateName);
            mPresentation->setTemplate(&mTemplate);
        }
        mPresentation->setFrames(frames);
        mErrorOutput->setText("Conversion succeeded \u2714");
    }  catch (ParserError& error) {
        mErrorOutput->setText("Line " + QString::number(error.line + 1) + ": " + error.message + " \u26A0");
        iface->addMark(error.line, KTextEditor::MarkInterface::MarkTypes::Error);
        return;
    }
    mFrameWidget->updateFrameId();
    mFrameWidget->update();
    auto const index = mFrameModel->index(mFrameWidget->pageNumber());
    ui->pagePreview->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
    ui->pagePreview->scrollTo(index);
}

void MainWindow::readTemplate(QString filename) {
    Parser templateParser{QFileInfo(filename).absolutePath()};
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
    auto const templateFrames = templateParser.readInput();
    mTemplate.setFrames(templateFrames);
}

void MainWindow::setupFileActions() {
    // HACK: Steal actions from the KPart
    QList<QAction*> actions;
    actions.append(importActionFromKDoc("file_save", [this](){save();}));
    actions.append(importActionFromKDoc("file_save_as", [this](){saveAs();}));
    ui->toolBar->insertActions(ui->actionCreatePDF, actions);
    connect(ui->actionOpen, &QAction::triggered,
            this, &MainWindow::openFile);
    connect(ui->actionNew, &QAction::triggered,
            this, &MainWindow::newDocument);
}

void MainWindow::openDocument() {
    auto url = QUrl::fromLocalFile(mFilename);
    if (!mDoc->openUrl(url)){
        qWarning() << "file not found";
    }
    mDoc->setHighlightingMode("LaTeX");
}

void MainWindow::openFile() {
    auto const newFile = QFileDialog::getOpenFileName(this,
        tr("Open File"), mFilename, tr("Input Files (*.txt)"));
    if(newFile.isEmpty()){
        return;
    }
    mFilename = newFile;
    openDocument();
    auto const configFile = getConfigFilename(mDoc->url());
    if(!QFile::exists(configFile)){
        int ret = QMessageBox::information(this, tr("Failed to open File"), tr("Failed to find %1. Genereate a new empty Configuration File").arg(configFile),
                                 QMessageBox::Ok);
        switch (ret) {
        case QMessageBox::Ok:
            resetPresentation();
            mPresentation->saveConfig(configFile);
            break;
        }
    }
    mPresentation->loadInput(configFile);
    mFrameWidget->setPresentation(mPresentation);
    fileChanged();
}

void MainWindow::newDocument() {
    mFilename = QString();
    mDoc = mEditor->createDocument(this);
    mViewTextDoc->deleteLater();
    mViewTextDoc = mDoc->createView(this);
    ui->editor->addWidget(mViewTextDoc);
    resetPresentation();
}

void MainWindow::save() {
    if(mFilename.isEmpty()){
        auto const newFile = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   QDir::homePath(),
                                   tr("Input Files (*.txt)"));
        if(newFile.isEmpty()){
            return;
        }
        mFilename = newFile;
    }
    writeToFile(mFilename);
}

void MainWindow::saveAs(){
    QFileDialog dialog;
    dialog.selectFile(mFilename);
    auto const newFile = dialog.getSaveFileName(this, tr("Save File as"),
                               mFilename,
                               tr("Input Files (*.txt)"));
    if(newFile.isEmpty()){
        return;
    }
    mFilename = newFile;
    writeToFile(mFilename);
    openDocument();
    fileChanged();
}

void MainWindow::writeToFile(QString filename) const {
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    file.write(mDoc->text().toUtf8());
    auto const configName = mFilename.section('.', 0, -2) + ".json";
    mPresentation->saveConfig(configName);
    file.close();
    ui->statusbar->showMessage(tr("Saved File to  \"%1\".").arg(mFilename), 10000);
}

void MainWindow::resetPresentation() {
    mPresentation = std::make_shared<Presentation>();
    mFrameWidget->setPresentation(mPresentation);
    mFrameModel->setPresentation(mPresentation);
    mFrameWidget->update();
    connect(mDoc, &KTextEditor::Document::textChanged,
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
                               mFilename,
                               tr("pdf (*.pdf)"));
    writePDF();
}

void MainWindow::writePDF() const {
    PDFCreator creator;
    creator.createPdf(mPdfFile, mPresentation);
    ui->statusbar->showMessage(tr("Saved PDF to \"%1\".").arg(mPdfFile), 10000);
}

QString MainWindow::getConfigFilename(QUrl inputUrl) {
    return inputUrl.toLocalFile().section('.', 0, -2) + ".json";
}

QString MainWindow::getPdfFilename() {
    return mDoc->url().toLocalFile().section('.', 0, -2) + ".pdf";
}

QAction* MainWindow::importActionFromKDoc(const char* name, std::function<void()> method){
    QAction *action = mViewTextDoc->action(name);
    if( action )
       {
            action->disconnect();
            action->setShortcutContext(Qt::WindowShortcut);
            connect(action, &QAction::triggered,
                    this, method);
       }
    return action;
}

void MainWindow::updateCursor() {
    if(!mCoupleButton->isChecked()) {
        return ;
    }
    auto [frame, box] = mPresentation->findBoxForLine(mViewTextDoc->cursorPosition().line());
    if(!frame) {
        return;
    }
    mFrameWidget->setActiveBox(box ? box->id() : QString(), frame->id());
    auto const index = mFrameModel->index(mFrameWidget->pageNumber());
    ui->pagePreview->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
    ui->pagePreview->scrollTo(index);
}
