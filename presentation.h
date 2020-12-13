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
    void updateFrames(QByteArray doc);
    bool empty();
    int size();
    std::shared_ptr<Frame> at(int pageNumber);
    void setBox(QString boxId, QRect rect, int pageNumber);
    std::shared_ptr<Box> getBox(QString id);
    Parser* const parser();
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
