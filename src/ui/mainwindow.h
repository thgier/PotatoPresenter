#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <QListWidget>
#include <KXmlGuiWindow>
#include "frame.h"
#include "paintdocument.h"
#include "configboxes.h"
#include "layout.h"
#include "framelistmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private Q_SLOTS:

private:
    void fileChanged();
    void setupFileActions();
    void openFile();
    void openDocument();
    void newDocument();
    void save();
    void saveAs();
    void loadTemplate();
    void writeToFile(QString filename) const;
    void resetPresentation();
    void exportPDF();
    void exportPDFAs();
    QString getConfigFilename(QUrl inputUrl);
    QString getPdfFilename();
    QAction* importActionFromKDoc(const char* name, std::function<void()> method);

    Ui::MainWindow *ui;
    KTextEditor::Editor* mEditor;
    KTextEditor::Document* mDoc;
    KTextEditor::View* mViewTextDoc = nullptr;

    PaintDocument* mPaintDocument;
    std::shared_ptr<Presentation> mPresentation;

    QListWidget *mListWidget;
    FrameListModel *mFrameModel;

    QString mFilename;
    QString mPdfFile;
};
#endif // MAINWINDOW_H
