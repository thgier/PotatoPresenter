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
    QColor mColor = Qt::black;
    int mFontSize = 50;
    double mLineSpacing = 1.15;
    FontWeight mFontWeight = FontWeight::normal;
    QString mFont = "sans-serif";
    Qt::Alignment mAlignment = Qt::AlignLeft;
    qreal mOpacity = 1;
    struct {
        std::optional<int> left;
        std::optional<int> top ;
        std::optional<int> width;
        std::optional<int> height;
        std::optional<qreal> angle;
    } mGeometry;
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
    Box(BoxGeometry const& geometry, QString id);

    // Implement this in child classes to draw the box's contents given the passed @p variables
    virtual void drawContent(QPainter& painter, std::map<QString, QString> variables) = 0;
    void drawSelectionFrame(QPainter& painter);
    void drawScaleHandle(QPainter& painter, int size);

    BoxGeometry geometry() const;
    BoxStyle style() const;

    void setGeometry(BoxGeometry const& geometry);
    void setVisibility(bool vis);
    void setMovable(bool move);
    void setBoxStyle(BoxStyle style);
    void setPauseCounter(int counter);

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
    BoxGeometry mGeometry;
    QString mId;
    bool mVisible = true;
    bool mMovable = true;
    int mPauseCounter = 0;
};
