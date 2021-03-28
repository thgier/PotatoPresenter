/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include <vector>
#include "slide.h"
#include "configboxes.h"

class Template;

struct SlideList {
    std::vector<Slide::Ptr> vector;

    void appendSlide(Slide::Ptr slide) {
        vector.push_back(slide);
    }

    Slide::Ptr slideAt(int pageNumber) const {
        if(vector.empty() || pageNumber >= int(vector.size())) {
            return {};
        }
        return vector[pageNumber];
    };

    Box::Ptr findBox(QString const& id) {
        for(auto const& slide: vector) {
            if(slide->findBox(id)) {
                return slide->findBox(id);
            }
        }
        return {};
    };

    Slide::Ptr findSlide(QString const& id) const {
        for(auto const &slide: vector) {
            if(id == slide->id()) {
                return slide;
            }
        }
        return {};
    };

    int numberSlides() const {
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

    // Access contained Slides
    SlideList slideList() const;
    void setTemplate(Template *templateObject);
    void setSlides(SlideList const& slides);

    // access to contained box
    Box::Ptr findBox(QString const& id) const;
    std::pair<Slide::Ptr, Box::Ptr> findBoxForLine(int line) const;

    bool empty() const;
    QSize dimensions() const;

    void applyStandardTemplateToBox(Box::Ptr box) const;

    // Change Geometry of Box only through the presentation in order to
    // save it in the Configuration
    void setBoxGeometry(QString const& boxId, const BoxGeometry &rect, int pageNumber);
    void deleteBoxGeometry(QString const& boxId, int pageNumber);

    // Configuration Class to follow and save the Geometry of the boxes
    void saveConfig(QString const& file);
    ConfigBoxes& configuration();
    void setConfig(ConfigBoxes config);

    void deleteNotNeededConfigurations();

Q_SIGNALS:
    void presentationChanged();
    void slideChanged(int pageNumber);
    void rebuildNeeded();

private:
    // apply Configuration in json file to mSlides
    void applyConfiguration();
    SlideList const& applyStandardTemplate(SlideList const& slides) const;

private:
    SlideList mSlides;
    QString mInputDir;
    ConfigBoxes mConfig;
    QSize mDimensions{1600, 900};
    Template *mTemplate = nullptr;
};

#endif // PRESENTATION_H
