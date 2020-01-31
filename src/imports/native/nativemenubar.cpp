/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Labs Platform module of Qt).
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

#include "nativemenubar.h"
#include "nativemenu.h"

#include <QtCore/qloggingcategory.h>
#include <QtGui/qpa/qplatformmenu.h>
#include <QtGui/qpa/qplatformtheme.h>
#include <QtGui/private/qguiapplication_p.h>
#include <QtQuick/qquickwindow.h>
#include <QtQuick/qquickitem.h>

Q_DECLARE_LOGGING_CATEGORY(lcMenus)

NativeMenuBar::NativeMenuBar(QObject *parent)
    : QObject(parent)
{
    m_handle = QGuiApplicationPrivate::platformTheme()->createPlatformMenuBar();
    qCInfo(lcMenus) << "MenuBar ->" << m_handle;
}

NativeMenuBar::~NativeMenuBar()
{
    for (NativeMenu *menu : qAsConst(m_menus))
        menu->setMenuBar(nullptr);
    delete m_handle;
    m_handle = nullptr;
}

QPlatformMenuBar *NativeMenuBar::handle() const
{
    return m_handle;
}

QQmlListProperty<QObject> NativeMenuBar::data()
{
    return QQmlListProperty<QObject>(this, nullptr, data_append, data_count, data_at, data_clear);
}

QQmlListProperty<NativeMenu> NativeMenuBar::menus()
{
    return QQmlListProperty<NativeMenu>(this, nullptr, menus_append, menus_count, menus_at, menus_clear);
}

QWindow *NativeMenuBar::window() const
{
    return m_window;
}

void NativeMenuBar::setWindow(QWindow *window)
{
    if (m_window == window)
        return;

    if (m_handle)
        m_handle->handleReparent(window);

    m_window = window;
    emit windowChanged();
}

void NativeMenuBar::addMenu(NativeMenu *menu)
{
    insertMenu(m_menus.count(), menu);
}

void NativeMenuBar::insertMenu(int index, NativeMenu *menu)
{
    if (!menu || m_menus.contains(menu))
        return;

    NativeMenu *before = m_menus.value(index);
    m_menus.insert(index, menu);
    m_data.append(menu);
    menu->setMenuBar(this);
    if (m_handle)
        m_handle->insertMenu(menu->create(), before ? before->handle() : nullptr);
    emit menusChanged();
}

void NativeMenuBar::removeMenu(NativeMenu *menu)
{
    if (!menu || !m_menus.removeOne(menu))
        return;

    m_data.removeOne(menu);
    if (m_handle)
        m_handle->removeMenu(menu->handle());
    menu->setMenuBar(nullptr);
    emit menusChanged();
}

void NativeMenuBar::clear()
{
    if (m_menus.isEmpty())
        return;

    for (NativeMenu *menu : qAsConst(m_menus)) {
        m_data.removeOne(menu);
        if (m_handle)
            m_handle->removeMenu(menu->handle());
        menu->setMenuBar(nullptr);
        delete menu;
    }

    m_menus.clear();
    emit menusChanged();
}

void NativeMenuBar::classBegin()
{
}

void NativeMenuBar::componentComplete()
{
    m_complete = true;
    for (NativeMenu *menu : qAsConst(m_menus))
        menu->sync();
    if (!m_window)
        setWindow(findWindow());
}

QWindow *NativeMenuBar::findWindow() const
{
    QObject *obj = parent();
    while (obj) {
        QWindow *window = qobject_cast<QWindow *>(obj);
        if (window)
            return window;
        QQuickItem *item = qobject_cast<QQuickItem *>(obj);
        if (item && item->window())
            return item->window();
        obj = obj->parent();
    }
    return nullptr;
}

void NativeMenuBar::data_append(QQmlListProperty<QObject> *property, QObject *object)
{
    NativeMenuBar *menuBar = static_cast<NativeMenuBar *>(property->object);
    NativeMenu *menu = qobject_cast<NativeMenu *>(object);
    if (menu)
        menuBar->addMenu(menu);
    else
        menuBar->m_data.append(object);
}

int NativeMenuBar::data_count(QQmlListProperty<QObject> *property)
{
    NativeMenuBar *menuBar = static_cast<NativeMenuBar *>(property->object);
    return menuBar->m_data.count();
}

QObject *NativeMenuBar::data_at(QQmlListProperty<QObject> *property, int index)
{
    NativeMenuBar *menuBar = static_cast<NativeMenuBar *>(property->object);
    return menuBar->m_data.value(index);
}

void NativeMenuBar::data_clear(QQmlListProperty<QObject> *property)
{
    NativeMenuBar *menuBar = static_cast<NativeMenuBar *>(property->object);
    menuBar->m_data.clear();
}

void NativeMenuBar::menus_append(QQmlListProperty<NativeMenu> *property, NativeMenu *menu)
{
    NativeMenuBar *menuBar = static_cast<NativeMenuBar *>(property->object);
    menuBar->addMenu(menu);
}

int NativeMenuBar::menus_count(QQmlListProperty<NativeMenu> *property)
{
    NativeMenuBar *menuBar = static_cast<NativeMenuBar *>(property->object);
    return menuBar->m_menus.count();
}

NativeMenu *NativeMenuBar::menus_at(QQmlListProperty<NativeMenu> *property, int index)
{
    NativeMenuBar *menuBar = static_cast<NativeMenuBar *>(property->object);
    return menuBar->m_menus.value(index);
}

void NativeMenuBar::menus_clear(QQmlListProperty<NativeMenu> *property)
{
    NativeMenuBar *menuBar = static_cast<NativeMenuBar *>(property->object);
    menuBar->clear();
}
