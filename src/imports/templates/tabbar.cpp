/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Quick Templates 2 module of Qt).
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

#include "tabbar.h"

#include <QtQml/private/qqmlobjectmodel_p.h>

TabBar::TabBar(QQuickItem *parent) : QQuickTabBar(parent)
{
}

TabBarAttached *TabBar::qmlAttachedProperties(QObject *object)
{
    return new TabBarAttached(object);
}

bool TabBar::isContent(QQuickItem *item) const
{
    if (!QQuickTabBar::isContent(item))
        return false;

    TabBarAttached *attached = qobject_cast<TabBarAttached *>(qmlAttachedPropertiesObject<TabBar>(item));
    if (!attached)
        return true;

    return attached->isVisible();
}

TabBarAttached::TabBarAttached(QObject *parent) : QQuickTabBarAttached(parent)
{
}

bool TabBarAttached::isVisible() const
{
    return m_visible;
}

void TabBarAttached::setVisible(bool visible)
{
    if (m_visible == visible)
        return;

    m_visible = visible;

    QQuickItem *item = qobject_cast<QQuickItem *>(parent());
    if (!item)
        return;

    TabBar *tabBar = qobject_cast<TabBar *>(item->parent());
    if (!tabBar)
        return;

    QQmlObjectModel *model = tabBar->contentModel().value<QQmlObjectModel *>();
    if (!model)
        return;

    if (visible) {
        if (m_index != -1)
            model->insert(m_index, item);
    } else {
        m_index = model->indexOf(item, qmlContext(item));
        if (m_index != -1)
            model->remove(m_index);
    }

    emit visibleChanged();
}
