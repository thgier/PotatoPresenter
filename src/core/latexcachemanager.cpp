/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "latexcachemanager.h"
#include <QDir>
#include <QThread>

void assertNoNull(std::vector<Job> const& jobs) {
    auto const hasNull = std::any_of(jobs.begin(), jobs.end(), [](auto const& p) { return !p.mProcess; });
    if (hasNull)
        throw;
}

LatexCacheManager::LatexCacheManager()
{
}

LatexCacheManager::~LatexCacheManager()
{
    assertNoNull(mRunningLatexJobs);
    assertNoNull(mRunningDviJobs);
#if 0
    for(auto const& job: mRunningLatexJobs) {
        qDebug() << "process is" << job.mProcess.get();
        if(job.mProcess->state() != QProcess::NotRunning) {
            job.mProcess->disconnect(this);
            job.mProcess->terminate();
            job.mProcess->waitForFinished();
        }
    }
    for(auto const& job: mRunningDviJobs) {
        if(job.mProcess->state() != QProcess::NotRunning) {
            job.mProcess->disconnect(this);
            job.mProcess->terminate();
            job.mProcess->waitForFinished();
        }
    }
#endif
}

LatexCacheManager& cacheManager()
{
    static LatexCacheManager instance;
    return instance;
}

void LatexCacheManager::startConversionProcess(QString latexInput) {
    if(mRunningLatexJobs.size() + mRunningDviJobs.size() > QThread::idealThreadCount()){
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

    QString program = "/usr/bin/pdflatex";
    QStringList arguments;
    arguments << "-halt-on-error" << "-interaction=nonstopmode" << "-output-directory=" + tempDir->path() << inputFile.fileName();

    auto& job = mRunningLatexJobs.emplace_back();
    job.mProcess.reset(new QProcess());
    job.mTempDir = std::move(tempDir);
    job.mInput = latexInput;

    connect(job.mProcess.get(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &LatexCacheManager::startSvgGeneration);

    job.mProcess->start(program, arguments);
    assertNoNull(mRunningLatexJobs);
    assertNoNull(mRunningDviJobs);
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
    assertNoNull(mRunningLatexJobs);
    assertNoNull(mRunningDviJobs);
    auto ret = std::move(*latexJob);
    jobs.erase(latexJob);
    assertNoNull(mRunningLatexJobs);
    assertNoNull(mRunningDviJobs);
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

    auto& job = mRunningDviJobs.emplace_back();
    job.mProcess.reset(new QProcess);
    job.mTempDir = std::move(latexJob->mTempDir);
    job.mInput = latexJob->mInput;

    QString programDvisvgm = "/usr/bin/dvisvgm";
    QStringList argumentsDvisvgm;

    argumentsDvisvgm << "--pdf" << "-o " + job.mTempDir->path() + "/input.svg" << job.mTempDir->path() + "/input.pdf";

    QObject::connect(job.mProcess.get(), QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                     this, &LatexCacheManager::writeSvgToMap);
    job.mProcess->start(programDvisvgm, argumentsDvisvgm);
    assertNoNull(mRunningLatexJobs);
    assertNoNull(mRunningDviJobs);
}

void LatexCacheManager::writeSvgToMap(){
    assertNoNull(mRunningLatexJobs);
    assertNoNull(mRunningDviJobs);
    // find finished Latex job
    auto dviJob = takeOneFinishedJob(mRunningDviJobs);
    if(!dviJob) {
        return;
    }
    assertNoNull(mRunningLatexJobs);
    assertNoNull(mRunningDviJobs);
    if (!dviJob->mTempDir)
        throw;

    auto file = QFile(dviJob->mTempDir->path() + "/input.svg");
    if(!file.open(QIODevice::ReadOnly)) {
        return;
    }
    mCachedImages[dviJob->mInput] = SvgEntry{SvgStatus::Success, std::make_shared<QSvgRenderer>(file.readAll())};
    qWarning() << "status when finished" << mCachedImages[dviJob->mInput].status;
    Q_EMIT conversionFinished();
    assertNoNull(mRunningLatexJobs);
    assertNoNull(mRunningDviJobs);
}
