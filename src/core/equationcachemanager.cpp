/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "equationcachemanager.h"
#include <QDir>
#include <QThread>

EquationCacheManager::EquationCacheManager()
{
    auto temp = QDir("/tmp");
    temp.mkdir("praes");
    mFolder = "/tmp/praes/";
    mRemoveFiles << "a.svg" << "a.dvi" << "a.log" << "a.tex" << "a.aux" << "texput.log";
}

EquationCacheManager& cacheManager()
{
    static EquationCacheManager instance;
    return instance;
}

void EquationCacheManager::startConversionProcess(QString latexInput) {
    if(mProcessCounter > QThread::idealThreadCount()){
        mCachedImages[latexInput] = SvgEntry{SvgStatus::NotStarted, nullptr};
        return;
    }
    mCachedImages[latexInput] = SvgEntry{SvgStatus::Pending, nullptr};
    qWarning() << "process counter" << mProcessCounter;
    mProcessCounter++;

    auto standardFile = QFile(":/core/generaterLatex.tex");
    QDir(mFolder).mkpath(latexInput);
    standardFile.copy(pathAndFile(hash) + ".tex");

    QString program = "/usr/bin/latex";
    QStringList arguments;
    QString string = "\\def\\myvar{" + latexInput + "} \\input{" + pathAndFile(hash) + ".tex}";
    arguments << "-halt-on-error" << "-output-directory=" + path(hash) << "-interaction=batchmode" << string;
    QProcess *myProcess = new QProcess(this);

    auto lambda = [hash, this, myProcess](){
        startSvgGeneration(hash, myProcess);
        myProcess->deleteLater();
    };
    QObject::connect(myProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                     this, lambda);
    connect(myProcess, &QProcess::readyReadStandardOutput,
            [myProcess](){qWarning() << "got output: " << myProcess->readAllStandardOutput();});

    myProcess->start(program, arguments);
}


SvgEntry EquationCacheManager::getCachedImage(QByteArray hash) const{
    const auto it = mCachedImages.find(hash);
    if(it == mCachedImages.end()){
        return SvgEntry{SvgStatus::NotStarted, nullptr};
    }
    else{
        return it->second;
    }
}

void EquationCacheManager::startSvgGeneration(QByteArray hash, QProcess* latex){
    qWarning() << "latex exit code " << latex->exitCode();
    if(latex->exitCode() != 0){
        mCachedImages[hash].status = SvgStatus::Error;
        mProcessCounter--;
        Q_EMIT conversionFinished();
        removeFiles(hash);
        return;
    }
    QString programDvisvgm = "/usr/bin/dvisvgm";
    QStringList argumentsDvisvgm;
    argumentsDvisvgm << "-n" << "-o " + pathAndFile(hash) + ".svg" << pathAndFile(hash) + ".dvi";
    QProcess *dvisvgm = new QProcess();
    dvisvgm->start(programDvisvgm, argumentsDvisvgm);
    auto lambda = [hash, this, dvisvgm](){
        dvisvgm->deleteLater();

        writeSvgToMap(hash, removeIntegral(hash));
    };
    QObject::connect(dvisvgm, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                     this, lambda);
}

QByteArray EquationCacheManager::removeIntegral(QByteArray hash) {
    auto file = QFile(pathAndFile(hash) + ".svg");
    if(!file.open(QIODevice::ReadWrite)) {
        return {};
    }
    QByteArray fileContent = "";
    bool notIntegral = true;
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        if(notIntegral) {
            fileContent.append(line);
        }
        else if(line == QString("</g>\n").toUtf8()) {
            notIntegral = true;
        }
        if(line == QString("<g id='page1'>\n").toUtf8()) {
            notIntegral = false;
        }
    }
    file.close();
    return fileContent;
}

void EquationCacheManager::writeSvgToMap(QByteArray hash, QByteArray svg){
    mCachedImages[hash] = SvgEntry{SvgStatus::Success, std::make_shared<QSvgRenderer>(svg)};
    qWarning() << "status when finished" << mCachedImages[hash].status;
    removeFiles(hash);
    mProcessCounter--;
    Q_EMIT conversionFinished();
}

void EquationCacheManager::removeFiles(QByteArray hash) {
    for(auto &file : mRemoveFiles)  {
        QFile().remove(path(hash) + file);
    }
    QDir().rmdir(path(hash));
}

QString EquationCacheManager::pathAndFile(QByteArray hash) const {
    return mFolder + hash + "/" + "a";
}

QString EquationCacheManager::path(QByteArray hash) const {
    return mFolder + hash + "/";
}
