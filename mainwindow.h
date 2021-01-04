#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <QListWidget>
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
    void fileChanged();
    void openFile();
    void openDocument();
    void newDocument();
    void save();
    void saveAs();
    void writeToFile(QString filename) const;
    void resetPresentation();
    QString getConfigFilename(QUrl inputUrl);

private slots:

private:
    Ui::MainWindow *ui;
    KTextEditor::Document* mDoc;
    KTextEditor::Editor* mEditor;
    PaintDocument* mPaintDocument;
    QWidget* mViewTextDoc = nullptr;
    QListWidget *mListWidget;
    FrameListModel *mFrameModel;
    std::shared_ptr<Presentation> mPresentation;
    QString mFilename;
};
#endif // MAINWINDOW_H
