    #include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <KTextEditor/Editor>
#include <KTextEditor/View>
#include <KParts/ReadOnlyPart>
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
    , mConfiguration("/home/theresa/Documents/praes/inputConfig.json")
{
    ui->setupUi(this);
    ui->splitter->setSizes(QList<int>{10000, 10000});
    KTextEditor::Editor *editor = KTextEditor::Editor::instance();
    auto url = QUrl::fromLocalFile("/home/theresa/Documents/praes/input.json");
    KTextEditor::Document *doc = editor->createDocument(this);
    if (!doc->openUrl(url)){
        qWarning() << "file not found";
    }
    KTextEditor::View *view = doc->createView(this);
    ui->editor->addWidget(view);

    mConfiguration.loadConfigurationFile();
    mPaintDocument = ui->paintDocument;

    mFrameModel = new FrameListModel();
    ui->pagePreview->setModel(mFrameModel);
    FrameListDelegate *delegate = new FrameListDelegate(this);
    ui->pagePreview->setItemDelegate(delegate);
    ui->pagePreview->setViewMode(QListView::IconMode);

    fileChanged(doc);
    connect(ui->actionsave, &QAction::triggered,
            doc, &KTextEditor::Document::documentSave);
    QObject::connect(ui->pageNumber, QOverload<int>::of(&QSpinBox::valueChanged),
                mPaintDocument, &PaintDocument::setCurrentPage);

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

    QObject::connect(&cacheManager(), &EquationCacheManager::conversionFinished,
            mPaintDocument, QOverload<>::of(&PaintDocument::update));
    ui->error->setReadOnly(true);
    QObject::connect(&cacheManager(), &EquationCacheManager::errorWhileLatexConversion,
                     ui->error, &QLineEdit::setText);
    QObject::connect(&cacheManager(), &EquationCacheManager::conversionFinished,
                     this, [this](){ui->error->setText("");});
    connect(&cacheManagerImages(), &ImageCacheManager::imageChanged,
            this, [this, doc](){MainWindow::fileChanged(doc);});

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileChanged(KTextEditor::Document *doc) {
    Parser parser;
    auto frames = parser.readJson(doc->text(), &mConfiguration);
    if(!frames){
        return;
    }

    mPaintDocument->setFrames(*frames, ui->pageNumber->value());
    ui->pageNumber->setMaximum(frames->size()-1);
    for(auto frame : *frames){
        for(auto box : frame->getBoxes()){
            auto boxptr = box.get();
            auto lambda = [boxptr, this](){mConfiguration.addRect(boxptr->Rect(), boxptr->id());};
            QObject::connect(boxptr, &Box::rectChanged,
                             this, lambda);
        }
    }
    mFrameModel->setFrames(frames.value());

    mPaintDocument->update();
}
