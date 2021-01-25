#include "template.h"
#include <QFile>
#include <configboxes.h>

Template::Template()
{

}

void Template::readTemplateFile(QString directory){
    ConfigBoxes JsonConfig;
    JsonConfig.loadConfigurationFile(directory + "/" + "template.json");
    mPresentation.loadInput(directory + "/" + "template.json");
    auto file = QFile(directory + "/" + "template.txt");
    if (!file.open(QIODevice::ReadOnly)){
        return;
    }
    mPresentation.updateFrames(file.readAll());
}

BoxGeometry Template::getGeometry(QString id) const{
    return mPresentation.getBox(id)->geometry();
}

BoxStyle Template::getStyle(QString id) const{
    return mPresentation.getBox(id)->style();
}

void Template::declareVariable(QString name, QString value){
    mVariables[name] = value;
}

Box::List Template::getTemplateSlide(QString frameId) const{
//    return mPresentation.getFrame(frameId);

}


