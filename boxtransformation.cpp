#include "boxtransformation.h"
#include "vector"

BoxTransformation::BoxTransformation()
{

}

BoxTransformation::BoxTransformation(std::shared_ptr<Box> box, TransformationType trafo, pointPosition posMouseBox, int pageNumber)
    : mBox{box}
    , mTrafo{trafo}
    , mPosMouseBox{posMouseBox}
    , mPageNumber{pageNumber}
{
}

void BoxTransformation::makeTransformation(QPoint mouseMovement, Presentation* pres){
    BoxRect box;
    switch (mTrafo) {
        case TransformationType::translate:{
            box = makeScaleTransformation(mouseMovement);
            break;
        }
        case TransformationType::rotate:
            box = makeRotateTransformation(mouseMovement);
            break;
        }
    pres->setBox(mBox->id(), box, mPageNumber);
}

QRect BoxTransformation::scale(QPoint mouse, QPointF v, BoxRect* boxrect) const{
    QRect rect = boxrect->rect();
    auto const transformV = boxrect->rotateTransform().map(v);
    auto const projection = QPointF::dotProduct(mouse, transformV);
    qWarning() << "pro" << projection * v.x() << mouse.x();
    auto const width = rect.width() - projection * v.x();
    auto const height = rect.height() - projection * v.y();
    rect.setSize(QSize(width, height));
    return rect;
}

BoxRect BoxTransformation::makeScaleTransformation(QPoint mouseMovement){
    auto boxrect = mBox->Rect();
    auto rect = boxrect.rect();
    mouseMovement = boxrect.rotateTransform().inverted().map(mouseMovement);
    switch (mPosMouseBox) {
        case pointPosition::topLeftCorner:{
            auto const point = rect.bottomRight();
            auto const width = rect.width() - mouseMovement.x();
            auto const heigth = rect.height() - mouseMovement.y();
            rect.setSize(QSize(width, heigth));
            rect.moveBottomRight(point);
            break;
        }
        case pointPosition::topRightCorner:{
            auto const point = rect.bottomLeft();
            auto const width = rect.width() + mouseMovement.x();
            auto const heigth = rect.height() - mouseMovement.y();
            rect.setSize(QSize(width, heigth));
            rect.moveBottomLeft(point);
            break;
        }
        case pointPosition::bottomLeftCorner:{
            auto const point = rect.topRight();
            auto const width = rect.width() - mouseMovement.x();
            auto const heigth = rect.height() + mouseMovement.y();
            rect.setSize(QSize(width, heigth));
            rect.moveTopRight(point);
            break;
        }
        case pointPosition::bottomRightCorner:{
            auto const point = rect.topLeft();
            auto const width = rect.width() + mouseMovement.x();
            auto const heigth = rect.height() + mouseMovement.y();
            rect.setSize(QSize(width, heigth));
            rect.moveTopLeft(point);
            break;
        }
        case pointPosition::topBorder:{
            auto const point = rect.bottomLeft();
            auto const heigth = rect.height() - mouseMovement.y();
            rect.setHeight(heigth);
            rect.moveBottomLeft(point);
            break;
        }
        case pointPosition::bottomBorder:{
            auto const heigth = rect.height() + mouseMovement.y();
            rect.setHeight(heigth);
            break;
        }
        case pointPosition::leftBorder:{
            auto const point = rect.topRight();
            auto const width = rect.width() - mouseMovement.x();
            rect.setWidth(width);
            rect.moveTopRight(point);
            break;
        }
        case pointPosition::rightBorder:{
            auto const width = rect.width() + mouseMovement.x();
            qWarning() << "pro right" << mouseMovement.x();
            rect.setWidth(width);
            break;
        }
        case pointPosition::inBox:{
            rect.translate(mouseMovement);
            boxrect.setRect(rect);
            return boxrect;
            break;
        }
        case pointPosition::notInBox:{
            return {};
        }
    }
    rect = rect.normalized();
    boxrect.setRect(rect);
    return boxrect;
}

BoxRect BoxTransformation::makeRotateTransformation(QPoint mouseMovement){
    auto boxrect = mBox->Rect();
    qreal angle = boxrect.angle();
    QPointF projectionVector;
    switch (mPosMouseBox) {
    case pointPosition::topLeftCorner:
        projectionVector = QPointF(1, -1);
        break;
    case pointPosition::bottomLeftCorner:
        projectionVector = QPointF(-1, -1);
        break;
    case pointPosition::bottomRightCorner:
        projectionVector = QPointF(-1, 1);
        break;
    case pointPosition::topRightCorner:
        projectionVector = QPointF(1, 1);
        break;
    case pointPosition::inBox:{
        auto rect = boxrect.rect();
        rect.translate(mouseMovement);
        boxrect.setRect(rect);
        return boxrect;
    }
    default:
        return {};
        break;
    }
    projectionVector = boxrect.rotateTransform().map(projectionVector / std::sqrt(2.0));
    auto const projection = QPointF::dotProduct(projectionVector, mouseMovement);
    qWarning() << "projection" << projection;
    angle = boxrect.distanceToAngle(projection);
    boxrect.addAngle(angle);
    return boxrect;
}



