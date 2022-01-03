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
#include "presentationdata.h"

class Template;


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
    PresentationData& data();
    PresentationData const& data() const;

    // Change Geometry of Box only through the presentation in order to
    // save it in the Configuration
    void setBoxGeometry(QString const& boxId, const BoxGeometry &rect, int pageNumber);
    void deleteBoxGeometry(QString const& boxId, int pageNumber);
    void deleteBoxAngle(QString const& boxId, int pageNumber);

    // Configuration Class to follow and save the Geometry of the boxes
    void setConfig(ConfigBoxes config);
    ConfigBoxes const& configuration() const;

    // deletes the configuration entries from boxes that do not exist
    // in the presentation at the moment
    void deleteNotNeededConfigurations();

Q_SIGNALS:
    // emited if the position of a box on a slide is changed
    void slideChanged(int pageNumberFront, int pageNumberBack);
    void rebuildNeeded();
    void boxGeometryChanged();

private:
    PresentationData mData;
    ConfigBoxes mConfig;

    QSize mDimensions{1600, 900};
};

Q_DECLARE_METATYPE(Presentation::Ptr)

#endif // PRESENTATION_H
