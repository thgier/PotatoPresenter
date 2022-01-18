#include "presentationdata.h"
#include "utils.h"
#include "template.h"

namespace  {

void forEachBox(auto const& slides, auto func) {
    for (auto const& slide: slides.vector)
        for (auto const& box: slide->boxes())
            func(slide, box);
}

void applyClassIDDefinclass(SlideList & slides) {
    forEachBox(slides, [](Slide::Ptr slide, Box::Ptr box) {
        if(box->properties().find("class") != box->properties().end()) {
            box->style().mClass = box->properties().find("class")->second.mValue;
        }
        if(box->properties().find("id") != box->properties().end()) {
            box->style().mId = box->properties().find("id")->second.mValue;
        }
        if(box->properties().find("defineclass") != box->properties().end()) {
            box->style().mDefineclass = box->properties().find("defineclass")->second.mValue;
        }
    });
}

void applyGeometryToBoxIfSetInModel(Box::Ptr box, const BoxGeometry &modelGeometry) {

    if(modelGeometry.left()) {
        box->geometry().setLeft(modelGeometry.leftDisplay());
    }
    if(modelGeometry.top()) {
        box->geometry().setTop(modelGeometry.topDisplay());
    }
    if(modelGeometry.width()) {
        box->geometry().setWidth(modelGeometry.widthDisplay());
    }
    if(modelGeometry.height()) {
        box->geometry().setHeight(modelGeometry.heightDisplay());
    }
    if(modelGeometry.angle()) {
        box->geometry().setAngle(modelGeometry.angleDisplay());
    }
}

void applyStandardTemplateToBox(Box::Ptr box) {
    QRect rect;
    auto style = box->style();

    // set standard geometry
    if(style.getClass() == "title") {
        rect = QRect(50, 40, 1500, 100);
    }
    else if(style.getClass() == "body") {
        rect = QRect(50, 150, 1500, 650);
    }
    else if(style.getClass() == "code") {
        rect = QRect(50, 150, 1500, 650);
        if(!style.mFont) {
            style.mFont = "DejaVu Sans Mono";
        }
    }
    else if(style.getClass() == "image") {
        rect = QRect(50, 150, 1500, 650);
    }
    else if(style.getClass() == "right_column") {
        rect = QRect(830, 150, 720, 650);
    }
    else if(style.getClass() == "left_column") {
        rect = QRect(50, 150, 720, 650);
    }
    else if(style.getClass() == "fullscreen") {
        rect = QRect(0, 0, 1600, 900);
    }
    else {
        rect = QRect(50, 200, 300, 100);
    }

    applyGeometryToBoxIfSetInModel(box, BoxGeometry(rect, 0));
}

void applyStandardTemplate(SlideList &slides) {
    forEachBox(slides, [](Slide::Ptr slide, Box::Ptr box){
        applyStandardTemplateToBox(box);
    });
}

void forEachTemplateBox(auto const& slides, auto func) {
    for (auto const& slide: slides.vector)
        for (auto const& box: slide->templateBoxes())
            func(slide, box);
}

void setStyleToBoxIfSetInModel(Box::Ptr box, BoxStyle const& modelStyle) {
    auto const assignIfSet = [](auto& value, auto const& standard) {
        if(standard) {
            value = standard;
        }
    };

    assignIfSet(box->style().mFont, modelStyle.mFont);
    assignIfSet(box->style().mFontSize, modelStyle.mFontSize);
    assignIfSet(box->style().mFontWeight, modelStyle.mFontWeight);
    assignIfSet(box->style().mColor, modelStyle.mColor);
    assignIfSet(box->style().mBackgroundColor, modelStyle.mBackgroundColor);
    assignIfSet(box->style().mAlignment, modelStyle.mAlignment);
    assignIfSet(box->style().mLanguage, modelStyle.mLanguage);
    assignIfSet(box->style().mHighlight, modelStyle.mHighlight);
    assignIfSet(box->style().mLineSpacing, modelStyle.mLineSpacing);
    assignIfSet(box->style().mOpacity, modelStyle.mOpacity);
    assignIfSet(box->style().mPadding, modelStyle.mPadding);
    assignIfSet(box->style().mBorderRadius, modelStyle.mBorderRadius);
    assignIfSet(box->style().mTextMarker.color, modelStyle.mTextMarker.color);
    assignIfSet(box->style().mTextMarker.fontWeight, modelStyle.mTextMarker.fontWeight);
    assignIfSet(box->style().mBorder.width, modelStyle.mBorder.width);
    assignIfSet(box->style().mBorder.style, modelStyle.mBorder.style);
    assignIfSet(box->style().mBorder.color, modelStyle.mBorder.color);
    if(modelStyle.mText && !modelStyle.mText->isEmpty()) {
        box->style().mText = modelStyle.mText;
    }
}

void setStyleToBoxIfNotSettedAndSetInModel(Box::Ptr box, BoxStyle const& modelStyle) {
    auto const assignIfSet = [](auto& value, auto const& standard) {
        if(standard && !value) {
            value = standard;
        }
    };

    assignIfSet(box->style().mFont, modelStyle.mFont);
    assignIfSet(box->style().mFontSize, modelStyle.mFontSize);
    assignIfSet(box->style().mFontWeight, modelStyle.mFontWeight);
    assignIfSet(box->style().mColor, modelStyle.mColor);
    assignIfSet(box->style().mBackgroundColor, modelStyle.mBackgroundColor);
    assignIfSet(box->style().mAlignment, modelStyle.mAlignment);
    assignIfSet(box->style().mLanguage, modelStyle.mLanguage);
    assignIfSet(box->style().mHighlight, modelStyle.mHighlight);
    assignIfSet(box->style().mLineSpacing, modelStyle.mLineSpacing);
    assignIfSet(box->style().mOpacity, modelStyle.mOpacity);
    assignIfSet(box->style().mPadding, modelStyle.mPadding);
    assignIfSet(box->style().mBorderRadius, modelStyle.mBorderRadius);
    assignIfSet(box->style().mTextMarker.color, modelStyle.mTextMarker.color);
    assignIfSet(box->style().mTextMarker.fontWeight, modelStyle.mTextMarker.fontWeight);
    assignIfSet(box->style().mBorder.width, modelStyle.mBorder.width);
    assignIfSet(box->style().mBorder.style, modelStyle.mBorder.style);
    assignIfSet(box->style().mBorder.color, modelStyle.mBorder.color);
    if(modelStyle.mText && !modelStyle.mText->isEmpty()) {
        box->style().mText = modelStyle.mText;
    }
}

void applyStandardVariables(SlideList & slides) {
    forEachBox(slides, [](auto const& slide, auto const& box){
        auto const boxStyle = variablesToBoxStyle(slide->variables());
        setStyleToBoxIfNotSettedAndSetInModel(box, boxStyle);
    });

    forEachTemplateBox(slides, [](auto const& slide, auto const& box){
        auto const boxStyle = variablesToBoxStyle(slide->variables());
        setStyleToBoxIfNotSettedAndSetInModel(box, boxStyle);
    });
}

TableOfContent createTableOfContent(SlideList const& slides) {
    TableOfContent newTableOfContent;
    for(auto const& slide : slides.vector) {
        auto sectionVar = slide->valueOfVariable("%{section}");
        auto subsectionVar = slide->valueOfVariable("%{subsection}");

        // look for section in variables
        if(sectionVar.isEmpty()) {
            continue;
        }
        if(sectionVar != newTableOfContent.currentSectionName()) {
            // correct length of last section
            if(!newTableOfContent.sections.empty()) {
                auto & lastSection = newTableOfContent.sections.back();
                lastSection.length = slide->pagenumber() - lastSection.startPage;
                if(!lastSection.subsection.empty()) {
                    auto lastSubsection = lastSection.subsection.back();
                    lastSubsection.length = slide->pagenumber() - lastSubsection.startPage;
                }
            }

            // insert new entry
            newTableOfContent.sections.push_back({
                sectionVar,
                slide->pagenumber(),
                slides.numberSlides() + 1 - slide->pagenumber()
            });
        }

        // look for subsection in variables
        if(subsectionVar != newTableOfContent.currentSubsectionName()) {
            // if sections is empty push back empty entry
            if(newTableOfContent.sections.empty()) {
                newTableOfContent.sections.push_back({
                    "",
                    slide->pagenumber(),
                    slides.numberSlides() + 1 - slide->pagenumber()
                });
            }

            // correct length of last subsection
            if (!newTableOfContent.sections.back().subsection.empty()) {
                auto& lastSubection = newTableOfContent.sections.back().subsection.back();
                lastSubection.length = slide->pagenumber() - lastSubection.startPage;
            }

            newTableOfContent.sections.back().subsection.push_back({
                subsectionVar,
                slide->pagenumber(),
                slides.numberSlides() - slide->pagenumber()
            });
        }
    }
    return newTableOfContent;
}

void addTableOfContentsToContext(SlideList& slides, TableOfContent tableofcontents) {
    for(auto const& slide: slides.vector) {
        slide->setTableOfContents(tableofcontents);
    }
}

void applyCSSProperties(const SlideList &slides) {
    auto lambda = [](auto slide, auto box){
        setStyleToBoxIfSetInModel(box, propertyMapToBoxStyle(box->properties()));
    };
    forEachBox(slides, lambda);
}

}


PresentationData::PresentationData(SlideList slides, std::shared_ptr<Template> presentationTemplate)
    : mSlides(slides)
    , mTemplate(presentationTemplate)
{
}

void PresentationData::applyConfiguration(const ConfigBoxes &config) {
    applyClassIDDefinclass(mSlides);
    applyStandardTemplate(mSlides);
    if(mTemplate) {
        mTemplate->applyTemplate(mSlides);
    }
    applyDefinedClass(mSlides, config);

    setTitleIfTextUnset(mSlides);
    applyJSONGeometries(config);
    applyCSSProperties(mSlides);
}

const SlideList &PresentationData::slides() const {
    return mSlides;
}

void PresentationData::applyDefinedClass(const SlideList &slides, const ConfigBoxes &config) {
    auto const definedClasses = createMapDefinesClass(config);
    forEachBox(slides, [&definedClasses](Slide::Ptr slide, Box::Ptr box){
        auto const slideKey = slide->slideClass();
        if(!box->style().mClass){
            return;
        }
        auto const boxKey = box->style().mClass.value();
        if(definedClasses.find(boxKey) != definedClasses.end()) {
            auto const definedClassStyle = definedClasses.find(boxKey)->second;
            applyGeometryToBoxIfSetInModel(box, definedClassStyle.mGeometry);
            setStyleToBoxIfSetInModel(box, definedClassStyle);
        }
        if(definedClasses.find(slideKey + "-" + boxKey) != definedClasses.end()) {
            auto const definedClassStyle = definedClasses.find(slideKey + "-" + boxKey)->second;
            applyGeometryToBoxIfSetInModel(box, definedClassStyle.mGeometry);
            setStyleToBoxIfSetInModel(box, definedClassStyle);
        }
        else {
            return;
        }
    });

    auto const tableOfContents = createTableOfContent(slides);
    for(auto const& slide: slides.vector) {
        slide->setTableOfContents(tableOfContents);
    }
}

void PresentationData::setTitleIfTextUnset(const SlideList &slides) {
    forEachBox(slides, [](Slide::Ptr slide, Box::Ptr box){
        if(box->style().mClass == "title" && box->style().text().isEmpty()) {
            auto style = box->style();
            style.mText = slide->id();
            box->setBoxStyle(style);
        }
    });
}

std::map<QString, BoxStyle> PresentationData::createMapDefinesClass(ConfigBoxes const& config) const {
    std::map<QString, BoxStyle> definitionClass;
    forEachBox(mSlides, [&definitionClass, config, this](Slide::Ptr slide, Box::Ptr box){
        if(box->style().mDefineclass) {
            applyJSONToBox(slide, box, config);
            setStyleToBoxIfSetInModel(box, propertyMapToBoxStyle(box->properties()));
            QString key = "";
            if(!slide->definesClass().isEmpty()) {
                key = slide->definesClass() + "-" ;
            }
            key.append(box->style().mDefineclass.value());
            definitionClass[key] = box->style();
        }
    });
    return definitionClass;
}

void PresentationData::applyJSONGeometries(ConfigBoxes const& config) {
    forEachBox(mSlides, [this, config](Slide::Ptr slide, Box::Ptr box){
        applyJSONToBox(slide, box, config);
    });
}

void PresentationData::applyJSONToBox(Slide::Ptr slide, Box::Ptr box, ConfigBoxes const& config) const {
    auto const boxConfig = config.getRect(box->configId());
    if(boxConfig.empty()) {
        return;
    }
    box->geometry().setLeft(boxConfig.rect.left());
    box->geometry().setTop(boxConfig.rect.top());
    box->geometry().setWidth(boxConfig.rect.width());
    box->geometry().setHeight(boxConfig.rect.height());
    box->geometry().setAngle(boxConfig.angle);
}

int PresentationData::numberSlides() const {
    return slides().numberSlides();
}

const SlideList &PresentationData::slideListDefaultApplied() {
    applyStandardVariables(mSlides);
    return mSlides;
}
