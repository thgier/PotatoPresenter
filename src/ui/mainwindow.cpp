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
#include <QSettings>

#include <functional>
#include <algorithm>

#include "equationcachemanager.h"
#include "cachemanager.h"
#include "slidelistmodel.h"
#include "slidelistdelegate.h"
#include "templatelistdelegate.h"
#include "pdfcreator.h"
#include "utils.h"
#include "potatoformatvisitor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/potato_icon.png"));
    ui->splitter->setSizes(QList<int>{10000, 10000});


//    setup Editor
    mEditor = KTextEditor::Editor::instance();
    mDoc = mEditor->createDocument(this);
    mViewTextDoc = mDoc->createView(this);
    ui->editor->addWidget(mViewTextDoc);


//    setup Presentation, Slide Widget
    mPresentation = std::make_shared<Presentation>();
    mSlideWidget = ui->slideWidget;
    mSlideWidget->setPresentation(mPresentation);


//    setup Item model
    mSlideModel = new SlideListModel(this);
    mSlideModel->setPresentation(mPresentation);
    ui->pagePreview->setModel(mSlideModel);
    SlideListDelegate *delegate = new SlideListDelegate(this);
    ui->pagePreview->setItemDelegate(delegate);
    ui->pagePreview->setViewMode(QListView::IconMode);
    QItemSelectionModel *selectionModel = ui->pagePreview->selectionModel();
    connect(selectionModel, &QItemSelectionModel::currentChanged,
            this, [this](const QModelIndex &current){mSlideWidget->setCurrentPage(current.row());});


//    setup Action
    connect(ui->actionNew, &QAction::triggered,
            this, [this](){
                if(!closeDocument()) return;
                ui->mainWidget->setCurrentIndex(1);});
    connect(ui->actionOpen, &QAction::triggered,
            this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered,
            this, &MainWindow::save);
    connect(ui->actionSave_as, &QAction::triggered,
            this, &MainWindow::saveAs);
    connect(ui->actionCreatePDF, &QAction::triggered,
                     this, &MainWindow::exportPDF);
    connect(ui->actionExport_PDF_as, &QAction::triggered,
            this, &MainWindow::exportPDFAs);
    connect(ui->actionExport_PDF_Handout, &QAction::triggered,
            this, &MainWindow::exportPDFHandout);
    connect(ui->actionExport_PDF_Handout_as, &QAction::triggered,
            this, &MainWindow::exportPDFHandoutAs);

    connect(ui->actionUndo, &QAction::triggered,
            mSlideWidget, &SlideWidget::undo);
    connect(ui->actionRedo, &QAction::triggered,
            mSlideWidget, &SlideWidget::redo);
    connect(ui->actionReset_Position, &QAction::triggered,
            this, [this]() {
                mSlideWidget->deleteBoxPosition();
                fileChanged();
            });

    auto transformGroup = new QActionGroup(this);
    transformGroup->addAction(ui->actionRotate);
    transformGroup->addAction(ui->actionTranslate);
    ui->actionTranslate->setChecked(true);
    connect(ui->actionRotate, &QAction::triggered,
           this, [this](){mSlideWidget->setTransformationType(TransformationType::rotate);});
    connect(ui->actionTranslate, &QAction::triggered,
            this, [this](){mSlideWidget->setTransformationType(TransformationType::translate);});

    connect(ui->actionClean_Configurations, &QAction::triggered,
            mPresentation.get(), &Presentation::deleteNotNeededConfigurations);

//    open Recent
    QSettings settings("Potato", "Potato Presenter");
    updateOpenRecent();
    connect(ui->openRecent_listWidget, &QListWidget::itemClicked,
            this, [this](QListWidgetItem *item){openProject(item->data(Qt::ToolTipRole).toString());});

//    setup CacheManager
    connect(&cacheManager(), &EquationCacheManager::conversionFinished,
            this, &MainWindow::fileChanged);

    CacheManager<QImage>::instance().setCallback([this](QString){mSlideWidget->update();});
    CacheManager<QSvgRenderer>::instance().setCallback([this](QString){mSlideWidget->update();});


//    setup bar with error messages, snapping and couple button
    mErrorOutput = new QLabel(this);
    mErrorOutput->setWordWrap(true);

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

    barTop->addWidget(mCoupleButton);
    barTop->addWidget(mSnappingButton);
    barTop->addWidget(mErrorOutput);

    connect(mSnappingButton, &QToolButton::clicked,
            this, [this](){mSlideWidget->setSnapping(mSnappingButton->isChecked());});


//    coupling between document and slide widget selection
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


//    setup left column of the new from template dialog
    connect(ui->toolButtonOpen, &QPushButton::clicked,
            ui->actionOpen, &QAction::trigger);


//    setup Item model templates in create new from template dialog
    auto const dirList = std::vector<QString>{"/home/theresa/Documents/praes/templates/blue_line_template",
                                                "/home/theresa/Documents/praes/templates/blue_brown_template"};
    auto const presentationList = generateTemplatePresentationList(dirList);
    mTemplateModel = new TemplateListModel(this);
    mTemplateModel->setPresentationList(presentationList);
    ui->templateList->setModel(mTemplateModel);
    TemplateListDelegate *delegateTemplate = new TemplateListDelegate(this);
    ui->templateList->setItemDelegate(delegateTemplate);
    connect(ui->templateList, &QListView::clicked,
            this, [this, dirList]{
                mTemplatePath = dirList[ui->templateList->currentIndex().row()];
                openCreatePresentationDialog();
            });
    connect(ui->emptPresentationButton, &QPushButton::clicked,
            this, [this]{
                mTemplatePath = "/home/theresa/Documents/praes/templates/empty";
                openCreatePresentationDialog();
            });


//    setup create project from template dialog
    connect(ui->back_button, &QPushButton::clicked,
            this, [this]{ui->mainWidget->setCurrentIndex(1);});
    connect(ui->create_project_button, &QPushButton::clicked,
            this, [this, dirList]{createProjectFromTemplate();});
    connect(ui->change_directory_button, &QPushButton::clicked,
            this, [this]{ui->label_folder->setText(openDirectory());});
    connect(ui->project_name_lineEdit, &QLineEdit::returnPressed,
            ui->create_project_button, &QPushButton::click);


//    setup document
    connect(mDoc, &KTextEditor::Document::textChanged,
                     this, &MainWindow::fileChanged);
    newDocument();

//    open create new from template dialog
    ui->mainWidget->setCurrentIndex(1);
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
    auto const text = mDoc->text().toUtf8().toStdString();
    auto const parserOutput = generateSlides(text, file);
    if(parserOutput.successfull()) {
        auto const slides = parserOutput.slideList();
        auto const preamble = parserOutput.preamble();
        auto templateName = preamble.templateName;
        Template::Ptr presentationTemplate = nullptr;
        if(!templateName.isEmpty()) {
            if (!templateName.startsWith("/home")) {
                templateName = file + "/" + templateName;
            }
            presentationTemplate = readTemplate(templateName);
            if (!presentationTemplate) {
                return;
            }
        }
        mPresentation->setData({slides, presentationTemplate});
        mErrorOutput->setText("Conversion succeeded \u2714");
    }
    else {
        auto const error = parserOutput.parserError();
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

std::shared_ptr<Template> MainWindow::readTemplate(QString templateName) const {
    if(templateName.isEmpty()) {
        return {};
    }
    auto file = QFile(templateName + ".txt");
    if(!file.open(QIODevice::ReadOnly)){
        mErrorOutput->setText(tr("Cannot load template %1.").arg(file.fileName()));
        return {};
    }
    auto thisTemplate = std::make_shared<Template>();
    try {
        thisTemplate->setConfig(templateName + ".json");
    }  catch (ConfigError error) {
        mErrorOutput->setText(tr("Cannot load template %1.").arg(error.filename));
        return {};
    }
    auto const directoryPath = QFileInfo(templateName).absolutePath();
    auto const parserOutput = generateSlides(file.readAll().toStdString(), directoryPath, true);

    if(parserOutput.successfull()) {
        auto const slides = parserOutput.slideList();
        thisTemplate->setSlides(slides);
        return thisTemplate;
    }
    else {
        auto const error = parserOutput.parserError();
        mErrorOutput->setText("Cannot load template \u26A0");
        return {};
    }
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
    if(!QFile(path).exists()) {
        QMessageBox::information(this, tr("File does not exist"), tr("File does not exist"),
                                         QMessageBox::Ok);
        return;
    }
    ui->mainWidget->setCurrentIndex(0);
    newDocument();
    openInputFile(path);
    openJson();
    mPdfFile = "";
    fileChanged();
    setWindowTitle(windowTitle());
    mIsModified = false;
    addFileToOpenRecent(path);
    updateOpenRecent();
    addDirectoryToSettings(QFileInfo(filename()).path());
}

void MainWindow::newDocument() {
    ui->mainWidget->setCurrentIndex(0);
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
    mPresentation->configuration().saveConfig(jsonFileName());
}

void MainWindow::openJson() {
    if(!QFile::exists(jsonFileName())){
        int ret = QMessageBox::information(this, tr("Failed to open File"), tr("Failed to find %1. Genereate a new empty Configuration File").arg(jsonFileName()),
                                 QMessageBox::Ok);
        switch (ret) {
        case QMessageBox::Ok:
            resetPresentation();
            mPresentation->setConfig({jsonFileName()});
            break;
        }
    }
    mPresentation->setConfig({jsonFileName()});
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

    auto presentation = std::make_shared<Presentation>();
    presentation->setConfig({directory + "/demo.json"});

    auto const parserOutput = generateSlides(val.toStdString(), directory);
    if(parserOutput.successfull()) {
        auto const slides = parserOutput.slideList();
        auto const preamble = parserOutput.preamble();
        auto templateName = preamble.templateName;
        if (!templateName.startsWith("/home")) {
            templateName = directory + "/" + templateName;
        }
        auto const presentationTemplate = readTemplate(templateName);
        presentation->setData({slides, presentationTemplate});
        return presentation;
    }
    else {
        return{};
    }
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
                                                 guessSavingDirectory(),
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(dir.isEmpty()){
       return guessSavingDirectory();
    }
    addDirectoryToSettings(dir);
    return dir;
}

void MainWindow::createProjectFromTemplate() {
    auto const projectname = ui->project_name_lineEdit->text();
    if(projectname.isEmpty()) {
        QMessageBox::information(this, tr("Please insert Project name."), tr("Please insert Project name."),
                                 QMessageBox::Ok);
        return;
    }

//    copy template and demo into project folder and rename it
    if(!copyDirectory(mTemplatePath, assembleProjectDirectory(projectname))) {
        QMessageBox::information(this, tr("Copy of template failed."), tr("Copy of template faield. Source directory: %1. Destination Directory: %2").arg(mTemplatePath, assembleProjectDirectory(projectname)),
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
    QCoreApplication::setOrganizationName("Potato");
    QCoreApplication::setApplicationName("Potato Presenter");
    QSettings settings;
    auto const dir = settings.value("directory").toString();
    if(dir.isEmpty()) {
        return QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    }
    return dir;
}

void MainWindow::addFileToOpenRecent(QString path) {
    auto const maxEntries = 8;
    QCoreApplication::setOrganizationName("Potato");
    QCoreApplication::setApplicationName("Potato Presenter");
    QSettings settings;
    auto list = readOpenRecentArrayFromSettings(settings);
    auto const rm = std::ranges::remove(list, path);
    list.erase(rm.begin(), rm.end());
    list.insert(list.begin(), path);
    if (list.size() > maxEntries) {
        list.pop_back();
    }
    writeOpenRecentArrayToSettings(list, settings);
}

void MainWindow::updateOpenRecent() {
    QCoreApplication::setOrganizationName("Potato");
    QCoreApplication::setApplicationName("Potato Presenter");
    QSettings settings;
    auto const openRecentList = readOpenRecentArrayFromSettings(settings);
    ui->menuOpen_Recent->clear();
    ui->openRecent_listWidget->clear();
    for (auto const& entry : openRecentList) {
//        add to toolbar
        QAction *openAct = new QAction(entry, this);
        connect(openAct, &QAction::triggered,
                this, [this, entry]{openProject(entry);});
        ui->menuOpen_Recent->addAction(openAct);

//        add to new from template dialog
        auto const filename = QFileInfo(entry).baseName();
        qInfo() << "open recent filename" << filename;
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(filename);
        newItem->setData(Qt::ToolTipRole, entry);
        ui->openRecent_listWidget->addItem(newItem);
    }
}

void MainWindow::addDirectoryToSettings(QString directory) const {
    QCoreApplication::setOrganizationName("Potato");
    QCoreApplication::setApplicationName("Potato Presenter");
    QSettings settings;
    auto dir = QDir(directory);
    dir.cdUp();
    settings.setValue("directory", dir.path());
}

void MainWindow::openCreatePresentationDialog() {
    ui->mainWidget->setCurrentIndex(2);
    if(ui->label_folder->text().isEmpty()) {
        ui->label_folder->setText(guessSavingDirectory());
    }
    ui->project_name_lineEdit->clear();
    ui->project_name_lineEdit->setFocus();
}
