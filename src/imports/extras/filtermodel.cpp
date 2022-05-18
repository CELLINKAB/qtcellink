/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2016 The Qt Company Ltd.
**
** This file is part of QtCellink (based on Qt examples).
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice,
**    this list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice,
**    this list of conditions and the following disclaimer in the documentation
**    and/or other materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors
**    may be used to endorse or promote products derived from this software
**    without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
** POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

#include "filtermodel.h"
#include <QtQml/qqmlengine.h>

FilterModel::FilterModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    connect(this, &QSortFilterProxyModel::rowsInserted, this, &FilterModel::countChanged);
    connect(this, &QSortFilterProxyModel::rowsRemoved, this, &FilterModel::countChanged);
}

int FilterModel::count() const
{
    return rowCount();
}

QObject *FilterModel::source() const
{
    return sourceModel();
}

void FilterModel::setSource(QObject *source)
{
    setSourceModel(qobject_cast<QAbstractItemModel *>(source));
}

FilterModel::FilterRule FilterModel::filterRule() const
{
    return m_filterRule;
}

void FilterModel::setFilterRule(FilterRule rule)
{
    if (m_filterRule == rule)
        return;

    m_filterRule = rule;
    if (m_complete)
        invalidateFilter();
}

QVariant FilterModel::filterValue() const
{
    return m_filterValue;
}

void FilterModel::setFilterValue(const QVariant &value)
{
    if (m_filterValue == value)
        return;

    m_filterValue = value;
    if (m_complete)
        invalidateFilter();
}

int FilterModel::mapToSourceRow(int row) const
{
    return mapToSource(index(row, 0)).row();
}

int FilterModel::mapFromSourceRow(int row) const
{
    return mapFromSource(index(row, 0)).row();
}

QJSValue FilterModel::get(int idx) const
{
    QJSEngine *engine = qmlEngine(this);
    if (!engine || idx < 0 || idx >= count())
        return QJSValue();

    QJSValue value = engine->newObject();
    QHash<int, QByteArray> roles = roleNames();
    QHashIterator<int, QByteArray> it(roles);
    while (it.hasNext()) {
        it.next();
        value.setProperty(QString::fromUtf8(it.value()), data(index(idx, 0), it.key()).toString());
    }
    return value;
}

void FilterModel::classBegin()
{
    m_complete = false;
}

void FilterModel::componentComplete()
{
    m_complete = true;
    invalidateFilter();
}

QHash<int, QByteArray> FilterModel::roleNames() const
{
    QAbstractItemModel *source = sourceModel();
    if (!source)
        return QHash<int, QByteArray>();
    return source->roleNames();
}

bool FilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (!m_filterValue.isValid())
        return true;

    QAbstractItemModel *model = sourceModel();
    QModelIndex sourceIndex = model->index(sourceRow, 0, sourceParent);
    QVariant value = model->data(sourceIndex, filterRole());
    if (!value.isValid())
        return false;

    switch (m_filterRule) {
    case EqualTo:
        return value == m_filterValue;
    case LessThan:
        // Qt 5.15.x does not provide an alternative for the deprecration
        // of this operator. A suggestion is to leave it as it is until
        // the migration to Qt 6 which offers the QVariant::compare function
        return value < m_filterValue;
    case GreaterThan:
        return value > m_filterValue;
    case NotEqualTo:
        return value != m_filterValue;
    default:
        break;
    }
    return false;
}
