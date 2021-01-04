#ifndef FRAMELISTMODEL_H
#define FRAMELISTMODEL_H
#include <QAbstractListModel>
#include <vector>
#include "presentation.h"

using FrameList = std::vector<std::shared_ptr<Frame>>;
class FrameListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    FrameListModel(Presentation *presentation, QObject *parent = nullptr)
        : QAbstractListModel(parent), mPresentation(presentation) {}
    FrameListModel(QObject *parent = nullptr)
        : QAbstractListModel(parent){}

    void setPresentation(std::shared_ptr<Presentation> presentation);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
private:
    std::shared_ptr<Presentation> mPresentation = nullptr;
};

#endif // FRAMELISTMODEL_H
