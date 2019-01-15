/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
**
** This file is part of QtCellink.
**
** QtCellink is free software: you can redistribute it and/or modify it
** under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QtCellink is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with QtCellink. If not, see <https://www.gnu.org/licenses/>.
**
****************************************************************************/

#ifndef LAYOUTGROUP_H
#define LAYOUTGROUP_H

#include <QtCore/qobject.h>
#include <QtQml/qqml.h>

class QQuickItem;
class LayoutGroupItem;
class LayoutGroupPrivate;
class LayoutGroupItemPrivate;

class LayoutGroup : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal implicitWidth READ implicitWidth NOTIFY implicitWidthChanged FINAL)
    Q_PROPERTY(qreal implicitHeight READ implicitHeight NOTIFY implicitHeightChanged FINAL)

public:
    explicit LayoutGroup(QObject *parent = nullptr);

    qreal implicitWidth() const;
    qreal implicitHeight() const;

    static LayoutGroupItem *qmlAttachedProperties(QObject *object);

public Q_SLOTS:
    void addItem(QQuickItem *item);
    void removeItem(QQuickItem *item);

Q_SIGNALS:
    void implicitWidthChanged();
    void implicitHeightChanged();

private:
    Q_DISABLE_COPY(LayoutGroup)
    Q_DECLARE_PRIVATE(LayoutGroup)
};

class LayoutGroupItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal implicitWidth READ implicitWidth WRITE setImplicitWidth NOTIFY implicitWidthChanged FINAL)
    Q_PROPERTY(qreal implicitHeight READ implicitHeight WRITE setImplicitHeight NOTIFY implicitHeightChanged FINAL)
    Q_PROPERTY(LayoutGroup *group READ group WRITE setGroup NOTIFY groupChanged FINAL)

public:
    explicit LayoutGroupItem(QObject *parent = nullptr);
    ~LayoutGroupItem();

    qreal implicitWidth() const;
    void setImplicitWidth(qreal width);

    qreal implicitHeight() const;
    void setImplicitHeight(qreal height);

    LayoutGroup *group() const;
    void setGroup(LayoutGroup *group);

Q_SIGNALS:
    void implicitWidthChanged();
    void implicitHeightChanged();
    void groupChanged();

private:
    Q_DISABLE_COPY(LayoutGroupItem)
    Q_DECLARE_PRIVATE(LayoutGroupItem)
};

QML_DECLARE_TYPE(LayoutGroup)
QML_DECLARE_TYPEINFO(LayoutGroup, QML_HAS_ATTACHED_PROPERTIES)

#endif // LAYOUTGROUP_H
