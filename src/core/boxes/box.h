/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#pragma once

#include <QRect>
#include <QPainter>
#include <memory>
#include <optional>
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
    QString mId = "";
    std::optional<QString> mClass;
    int mLine = 0;
    std::optional<QString> mConfigId;
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
    std::optional<QString> mDefineclass;
    std::optional<QString> mText;
    BoxGeometry mGeometry;
    std::optional<int> mPadding;
    struct {
        std::optional<int> width;
        std::optional<QString> style;
        std::optional<QColor> color;
    } mBorder;
    struct {
        std::optional<QColor> color;
        std::optional<FontWeight> fontWeight;
    } mTextMarker;

    QColor color() const {
        return mColor.value_or(Qt::black);
    }
    QColor backgroundColor() const {
        return mBackgroundColor.value_or(Qt::white);
    }
    int fontSize() const {
        return mFontSize.value_or(26);
    }
    double linespacing() const {
        return mLineSpacing.value_or(1.15);
    }
    FontWeight fontWeight() const {
        return mFontWeight.value_or(FontWeight::normal);
    }
    QString font() const {
        return mFont.value_or("DejaVu Sans");
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
    bool hasBorder() const {
        // CSS standard says style has to be given
        return mBorder.style.has_value();
    }
    int borderWidth() const {
        return mBorder.width.value_or(5);
    }
    QColor borderColor() const {
        return mBorder.color.value_or(Qt::black);
    }
    QString borderStyle() const {
        return mBorder.style.value_or("solid");
    }
    QColor markerColor() const {
        return mTextMarker.color.value_or(color());
    }
    FontWeight markerFontWeight() const {
        return mTextMarker.fontWeight.value_or(fontWeight());
    }
    QString getClass() const {
        return mClass.value_or("default");
    }
    QString id() const {
        return mId;
    }
    int line() const {
        return mLine;
    }
    QString configId() const {
        return mConfigId.value_or(mId);
    }
    QString text() const {
        return mText.value_or("");
    }
};


class Box
{
public:
    using Ptr = std::shared_ptr<Box>;
    using List = std::vector<Ptr>;

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

    const QString id() const;
    void setId(QString const& id);

    // line in input file where box is defined
    int line() const;

    // pause comment construct several boxes with different content and different
    // read configuration from another box if this is the case
//    void setConfigId(QString configId);
    QString configId() const;
    void setConfigId(QString configId);

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
    int mPauseCounter = 0;
    PauseDisplayMode mPauseMode = PauseDisplayMode::fromPauseOn;
};
