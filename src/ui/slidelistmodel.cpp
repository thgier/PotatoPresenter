#include "slidelistmodel.h"
#include "presentation.h"

int SlideListModel::rowCount(const QModelIndex &) const {
    return int(mPresentation->slideList().vector.size());
}

QVariant SlideListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= int(mPresentation->slideList().vector.size()))
        return QVariant();

    if (role == Qt::DisplayRole){
        QVariant var;
        auto slide = mPresentation->slideList().vector[index.row()];
        var.setValue(slide);
        return var;
    }
    else
        return QVariant();
}

void SlideListModel::setPresentation(std::shared_ptr<Presentation> presentation){
    if(mPresentation){
        mPresentation->disconnect(this);
    }
    beginResetModel();
    mPresentation = presentation;
    endResetModel();
    connect(mPresentation.get(), &Presentation::slideChanged,
            this, [this](int pageNumber){Q_EMIT dataChanged(index(pageNumber), index(pageNumber));});
    connect(mPresentation.get(), &Presentation::presentationChanged,
            this, [this](){
            beginResetModel();
            endResetModel();
            });

}
