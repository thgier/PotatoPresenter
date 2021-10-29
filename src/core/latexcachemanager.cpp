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

LatexCacheManager& cacheManager()
{
    static LatexCacheManager instance;
    return instance;
}

void LatexCacheManager::startConversionProcess(QString latexInput) {
    if(mProcessCounter > QThread::idealThreadCount()){
        mCachedImages[latexInput] = SvgEntry{SvgStatus::NotStarted, nullptr};
        return;
    }
    mCachedImages[latexInput] = SvgEntry{SvgStatus::Pending, nullptr};
    qWarning() << "process counter" << mProcessCounter;
    mProcessCounter++;

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
    QProcess *myProcess = new QProcess(this);

    connect(myProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                     this, [latexInput, dir=std::move(tempDir), myProcess, this]() mutable {
        startSvgGeneration(latexInput, myProcess, std::move(dir));
    });

    myProcess->start(program, arguments);

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

void LatexCacheManager::startSvgGeneration(QString latexInput, QProcess* latex, std::unique_ptr<QTemporaryDir> tempDir){
    qWarning() << "latex exit code " << latex->errorString();
    if(latex->exitCode() != 0){
        auto exitCode = latex->exitCode();
        auto error = latex->readAllStandardError();
        auto out = latex->readAllStandardOutput();
        qWarning() << "latex error " << error << exitCode << out;
        mCachedImages[latexInput].status = SvgStatus::Error;
        mProcessCounter--;
        Q_EMIT conversionFinished();
        return;
    }
    QString programDvisvgm = "/usr/bin/dvisvgm";
    QStringList argumentsDvisvgm;
    argumentsDvisvgm << "--pdf" << "-o " + tempDir->path() + "/input.svg" << tempDir->path() + "/input.pdf";
    QProcess *dvisvgm = new QProcess();
    dvisvgm->start(programDvisvgm, argumentsDvisvgm);
    QObject::connect(dvisvgm, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                     this, [this, dir=std::move(tempDir), latexInput](){
                    writeSvgToMap(latexInput, dir);});
}

void LatexCacheManager::writeSvgToMap(QString input, std::unique_ptr<QTemporaryDir> const& tempDir){
    auto file = QFile(tempDir->path() + "/input.svg");
    if(!file.open(QIODevice::ReadOnly)) {
        return;
    }
    mCachedImages[input] = SvgEntry{SvgStatus::Success, std::make_shared<QSvgRenderer>(file.readAll())};
    qWarning() << "status when finished" << mCachedImages[input].status;
    mProcessCounter--;
    Q_EMIT conversionFinished();
}
