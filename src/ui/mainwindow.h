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
#include "framewidget.h"
#include "configboxes.h"
#include "layout.h"
#include "framelistmodel.h"
#include "template.h"

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
    void openDocument();
    void newDocument();
    void resetPresentation();

    // functions connected to actions
    void save();
    void saveAs();
    void openFile();
    void exportPDF();
    void exportPDFAs();

    void writeToFile(QString filename) const;
    void writePDF() const;
    QString getConfigFilename(QUrl inputUrl);
    QString getPdfFilename();
    QAction* importActionFromKDoc(const char* name, std::function<void()> method);

private:
    Ui::MainWindow *ui;
    KTextEditor::Editor* mEditor;
    KTextEditor::Document* mDoc;
    KTextEditor::View* mViewTextDoc = nullptr;

    FrameWidget* mFrameWidget;
    std::shared_ptr<Presentation> mPresentation;

    QListWidget *mListWidget;
    FrameListModel *mFrameModel;

    QString mFilename;
    QString mPdfFile;
};
#endif // MAINWINDOW_H
