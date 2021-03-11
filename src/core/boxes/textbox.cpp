#include "textbox.h"

TextBox::TextBox(QString text, BoxStyle style, QString id, int line)
    : Box(style, id, line)
    , mText(text)
{
}

bool TextBox::containsPoint(QPoint point, int margin) const {
    return mTextBoundings.contains(point, margin, geometry());
}

void TextBox::appendText(QString const& text) {
    mText.append(text);
}

QString const& TextBox::text() const {
    return mText;
}
