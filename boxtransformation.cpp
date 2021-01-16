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

void BoxTransformation::doTransformation(QPoint mousePos, std::shared_ptr<Presentation> pres){
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
    auto const rotateMouseMovement = boxrect.rotateTransform().inverted().map(mouseMovement);
    auto const transformation = boxrect.transform().inverted();
    switch (mPosMouseBox) {
        case pointPosition::topLeftCorner:{
            auto point = transformation.map(rect.bottomRight());
            auto const width = rect.width() - rotateMouseMovement.x();
            auto const heigth = rect.height() - rotateMouseMovement.y();
            rect.setSize(QSize(width, heigth));
            boxrect.setRect(rect);
            point = boxrect.transform().map(point);
            rect.moveBottomRight(point);
            break;
        }
        case pointPosition::topRightCorner:{
            auto point = transformation.map(rect.bottomLeft());
            auto const localMouse = transformation.map(mousePos);
            rect.setBottomLeft(localMouse);
            boxrect.setRect(rect);
            point = boxrect.transform().map(point);
            rect.moveBottomLeft(point);
            break;
        }
        case pointPosition::bottomLeftCorner:{
//            auto point = transformation.map(rect.topRight());
            auto const width = rect.width() - rotateMouseMovement.x();
            auto const heigth = rect.height() + rotateMouseMovement.y();
            rect.setSize(QSize(width, heigth));
            rect = rect.normalized();
            auto const widthCenter = rect.center().x() - mouseMovement.x();
            auto const heigthCenter = rect.center().y() + mouseMovement.y();
            rect.moveCenter(QPoint(widthCenter, heigthCenter));
//            boxrect.setRect(rect);
//            point = boxrect.transform().map(point);
//            rect.moveTopRight(point);
            break;
        }
        case pointPosition::bottomRightCorner:{
            auto const width = rect.width() + rotateMouseMovement.x();
            auto const heigth = rect.height() + rotateMouseMovement.y();
            rect.setSize(QSize(width, heigth));
            break;
        }
        case pointPosition::topBorder:{
            auto point = transformation.map(rect.bottomLeft());
            auto const heigth = rect.height() - rotateMouseMovement.y();
            rect.setHeight(heigth);
            boxrect.setRect(rect);
            point = boxrect.transform().map(point);
            rect.moveBottomLeft(point);
            break;
        }
        case pointPosition::bottomBorder:{
            auto point = transformation.map(rect.topLeft());
            auto const heigth = rect.height() + rotateMouseMovement.y();
            rect.setHeight(heigth);
            boxrect.setRect(rect);
            point = boxrect.transform().map(point);
            rect.moveTopLeft(point);
            break;
        }
        case pointPosition::leftBorder:{
            auto point = transformation.map(rect.topRight());
            auto const width = rect.width() - rotateMouseMovement.x();
            rect.setWidth(width);
            boxrect.setRect(rect);
            point = boxrect.transform().map(point);
            rect.moveTopRight(point);
            break;
        }
        case pointPosition::rightBorder:{
            auto point = transformation.map(rect.bottomLeft());
            auto const width = rect.width() + rotateMouseMovement.x();
            rect.setWidth(width);
            boxrect.setRect(rect);
            point = boxrect.transform().map(point);
            rect.moveBottomLeft(point);
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


