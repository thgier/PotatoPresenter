#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <iostream>
#include <vector>
#include "box.h"
#include "parser.h"
#include "slide.h"
#include "sliderenderer.h"

enum keywords{
    tile,
    layout,
    text
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

