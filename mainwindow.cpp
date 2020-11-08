    #include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <KTextEditor/Editor>
#include <KTextEditor/View>
#include <KParts/ReadOnlyPart>

#include<QObject>
#include "parser.h"

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

    Parser parser;
    std::vector<std::shared_ptr<Frame>> frames = parser.readJson(doc->text(), &mConfiguration);

    mPaintDocument = new PaintDocument();
    mPaintDocument->setFrames(frames);
    ui->paint->addWidget(mPaintDocument);
    QObject::connect(ui->pageNumber, QOverload<int>::of(&QSpinBox::valueChanged),
                mPaintDocument, &PaintDocument::setCurrentPage);

    QObject::connect(doc, &KTextEditor::Document::textChanged,
                     this, &MainWindow::fileChanged);

    QObject::connect(ui->createPDF, &QPushButton::pressed,
                     mPaintDocument, &PaintDocument::createPDF);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileChanged(KTextEditor::Document *doc) {
    Parser parser;
    std::vector<std::shared_ptr<Frame>> frames = parser.readJson(doc->text(), &mConfiguration);

    mPaintDocument->setFrames(frames);
    mPaintDocument->update();
}
