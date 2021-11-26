/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once

#include <QString>
#include <vector>
#include <QSettings>

bool copyDirectory(QString sourceFolder, QString destFolder);
QString guessSavingDirectory();

void writeOpenRecentArrayToSettings(std::vector<QString> list, QSettings& settings);
std::vector<QString> readOpenRecentArrayFromSettings(QSettings& settings);
