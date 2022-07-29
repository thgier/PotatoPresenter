/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "latexcachemanager.h"
#include <QDir>
#include <QThread>

LatexCacheManager::LatexCacheManager()
{
}

LatexCacheManager::~LatexCacheManager()
{
    for(auto const& job: mRunningLatexJobs) {
        qDebug() << "process is" << job.mProcess.get();
        if(job.mProcess->state() != QProcess::NotRunning) {
            job.mProcess->disconnect(this);
            job.mProcess->terminate();
            job.mProcess->waitForFinished();
        }
    }
    for(auto const& job: mRunningPdfToSvgJobs) {
        if(job.mProcess->state() != QProcess::NotRunning) {
            job.mProcess->disconnect(this);
            job.mProcess->terminate();
            job.mProcess->waitForFinished();
        }
    }
}

LatexCacheManager& cacheManager()
{
    static LatexCacheManager instance;
    return instance;
}

void LatexCacheManager::startConversionProcess(QString latexInput, ConversionType conversionType) {
    if(mRunningLatexJobs.size() + mRunningPdfToSvgJobs.size() > QThread::idealThreadCount()){
        mCachedImages[latexInput] = SvgEntry{SvgStatus::NotStarted, nullptr};
        return;
    }
    mCachedImages[latexInput] = SvgEntry{SvgStatus::Pending, nullptr};

    auto tempDir = std::make_unique<QTemporaryDir>();
    if (!tempDir->isValid()) {
        return;
    }
    auto inputFile = QFile(tempDir->path() + "/input.tex");
    if(!inputFile.open(QIODevice::WriteOnly)) {
        return;
    }
    inputFile.write(latexInput.toUtf8());
    inputFile.close();

    QString program = "/usr/bin/pdflatex";
    QStringList arguments;
    arguments << "-halt-on-error" << "-interaction=nonstopmode" << "-output-directory=" + tempDir->path() << inputFile.fileName();

    auto& job = mRunningLatexJobs.emplace_back();
    job.mProcess.reset(new QProcess());
    job.mTempDir = std::move(tempDir);
    job.mInput = latexInput;
    job.mConversionType = conversionType;

    connect(job.mProcess.get(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &LatexCacheManager::startSvgGeneration);

    job.mProcess->start(program, arguments);

    if(conversionType == BreakUntillFinished) {
        job.mProcess->waitForFinished(-1);
    }
}


SvgEntry LatexCacheManager::getCachedImage(QString latexInput) const{
    const auto it = mCachedImages.find(latexInput);
    if(it == mCachedImages.end()){
        return SvgEntry{SvgStatus::NotStarted, nullptr};
    }
    else{
        return it->second;
    }
}

std::optional<Job> LatexCacheManager::takeOneFinishedJob(std::vector<Job>& jobs) {
    auto const latexJob = std::find_if(jobs.begin(), jobs.end(),
                                  [](auto const& job){return job.mProcess->state() == QProcess::NotRunning;});
    if(latexJob == jobs.end()) {
        return std::nullopt;
    }
    auto ret = std::move(*latexJob);
    jobs.erase(latexJob);
    return ret;
}

void LatexCacheManager::startSvgGeneration(){
    // find finished Latex job
    auto latexJob = takeOneFinishedJob(mRunningLatexJobs);
    if(!latexJob) {
        return;
    }

    // latex process failed
    qWarning() << "latex exit code " << latexJob->mProcess->errorString();
    if(latexJob->mProcess->exitCode() != 0){
        auto exitCode = latexJob->mProcess->exitCode();
        auto error = latexJob->mProcess->readAllStandardError();
        auto out = latexJob->mProcess->readAllStandardOutput();
        qWarning() << "latex error " << error << exitCode << out;
        mCachedImages[latexJob->mInput].status = SvgStatus::Error;
        Q_EMIT conversionFinished();
        return;
    }

    auto& job = mRunningPdfToSvgJobs.emplace_back();
    job.mProcess.reset(new QProcess);
    job.mTempDir = std::move(latexJob->mTempDir);
    job.mInput = latexJob->mInput;
    job.mConversionType = latexJob->mConversionType;

    QString programDvisvgm = "/usr/bin/pdftocairo";
    QStringList argumentsDvisvgm;

    argumentsDvisvgm << "-svg" << job.mTempDir->path() + "/input.pdf" << job.mTempDir->path() + "/input.svg" ;

    QObject::connect(job.mProcess.get(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                     this, &LatexCacheManager::writeSvgToMap);
    job.mProcess->start(programDvisvgm, argumentsDvisvgm);

    if(job.mConversionType == BreakUntillFinished) {
        job.mProcess->waitForFinished(-1);
    }
}

void LatexCacheManager::writeSvgToMap(){
    // find finished Latex job
    auto dviJob = takeOneFinishedJob(mRunningPdfToSvgJobs);
    if(!dviJob) {
        return;
    }
    if (!dviJob->mTempDir)
        throw;

    auto file = QFile(dviJob->mTempDir->path() + "/input.svg");
    if(!file.open(QIODevice::ReadOnly)) {
        return;
    }
    mCachedImages[dviJob->mInput] = SvgEntry{SvgStatus::Success, std::make_shared<QSvgRenderer>(file.readAll())};
    qWarning() << "status when finished" << mCachedImages[dviJob->mInput].status;
    Q_EMIT conversionFinished();
}

void LatexCacheManager::resetCache() {
    mCachedImages.clear();
}
