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

class Presentation : public QObject
{
    Q_OBJECT
public:
    using Ptr = std::shared_ptr<Presentation>;
    using List = std::vector<Presentation::Ptr>;

    Presentation();
    void loadInput(QString configFilename);

    // Access contained Slides
    SlideList slideList() const;
    void setTemplate(std::shared_ptr<Template> templateObject);
    void setSlides(SlideList const& slides);

    // access to contained box
    Box::Ptr findBox(QString const& id) const;
    std::pair<Slide::Ptr, Box::Ptr> findBoxForLine(int line) const;

    bool empty() const;
    QSize dimensions() const;
    int numberOfSlides() const;

    void applyStandardTemplateToBox(Box::Ptr box, BoxStyle const& standardBoxStyle) const;

    // Change Geometry of Box only through the presentation in order to
    // save it in the Configuration
    void setBoxGeometry(QString const& boxId, const BoxGeometry &rect, int pageNumber);
    void deleteBoxGeometry(QString const& boxId, int pageNumber);

    // Configuration Class to follow and save the Geometry of the boxes
    void saveConfig(QString const& file);
    ConfigBoxes& configuration();
    void setConfig(ConfigBoxes config);

    void deleteNotNeededConfigurations();

    std::map<QString, BoxStyle> definedClasses() const;
    void applyDefinedClass(SlideList const& slides);

Q_SIGNALS:
    void presentationChanged();
    void slideChanged(int pageNumber);
    void rebuildNeeded();

private:
    // apply Configuration in json file to mSlides
    void applyConfiguration();
    SlideList const& applyStandardTemplate(SlideList const& slides) const;

    void createMapDefinesClass();

    BoxStyle setStyleIfNotSet(BoxStyle &appliedStyle, BoxStyle const& modelStyle) const;
    void applyGeometryIfNotSet(BoxStyle &appliedStyle, BoxGeometry const& rect) const;

private:
    SlideList mSlides;
    QString mInputDir;
    ConfigBoxes mConfig;
    QSize mDimensions{1600, 900};
    std::shared_ptr<Template> mTemplate = nullptr;
    std::map<QString, BoxStyle> mDefinedStyles;
};

Q_DECLARE_METATYPE(Presentation::Ptr)

#endif // PRESENTATION_H
