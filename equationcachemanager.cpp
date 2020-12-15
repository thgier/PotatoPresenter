#include "equationcachemanager.h"
#include <QDir>

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

void EquationCacheManager::startConversionProcess(QString mathExpression, QByteArray hash) {
    if(mProcessCounter > 5){
        mCachedImages[hash] = SvgEntry{SvgStatus::notStarted, nullptr};
        return;
    }
    mCachedImages[hash] = SvgEntry{SvgStatus::pending, nullptr};
    qWarning() << "process counter" << mProcessCounter;
    mProcessCounter++;

    auto standardFile = QFile("/home/theresa/Documents/praes/generaterLatex.tex");
    QDir(mFolder).mkpath(hash);
    QString folder = mFolder + hash + "/";
    qWarning() << "copy" << hash << standardFile.copy(folder+"a.tex");

    QString program = "/usr/bin/latex";
    QStringList arguments;
    QString string = QString("\\def\\myvar{") + mathExpression + QString("} \\input{" + folder + "a.tex}");
    arguments << "-halt-on-error" << "-output-directory=" + folder << "-interaction=batchmode" << string;
    QProcess *myProcess = new QProcess();

    auto lambda = [hash, this, myProcess](){return startSvgGeneration(hash, myProcess);};
    QObject::connect(myProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                     this, lambda);
    connect(myProcess, &QProcess::readyReadStandardOutput,
            [myProcess](){qWarning() << "got output: " << myProcess->readAllStandardOutput();});

    myProcess->start(program, arguments);
}


SvgEntry EquationCacheManager::getCachedImage(QByteArray hash) const{
    const auto it = mCachedImages.find(hash);
    if(it == mCachedImages.end()){
        return SvgEntry{SvgStatus::notStarted, nullptr};
    }
    else{
        return it->second;
    }
}

void EquationCacheManager::startSvgGeneration(QByteArray hash, QProcess* latex){
    QString folder = mFolder + hash + "/";
    qWarning() << "latex exit code " << latex->exitCode();
    if(latex->exitCode() != 0){
        mCachedImages[hash].status = SvgStatus::error;
        mProcessCounter--;
        emit conversionFinished();
        removeFiles(hash);
        return;
    }
    QString programDvisvgm = "/usr/bin/dvisvgm";
    QStringList argumentsDvisvgm;
    argumentsDvisvgm << "-n" << "-o " + folder + "a.svg" << folder + "a.dvi";
    QProcess *dvisvgm = new QProcess();
    dvisvgm->start(programDvisvgm, argumentsDvisvgm);
    auto lambda = [hash, this](){return writeSvgToMap(hash);};
    QObject::connect(dvisvgm, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                     this, lambda);
}

void EquationCacheManager::writeSvgToMap(QByteArray hash){
    QString folder = mFolder + hash + "/";
    mCachedImages[hash] = SvgEntry{SvgStatus::success, std::make_shared<QSvgRenderer>(folder + "a.svg")};
    qWarning() << "status when finished" << mCachedImages[hash].status;
    removeFiles(hash);
    mProcessCounter--;
    emit conversionFinished();
}

void EquationCacheManager::removeFiles(QByteArray hash) {
    QString folder = mFolder + hash + "/";
    qWarning() << folder;
    for(auto file : mRemoveFiles)  {
        QFile().remove(folder + file);
    }
    QDir().rmdir(folder);
}
