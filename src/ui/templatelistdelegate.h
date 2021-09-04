#ifndef TEMPLATELISTDELEGATE_H
#define TEMPLATELISTDELEGATE_H

#include <qabstractitemdelegate.h>

class TemplateListDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    TemplateListDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

private:
    int const widthLogical = 1600;
    int const heightLogical = 900;
    int const border = 10;
    double const ratio = 1.0 * widthLogical / heightLogical;

};

#endif // TEMPLATELISTDELEGATE_H
