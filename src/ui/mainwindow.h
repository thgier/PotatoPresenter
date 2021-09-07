/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QListWidget>
#include <QTimer>
#include <QLabel>
#include <QToolButton>
#include <QSettings>

#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KXmlGuiWindow>

#include "slide.h"
#include "slidewidget.h"
#include "configboxes.h"
#include "slidelistmodel.h"
#include "templatelistmodel.h"
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
    void setupFileActionsFromKPart();
    void openInputFile(QString filename);
    void newDocument();
    void resetPresentation();
    std::shared_ptr<Template> readTemplate(QString filename) const;

    // functions connected to actions
    bool save();
    bool saveAs();
    void openFile();
    void openProject(QString path);
    void exportPDF();
    void exportPDFAs();
    void exportPDFHandout();
    void exportPDFHandoutAs();

    void writePDF() const;
    void writePDFHandout() const;
    QString getConfigFilename(QUrl inputUrl);
    QString getPdfFilename();
    QString getPdfFilenameHandout();
    QAction* deleteShortcutOfKDocAction(const char* name);
    QString jsonFileName() const;
    void saveJson();
    void openJson();
    QString filename() const;
    QString completeBaseName() const;
    QString applicationName() const;
    QString windowTitle() const;
    QString windowTitleNotSaved() const;
    bool closeDocument();
    void closeEvent(QCloseEvent *event) override;

    void updateCursorPosition();

//    start window
    Presentation::Ptr generateTemplatePresentation(QString directory) const;
    Presentation::List generateTemplatePresentationList(std::vector<QString> directories) const;
    void insertTextInEditor(QString path);

//    open save project dialog
    void createProjectFromTemplate(QString pathToSelectedTemplate);
    void createEmptyProject();
    QString assembleProjectDirectory(QString projectname) const;
    QString assembleProjectPathInputFile(QString projectname) const;
    QString assembleProjectPathJsonFile(QString projectname) const;
    QString openDirectory();
    QString guessSavingDirectory() const;

    void addFileToOpenRecent(QString path);
    void updateOpenRecent();

private:
    Ui::MainWindow *ui;
    KTextEditor::Editor* mEditor;
    KTextEditor::Document* mDoc;
    KTextEditor::View* mViewTextDoc = nullptr;

    SlideWidget* mSlideWidget;
    Presentation::Ptr mPresentation;

    QListWidget *mListWidget;
    SlideListModel *mSlideModel;

    TemplateListModel *mTemplateModel;

    QString mPdfFile;
    QString mPdfFileHandout;

    QTimer mCursorTimer;

    QLabel* mErrorOutput;
    QToolButton* mCoupleButton;
    QToolButton* mSnappingButton;

    bool mIsModified = false;
};
#endif // MAINWINDOW_H
