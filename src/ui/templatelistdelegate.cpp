#include "templatelistdelegate.h"
#include "presentation.h"
#include "sliderenderer.h"

TemplateListDelegate::TemplateListDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{

}

void TemplateListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    auto const presentation = index.data(Qt::DisplayRole).value<Presentation::Ptr>();
    auto const numberSlides = presentation->numberOfSlides();
    auto const height = option.rect.height() - 2 * border;
    auto const width = ratio * height;
    auto const left = option.rect.left();
    auto const top = option.rect.top();

    if(option.state & QStyle::State_Selected){
        auto const selectionRect = QRect(option.rect.topLeft(), QSize((width + border) * numberSlides + border, height + 2 * border));
        painter->fillRect(selectionRect, option.palette.highlight());
    }

    painter->save();
    SlideRenderer paint{*painter};
    auto const slideRect = QRect(0, 0, widthLogical, heightLogical);
    painter->setWindow(slideRect);
    for(int i = 0; i < numberSlides; i++) {
        painter->setViewport(left + (border + width) * i + border, top + border, width, height);
        auto const slide = presentation->slideList().slideAt(i);
        painter->setClipRect(slideRect);
        painter->fillRect(slideRect, Qt::white);
        paint.paintSlide(slide);
    }
    painter->restore();
}

QSize TemplateListDelegate::sizeHint(const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    auto const height = 140;
    auto const width = ratio * height;
    auto const numberSlides = index.data(Qt::DisplayRole).value<Presentation::Ptr>().get()->numberOfSlides();
    auto const fullWidth = (width + border) * numberSlides + border;
    return QSize(fullWidth, height);
}
