#include "textbox.h"

TextBox::TextBox(QString text, BoxStyle style, QString id, int line)
    : Box(style, id, line)
    , mText(text)
{
}

void TextBox::appendText(QString const& text) {
    mText.append(text);
}

QString const& TextBox::text() const {
    return mText;
}
