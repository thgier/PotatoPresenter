#include "framelistmodel.h"

int FrameListModel::rowCount(const QModelIndex &parent) const {
    return int(mPresentation->frames().size());
}

QVariant FrameListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= int(mPresentation->frames().size()))
        return QVariant();

    if (role == Qt::DisplayRole){
        QVariant var;
        auto frame = mPresentation->frames().at(index.row());
        var.setValue(frame);
        return var;
    }
    else
        return QVariant();
}

void FrameListModel::setPresentation(Presentation * presentation){
    if(mPresentation){
        mPresentation->disconnect(this);
    }
    beginResetModel();
    mPresentation = presentation;
    endResetModel();
    connect(mPresentation, &Presentation::frameChanged,
            this, [this](int pageNumber){emit dataChanged(index(pageNumber), index(pageNumber));});
    emit dataChanged(index(0), index(rowCount()));
    connect(mPresentation, &Presentation::presentationChanged,
            this, [this](){
            });

}
