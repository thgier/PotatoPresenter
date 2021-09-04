#ifndef TEMPLATELISTMODEL_H
#define TEMPLATELISTMODEL_H
#include <QAbstractListModel>
#include <vector>
#include <memory>
#include "slide.h"
#include "presentation.h"

class TemplateListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    TemplateListModel(Presentation::List presentationList, QObject *parent = nullptr)
        : QAbstractListModel(parent), mPresentationList(presentationList) {}
    TemplateListModel(QObject *parent = nullptr)
        : QAbstractListModel(parent){}

    void setPresentationList(Presentation::List presentationList);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
private:
    Presentation::List mPresentationList;
};

#endif // TEMPLATELISTMODEL_H
