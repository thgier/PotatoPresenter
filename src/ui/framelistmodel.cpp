#include "framelistmodel.h"
#include "presentation.h"

int FrameListModel::rowCount(const QModelIndex &) const {
    return int(mPresentation->frameList().vector.size());
}

QVariant FrameListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= int(mPresentation->frameList().vector.size()))
        return QVariant();

    if (role == Qt::DisplayRole){
        QVariant var;
        auto frame = mPresentation->frameList().vector[index.row()];
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

