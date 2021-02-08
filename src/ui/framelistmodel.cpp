#include "framelistmodel.h"
#include "presentation.h"

int FrameListModel::rowCount(const QModelIndex &) const {
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

void FrameListModel::setPresentation(std::shared_ptr<Presentation> presentation){
    if(mPresentation){
        mPresentation->disconnect(this);
    }
    beginResetModel();
    mPresentation = presentation;
    endResetModel();
    connect(mPresentation.get(), &Presentation::frameChanged,
            this, [this](int pageNumber){Q_EMIT dataChanged(index(pageNumber), index(pageNumber));});
    connect(mPresentation.get(), &Presentation::presentationChanged,
            this, [this](){
            beginResetModel();
            endResetModel();
            });

}

