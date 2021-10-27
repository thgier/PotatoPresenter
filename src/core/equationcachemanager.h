/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef EQUATIONCACHEMANAGER_H
#define EQUATIONCACHEMANAGER_H
#include <QSvgRenderer>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QTemporaryDir>

#include <memory>

enum SvgStatus{
    Success,
    Error,
    Pending,
    NotStarted,
};

struct SvgEntry{
    SvgStatus status;
    std::shared_ptr<QSvgRenderer> svg;
};

class EquationCacheManager : public QObject
{
    Q_OBJECT
public:
    EquationCacheManager();    
    void startConversionProcess(QString latexInput);
    SvgEntry getCachedImage(QByteArray hash) const;
    void startSvgGeneration(QString latexInput, QProcess* latex, std::unique_ptr<QTemporaryDir> tempDir);
    void writeSvgToMap(QString input, const std::unique_ptr<QTemporaryDir> &tempDir);

Q_SIGNALS:
    void conversionFinished();

private:
    std::unordered_map<QString, SvgEntry> mCachedImages;
    int mProcessCounter = 0;
};

EquationCacheManager& cacheManager();

#endif
