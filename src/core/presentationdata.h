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

    void applyConfiguration(ConfigBoxes const& config);

    SlideList const& slides() const;
    int numberSlides() const;

    SlideList const& slideListDefaultApplied();

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
