/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
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

#include "nativemenuitem.h"
#include "nativemenu.h"
#include "iconloader.h"

#include <QtGui/qicon.h>
#include <QtGui/qkeysequence.h>
#include <QtGui/qpa/qplatformtheme.h>
#include <QtGui/private/qguiapplication_p.h>
#include <QtQuickTemplates2/private/qquickaction_p.h>

NativeMenuItem::NativeMenuItem(QObject *parent)
    : QObject(parent)
{
}

NativeMenuItem::~NativeMenuItem()
{
    if (m_menu)
        m_menu->removeItem(this);
    delete m_iconLoader;
    m_iconLoader = nullptr;
    delete m_handle;
    m_handle = nullptr;
}

QPlatformMenuItem *NativeMenuItem::handle() const
{
    return m_handle;
}

QPlatformMenuItem *NativeMenuItem::create()
{
    if (!m_handle && m_menu && m_menu->handle()) {
        m_handle = m_menu->handle()->createMenuItem();

        // TODO: implement QCocoaMenu::createMenuItem()
        if (!m_handle)
            m_handle = QGuiApplicationPrivate::platformTheme()->createPlatformMenuItem();

        if (m_handle) {
            connect(m_handle, &QPlatformMenuItem::activated, this, &NativeMenuItem::activate);
            connect(m_handle, &QPlatformMenuItem::hovered, this, &NativeMenuItem::hovered);
        }
    }
    return m_handle;
}

void NativeMenuItem::sync()
{
    if (!m_complete || !create())
        return;

    m_handle->setEnabled(isEnabled());
    m_handle->setVisible(isVisible());
    m_handle->setIsSeparator(m_separator);
    m_handle->setCheckable(m_checkable);
    m_handle->setChecked(m_checked);
    m_handle->setRole(m_role);
    m_handle->setText(m_text);
    m_handle->setFont(m_font);
    if (m_subMenu && m_subMenu->handle())
        m_handle->setMenu(m_subMenu->handle());

#if QT_CONFIG(shortcut)
    QKeySequence sequence;
    if (m_shortcut.type() == QVariant::Int)
        sequence = QKeySequence(static_cast<QKeySequence::StandardKey>(m_shortcut.toInt()));
    else
        sequence = QKeySequence::fromString(m_shortcut.toString());
    m_handle->setShortcut(sequence.toString());
#endif

    if (m_menu && m_menu->handle())
        m_menu->handle()->syncMenuItem(m_handle);
}

NativeMenu *NativeMenuItem::menu() const
{
    return m_menu;
}

void NativeMenuItem::setMenu(NativeMenu *menu)
{
    if (m_menu == menu)
        return;

    m_menu = menu;
    emit menuChanged();
}

NativeMenu *NativeMenuItem::subMenu() const
{
    return m_subMenu;
}

void NativeMenuItem::setSubMenu(NativeMenu *menu)
{
    if (m_subMenu == menu)
        return;

    m_subMenu = menu;
    sync();
    emit subMenuChanged();
}

bool NativeMenuItem::isEnabled() const
{
    return m_enabled;
}

void NativeMenuItem::setEnabled(bool enabled)
{
    if (m_enabled == enabled)
        return;

    bool wasEnabled = isEnabled();
    m_enabled = enabled;
    sync();
    if (isEnabled() != wasEnabled)
        emit enabledChanged();
}

bool NativeMenuItem::isVisible() const
{
    return m_visible;
}

void NativeMenuItem::setVisible(bool visible)
{
    if (m_visible == visible)
        return;

    bool wasVisible = isVisible();
    m_visible = visible;
    sync();
    if (isVisible() != wasVisible)
        emit visibleChanged();
}

bool NativeMenuItem::isSeparator() const
{
    return m_separator;
}

void NativeMenuItem::setSeparator(bool separator)
{
    if (m_separator == separator)
        return;

    m_separator = separator;
    sync();
    emit separatorChanged();
}

bool NativeMenuItem::isCheckable() const
{
    return m_checkable;
}

void NativeMenuItem::setCheckable(bool checkable)
{
    if (m_checkable == checkable)
        return;

    m_checkable = checkable;
    if (m_action)
        m_action->setCheckable(checkable);
    sync();
    emit checkableChanged();
}

bool NativeMenuItem::isChecked() const
{
    return m_checked;
}

void NativeMenuItem::setChecked(bool checked)
{
    if (m_checked == checked)
        return;

    if (checked && !m_checkable)
        setCheckable(true);

    m_checked = checked;
    if (m_action)
        m_action->setChecked(checked);
    sync();
    emit checkedChanged();
}

QPlatformMenuItem::MenuRole NativeMenuItem::role() const
{
    return m_role;
}

void NativeMenuItem::setRole(QPlatformMenuItem::MenuRole role)
{
    if (m_role == role)
        return;

    m_role = role;
    sync();
    emit roleChanged();
}

QString NativeMenuItem::text() const
{
    return m_text;
}

void NativeMenuItem::setText(const QString &text)
{
    if (m_text == text)
        return;

    m_text = text;
    sync();
    emit textChanged();
}

QVariant NativeMenuItem::shortcut() const
{
    return m_shortcut;
}

void NativeMenuItem::setShortcut(const QVariant& shortcut)
{
    if (m_shortcut == shortcut)
        return;

    m_shortcut = shortcut;
    sync();
    emit shortcutChanged();
}

QFont NativeMenuItem::font() const
{
    return m_font;
}

void NativeMenuItem::setFont(const QFont& font)
{
    if (m_font == font)
        return;

    m_font = font;
    sync();
    emit fontChanged();
}

QQuickIcon NativeMenuItem::icon() const
{
    if (!m_iconLoader)
        return QQuickIcon();

    return m_iconLoader->icon();
}

void NativeMenuItem::setIcon(const QQuickIcon &icon)
{
    if (iconLoader()->icon() == icon)
        return;

    iconLoader()->setIcon(icon);
    emit iconChanged();
}

QQuickAction *NativeMenuItem::action() const
{
    return m_action;
}

void NativeMenuItem::setAction(QQuickAction *action)
{
    if (m_action == action)
        return;

    if (QQuickAction *oldAction = m_action) {
        disconnect(oldAction, &QQuickAction::triggered, this, &NativeMenuItem::triggered);
        disconnect(oldAction, &QQuickAction::textChanged, this, &NativeMenuItem::setText);
        disconnect(oldAction, &QQuickAction::enabledChanged, this, &NativeMenuItem::setEnabled);
        disconnect(oldAction, &QQuickAction::checkedChanged, this, &NativeMenuItem::setChecked);
        disconnect(oldAction, &QQuickAction::checkableChanged, this, &NativeMenuItem::setCheckable);
        disconnect(oldAction, &QQuickAction::shortcutChanged, this, &NativeMenuItem::setShortcut);
    }

    if (action) {
        connect(action, &QQuickAction::triggered, this, &NativeMenuItem::triggered);
        connect(action, &QQuickAction::textChanged, this, &NativeMenuItem::setText);
        connect(action, &QQuickAction::enabledChanged, this, &NativeMenuItem::setEnabled);
        connect(action, &QQuickAction::checkedChanged, this, &NativeMenuItem::setChecked);
        connect(action, &QQuickAction::checkableChanged, this, &NativeMenuItem::setCheckable);
        connect(action, &QQuickAction::shortcutChanged, this, &NativeMenuItem::setShortcut);

        setText(action->text());
        setChecked(action->isChecked());
        setCheckable(action->isCheckable());
        setEnabled(action->isEnabled());
    }

    m_action = action;
    sync();
    emit actionChanged();
}

void NativeMenuItem::toggle()
{
    if (m_checkable)
        setChecked(!m_checked);
}

void NativeMenuItem::classBegin()
{
}

void NativeMenuItem::componentComplete()
{
    if (m_handle && m_iconLoader)
        m_iconLoader->setEnabled(true);
    m_complete = true;
    sync();
}

IconLoader *NativeMenuItem::iconLoader() const
{
    if (!m_iconLoader) {
        NativeMenuItem *that = const_cast<NativeMenuItem *>(this);
        static int slot = staticMetaObject.indexOfSlot("updateIcon()");
        m_iconLoader = new IconLoader(slot, that);
        m_iconLoader->setEnabled(m_complete);
    }
    return m_iconLoader;
}

void NativeMenuItem::activate()
{
    toggle();
    if (m_action && m_action->isEnabled())
        m_action->trigger(this);
    else if (m_enabled)
        emit triggered();
}

void NativeMenuItem::updateIcon()
{
    if (!m_handle || !m_iconLoader)
        return;

    m_handle->setIcon(m_iconLoader->toQIcon());
    sync();
}
