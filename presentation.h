#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include <vector>
#include "frame.h"
#include "parser.h"
#include "configboxes.h"

using FrameList = std::vector<std::shared_ptr<Frame>>;
class Presentation : public QObject
{
    Q_OBJECT
public:
    Presentation();
    void loadInput();
    FrameList frames();
    void updateFrames(QString doc);
    bool empty();
    int size();
    std::shared_ptr<Frame> at(int pageNumber);
    void setBox(std::shared_ptr<Box> box, QRect rect, int pageNumber);
signals:
    void presentationChanged();
    void frameChanged(int pageNumber);
private:
    FrameList mFrames;
    QString mInputDir;
    Parser mParser;
    ConfigBoxes mConfig;
};

#endif // PRESENTATION_H
