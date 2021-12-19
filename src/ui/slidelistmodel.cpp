/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "slidelistmodel.h"
#include "presentation.h"

int SlideListModel::rowCount(const QModelIndex &) const {
    return int(mPresentation->slideList().vector.size());
}

QVariant SlideListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= mPresentation->numberOfSlides())
        return QVariant();

    if (role == Qt::DisplayRole){
        QVariant var;
        auto slide = mPresentation->slideListDefaultApplied().vector[index.row()];
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
    mNumberOfSlides = rowCount();
    connect(mPresentation.get(), &Presentation::slideChanged,
            this, &SlideListModel::slidesChanged);
}

void SlideListModel::slidesChanged(int firstSlide, int lastSlide) {
    if (mPresentation->numberOfSlides() == mNumberOfSlides) {
        Q_EMIT dataChanged(index(firstSlide), index(lastSlide));
        return;
    }
    beginResetModel();
    endResetModel();
    mNumberOfSlides = rowCount();
}


