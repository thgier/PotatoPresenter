#pragma once

#include <QString>
#include <vector>
#include <QSettings>

bool copyDirectory(QString sourceFolder, QString destFolder);
QString guessSavingDirectory();

void writeOpenRecentArrayToSettings(std::vector<QString> list, QSettings& settings);
std::vector<QString> readOpenRecentArrayFromSettings(QSettings& settings);
