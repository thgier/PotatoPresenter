/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef PICTURE_H
#define PICTURE_H
#include "box.h"
#include <QSvgRenderer>


class ImageBox: public Box
{
public:
    ImageBox(QString imagePath);

    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
    bool containsPoint(QPoint point, int) const override;

    QString ImagePath() const;

private:
    std::shared_ptr<QImage> loadImage(QString path) const;
    std::shared_ptr<QPixmap> loadSvg(QString path, QSize size);
    std::shared_ptr<QSvgRenderer> loadPdf(QString path) const;
    void drawImage(std::shared_ptr<QImage> image, QPainter& painter);
    void drawPixmap(std::shared_ptr<QPixmap> pixmap, QPainter& painter);

private:
    QString mImagePath;
    QRect mBoundingBox;
};

#endif // PICTURE_H
