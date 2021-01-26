#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QPainter>
#include <frame.h>
#include <presentation.h>

enum TemplateStyle{
    defaultPage,
    titlePage,
    content,
    plain
};

class Template
{
public:
    Template();
    void readTemplateConfig(QString configFile);
    BoxGeometry getGeometry(QString id) const;
    BoxStyle getStyle(QString id) const;
    void declareVariable(QString name, QString value);
    void drawTemplate(QString frameId);
    Box::List getTemplateSlide(QString frameId) const;
    void setVariables(std::map<QString, QString> variables);
    ConfigBoxes& Configuration();
    void setFrames(Frame::List frames);
private:
    Presentation mPresentation;
    std::map<QString, QString> mVariables;
    std::map<QString, Frame> mTemplateSlides;
};

#endif // TEMPLATE_H
