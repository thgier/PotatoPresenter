#ifndef FRAMELISTMODEL_H
#define FRAMELISTMODEL_H
#include <QAbstractListModel>
#include <vector>
#include <memory>
#include "slide.h"

class Presentation;

class SlideListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    SlideListModel(std::shared_ptr<Presentation> presentation, QObject *parent = nullptr)
        : QAbstractListModel(parent), mPresentation(presentation) {}
    SlideListModel(QObject *parent = nullptr)
        : QAbstractListModel(parent){}

    void setPresentation(std::shared_ptr<Presentation> presentation);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
private:
    std::shared_ptr<Presentation> mPresentation = nullptr;
};

#endif // FRAMELISTMODEL_H
