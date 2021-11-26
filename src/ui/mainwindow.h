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
#include "templatecache.h"

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
    std::shared_ptr<Template> readTemplate(QString templateName) const;

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
    QString jsonFileName(QString textPath) const;
    void saveJson();
    void openJson();
    QString filename() const;
    QString filenameWithoutSuffix() const;
    QString completeBaseName() const;
    QString applicationName() const;
    QString windowTitle() const;
    QString windowTitleNotSaved() const;
    bool closeDocument();
    void closeEvent(QCloseEvent *event) override;

    void autosave();
    void askToRecoverAutosave(QString path);
    void recoverAutosave(QString path);
    void deleteAutosave(QString path);
    QString autosaveTextFile() const;
    QString autosaveTextFile(QString inputFile) const;
    QString autosaveJsonFile() const;
    QString autosaveJsonFile(QString jsonFile) const;

    void updateCursorPosition();

//    start window
    Presentation::Ptr generateTemplatePresentation(QString directory) const;
    Presentation::List generateTemplatePresentationList(std::vector<QString> directories) const;
    void insertTextInEditor(QString path);

//    open save project dialog
    void openCreatePresentationDialog();
    void createProjectFromTemplate();

//    path management
    QString assembleProjectDirectory(QString projectname) const;
    QString assembleProjectPathInputFile(QString projectname) const;
    QString assembleProjectPathJsonFile(QString projectname) const;
    void addDirectoryToSettings(QString directory) const;
    QString guessSavingDirectory() const;
    QString openDirectory();

//    open Recent
    void addFileToOpenRecent(QString path);
    void updateOpenRecent();

    // enable / disable action, when project is opened / not opened
    void setActionenEnabled(bool enabled);

    void resetCacheManager();

private:
    Ui::MainWindow *ui;
    KTextEditor::Editor* mEditor;
    KTextEditor::Document* mDoc;
    KTextEditor::View* mViewTextDoc = nullptr;

    SlideWidget* mSlideWidget;
    Presentation::Ptr mPresentation;
    QString mTemplatePath;
    TemplateCache mTemplateCache;

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
    QDateTime mLastAutosave;
};
#endif // MAINWINDOW_H
