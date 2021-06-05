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
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <QListWidget>
#include <QTimer>
#include <QLabel>
#include <QToolButton>
#include <KXmlGuiWindow>
#include "slide.h"
#include "slidewidget.h"
#include "configboxes.h"
#include "slidelistmodel.h"
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
    void readTemplate(QString filename);

    // functions connected to actions
    void save();
    void saveAs();
    void openFile();
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

    void updateCursorPosition();

private:
    Ui::MainWindow *ui;
    KTextEditor::Editor* mEditor;
    KTextEditor::Document* mDoc;
    KTextEditor::View* mViewTextDoc = nullptr;

    SlideWidget* mSlideWidget;
    std::shared_ptr<Presentation> mPresentation;

    QListWidget *mListWidget;
    SlideListModel *mSlideModel;

    QString mPdfFile;
    QString mPdfFileHandout;

    Template mTemplate;

    QTimer mCursorTimer;

    QLabel* mErrorOutput;
    QToolButton* mCoupleButton;
    QToolButton* mSnappingButton;
};
#endif // MAINWINDOW_H
