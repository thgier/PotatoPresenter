#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include <vector>
#include "frame.h"
#include "configboxes.h"
#include "layout.h"

class Presentation : public QObject
{
    Q_OBJECT
public:
    Presentation();
    void loadInput(QString configFilename);

//    Access contained Frames
    Frame::List frames() const;
    void setFrames(Frame::List const& frames);
    Frame::Ptr frameAt(int pageNumber) const;
    Frame::Ptr findFrame(QString const& id) const;
    int numberFrames() const;
    bool empty() const;

    Box::Ptr findBox(QString const& id) const;

//    Change Geometry of Box only through the presentation in order to
//    save it in the Configuration
    void setBoxGeometry(QString const& boxId, BoxGeometry const& rect, int pageNumber);

//    Configuration Class to follow and save the Geometry of the boxes
    void saveConfig(QString const& file);
    ConfigBoxes& configuration();

//    Layout class has the information about the positions of the predefined boxes
//    avaible throught the tool bar e.g. the position of the title and the body
    void setLayout(Layout layout);
    Layout layout() const;

Q_SIGNALS:
    void presentationChanged();
    void frameChanged(int pageNumber);

private:
    Frame::List mFrames;
    QString mInputDir;
    ConfigBoxes mConfig;
    Layout mLayout;
};

#endif // PRESENTATION_H
