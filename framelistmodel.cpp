#include "framelistmodel.h"

int FrameListModel::rowCount(const QModelIndex &parent) const {
    return int(mFramesList.size());
}

QVariant FrameListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= int(mFramesList.size()))
        return QVariant();

    if (role == Qt::DisplayRole){
        QVariant var;
        auto frame = mFramesList.at(index.row());
        var.setValue(frame);
        return var;
    }
    else
        return QVariant();
}

void FrameListModel::setFrames(const FrameList frames){
    beginResetModel();
    mFramesList = frames;
    endResetModel();
}
