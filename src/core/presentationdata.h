#ifndef PRESENTATIONDATA_H
#define PRESENTATIONDATA_H

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

    Box::Ptr findBox(QString const& id) const {
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


class PresentationData
{
public:
    PresentationData() = default;
    PresentationData(SlideList slides, std::shared_ptr<Template> presentationTemplate=nullptr);

    // starts the process that applys defined classes, templates,
    // the geometries given by config, and the properties to the boxes
    void applyConfiguration(ConfigBoxes const& config);

    SlideList const& slides() const;
    int numberSlides() const;

    // use this to render slide
    // slides with the default properties set
    // e.g. by \setvar color black
    SlideList const& slideListDefaultApplied();

    // find the classes that are defined in the PresentationData and apply it to another SlideList
    // (config that belongs to PresentationData is needed)
    void applyDefinedClass(SlideList const& slides, ConfigBoxes const& config);

private:
    // creating and applying of a map of the boxes that defines
    // a class e.g. has the argument defineclass
    std::map<QString, BoxStyle> createMapDefinesClass(const ConfigBoxes &config) const;

    void setTitleIfTextUnset(SlideList const& slides);
    void applyJSONGeometries(ConfigBoxes const& config);
    void applyJSONToBox(Slide::Ptr slide, Box::Ptr box, ConfigBoxes const& config) const;


private:
    SlideList mSlides;
    std::shared_ptr<Template> mTemplate;
};

#endif // PRESENTATIONDATA_H
