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

#ifndef TABBAR_H
#define TABBAR_H

#include <QtQuickTemplates2/private/qquicktabbar_p.h>

class TabBarAttached;

class TabBar : public QQuickTabBar
{
    Q_OBJECT

public:
    explicit TabBar(QQuickItem *parent = nullptr);

    static TabBarAttached *qmlAttachedProperties(QObject *object);

protected:
    bool isContent(QQuickItem *item) const override;
};

class TabBarAttached : public QQuickTabBarAttached
{
    Q_OBJECT
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged FINAL)

public:
    explicit TabBarAttached(QObject *parent = nullptr);

    bool isVisible() const;
    void setVisible(bool visible);

signals:
    void visibleChanged();

private:
    bool m_visible = true;
    int m_index = -1;
};

QML_DECLARE_TYPE(TabBar)
QML_DECLARE_TYPEINFO(TabBar, QML_HAS_ATTACHED_PROPERTIES)

#endif // TABBAR_H
