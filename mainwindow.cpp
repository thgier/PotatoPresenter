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
#include "parser.h"
#include "equationcachemanager.h"
#include "imagecachemanager.h"
#include "framelistmodel.h"
#include "framelistdelegate.h"
#include "functional"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setSizes(QList<int>{10000, 10000});
    mEditor = KTextEditor::Editor::instance();
    mFilename = "/home/theresa/Documents/praes/inputFiles/input.txt";
    mDoc = mEditor->createDocument(this);

    mPresentation = std::make_shared<Presentation>();
    mPaintDocument = ui->paintDocument;
    mPaintDocument->setPresentation(mPresentation);
    openDocument();

    auto const configFile = getConfigFilename(mDoc->url());
    if(!QFile::exists(configFile)){
        int ret = QMessageBox::information(this, tr("Failed to open File"), tr("Failed to find %1. Do you want to generate a new empty Configuration File?").arg(configFile),
                                 QMessageBox::Yes | QMessageBox::Cancel);
        switch (ret) {
        case QMessageBox::Yes:
            resetPresentation();
            fileChanged();
            mPresentation->saveConfig(configFile);
            break;
        case QMessageBox::Cancel:
            openFile();
            break;
        }
    }
    mPresentation->loadInput(configFile);

    mViewTextDoc = mDoc->createView(this);
    ui->editor->addWidget(mViewTextDoc);

    mFrameModel = new FrameListModel();
    mFrameModel->setPresentation(mPresentation);
    ui->pagePreview->setModel(mFrameModel);
    FrameListDelegate *delegate = new FrameListDelegate(this);
    ui->pagePreview->setItemDelegate(delegate);
    ui->pagePreview->setViewMode(QListView::IconMode);
    QItemSelectionModel *selectionModel = ui->pagePreview->selectionModel();

    fileChanged();
    setupFileActions();

    QObject::connect(ui->pageNumber, QOverload<int>::of(&QSpinBox::valueChanged),
                mPaintDocument, QOverload<int>::of(&PaintDocument::setCurrentPage));
    connect(mPaintDocument, &PaintDocument::pageNumberChanged,
            ui->pageNumber, &QSpinBox::setValue);
    connect(selectionModel, &QItemSelectionModel::currentChanged, this,
        [this](const QModelIndex &current){
            ui->pageNumber->setValue(current.row());
        });
    connect(ui->pageNumber, QOverload<int>::of(&QSpinBox::valueChanged), this,
        [selectionModel, this](int page) {
            auto const index = mFrameModel->index(page);
            selectionModel->select(index, QItemSelectionModel::ClearAndSelect);
            ui->pagePreview->scrollTo(index);
        });

    QObject::connect(mDoc, &KTextEditor::Document::textChanged,
                     this, &MainWindow::fileChanged);

    QObject::connect(ui->actionCreatePDF, &QAction::triggered,
                     this, &MainWindow::exportPDF);

    QObject::connect(ui->actionLayoutTitle, &QAction::triggered,
                     mPaintDocument, &PaintDocument::layoutTitle);
    QObject::connect(ui->actionLayoutBody, &QAction::triggered,
                     mPaintDocument, &PaintDocument::layoutBody);
    QObject::connect(ui->actionLayoutFullscreen, &QAction::triggered,
                     mPaintDocument, &PaintDocument::layoutFull);
    QObject::connect(ui->actionLayoutLeft, &QAction::triggered,
                     mPaintDocument, &PaintDocument::layoutLeft);
    QObject::connect(ui->actionLayoutRight, &QAction::triggered,
                     mPaintDocument, &PaintDocument::layoutRight);

    QToolButton *moreButton = new QToolButton(this);
    moreButton->setIcon(QIcon::fromTheme("view-more-horizontal-symbolic"));
    moreButton->setText("More");
    moreButton->setPopupMode(QToolButton::InstantPopup);
    QMenu *moreMenu = new QMenu(moreButton);
    moreMenu->addAction(ui->actionPresentationTitle);
    moreMenu->addAction(ui->actionSubtitle);
    moreButton->setMenu(moreMenu);
    ui->toolBar->insertWidget(ui->actionTranslate, moreButton);
    ui->toolBar->insertSeparator(ui->actionTranslate);

    QObject::connect(ui->actionPresentationTitle, &QAction::triggered,
                     mPaintDocument, &PaintDocument::layoutPresTitle);
    QObject::connect(ui->actionSubtitle, &QAction::triggered,
                     mPaintDocument, &PaintDocument::layoutSubtitle);

    QObject::connect(&cacheManager(), &EquationCacheManager::conversionFinished,
            mPaintDocument, QOverload<>::of(&PaintDocument::update));
    connect(&cacheManagerImages(), &ImageCacheManager::imageChanged,
            this, [this](){MainWindow::fileChanged();});
    ui->error->setWordWrap(true);

    auto transformGroup = new QActionGroup(this);
    transformGroup->addAction(ui->actionRotate);
    transformGroup->addAction(ui->actionTranslate);
    ui->actionTranslate->setChecked(true);
    connect(ui->actionRotate, &QAction::triggered,
           this, [this](){mPaintDocument->setTransformationType(TransformationType::rotate);});
    connect(ui->actionTranslate, &QAction::triggered,
            this, [this](){mPaintDocument->setTransformationType(TransformationType::translate);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileChanged() {
    auto iface = qobject_cast<KTextEditor::MarkInterface*>(mDoc);
    iface->clearMarks();
    try {
        mPresentation->updateFrames(mDoc->text().toUtf8());
        ui->error->setText("Conversion succeeded \u2714");
    }  catch (ParserError& error) {
        ui->error->setText("Line " + QString::number(error.line + 1) + ": " + error.message + " \u26A0");
        iface->addMark(error.line, KTextEditor::MarkInterface::MarkTypes::Error);
        return;
    }
    ui->pageNumber->setMaximum(mPresentation->frames().size()-1);
}

void MainWindow::setupFileActions(){
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

void MainWindow::openDocument(){
    auto url = QUrl::fromLocalFile(mFilename);
    if (!mDoc->openUrl(url)){
        qWarning() << "file not found";
    }
    mDoc->setHighlightingMode("LaTeX");
}

void MainWindow::openFile(){
    auto const newFile = QFileDialog::getOpenFileName(this,
        tr("Open File"), mFilename, tr("Input Files (*.txt)"));
    if(newFile.isEmpty()){
        return;
    }
    auto const oldFile = mFilename;
    mFilename = newFile;
    openDocument();
    auto const configFile = getConfigFilename(mDoc->url());
    if(!QFile::exists(configFile)){
        int ret = QMessageBox::information(this, tr("Failed to open File"), tr("Failed to find %1. Do you want to generate a new empty Configuration File?").arg(configFile),
                                 QMessageBox::Yes | QMessageBox::Cancel);
        switch (ret) {
        case QMessageBox::Yes:
            resetPresentation();
            fileChanged();
            mPresentation->saveConfig(configFile);
            break;
        case QMessageBox::Cancel:
            mFilename = oldFile;
            openFile();
            break;
        }
    }
    mPresentation->loadInput(configFile);
    mPaintDocument->setPresentation(mPresentation);
    fileChanged();
}

void MainWindow::newDocument(){
    mFilename = QString();
    mDoc = mEditor->createDocument(this);
    mViewTextDoc->deleteLater();
    mViewTextDoc = mDoc->createView(this);
    ui->editor->addWidget(mViewTextDoc);
    resetPresentation();
}

void MainWindow::save(){
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
    mPdfFile = getPdfFilename();
}

void MainWindow::writeToFile(QString filename) const{
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    file.write(mDoc->text().toUtf8());
    auto const configName = mFilename.section('.', 0, -2) + ".json";
    mPresentation->saveConfig(configName);
    file.close();
}

void MainWindow::resetPresentation(){
    mPresentation = std::make_shared<Presentation>();
    mPaintDocument->setPresentation(mPresentation);
    mFrameModel->setPresentation(mPresentation);
    mPaintDocument->update();
    connect(mDoc, &KTextEditor::Document::textChanged,
                     this, &MainWindow::fileChanged);
    setupFileActions();
}

void MainWindow::exportPDF(){
    QFileDialog dialog;
    if(mPdfFile.isEmpty()){
        mPdfFile = getPdfFilename();
    }
    dialog.selectFile(mPdfFile);
    mPdfFile = dialog.getSaveFileName(this, tr("Export PDF"),
                               mFilename,
                               tr("pdf (*.pdf)"));
    mPaintDocument->createPDF(mPdfFile);

}

QString MainWindow::getConfigFilename(QUrl inputUrl){
    return inputUrl.toLocalFile().section('.', 0, -2) + ".json";
}

QString MainWindow::getPdfFilename(){
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

