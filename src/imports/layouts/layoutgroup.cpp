/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
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

#include "layoutgroup.h"

#include <QtQuick/private/qquickitem_p.h>
#include <QtQuick/private/qquickitemchangelistener_p.h>
#include <QtQuick/qquickitem.h>

static const QQuickItemPrivate::ChangeTypes LayoutChanges = QQuickItemPrivate::ImplicitWidth
                                                            | QQuickItemPrivate::ImplicitHeight
                                                            | QQuickItemPrivate::Destroyed;

class LayoutGroupPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(LayoutGroup)

public:
    static LayoutGroupPrivate* get(LayoutGroup* group) { return group->d_func(); }

    void update(Qt::Orientations orientations = Qt::Horizontal | Qt::Vertical);

    void addItem(LayoutGroupItem* item);
    void removeItem(LayoutGroupItem* item);
    void clear();

    qreal implicitWidth = 0;
    qreal implicitHeight = 0;
    QList<LayoutGroupItem*> items;
};

class LayoutGroupItemPrivate : public QObjectPrivate, public QQuickItemChangeListener
{
public:
    static LayoutGroupItemPrivate* get(LayoutGroupItem* layoutItem) { return layoutItem->d_func(); }

    void reset();

    void itemImplicitWidthChanged(QQuickItem* item) override;
    void itemImplicitHeightChanged(QQuickItem* item) override;
    void itemDestroyed(QQuickItem* item) override;

    bool hasImplicitWidth = false;
    bool hasImplicitHeight = false;
    qreal implicitWidth = 0;
    qreal implicitHeight = 0;
    QPointer<LayoutGroup> group;
};

static qreal getImplicitWidth(LayoutGroupItem* layoutItem)
{
    LayoutGroupItemPrivate* p = LayoutGroupItemPrivate::get(layoutItem);
    if (p->hasImplicitWidth)
        return std::ceil(p->implicitWidth);
    QQuickItem* item = qobject_cast<QQuickItem*>(layoutItem->parent());
    if (!item)
        return 0;
    return std::ceil(item->implicitWidth());
}

static qreal getImplicitHeight(LayoutGroupItem* layoutItem)
{
    LayoutGroupItemPrivate* p = LayoutGroupItemPrivate::get(layoutItem);
    if (p->hasImplicitHeight)
        return std::ceil(p->implicitHeight);
    QQuickItem* item = qobject_cast<QQuickItem*>(layoutItem->parent());
    if (!item)
        return 0;
    return std::ceil(item->implicitHeight());
}

void LayoutGroupPrivate::update(Qt::Orientations orientations)
{
    Q_Q(LayoutGroup);
    qreal maxWidth = 0;
    qreal maxHeight = 0;

    const bool hor = orientations & Qt::Horizontal;
    const bool ver = orientations & Qt::Vertical;

    if (!items.isEmpty()) {
        LayoutGroupItem* item = items.first();
        if (hor)
            maxWidth = getImplicitWidth(item);
        if (ver)
            maxHeight = getImplicitHeight(item);

        for (int i = 1; i < items.count(); ++i) {
            LayoutGroupItem* item = items.at(i);
            if (hor)
                maxWidth = std::max(maxWidth, getImplicitWidth(item));
            if (ver)
                maxHeight = std::max(maxHeight, getImplicitHeight(item));
        }
    }

    const bool widthChange = hor && !qFuzzyCompare(implicitWidth, maxWidth);
    const bool heightChange = ver && !qFuzzyCompare(implicitHeight, maxHeight);

    if (hor)
        implicitWidth = maxWidth;
    if (ver)
        implicitHeight = maxHeight;

    if (widthChange)
        emit q->implicitWidthChanged();
    if (heightChange)
        emit q->implicitHeightChanged();
}

void LayoutGroupPrivate::addItem(LayoutGroupItem* item)
{
    if (!item || items.contains(item))
        return;

    items.append(item);
    update();
}

void LayoutGroupPrivate::removeItem(LayoutGroupItem* item)
{
    if (!item || !items.contains(item))
        return;

    items.removeOne(item);
    update();
}

LayoutGroup::LayoutGroup(QObject* parent)
    : QObject(*(new LayoutGroupPrivate), parent)
{}

qreal LayoutGroup::implicitWidth() const
{
    Q_D(const LayoutGroup);
    return d->implicitWidth;
}

qreal LayoutGroup::implicitHeight() const
{
    Q_D(const LayoutGroup);
    return d->implicitHeight;
}

LayoutGroupItem* LayoutGroup::qmlAttachedProperties(QObject* object)
{
    return new LayoutGroupItem(object);
}

void LayoutGroup::addItem(QQuickItem* item)
{
    Q_D(LayoutGroup);
    if (!item)
        return;
    d->addItem(static_cast<LayoutGroupItem*>(qmlAttachedPropertiesObject<LayoutGroup>(item, true)));
}

void LayoutGroup::removeItem(QQuickItem* item)
{
    Q_D(LayoutGroup);
    if (!item)
        return;
    d->removeItem(
        static_cast<LayoutGroupItem*>(qmlAttachedPropertiesObject<LayoutGroup>(item, true)));
}

void LayoutGroupItemPrivate::reset()
{
    hasImplicitWidth = false;
    hasImplicitHeight = false;
    implicitWidth = 0;
    implicitHeight = 0;

    if (group)
        LayoutGroupPrivate::get(group)->update();
}

void LayoutGroupItemPrivate::itemImplicitWidthChanged(QQuickItem*)
{
    if (!group)
        return;

    LayoutGroupPrivate::get(group)->update(Qt::Horizontal);
}

void LayoutGroupItemPrivate::itemImplicitHeightChanged(QQuickItem*)
{
    if (!group)
        return;

    LayoutGroupPrivate::get(group)->update(Qt::Vertical);
}

void LayoutGroupItemPrivate::itemDestroyed(QQuickItem*)
{
    reset();
}

LayoutGroupItem::LayoutGroupItem(QObject* parent)
    : QObject(*(new LayoutGroupItemPrivate), parent)
{
    Q_D(LayoutGroupItem);
    if (QQuickItem* item = qobject_cast<QQuickItem*>(parent))
        QQuickItemPrivate::get(item)->addItemChangeListener(d, LayoutChanges);
}

LayoutGroupItem::~LayoutGroupItem()
{
    Q_D(LayoutGroupItem);
    if (QQuickItem* item = qobject_cast<QQuickItem*>(parent()))
        QQuickItemPrivate::get(item)->removeItemChangeListener(d, LayoutChanges);
    setGroup(nullptr);
}

qreal LayoutGroupItem::implicitWidth() const
{
    Q_D(const LayoutGroupItem);
    return d->implicitWidth;
}

void LayoutGroupItem::setImplicitWidth(qreal width)
{
    Q_D(LayoutGroupItem);
    if (d->hasImplicitWidth && qFuzzyCompare(d->implicitWidth, width))
        return;

    d->hasImplicitWidth = true;
    d->implicitWidth = width;
    if (d->group)
        LayoutGroupPrivate::get(d->group)->update(Qt::Horizontal);
    emit implicitWidthChanged();
}

qreal LayoutGroupItem::implicitHeight() const
{
    Q_D(const LayoutGroupItem);
    return d->implicitHeight;
}

void LayoutGroupItem::setImplicitHeight(qreal height)
{
    Q_D(LayoutGroupItem);
    if (d->hasImplicitHeight && qFuzzyCompare(d->implicitHeight, height))
        return;

    d->hasImplicitHeight = true;
    d->implicitHeight = height;
    if (d->group)
        LayoutGroupPrivate::get(d->group)->update(Qt::Vertical);
    emit implicitHeightChanged();
}

LayoutGroup* LayoutGroupItem::group() const
{
    Q_D(const LayoutGroupItem);
    return d->group;
}

void LayoutGroupItem::setGroup(LayoutGroup* group)
{
    Q_D(LayoutGroupItem);
    if (d->group == group)
        return;

    if (d->group)
        LayoutGroupPrivate::get(d->group)->removeItem(this);
    d->group = group;
    if (group)
        LayoutGroupPrivate::get(group)->addItem(this);
    emit groupChanged();
}
