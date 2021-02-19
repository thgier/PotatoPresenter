#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include <vector>
#include "frame.h"
#include "configboxes.h"
#include "layout.h"

using FrameList = std::vector<std::shared_ptr<Frame>>;
class Presentation : public QObject
{
    Q_OBJECT
public:
    Presentation();
    void loadInput(QString configFilename);
    FrameList frames() const;
    void setFrames(Frame::List frames);

    bool empty() const;
    int numberFrames() const;

    std::shared_ptr<Frame> frameAt(int pageNumber) const;
    void setBox(QString boxId, BoxGeometry rect, int pageNumber);
    std::shared_ptr<Box> getBox(QString id) const;
    std::shared_ptr<Frame> getFrame(QString id) const;
    void saveConfig(QString file);
    ConfigBoxes& Configuration();

    void setLayout(Layout layout);
    Layout layout() const;

Q_SIGNALS:
    void presentationChanged();
    void frameChanged(int pageNumber);
private:
    FrameList mFrames;
    QString mInputDir;
    ConfigBoxes mConfig;
    Layout mLayout;
};

#endif // PRESENTATION_H
