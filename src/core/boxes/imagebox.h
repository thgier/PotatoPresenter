/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef PICTURE_H
#define PICTURE_H
#include "box.h"
#include "cachemanager.h"
#include <QSvgRenderer>


class ImageBox: public Box
{
public:
    ImageBox() = default;

    void drawContent(QPainter& painter, std::map<QString, QString> const& variables, PresentationRenderHints hints = PresentationRenderHints::NoRenderHints) override;
    bool containsPoint(QPoint point, int) const override;

    std::shared_ptr<Box> clone() override;

    QString ImagePath() const;

private:
    PixMapElement loadImage(QString path, QSize size) const;
    PixMapElement loadSvg(QString path, QSize size) const;
    std::shared_ptr<QSvgRenderer> loadPdf(QString path) const;
    void drawPixmap(PixMapElement pixmapElement, QPainter& painter);

private:
    QString mImagePath;
    QRect mBoundingBox;
};

#endif // PICTURE_H
