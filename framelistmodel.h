#ifndef FRAMELISTMODEL_H
#define FRAMELISTMODEL_H
#include <QAbstractListModel>
#include <vector>
#include "frame.h"

using FrameList = std::vector<std::shared_ptr<Frame>>;
class FrameListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    FrameListModel(const FrameList frames, QObject *parent = nullptr)
        : QAbstractListModel(parent), mFramesList(frames) {}
    FrameListModel(QObject *parent = nullptr)
        : QAbstractListModel(parent){}

    void setFrames(const FrameList frames);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
//    QVariant headerData(int section, Qt::Orientation orientation,
//                        int role = Qt::DisplayRole) const override;
private:
    FrameList mFramesList;
};

#endif // FRAMELISTMODEL_H
