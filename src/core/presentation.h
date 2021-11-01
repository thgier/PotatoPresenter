/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include <QVariant>
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

    Slide::Ptr findDefiningSlide(QString const& definition) const {
        for(auto const &slide: vector) {
            if(slide->definesClass() == definition) {
                return slide;
            }
        }
        return {};
    };

    Slide::Ptr lastSlide() const {
        if(vector.empty()) {
            return {};
        }
        return vector.back();
    }

    int numberSlides() const {
        return int(vector.size());
    };

    bool empty() const {
        return vector.empty();
    }
};

struct PresentationData {
    SlideList mSlideList;
    std::shared_ptr<Template> mTemplate = nullptr;
};

class Presentation : public QObject
{
    Q_OBJECT
public:
    using Ptr = std::shared_ptr<Presentation>;
    using List = std::vector<Presentation::Ptr>;

    Presentation();

    // set data
    void setData(PresentationData data);

    // Access contained Slides
    SlideList const& slideList() const;

    // access to contained box
    Box::Ptr findBox(QString const& id) const;
    std::pair<Slide::Ptr, Box::Ptr> findBoxForLine(int line) const;

    // getter
    bool empty() const;
    QSize dimensions() const;
    int numberOfSlides() const;
    QString title() const;

    // Change Geometry of Box only through the presentation in order to
    // save it in the Configuration
    void setBoxGeometry(QString const& boxId, const BoxGeometry &rect, int pageNumber);
    void deleteBoxGeometry(QString const& boxId, int pageNumber);
    void deleteBoxAngle(QString const& boxId, int pageNumber);

    // Configuration Class to follow and save the Geometry of the boxes
    void setConfig(ConfigBoxes config);
    ConfigBoxes const& configuration() const;

    // creating and applying of a map of the boxes that defines
    // a class e.g. has the argument defineclass
    const std::map<QString, BoxStyle> createMapDefinesClass() const;
    void applyDefinedClass(SlideList const& slides);

    // applys first the values that are given by the variables
    // e.g. \setvar font Hack
    // then apply standard values for the geometry
    void applyStandardTemplate(SlideList &slides) const;

    // deletes the configuration entries from boxes that do not exist
    // in the presentation at the moment
    void deleteNotNeededConfigurations();

Q_SIGNALS:
    // emited if the position of a box on a slide is changed
    void slideChanged(int pageNumberFront, int pageNumberBack);
    void rebuildNeeded();

private:
    // apply Configuration in json file to mSlides
    void applyConfiguration();

    // call to apply all configuration, template etc. to mSlides
    void applyConfigurationTemplate();

private:
    SlideList mSlides;
    ConfigBoxes mConfig;
    std::shared_ptr<Template> mTemplate = nullptr;

    QSize mDimensions{1600, 900};
};

Q_DECLARE_METATYPE(Presentation::Ptr)

#endif // PRESENTATION_H
