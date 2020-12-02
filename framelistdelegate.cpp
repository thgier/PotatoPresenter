#include "framelistdelegate.h"
#include "frame.h"

FrameListDelegate::FrameListDelegate(QObject *parent)
{

}

void FrameListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    auto const frame = index.model()->data(index, Qt::DisplayRole).value<std::shared_ptr<Frame>>();
    painter->save();
    painter->setViewport(option.rect);
    painter->setWindow(-50, -50, 1700, 1200);
    painter->save();
    painter->setClipRect(QRect(0, 0, 1600, 900));
    for(auto box: frame->getBoxes()){
        box->drawContent(*painter);
    }
    painter->restore();

    QFont font = painter->font();
    font.setPixelSize(100);
    painter->setFont(font);
    painter->drawText(QRect(0, 900, 1700, 200), Qt::AlignCenter, frame->id());

    painter->setPen(Qt::blue);
    painter->drawRect(QRect(0, 0, 1600, 900));

    if(option.state & QStyle::State_Selected){
        painter->save();
        painter->setPen(Qt::red);
        painter->drawRect(QRect(0, 0, 1600, 900));
        painter->restore();
    }
    painter->restore();
}

QSize FrameListDelegate::sizeHint(const QStyleOptionViewItem &option,
                              const QModelIndex & /* index */) const
{
    auto const height = option.rect.height();
    return QSize(height / 9.0 * 16, height);
}
