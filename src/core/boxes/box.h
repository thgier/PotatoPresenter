/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once

#include <QRect>
#include <QPainter>
#include <memory>
#include "boxgeometry.h"

using Variables = std::map<QString, QString>;

enum FontWeight{
    normal,
    bold
};

enum PauseDisplayMode {
    onlyInPause,
    fromPauseOn
};

struct BoxStyle{
    QString boxClass;
    QString language;
    bool movable = true;
    std::optional<QColor> mColor;
    std::optional<QColor> mBackgroundColor;
    std::optional<int> mFontSize;
    std::optional<double> mLineSpacing;
    std::optional<FontWeight> mFontWeight;
    std::optional<QString> mFont;
    std::optional<Qt::Alignment> mAlignment;
    std::optional<double> mOpacity;
    BoxGeometry mGeometry;
    std::optional<int> mPadding;
    struct {
        std::optional<int> width;
        std::optional<QString> style;
        std::optional<QColor> color;
    } mBorder;

    QColor color() const {
        return mColor.value_or(Qt::black);
    }
    QColor backgroundColor() const {
        return mBackgroundColor.value_or(Qt::white);
    }
    int fontSize() const {
        return mFontSize.value_or(50);
    }
    double linespacing() const {
        return mLineSpacing.value_or(1.15);
    }
    FontWeight fontWeight() const {
        return mFontWeight.value_or(FontWeight::normal);
    }
    QString font() const {
        return mFont.value_or("sans-serif");
    }
    Qt::Alignment alignment() const {
        return mAlignment.value_or(Qt::AlignLeft);
    }
    double opacity() const {
        return mOpacity.value_or(1);
    }
    bool empty() const {
        return !(mColor.has_value() || mFontSize.has_value() || mLineSpacing.has_value() || mFontWeight.has_value()
                || mFont.has_value() || mAlignment.has_value() || mOpacity.has_value()) && mGeometry.empty();
    }
    bool hasBorder() {
        // CSS standard says style has to be given
        return mBorder.style.has_value();
    }
    int borderWidth() {
        return mBorder.width.value_or(5);
    }
    QColor borderColor() {
        return mBorder.color.value_or(Qt::black);
    }
    QString borderStyle() {
        return mBorder.style.value_or("solid");
    }
};

struct VariableSubstitution{
    int begin;
    int end;
    QString word;
};

class Box
{
public:
    using Ptr = std::shared_ptr<Box>;
    using List = std::vector<Ptr>;

    Box();
    Box(BoxStyle const& boxStyle, QString const& id, int line);

    // Implement this in child classes to draw the box's contents given the passed @p variables
    virtual void drawContent(QPainter& painter, std::map<QString, QString> variables) = 0;
    void drawManipulationSlide(QPainter& painter, int size);
    // e.g. Border, background
    void drawGlobalBoxSettings(QPainter& painter);

    // override this if the selectable area should be another than the boxGeometry
    virtual bool containsPoint(QPoint point, int margin) const;

    BoxStyle const& style() const;
    BoxGeometry const& geometry() const;
    BoxStyle& style();
    BoxGeometry& geometry();

    void setBoxStyle(BoxStyle style);
    void setGeometry(BoxGeometry const& geometry);
    void setGeometry(MemberBoxGeometry const& geometry);

    QString const& id() const;
    void setId(QString const& id);

    // line in input file where box is defined
    int line() const;

    // pause comment construct several boxes with different content and different
    // read configuration from another box if this is the case
    void setConfigId(QString configId);
    QString configId() const;

    // box is only shown on one pause counter or on different
    void setPauseMode(PauseDisplayMode mode);
    void setPauseCounter(int counter);
    std::pair<int, PauseDisplayMode> pauseCounter() const;

protected:
    // Call this in child classes when implemting drawContent to substitute variables (e.g. page number)
    // in text.
    QString substituteVariables(QString text, std::map<QString, QString> variables) const;

    struct PainterTransformScope {
        PainterTransformScope(Box* self, QPainter& painter)
            : mSelf(self)
            , mPainter(painter)
        {
            self->startDraw(mPainter);
        }
        ~PainterTransformScope() {
            mSelf->endDraw(mPainter);
        }
    private:
        Box* mSelf;
        QPainter& mPainter;
    };

    BoxStyle mStyle;

private:
    void startDraw(QPainter& painter);
    void endDraw(QPainter& painter) const;

private:
    QString mId;
    int mPauseCounter = 0;
    int mLine;
    std::optional<QString> mConfigId;
    PauseDisplayMode mPauseMode = PauseDisplayMode::fromPauseOn;
};
