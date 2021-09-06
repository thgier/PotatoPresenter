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
#include <QStandardPaths>
#include <QDir>

#include <functional>

#include "parser.h"
#include "equationcachemanager.h"
#include "cachemanager.h"
#include "slidelistmodel.h"
#include "slidelistdelegate.h"
#include "templatelistdelegate.h"
#include "pdfcreator.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/potato_icon.png"));
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
    mCoupleButton->setIcon(QIcon(":/icons/link.svg"));
    mCoupleButton->setToolTip("Couple the Cursor in the Editor and the selection in Slide view");

    mSnappingButton = new QToolButton(this);
    mSnappingButton->setCheckable(true);
    mSnappingButton->setChecked(true);
    mSnappingButton->setIcon(QIcon(":/icons/snap-nodes-cusp.svg"));
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


    connect(mSnappingButton, &QToolButton::clicked,
            this, [this](){mSlideWidget->setSnapping(mSnappingButton->isChecked());});
    ui->mainWidget->setCurrentIndex(1);

    connect(ui->actionOpen, &QAction::triggered,
            this, &MainWindow::openFile);
    connect(ui->actionNew, &QAction::triggered,
            this, [this]{ui->mainWidget->setCurrentIndex(3);});

    connect(ui->pushButtonOpen, &QPushButton::pressed,
            ui->actionOpen, &QAction::trigger);
    connect(ui->pushButtonNew, &QPushButton::pressed,
            ui->actionNew, &QAction::trigger);

    connect(ui->actionNew_From_Template, &QAction::triggered,
            this, [this](){ui->actionNew->trigger();
                           ui->mainWidget->setCurrentIndex(1);});

    // setup Item model template
    auto const dirList = std::vector<QString>{"/home/theresa/Documents/praes/templates/blue_line_template",
                                                "/home/theresa/Documents/praes/templates/blue_brown_template"};
    auto const presentationList = generateTemplatePresentationList(dirList);
    mTemplateModel = new TemplateListModel(this);
    mTemplateModel->setPresentationList(presentationList);
    ui->templateList->setModel(mTemplateModel);
    TemplateListDelegate *delegateTemplate = new TemplateListDelegate(this);
    ui->templateList->setItemDelegate(delegateTemplate);
    connect(ui->templateList, &QListView::doubleClicked,
            this, [this](){ui->mainWidget->setCurrentIndex(2);});

//    setup create project from dialog
    ui->label_folder->setText(guessSavingDirectory());
    connect(ui->back_button, &QPushButton::clicked,
            this, [this]{ui->mainWidget->setCurrentIndex(1);});
    connect(ui->create_project_button, &QPushButton::clicked,
            this, [this, dirList]{createProjectFromTemplate(dirList[ui->templateList->currentIndex().row()]);});
    connect(ui->change_directory_button, &QPushButton::clicked,
            this, [this]{ui->label_folder->setText(openDirectory());});

//    setup create new project
    ui->label_folder->setText(guessSavingDirectory());
    connect(ui->back_button_new, &QPushButton::clicked,
            this, [this]{ui->mainWidget->setCurrentIndex(1);});
    connect(ui->create_new_project_button, &QPushButton::clicked,
            this, &MainWindow::createEmptyProject);
    connect(ui->change_directory_button, &QPushButton::clicked,
            this, [this]{ui->label_folder->setText(openDirectory());});

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
            mPresentation->setTemplate(readTemplate(preamble.templateName));
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

std::shared_ptr<Template> MainWindow::readTemplate(QString filename) const {
    auto thisTemplate = std::make_shared<Template>();
    Parser templateParser{QFileInfo(filename).absolutePath()};
    templateParser.setParseTemplate(true);
    try {
        thisTemplate->readTemplateConfig(filename + ".json");
    }  catch (ConfigError& error) {
        throw ParserError{error.errorMessage, 0};
    }

    auto file = QFile(filename + ".txt");
    if(!file.open(QIODevice::ReadOnly)){
        throw ParserError{"Can't open file" + file.fileName(), 0};
    }
    templateParser.loadInput(file.readAll());
    auto const templateSlides = templateParser.readInput();
    thisTemplate->setSlides(templateSlides);
    return thisTemplate;
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
        tr("Open File"), filename());
    if(newFile.isEmpty()){
        return;
    }
    openProject(newFile);
}

void MainWindow::openProject(QString path) {
    ui->mainWidget->setCurrentIndex(0);
    newDocument();
    openInputFile(path);
    openJson();
    mPdfFile = "";
    fileChanged();
    setWindowTitle(windowTitle());
    mIsModified = false;
}

void MainWindow::newDocument() {
    ui->mainWidget->setCurrentIndex(0);
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

Presentation::Ptr MainWindow::generateTemplatePresentation(QString directory) const {
    QFile file(directory + "/demo.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        return {};
    }
    auto const val = file.readAll();
    Parser parser{directory};
    parser.loadInput(val);
    auto presentation = std::make_shared<Presentation>();
    try {
        auto const preamble = parser.readPreamble();
        auto slides = parser.readInput();
        if(!preamble.templateName.isEmpty()) {
            presentation->setTemplate(readTemplate(preamble.templateName));
        }
        presentation->setSlides(slides);
        mErrorOutput->setText("Conversion succeeded \u2714");
    }  catch (ParserError& error) {
        return {};
    }
    return presentation;
}

Presentation::List MainWindow::generateTemplatePresentationList(std::vector<QString> directories) const {
    Presentation::List list;
    for(auto const& directory : directories) {
        auto const presentation = generateTemplatePresentation(directory);
        if (!presentation) {
            continue;
        }
        list.push_back(presentation);
    }
    return list;
}

void MainWindow::insertTextInEditor(QString path) {
    QFile file(path + "/demo.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    auto const val = file.readAll();
    mDoc->setText(val);
}


QString MainWindow::openDirectory() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 ui->label_folder->text(),
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(dir.isEmpty()){
       return ui->label_folder->text();
    }
    return dir;
}

void MainWindow::createProjectFromTemplate(QString pathToSelectedTemplate) {
    auto const projectname = ui->project_name_lineEdit->text();
    if(projectname.isEmpty()) {
        ui->create_project_error_label->setText(tr("Please insert a project name."));
        return;
    }

//    copy template and demo into project folder and rename it
    if(!copyDirectory(pathToSelectedTemplate, assembleProjectDirectory(projectname))) {
        QMessageBox::information(this, tr("Copy of template failed."), tr("Copy of template faield. Source directory: %1. Destination Directory: %2").arg(pathToSelectedTemplate, assembleProjectDirectory(projectname)),
                                 QMessageBox::Ok);
        return;
    }
    auto const projectName = ui->project_name_lineEdit->text();
    auto inputFile = QFile(assembleProjectDirectory(projectname) + "/demo.txt");
    auto jsonFile = QFile(assembleProjectDirectory(projectname) + "/demo.json");
    qInfo() << inputFile.fileName() << inputFile.exists() << projectName;
    if(!(inputFile.rename(assembleProjectPathInputFile(projectname)) && jsonFile.rename(assembleProjectPathJsonFile(projectname)))) {
        QMessageBox::information(this, tr("Rename failed."), tr("Rename failed."),
                                 QMessageBox::Ok);
        return;
    }
    openProject(assembleProjectPathInputFile(projectname));
}

void MainWindow::createEmptyProject() {
    auto const projectname = ui->new_project_name_lineEdit->text();
    QDir destDir(assembleProjectDirectory(projectname));
    if(destDir.exists()) {
        QMessageBox::information(this, tr("Folder already exists."),
                                 tr("Folder %1 already exists. Please select another project name.").arg(assembleProjectDirectory(projectname)),
                                 QMessageBox::Ok);
        return;
    }
    destDir.mkdir(assembleProjectDirectory(projectname));
    if(!QFile(assembleProjectPathInputFile(projectname)).open(QIODevice::NewOnly)) {
        QMessageBox::information(this, tr("File already exists."),
                                 tr("File %1 already exists. Please select another project name.").arg(assembleProjectPathInputFile(projectname)),
                                 QMessageBox::Ok);
        return;
    }
    if(!QFile(assembleProjectPathJsonFile(projectname)).open(QIODevice::NewOnly)) {
        QMessageBox::information(this, tr("File already exists."),
                                 tr("File %1 already exists. Please select another project name.").arg(assembleProjectPathJsonFile(projectname)),
                                 QMessageBox::Ok);
        return;
    }
    openProject(assembleProjectPathInputFile(projectname));
}

QString MainWindow::assembleProjectPathInputFile(QString projectname) const {
    return assembleProjectDirectory(projectname) + "/" + projectname + ".txt";
}

QString MainWindow::assembleProjectPathJsonFile(QString projectname) const {
    return assembleProjectDirectory(projectname) + "/" + projectname + ".json";
}

QString MainWindow::assembleProjectDirectory(QString projectname) const {
    return ui->label_folder->text() + "/" + projectname;
}

QString MainWindow::guessSavingDirectory() const {
    if(!ui->project_name_lineEdit->text().isEmpty()) {
        return ui->label_folder->text();
    }
    return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
}
