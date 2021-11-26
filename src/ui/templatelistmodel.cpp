/*
    SPDX-FileCopyrightText: 2020-2021 Theresa Gier <theresa@fam-gier.de>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "templatelistmodel.h"

int TemplateListModel::rowCount(const QModelIndex &) const {
    return int(mPresentationList.size());
}

QVariant TemplateListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= int(mPresentationList.size()))
        return QVariant();

    if (role == Qt::DisplayRole){
        QVariant var;
        auto slide = mPresentationList[index.row()];
        var.setValue(slide);
        return var;
    }
    else
        return QVariant();
}

void TemplateListModel::setPresentationList(Presentation::List presentationList) {
    beginResetModel();
    mPresentationList = presentationList;
    endResetModel();
}
