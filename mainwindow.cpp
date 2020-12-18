    #include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <KTextEditor/Editor>
#include <KTextEditor/View>
#include <KParts/ReadOnlyPart>
#include <KTextEditor/MarkInterface>
#include <QProcess>
#include <QDebug>
#include <QObject>
#include <QTableWidget>
#include "parser.h"
#include "equationcachemanager.h"
#include "imagecachemanager.h"
#include "framelistmodel.h"
#include "framelistdelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setSizes(QList<int>{10000, 10000});
    KTextEditor::Editor *editor = KTextEditor::Editor::instance();
    QString inputFile = "/home/theresa/Documents/praes/input";
    auto url = QUrl::fromLocalFile(inputFile);
    KTextEditor::Document *doc = editor->createDocument(this);
    if (!doc->openUrl(url)){
        qWarning() << "file not found";
    }
    doc->setHighlightingMode("LaTeX");
    KTextEditor::View *view = doc->createView(this);
    ui->editor->addWidget(view);

    mPresentation.loadInput();
    mPaintDocument = ui->paintDocument;
    mPaintDocument->setPresentation(&mPresentation);

    mFrameModel = new FrameListModel();
    mFrameModel->setPresentation(&mPresentation);
    ui->pagePreview->setModel(mFrameModel);
    FrameListDelegate *delegate = new FrameListDelegate(this);
    ui->pagePreview->setItemDelegate(delegate);
    ui->pagePreview->setViewMode(QListView::IconMode);
    QItemSelectionModel *selectionModel = ui->pagePreview->selectionModel();

    fileChanged(doc);
    connect(ui->actionsave, &QAction::triggered,
            doc, &KTextEditor::Document::documentSave);
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

    QObject::connect(doc, &KTextEditor::Document::textChanged,
                     this, &MainWindow::fileChanged);

    QObject::connect(ui->actionCreatePDF, &QAction::triggered,
                     mPaintDocument, &PaintDocument::createPDF);

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
    QObject::connect(ui->actionPresentationTitle, &QAction::triggered,
                     mPaintDocument, &PaintDocument::layoutPresTitle);
    QObject::connect(ui->actionSubtitle, &QAction::triggered,
                     mPaintDocument, &PaintDocument::layoutSubtitle);

    QObject::connect(&cacheManager(), &EquationCacheManager::conversionFinished,
            mPaintDocument, QOverload<>::of(&PaintDocument::update));
    connect(&cacheManagerImages(), &ImageCacheManager::imageChanged,
            this, [this, doc](){MainWindow::fileChanged(doc);});
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

void MainWindow::fileChanged(KTextEditor::Document *doc) {
    auto iface = qobject_cast<KTextEditor::MarkInterface*>(doc);
    iface->clearMarks();
    try {
        mPresentation.updateFrames(doc->text().toUtf8());
        ui->error->setText("Conversion succeeded \u2714");
    }  catch (ParserError& error) {
        ui->error->setText("Line " + QString::number(error.line + 1) + ": " + error.message + " \u26A0");
        iface->addMark(error.line, KTextEditor::MarkInterface::MarkTypes::Error);
        return;
    }
    ui->pageNumber->setMaximum(mPresentation.frames().size()-1);
    mPaintDocument->updateFrames();
}
