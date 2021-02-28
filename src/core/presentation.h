#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include <vector>
#include "frame.h"
#include "configboxes.h"
#include "layout.h"

struct FrameList {
    std::vector<Frame::Ptr> vector;

    void appendFrame(Frame::Ptr frame) {
        vector.push_back(frame);
    }

    Frame::Ptr frameAt(int pageNumber) const {
        return vector[pageNumber];
    };

    Box::Ptr findBox(QString const& id) {
        for(auto const& frame: vector) {
            if(frame->findBox(id)) {
                return frame->findBox(id);
            }
        }
        return {};
    };

    Frame::Ptr findFrame(QString const& id) const {
        for(auto const &frame: vector) {
            if(id == frame->id()) {
                return frame;
            }
        }
        return {};
    };

    int numberFrames() const {
        return int(vector.size());
    };

    bool empty() const {
        return vector.empty();
    }
};

class Presentation : public QObject
{
    Q_OBJECT
public:
    Presentation();
    void loadInput(QString configFilename);

    // Access contained Frames
    FrameList frameList() const;
    void setFrames(FrameList const& frames);

    bool empty() const;
    QSize dimensions() const;

    Box::Ptr findBox(QString const& id) const;

    // Change Geometry of Box only through the presentation in order to
    // save it in the Configuration
    void setBoxGeometry(QString const& boxId, BoxGeometry const& rect, int pageNumber);
    void deleteBoxGeometry(QString const& boxId, int pageNumber);

    // Configuration Class to follow and save the Geometry of the boxes
    void saveConfig(QString const& file);
    ConfigBoxes& configuration();

Q_SIGNALS:
    void presentationChanged();
    void frameChanged(int pageNumber);

private:
    // apply Configuration in json file to mFrames
    void applyConfiguration();

private:
    FrameList mFrames;
    QString mInputDir;
    ConfigBoxes mConfig;
    QSize mDimensions{1600, 900};
};

#endif // PRESENTATION_H
