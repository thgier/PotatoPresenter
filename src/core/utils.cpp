/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "src/core/utils.h"
#include <set>
#include <algorithm>

BoxStyle propertyMapToBoxStyle(const Box::Properties &properties) {
    BoxStyle boxStyle;
    for (auto const& entry: properties) {
        applyProperty(entry.first, entry.second, boxStyle);
    }
    return boxStyle;
}

BoxStyle variablesToBoxStyle(Variables const& variables) {
    BoxStyle boxStyle;
    for (auto const& var: variables) {
        auto property = var.first;
        property.remove(0, 2);
        property.chop(1);
        try {
            applyProperty(property, var.second, 0, boxStyle);
        }  catch (PorpertyConversionError) {

        }
    }
    return boxStyle;
}

void applyProperty(QString const& property, const QString &value, int line, BoxStyle & boxstyle) {
    bool numberOk = true;

    if(property == "defineclass") {
        boxstyle.mDefineclass = value;
    }
    else if(property == "text") {
        boxstyle.mText = value;
    }
    else if(property == "class")  {
        boxstyle.mClass = value;
    }
    else if(property == "color") {
        QColor color;
        color.setNamedColor(QString(value));
        if(!color.isValid()) {
            throw PorpertyConversionError {
                QString("Invalid color '%1'").arg(QString(value)),
                line
            };
        }
        boxstyle.mColor = color;
    }
    else if(property == "opacity") {
        boxstyle.mOpacity = value.toDouble(&numberOk);
    }
    else if(property == "font-size") {
        boxstyle.mFontSize = value.toInt(&numberOk);
    }
    else if(property == "line-height") {
        if(value.toDouble() != 0) {
            boxstyle.mLineSpacing = value.toDouble(&numberOk);
        }
    }
    else if(property == "font-weight") {
        if(QString(value) == "bold") {
            boxstyle.mFontWeight = FontWeight::bold;
        }
        else if(QString(value) == "normal") {
            boxstyle.mFontWeight = FontWeight::normal;
        }
        else {
            throw PorpertyConversionError {
                "Invalid value for 'font-weight' (possible values: bold, normal)",
                line
            };
        }
    }
    else if(property == "font-family") {
        boxstyle.mFont = QString(value);
    }
    else if(property == "id") {
        boxstyle.mId = value;
        if(value.startsWith("intern")) {
            throw PorpertyConversionError {
                "User defined box IDs must not start with \"intern\"",
                line
            };
        }
    }
    else if(property == "left") {
        boxstyle.mGeometry.setLeft(value.toInt(&numberOk));
        boxstyle.movable = false;
    }
    else if(property == "top") {
        boxstyle.mGeometry.setTop(value.toInt(&numberOk));
        boxstyle.movable = false;
    }
    else if(property == "width") {
        boxstyle.mGeometry.setWidth(value.toInt(&numberOk));
        boxstyle.movable = false;
    }
    else if(property == "height") {
        boxstyle.mGeometry.setHeight(value.toInt(&numberOk));
        boxstyle.movable = false;
    }
    else if(property == "angle") {
        boxstyle.mGeometry.setAngle(value.toDouble(&numberOk));
        boxstyle.movable = false;
    }
    else if(property == "movable") {
        if(value == "true") {
            boxstyle.movable = true;
        }
        else if(value == "false") {
            boxstyle.movable = false;
        }
        else {
            throw PorpertyConversionError {
                "Invalid value for 'movable' (possible values: true, false)",
                line
            };
        }
    }
    else if(property == "text-align") {
        if(value == "left") {
            boxstyle.mAlignment = Qt::AlignLeft;
        }
        else if(value == "right") {
            boxstyle.mAlignment = Qt::AlignRight;
        }
        else if(value == "center") {
            boxstyle.mAlignment = Qt::AlignCenter;
        }
        else if(value == "justify") {
            boxstyle.mAlignment = Qt::AlignJustify;
        }
        else {
            throw PorpertyConversionError {
                "Invalid value for 'text-align' (possible values: left, right, center, justify)",
                line
            };
        }
    }
    else if(property == "language") {
        boxstyle.language = QString(value);
    }
    else if(property == "background") {
        QColor color;
        color.setNamedColor(value);
        if(!color.isValid()) {
            throw PorpertyConversionError {"Invalid color", line};
        }
        boxstyle.mBackgroundColor = color;
    }
    else if(property == "background-color") {
        QColor color;
        color.setNamedColor(value);
        if(!color.isValid()) {
            throw PorpertyConversionError {"Invalid color", line};
        }
        boxstyle.mBackgroundColor = color;
    }
    else if(property == "padding") {
        boxstyle.mPadding = value.toInt(&numberOk);
    }
    else if(property == "border-radius") {
        boxstyle.mBorderRadius = value.toInt(&numberOk);
    }
    else if(property == "border") {
        static auto const borderStyles = std::set<QString>{"solid", "dashed", "dotted", "double"};
        bool borderOk = true;
        auto values = QString(value).split(" ");
        if(values.empty()) {
            throw PorpertyConversionError {
                "Give border in format: \"border: border-width px border-style (required) border color\", e.g. \"4px solid red\"",
                line
            };
        }
        if (values[0].endsWith("px") && values.length() >= 2) {
            auto value = values[0];
            value.chop(2);
            boxstyle.mBorder.width = value.toInt(&borderOk);
            if(borderStyles.find(values[1]) != borderStyles.end()) {
                boxstyle.mBorder.style = values[1];
            }
            else {
                borderOk = false;
            }
            if (values.length() >= 3) {
                auto const color = QColor(QString(values[2]));
                borderOk = borderOk && color.isValid();
                boxstyle.mBorder.color = color;
            }
        }
        else {
            if(borderStyles.find(values[0]) != borderStyles.end()) {
                boxstyle.mBorder.style = values[0];
            }
            else {
                borderOk = false;
            }
            if(values.length() >= 2) {
                auto const color = QColor(QString(values[1]));
                borderOk = borderOk && color.isValid();
                boxstyle.mBorder.color = color;
            }
        }
        if(!borderOk) {
            throw PorpertyConversionError {
                "Give border in format: \"border: border-width px border-style (required) border color\", e.g. \"4px solid red\"",
                line
            };
        }
    }
    else if (property == "marker") {
        auto values = QString(value).split(" ");
        if(values.empty()) {
            throw PorpertyConversionError{
                "Give marker in the format: \"marker: color (required) font-weight (optional)\", e.g. blue bold, red",
                line
            };
        }
        if(values[0] == "bold") {
            boxstyle.mTextMarker.fontWeight = FontWeight::bold;
        }
        else if(values[0] == "normal") {
            boxstyle.mTextMarker.fontWeight = FontWeight::normal;
        }
        else {
            boxstyle.mTextMarker.color = QColor(QString(values[0]));
            if(values.length() > 1) {
                if(values[1] == "bold") {
                    boxstyle.mTextMarker.fontWeight = FontWeight::bold;
                }
                else if(values[1] == "normal") {
                    boxstyle.mTextMarker.fontWeight = FontWeight::normal;
                }
            }
        }
    }
    else {
        throw PorpertyConversionError {
            QString("Invalid Argument %1.").arg(property),
            line
        };
    }
    if(!numberOk) {
        throw PorpertyConversionError {
            "Invalid number",
            line
        };
    }
}

void applyProperty(QString const& property, PropertyEntry const& entry, BoxStyle & boxstyle) {
    applyProperty(property, entry.mValue, entry.mLine, boxstyle);
}

Box::List copy(Box::List const& input) {
    Box::List copiedList(input.size());
    std::ranges::transform(input.begin(), input.end(), copiedList.begin(), [](auto const& element) { return element->clone(); });
    return copiedList;
}

