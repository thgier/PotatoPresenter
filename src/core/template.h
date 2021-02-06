#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QPainter>
#include <frame.h>
#include <presentation.h>
#include <layout.h>

struct TemplateError{
    QString message;
};

class Template
{
public:
    using variablesMap = std::shared_ptr<std::map<QString, QString>>;
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
    std::shared_ptr<Layout> getLayout() const;
private:
    Presentation mPresentation;
    std::map<QString, QString> mVariables;
    std::map<QString, Frame> mTemplateSlides;
    std::shared_ptr<Layout> mLayout;
};

#endif // TEMPLATE_H
