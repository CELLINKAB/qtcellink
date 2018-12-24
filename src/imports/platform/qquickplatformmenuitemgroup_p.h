/****************************************************************************
**
** Copyright (C) 2019 J-P Nurmi <jpnurmi@gmail.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Labs Platform module of Qt).
**
** QtCellink is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.

** QtCellink is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with QtCellink. If not, see <https://www.gnu.org/licenses/>.
**
****************************************************************************/

#ifndef QQUICKPLATFORMMENUITEMGROUP_P_H
#define QQUICKPLATFORMMENUITEMGROUP_P_H

#include <QtCore/qobject.h>
#include <QtCore/qvector.h>
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE

class QQuickPlatformMenuItem;
class QQuickPlatformMenuItemGroupPrivate;

class QQuickPlatformMenuItemGroup : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged FINAL)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged FINAL)
    Q_PROPERTY(bool exclusive READ isExclusive WRITE setExclusive NOTIFY exclusiveChanged FINAL)
    Q_PROPERTY(QQuickPlatformMenuItem *checkedItem READ checkedItem WRITE setCheckedItem NOTIFY checkedItemChanged FINAL)
    Q_PROPERTY(QQmlListProperty<QQuickPlatformMenuItem> items READ items NOTIFY itemsChanged FINAL)

public:
    explicit QQuickPlatformMenuItemGroup(QObject *parent = nullptr);
    ~QQuickPlatformMenuItemGroup();

    bool isEnabled() const;
    void setEnabled(bool enabled);

    bool isVisible() const;
    void setVisible(bool visible);

    bool isExclusive() const;
    void setExclusive(bool exclusive);

    QQuickPlatformMenuItem *checkedItem() const;
    void setCheckedItem(QQuickPlatformMenuItem *item);

    QQmlListProperty<QQuickPlatformMenuItem> items();

    Q_INVOKABLE void addItem(QQuickPlatformMenuItem *item);
    Q_INVOKABLE void removeItem(QQuickPlatformMenuItem *item);
    Q_INVOKABLE void clear();

Q_SIGNALS:
    void triggered(QQuickPlatformMenuItem *item);
    void hovered(QQuickPlatformMenuItem *item);

    void enabledChanged();
    void visibleChanged();
    void exclusiveChanged();
    void checkedItemChanged();
    void itemsChanged();

private:
    QQuickPlatformMenuItem *findCurrent() const;
    void updateCurrent();
    void activateItem();
    void hoverItem();

    static void items_append(QQmlListProperty<QQuickPlatformMenuItem> *prop, QQuickPlatformMenuItem *obj);
    static int items_count(QQmlListProperty<QQuickPlatformMenuItem> *prop);
    static QQuickPlatformMenuItem *items_at(QQmlListProperty<QQuickPlatformMenuItem> *prop, int index);
    static void items_clear(QQmlListProperty<QQuickPlatformMenuItem> *prop);

    bool m_enabled;
    bool m_visible;
    bool m_exclusive;
    QQuickPlatformMenuItem *m_checkedItem;
    QVector<QQuickPlatformMenuItem*> m_items;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickPlatformMenuItemGroup)

#endif // QQUICKPLATFORMMENUITEMGROUP_P_H
