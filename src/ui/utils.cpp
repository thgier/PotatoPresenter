#include "utils.h"

#include <QDir>
#include <QFile>
#include <QStandardPaths>

bool copyDirectory(QString sourceFolder, QString destFolder) {
    bool success = false;
    QDir sourceDir(sourceFolder);

    if(!sourceDir.exists())
        return false;

    QDir destDir(destFolder);
    if(!destDir.exists())
        destDir.mkdir(destFolder);

    QStringList files = sourceDir.entryList(QDir::Files);
    for(int i = 0; i< files.count(); i++) {
        QString srcName = sourceFolder + "/" + files[i];
        QString destName = destFolder + "/" + files[i];
        success = QFile::copy(srcName, destName);
        if(!success) {
            return false;
        }
    }

    files.clear();
    files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for(int i = 0; i < files.count(); i++)
    {
        QString srcName = sourceFolder + "/" + files[i];
        QString destName = destFolder + "/" + files[i];
        success = copyDirectory(srcName, destName);
        if(!success)
            return false;
    }

    return true;
}

void writeOpenRecentArrayToSettings(std::vector<QString> list, QSettings &settings) {
    settings.beginWriteArray("openRecent");
    for (int i = 0; i < list.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("entry", list.at(i));
    }
    settings.endArray();
}

std::vector<QString> readOpenRecentArrayFromSettings(QSettings &settings) {
    std::vector<QString> list;
    int size = settings.beginReadArray("openRecent");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        list.push_back(settings.value("entry").toString());
    }
    settings.endArray();
    return list;
}


