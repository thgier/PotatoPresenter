#include "painter.h"
#include <QDate>

Painter::Painter(QPainter& painter)
    : mPainter(painter)
{
}

void Painter::paintFrame(std::shared_ptr<Frame> frame){
    mVariables["%{pagenumber}"] = QString::number(frame->PageNumber());
    auto templateBoxes = frame->getTemplateBoxes();
    for(auto const& box: templateBoxes){
        box->drawContent(mPainter, mVariables);
    }
    auto boxes = frame->getBoxes();
    for(auto const& box: boxes){
        box->drawContent(mPainter, mVariables);
    }
}

QPainter& Painter::getPainter(){
    return mPainter;
}

void Painter::loadVariables(std::map<QString, QString> variables){
    mVariables = variables;
    setVariable("%{date}", QDate::currentDate().toString());
}

void Painter::setVariable(QString name, QString value){
    if(mVariables.find(name) == mVariables.end()){
        mVariables[name] = value;
    }
}
