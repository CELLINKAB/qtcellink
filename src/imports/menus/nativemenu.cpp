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

#include "nativemenu.h"

#include <QtCore/qloggingcategory.h>
#include <QtGui/private/qguiapplication_p.h>
#include <QtGui/private/qhighdpiscaling_p.h>
#include <QtGui/qcursor.h>
#include <QtGui/qicon.h>
#include <QtGui/qpa/qplatformtheme.h>
#include <QtQml/private/qqmlengine_p.h>
#include <QtQml/private/qv4qobjectwrapper_p.h>
#include <QtQml/private/qv4scopedvalue_p.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickrendercontrol.h>
#include <QtQuick/qquickwindow.h>
#include <QtQuickTemplates2/private/qquickaction_p.h>

#include "iconloader.h"
#include "nativemenubar.h"
#include "nativemenuitem.h"

Q_DECLARE_LOGGING_CATEGORY(lcMenus)

NativeMenu::NativeMenu(QObject* parent)
    : QObject(parent)
{}

NativeMenu::~NativeMenu()
{
    if (m_menuBar)
        m_menuBar->removeMenu(this);
    if (m_parentMenu)
        m_parentMenu->removeMenu(this);

    unparentSubmenus();

    delete m_iconLoader;
    m_iconLoader = nullptr;
    delete m_handle;
    m_handle = nullptr;
}

void NativeMenu::unparentSubmenus()
{
    for (NativeMenuItem* item : qAsConst(m_items)) {
        if (NativeMenu* subMenu = item->subMenu())
            subMenu->setParentMenu(nullptr);
        item->setMenu(nullptr);
    }
}

QPlatformMenu* NativeMenu::handle() const
{
    return m_handle;
}

QPlatformMenu* NativeMenu::create()
{
    if (!m_handle) {
        if (m_menuBar && m_menuBar->handle())
            m_handle = m_menuBar->handle()->createMenu();
        else if (m_parentMenu && m_parentMenu->handle())
            m_handle = m_parentMenu->handle()->createSubMenu();

        // TODO: implement ^
        // - QCocoaMenuBar::createMenu()
        // - QCocoaMenu::createSubMenu()
        // - QCocoaSystemTrayIcon::createMenu()
        if (!m_handle)
            m_handle = QGuiApplicationPrivate::platformTheme()->createPlatformMenu();

        qCInfo(lcMenus) << "Menu ->" << m_handle;

        if (m_handle) {
            connect(m_handle, &QPlatformMenu::aboutToShow, this, &NativeMenu::aboutToShow);
            connect(m_handle, &QPlatformMenu::aboutToHide, this, &NativeMenu::aboutToHide);
            connect(m_handle, &QPlatformMenu::aboutToShow, this, &NativeMenu::opened);
            connect(m_handle, &QPlatformMenu::aboutToHide, this, &NativeMenu::closed);

            for (NativeMenuItem* item : qAsConst(m_items))
                m_handle->insertMenuItem(item->create(), nullptr);

            if (m_menuItem) {
                if (QPlatformMenuItem* handle = m_menuItem->create())
                    handle->setMenu(m_handle);
            }
        }
    }
    return m_handle;
}

void NativeMenu::destroy()
{
    if (!m_handle)
        return;

    // Ensure that all submenus are unparented before we are destroyed,
    // so that they don't try to access a destroyed menu.
    unparentSubmenus();

    delete m_handle;
    m_handle = nullptr;
}

void NativeMenu::sync()
{
    if (!m_complete || !create())
        return;

    m_handle->setText(m_title);
    m_handle->setEnabled(m_enabled);
    m_handle->setVisible(m_visible);
    m_handle->setMinimumWidth(m_minimumWidth);
    m_handle->setFont(m_font);

    if (m_menuBar && m_menuBar->handle())
        m_menuBar->handle()->syncMenu(m_handle);

    for (NativeMenuItem* item : qAsConst(m_items))
        item->sync();
}

QQmlListProperty<QObject> NativeMenu::data()
{
    return QQmlListProperty<QObject>(this, nullptr, data_append, data_count, data_at, data_clear);
}

QQmlListProperty<NativeMenuItem> NativeMenu::items()
{
    return QQmlListProperty<NativeMenuItem>(this,
                                            nullptr,
                                            items_append,
                                            items_count,
                                            items_at,
                                            items_clear);
}

NativeMenuBar* NativeMenu::menuBar() const
{
    return m_menuBar;
}

void NativeMenu::setMenuBar(NativeMenuBar* menuBar)
{
    if (m_menuBar == menuBar)
        return;

    m_menuBar = menuBar;
    destroy();
    emit menuBarChanged();
}

NativeMenu* NativeMenu::parentMenu() const
{
    return m_parentMenu;
}

void NativeMenu::setParentMenu(NativeMenu* menu)
{
    if (m_parentMenu == menu)
        return;

    m_parentMenu = menu;
    destroy();
    emit parentMenuChanged();
}

NativeMenuItem* NativeMenu::menuItem() const
{
    if (!m_menuItem) {
        NativeMenu* that = const_cast<NativeMenu*>(this);
        m_menuItem = new NativeMenuItem(that);
        m_menuItem->setSubMenu(that);
        m_menuItem->setText(m_title);
        m_menuItem->setIcon(icon());
        m_menuItem->setVisible(m_visible);
        m_menuItem->setEnabled(m_enabled);
        m_menuItem->componentComplete();
    }
    return m_menuItem;
}

bool NativeMenu::isEnabled() const
{
    return m_enabled;
}

void NativeMenu::setEnabled(bool enabled)
{
    if (m_enabled == enabled)
        return;

    if (m_menuItem)
        m_menuItem->setEnabled(enabled);

    m_enabled = enabled;
    sync();
    emit enabledChanged();
}

bool NativeMenu::isVisible() const
{
    return m_visible;
}

void NativeMenu::setVisible(bool visible)
{
    if (m_visible == visible)
        return;

    if (m_menuItem)
        m_menuItem->setVisible(visible);

    m_visible = visible;
    sync();
    emit visibleChanged();
}

int NativeMenu::minimumWidth() const
{
    return m_minimumWidth;
}

void NativeMenu::setMinimumWidth(int width)
{
    if (m_minimumWidth == width)
        return;

    m_minimumWidth = width;
    sync();
    emit minimumWidthChanged();
}

QString NativeMenu::title() const
{
    return m_title;
}

void NativeMenu::setTitle(const QString& title)
{
    if (m_title == title)
        return;

    if (m_menuItem)
        m_menuItem->setText(title);

    m_title = title;
    sync();
    emit titleChanged();
}

QFont NativeMenu::font() const
{
    return m_font;
}

void NativeMenu::setFont(const QFont& font)
{
    if (m_font == font)
        return;

    m_font = font;
    sync();
    emit fontChanged();
}

QQuickIcon NativeMenu::icon() const
{
    if (!m_iconLoader)
        return QQuickIcon();

    return iconLoader()->icon();
}

void NativeMenu::setIcon(const QQuickIcon& icon)
{
    if (iconLoader()->icon() == icon)
        return;

    if (m_menuItem)
        m_menuItem->setIcon(icon);

    iconLoader()->setIcon(icon);
    emit iconChanged();
}

void NativeMenu::addItem(NativeMenuItem* item)
{
    insertItem(m_items.count(), item);
}

void NativeMenu::insertItem(int index, NativeMenuItem* item)
{
    if (!item || m_items.contains(item))
        return;

    m_items.insert(index, item);
    m_data.append(item);
    item->setMenu(this);
    if (m_handle && item->create()) {
        NativeMenuItem* before = m_items.value(index + 1);
        m_handle->insertMenuItem(item->handle(), before ? before->create() : nullptr);
    }
    sync();
    emit itemsChanged();
}

void NativeMenu::removeItem(NativeMenuItem* item)
{
    if (!item || !m_items.removeOne(item))
        return;

    m_data.removeOne(item);
    if (m_handle)
        m_handle->removeMenuItem(item->handle());
    item->setMenu(nullptr);
    sync();
    emit itemsChanged();
}

void NativeMenu::addMenu(NativeMenu* menu)
{
    insertMenu(m_items.count(), menu);
}

void NativeMenu::insertMenu(int index, NativeMenu* menu)
{
    if (!menu)
        return;

    menu->setParentMenu(this);
    insertItem(index, menu->menuItem());
}

void NativeMenu::removeMenu(NativeMenu* menu)
{
    if (!menu)
        return;

    menu->setParentMenu(nullptr);
    removeItem(menu->menuItem());
}

void NativeMenu::addAction(QQuickAction* action)
{
    insertAction(m_items.count(), action);
}

void NativeMenu::insertAction(int index, QQuickAction* action)
{
    if (!action)
        return;

    NativeMenuItem* item = new NativeMenuItem(this);
    item->setAction(action);
    item->componentComplete();
    insertItem(index, item);
}

void NativeMenu::removeAction(QQuickAction* action)
{
    if (!action)
        return;

    const int count = m_items.count();
    for (int i = 0; i < count; ++i) {
        NativeMenuItem* item = qobject_cast<NativeMenuItem*>(m_items.at(i));
        if (!item || item->action() != action)
            continue;

        removeItem(item);
        break;
    }

    action->deleteLater();
}

void NativeMenu::clear()
{
    if (m_items.isEmpty())
        return;

    for (NativeMenuItem* item : qAsConst(m_items)) {
        m_data.removeOne(item);
        if (m_handle)
            m_handle->removeMenuItem(item->handle());
        item->setMenu(nullptr);
        delete item;
    }

    m_items.clear();
    sync();
    emit itemsChanged();
}

void NativeMenu::popup(QQmlV4Function* args)
{
    if (!m_handle)
        return;

    if (args->length() > 2) {
        args->v4engine()->throwTypeError();
        return;
    }

    QV4::ExecutionEngine* v4 = args->v4engine();
    QV4::Scope scope(v4);

    QQuickItem* targetItem = nullptr;
    if (args->length() > 0) {
        QV4::ScopedValue value(scope, (*args)[0]);
        QV4::Scoped<QV4::QObjectWrapper> object(scope, value->as<QV4::QObjectWrapper>());
        if (object)
            targetItem = qobject_cast<QQuickItem*>(object->object());
    }

    NativeMenuItem* menuItem = nullptr;
    if (args->length() > 1) {
        QV4::ScopedValue value(scope, (*args)[1]);
        QV4::Scoped<QV4::QObjectWrapper> object(scope, value->as<QV4::QObjectWrapper>());
        if (object)
            menuItem = qobject_cast<NativeMenuItem*>(object->object());
    }

    QPoint offset;
    QWindow* window = findWindow(targetItem, &offset);

    QRect targetRect;
    if (targetItem) {
        QRectF sceneBounds = targetItem->mapRectToScene(targetItem->boundingRect());
        targetRect = sceneBounds.toAlignedRect().translated(offset);
    } else {
#if QT_CONFIG(cursor)
        QPoint pos = QCursor::pos();
        if (window)
            pos = window->mapFromGlobal(pos);
        targetRect.moveTo(pos);
#endif
    }
    m_handle->showPopup(window,
                        QHighDpi::toNativePixels(targetRect, window),
                        menuItem ? menuItem->handle() : nullptr);
}

void NativeMenu::close()
{
    if (m_handle)
        m_handle->dismiss();
}

void NativeMenu::classBegin() {}

void NativeMenu::componentComplete()
{
    m_complete = true;
    if (m_handle && m_iconLoader)
        m_iconLoader->setEnabled(true);
    sync();
}

IconLoader* NativeMenu::iconLoader() const
{
    if (!m_iconLoader) {
        NativeMenu* that = const_cast<NativeMenu*>(this);
        static int slot = staticMetaObject.indexOfSlot("updateIcon()");
        m_iconLoader = new IconLoader(slot, that);
        m_iconLoader->setEnabled(m_complete);
    }
    return m_iconLoader;
}

static QWindow* effectiveWindow(QWindow* window, QPoint* offset)
{
    QQuickWindow* quickWindow = qobject_cast<QQuickWindow*>(window);
    if (quickWindow) {
        QWindow* renderWindow = QQuickRenderControl::renderWindowFor(quickWindow, offset);
        if (renderWindow)
            return renderWindow;
    }
    return window;
}

QWindow* NativeMenu::findWindow(QQuickItem* target, QPoint* offset) const
{
    if (target)
        return effectiveWindow(target->window(), offset);

    if (m_menuBar && m_menuBar->window())
        return effectiveWindow(m_menuBar->window(), offset);

    QObject* obj = parent();
    while (obj) {
        QWindow* window = qobject_cast<QWindow*>(obj);
        if (window)
            return effectiveWindow(window, offset);

        QQuickItem* item = qobject_cast<QQuickItem*>(obj);
        if (item && item->window())
            return effectiveWindow(item->window(), offset);

        obj = obj->parent();
    }
    return nullptr;
}

void NativeMenu::data_append(QQmlListProperty<QObject>* property, QObject* object)
{
    NativeMenu* menu = static_cast<NativeMenu*>(property->object);
    if (NativeMenuItem* item = qobject_cast<NativeMenuItem*>(object))
        menu->addItem(item);
    else if (NativeMenu* subMenu = qobject_cast<NativeMenu*>(object))
        menu->addMenu(subMenu);
    else if (QQuickAction* action = qobject_cast<QQuickAction*>(object))
        menu->addAction(action);
    else
        menu->m_data.append(object);
}

int NativeMenu::data_count(QQmlListProperty<QObject>* property)
{
    NativeMenu* menu = static_cast<NativeMenu*>(property->object);
    return menu->m_data.count();
}

QObject* NativeMenu::data_at(QQmlListProperty<QObject>* property, int index)
{
    NativeMenu* menu = static_cast<NativeMenu*>(property->object);
    return menu->m_data.value(index);
}

void NativeMenu::data_clear(QQmlListProperty<QObject>* property)
{
    NativeMenu* menu = static_cast<NativeMenu*>(property->object);
    menu->m_data.clear();
}

void NativeMenu::items_append(QQmlListProperty<NativeMenuItem>* property, NativeMenuItem* item)
{
    NativeMenu* menu = static_cast<NativeMenu*>(property->object);
    menu->addItem(item);
}

int NativeMenu::items_count(QQmlListProperty<NativeMenuItem>* property)
{
    NativeMenu* menu = static_cast<NativeMenu*>(property->object);
    return menu->m_items.count();
}

NativeMenuItem* NativeMenu::items_at(QQmlListProperty<NativeMenuItem>* property, int index)
{
    NativeMenu* menu = static_cast<NativeMenu*>(property->object);
    return menu->m_items.value(index);
}

void NativeMenu::items_clear(QQmlListProperty<NativeMenuItem>* property)
{
    NativeMenu* menu = static_cast<NativeMenu*>(property->object);
    menu->clear();
}

void NativeMenu::updateIcon()
{
    if (!m_handle || !m_iconLoader)
        return;

    m_handle->setIcon(m_iconLoader->toQIcon());
    sync();
}
