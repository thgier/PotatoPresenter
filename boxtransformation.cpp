#include "boxtransformation.h"
#include "vector"
#include <math.h>
#include <numbers>

BoxTransformation::BoxTransformation()
{

}

BoxTransformation::BoxTransformation(std::shared_ptr<Box> box, TransformationType trafo, pointPosition posMouseBox, int pageNumber, QPoint mousePos)
    : mBox{box}
    , mTrafo{trafo}
    , mPosMouseBox{posMouseBox}
    , mPageNumber{pageNumber}
    , mLastMousePosition{mousePos}
{
}

void BoxTransformation::doTransformation(QPoint mousePos, Presentation* pres){
    BoxGeometry box;
    switch (mTrafo) {
        case TransformationType::translate:{
            box = makeScaleTransformation(mousePos);
            break;
        }
        case TransformationType::rotate:
            box = makeRotateTransformation(mousePos);
            break;
        }
    pres->setBox(mBox->id(), box, mPageNumber);
}

QRect BoxTransformation::scale(QPoint mouse, QPointF v, BoxGeometry* boxrect) const{
    QRect rect = boxrect->rect();
    auto const transformV = boxrect->rotateTransform().map(v);
    auto const projection = QPointF::dotProduct(mouse, transformV);
    qWarning() << "pro" << projection * v.x() << mouse.x();
    auto const width = rect.width() - projection * v.x();
    auto const height = rect.height() - projection * v.y();
    rect.setSize(QSize(width, height));
    return rect;
}

BoxGeometry BoxTransformation::makeScaleTransformation(QPoint mousePos){
    auto mouseMovement = mousePos - mLastMousePosition;
    mLastMousePosition = mousePos;
    auto boxrect = mBox->geometry();
    auto rect = boxrect.rect();
    switch (mPosMouseBox) {
        case pointPosition::topLeftCorner:{
            mouseMovement = boxrect.rotateTransform().inverted().map(mouseMovement);
            auto const point = rect.bottomRight();
            auto const width = rect.width() - mouseMovement.x();
            auto const heigth = rect.height() - mouseMovement.y();
            rect.setSize(QSize(width, heigth));
            rect.moveBottomRight(point);
            break;
        }
        case pointPosition::topRightCorner:{
            mouseMovement = boxrect.rotateTransform().inverted().map(mouseMovement);
            auto const point = rect.bottomLeft();
            auto const width = rect.width() + mouseMovement.x();
            auto const heigth = rect.height() - mouseMovement.y();
            rect.setSize(QSize(width, heigth));
            rect.moveBottomLeft(point);
            break;
        }
        case pointPosition::bottomLeftCorner:{
            mouseMovement = boxrect.rotateTransform().inverted().map(mouseMovement);
            auto const point = rect.topRight();
            auto const width = rect.width() - mouseMovement.x();
            auto const heigth = rect.height() + mouseMovement.y();
            rect.setSize(QSize(width, heigth));
            rect.moveTopRight(point);
            break;
        }
        case pointPosition::bottomRightCorner:{
            mouseMovement = boxrect.rotateTransform().inverted().map(mouseMovement);
            auto const point = rect.topLeft();
            auto const width = rect.width() + mouseMovement.x();
            auto const heigth = rect.height() + mouseMovement.y();
            rect.setSize(QSize(width, heigth));
            rect.moveTopLeft(point);
            break;
        }
        case pointPosition::topBorder:{
            mouseMovement = boxrect.rotateTransform().inverted().map(mouseMovement);
            auto const point = rect.bottomLeft();
            auto const heigth = rect.height() - mouseMovement.y();
            rect.setHeight(heigth);
            rect.moveBottomLeft(point);
            break;
        }
        case pointPosition::bottomBorder:{
            mouseMovement = boxrect.rotateTransform().inverted().map(mouseMovement);
            auto const heigth = rect.height() + mouseMovement.y();
            rect.setHeight(heigth);
            break;
        }
        case pointPosition::leftBorder:{
            mouseMovement = boxrect.rotateTransform().inverted().map(mouseMovement);
            auto const point = rect.topRight();
            auto const width = rect.width() - mouseMovement.x();
            rect.setWidth(width);
            rect.moveTopRight(point);
            break;
        }
        case pointPosition::rightBorder:{
            mouseMovement = boxrect.rotateTransform().inverted().map(mouseMovement);
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

BoxGeometry BoxTransformation::makeRotateTransformation(QPoint mousePos){
    auto boxrect = mBox->geometry();
    auto const center = boxrect.rect().center();
    auto const centerToMouse = center - mousePos;
    qInfo() << centerToMouse;
    auto const mouseAngle = std::atan2(double(centerToMouse.y()), centerToMouse.x());
    auto const angleCenterEdge = std::atan2(boxrect.rect().height(), boxrect.rect().width());
    qreal rectAngle;
    qInfo() << "mouseAngle: " << mouseAngle;
    switch (mPosMouseBox) {
    case pointPosition::topLeftCorner:
        rectAngle = mouseAngle - angleCenterEdge;
        break;
    case pointPosition::bottomLeftCorner:
        rectAngle = mouseAngle + angleCenterEdge;
        break;
    case pointPosition::bottomRightCorner:
        rectAngle = mouseAngle + std::numbers::pi - angleCenterEdge;
        break;
    case pointPosition::topRightCorner:
        rectAngle = mouseAngle - std::numbers::pi + angleCenterEdge;
        break;
    case pointPosition::inBox:{
        auto rect = boxrect.rect();
        rect.translate(mousePos - mLastMousePosition);
        mLastMousePosition = mousePos;
        boxrect.setRect(rect);
        return boxrect;
    }
    default:
        return {};
        break;
    }
    boxrect.setAngle(rectAngle / std::numbers::pi * 180);
    return boxrect;
}



