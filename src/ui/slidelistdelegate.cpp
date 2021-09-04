/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "slidelistdelegate.h"
#include "slide.h"
#include "sliderenderer.h"
#include "slidelistmodel.h"

SlideListDelegate::SlideListDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{

}

void SlideListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    auto const slide = index.data(Qt::DisplayRole).value<std::shared_ptr<Slide>>();
    painter->save();
    painter->setViewport(option.rect);
    auto const windowRect = QRect(-50, -50, 1700, 1200);
    auto const slideRect = QRect(0, 0, 1600, 900);
    painter->setWindow(windowRect);
    painter->save();
    if(option.state & QStyle::State_Selected){
        painter->fillRect(windowRect, option.palette.highlight());
    }
    painter->fillRect(slideRect, Qt::white);
    painter->setClipRect(slideRect);
    SlideRenderer paint{*painter};
    paint.paintSlide(slide);
    painter->restore();

    QFont font = painter->font();
    font.setPixelSize(100);
    painter->setFont(font);
    if(option.state & QStyle::State_Selected){
        painter->setPen(option.palette.HighlightedText);
        painter->drawText(QRect(0, 900, 1700, 200), Qt::AlignCenter, slide->id());
    }else{
        painter->drawText(QRect(0, 900, 1700, 200), Qt::AlignCenter, slide->id());
    }

    painter->setPen(Qt::blue);
    painter->drawRect(QRect(0, 0, 1600, 900));

    painter->restore();
}

QSize SlideListDelegate::sizeHint(const QStyleOptionViewItem &option,
                              const QModelIndex & /* index */) const
{
    auto const height = option.rect.height();
    return QSize(height / 9.0 * 16, height);
}
