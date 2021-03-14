#include "boxtransformation.h"
#include <vector>
#include <math.h>
#include <numbers>

BoxTransformation::BoxTransformation(BoxGeometry geometry, TransformationType trafo, pointPosition classifiedMousePosition, QPoint mousePos)
    : mGeometry(geometry)
    , mTrafo{trafo}
    , mClassifiedMousePosition{classifiedMousePosition}
    , mStartMousePosition{mousePos}
{
}

BoxGeometry BoxTransformation::doTransformation(QPoint mousePos){
    BoxGeometry geometry;
    switch (mTrafo) {
        case TransformationType::translate:{
            geometry = makeScaleTransformation(mousePos);
            break;
        }
        case TransformationType::rotate:
            geometry = makeRotateTransformation(mousePos);
            break;
        }
    return geometry;
}

BoxGeometry BoxTransformation::makeScaleTransformation(QPoint mousePos){
    auto mouseMovement = mousePos - mStartMousePosition;
    auto geometry = mGeometry;
    auto rect = geometry.rect();
    switch (mClassifiedMousePosition) {
        case pointPosition::topLeftCorner:{
            auto const bottomRight = geometry.transform().map(rect.bottomRight());
            rect.moveBottomRight(bottomRight);
            auto const localMouse = geometry.transform(bottomRight).inverted().map(mousePos);
            rect.setTopLeft(localMouse);
            auto const center = geometry.transform(bottomRight).map(rect.center());
            rect.moveCenter(center);
            break;
        }
        case pointPosition::topRightCorner:{
            auto const bottomLeft = geometry.transform().map(rect.bottomLeft());
            rect.moveBottomLeft(bottomLeft);
            auto const localMouse = geometry.transform(bottomLeft).inverted().map(mousePos);
            rect.setTopRight(localMouse);
            auto const center = geometry.transform(bottomLeft).map(rect.center());
            rect.moveCenter(center);
            break;
        }
        case pointPosition::bottomLeftCorner:{
            auto const topRight = geometry.transform().map(rect.topRight());
            rect.moveTopRight(topRight);
            auto const localMouse = geometry.transform(topRight).inverted().map(mousePos);
            rect.setBottomLeft(localMouse);
            auto const center = geometry.transform(topRight).map(rect.center());
            rect.moveCenter(center);
            break;
        }
        case pointPosition::bottomRightCorner:{
            auto const topLeft = geometry.transform().map(rect.topLeft());
            rect.moveTopLeft(topLeft);
            auto const localMouse = geometry.transform(topLeft).inverted().map(mousePos);
            rect.setBottomRight(localMouse);
            auto const center = geometry.transform(topLeft).map(rect.center());
            rect.moveCenter(center);
            break;
        }
        case pointPosition::topBorder:{
            auto const bottomLeft = geometry.transform().map(rect.bottomLeft());
            rect.moveBottomLeft(bottomLeft);
            auto const localMouse = geometry.transform(bottomLeft).inverted().map(mousePos);
            rect.setTop(localMouse.y());
            auto const center = geometry.transform(bottomLeft).map(rect.center());
            rect.moveCenter(center);
            break;
        }
        case pointPosition::bottomBorder:{
            auto const topLeft = geometry.transform().map(rect.topLeft());
            rect.moveTopLeft(topLeft);
            auto const localMouse = geometry.transform(topLeft).inverted().map(mousePos);
            rect.setBottom(localMouse.y());
            auto const center = geometry.transform(topLeft).map(rect.center());
            rect.moveCenter(center);
            break;
        }
        case pointPosition::leftBorder:{
            auto const topRight = geometry.transform().map(rect.topRight());
            rect.moveTopRight(topRight);
            auto const localMouse = geometry.transform(topRight).inverted().map(mousePos);
            rect.setLeft(localMouse.x());
            auto const center = geometry.transform(topRight).map(rect.center());
            rect.moveCenter(center);
            break;
        }
        case pointPosition::rightBorder:{
            auto const topLeft = geometry.transform().map(rect.topLeft());
            rect.moveTopLeft(topLeft);
            auto const localMouse = geometry.transform(topLeft).inverted().map(mousePos);
            rect.setRight(localMouse.x());
            auto const center = geometry.transform(topLeft).map(rect.center());
            rect.moveCenter(center);
            break;
        }
        case pointPosition::inBox:{
            rect.translate(mouseMovement);
            geometry.setRect(rect);
            return geometry;
            break;
        }
        case pointPosition::notInBox:{
            return {};
        }
    }
    rect = rect.normalized();
    geometry.setRect(rect);
    return geometry;
}

BoxGeometry BoxTransformation::makeRotateTransformation(QPoint mousePos){
    auto geometry = mGeometry;
    auto const center = geometry.rect().center();
    auto const centerToMouse = center - mousePos;
    qInfo() << centerToMouse;
    auto const mouseAngle = std::atan2(double(centerToMouse.y()), centerToMouse.x());
    auto const angleCenterEdge = std::atan2(geometry.rect().height(), geometry.rect().width());
    qreal rectAngle;
    qInfo() << "mouseAngle: " << mouseAngle;
    switch (mClassifiedMousePosition) {
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
        auto rect = geometry.rect();
        rect.translate(mousePos - mStartMousePosition);
        geometry.setRect(rect);
        return geometry;
    }
    default:
        return {};
        break;
    }
    geometry.setAngle(rectAngle / std::numbers::pi * 180);
    return geometry;
}


