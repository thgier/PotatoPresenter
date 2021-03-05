#pragma once

#include <QRect>
#include <QPainter>
#include "boxgeometry.h"

using Variables = std::map<QString, QString>;

enum FontWeight{
    normal,
    bold
};

struct BoxStyle{
    QString boxClass;
    std::optional<QColor> mColor;
    std::optional<int> mFontSize;
    std::optional<double> mLineSpacing;
    std::optional<FontWeight> mFontWeight;
    std::optional<QString> mFont;
    std::optional<Qt::Alignment> mAlignment;
    std::optional<double> mOpacity;
    BoxGeometry mGeometry;

    QColor color() const {
        return mColor.value_or(Qt::black);
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
    Box(BoxStyle boxStyle, QString id);

    // Implement this in child classes to draw the box's contents given the passed @p variables
    virtual void drawContent(QPainter& painter, std::map<QString, QString> variables) = 0;
    void drawSelectionFrame(QPainter& painter);
    void drawScaleHandle(QPainter& painter, int size);

    BoxStyle const& style() const;
    BoxGeometry const& geometry() const;
    BoxStyle& style();
    BoxGeometry& geometry();

    void setVisibility(bool vis);
    void setMovable(bool move);
    void setBoxStyle(BoxStyle style);
    void setPauseCounter(int counter);
    void setGeometry(BoxGeometry const& geometry);
    void setGeometry(MemberBoxGeometry const& geometry);

    QString id();
    bool pauseCounterSmaller(int counter) const;
    int pauseCounter() const;

protected:
    // Call this in child classes when implemting drawContent to substitute variables (e.g. page number)
    // in text.
    QString substituteVariables(QString text, std::map<QString, QString> variables) const;

    struct PainterTransformScope {
        PainterTransformScope(Box* self, QPainter& painter)
            : mSelf(self)
            , mPainter(painter)
        {
            self->startDraw(painter);
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
    bool mVisible = true;
    bool mMovable = true;
    int mPauseCounter = 0;
};
