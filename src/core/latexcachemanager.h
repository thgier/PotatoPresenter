/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once

#include <QSvgRenderer>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QTemporaryDir>

#include <memory>
#include <optional>

enum SvgStatus{
    Success,
    Error,
    Pending,
    NotStarted,
};

enum ConversionType {
    NoBreak,
    BreakUntillFinished
};

struct SvgEntry{
    SvgStatus status;
    std::shared_ptr<QSvgRenderer> svg;
};

struct DelayedDelete {
    void operator()(QProcess* p) { p->deleteLater(); }
};

struct Job {
    std::unique_ptr<QProcess, DelayedDelete> mProcess;
    std::unique_ptr<QTemporaryDir> mTempDir;
    QString mInput;
    ConversionType mConversionType = NoBreak;
};

class LatexCacheManager : public QObject
{
    Q_OBJECT
public:
    LatexCacheManager();
    ~LatexCacheManager();
    void startConversionProcess(QString latexInput, ConversionType conversionType = NoBreak);
    SvgEntry getCachedImage(QString latexInput) const;
    void startSvgGeneration();
    void writeSvgToMap();
    void resetCache();

Q_SIGNALS:
    void conversionFinished();

private:
    std::optional<Job> takeOneFinishedJob(std::vector<Job>& jobs);

private:
    std::unordered_map<QString, SvgEntry> mCachedImages;
    std::vector<Job> mRunningLatexJobs;
    std::vector<Job> mRunningDviJobs;
};

LatexCacheManager& cacheManager();

