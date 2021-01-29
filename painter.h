#ifndef PAINTER_H
#define PAINTER_H
#include "frame.h"
#include "box.h"

#include<QPainter>

class Painter
{
public:
    Painter();
    Painter(QPainter& painter);
    void paintFrame(std::shared_ptr<Frame> frame);
    QPainter& getPainter();
    void loadVariables(std::map<QString, QString> variables);
private:
    QPainter& mPainter;
    std::map<QString, QString> mVariables;
    int mPageNumber = 0;

    void setVariable(QString name, QString value);
};

#endif // PAINTER_H
