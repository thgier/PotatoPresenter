# pragma once

#include <QPainter>
#include "frame.h"
#include "configboxes.h"
#include "presentation.h"

struct TemplateError{
    QString message;
};

class Template
{
public:
    using variablesMap = std::shared_ptr<std::map<QString, QString>>;
    Template();
    void setFrames(FrameList frames);
    void readTemplateConfig(QString configFile);
    void applyTemplate(FrameList& frameList);
    BoxGeometry getGeometry(QString id) const;
    BoxStyle getStyle(QString id) const;
    void declareVariable(QString name, QString value);
    void drawTemplate(QString frameId);
    Box::List getTemplateSlide(QString frameId) const;
    void setVariables(std::map<QString, QString> variables);
    ConfigBoxes& Configuration();

private:
    void applyTemplateToBox(Box::Ptr box) const;

private:
    Presentation mPresentation;
    std::map<QString, QString> mVariables;
    std::map<QString, Frame> mTemplateSlides;
};
