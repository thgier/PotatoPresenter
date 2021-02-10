#ifndef PLAINTEXTBOX_H
#define PLAINTEXTBOX_H

#include "box.h"

class PlainTextBox : public Box
{
public:
    PlainTextBox(QString text, BoxGeometry rect, QString id);
    QString mText;
    QString Text();
    void drawContent(QPainter& painter, std::map<QString, QString> variables) override;
};

#endif // PLAINTEXTBOX_H