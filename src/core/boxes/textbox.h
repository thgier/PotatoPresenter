#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <box.h>

class TextBox : public Box
{
public:
    TextBox(QString text, BoxStyle style, QString id, int line);
    virtual std::shared_ptr<TextBox> clone() = 0;
    void appendText(QString const& text);
    QString const& text() const;

protected:
    QString mText;
};

#endif // TEXTBOX_H
