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

#include "qquickplatformmenuitem_p.h"
#include "qquickplatformmenu_p.h"
#include "qquickplatformmenuitemgroup_p.h"
#include "qquickplatformiconloader_p.h"

#include <QtGui/qicon.h>
#include <QtGui/qkeysequence.h>
#include <QtGui/qpa/qplatformtheme.h>
#include <QtGui/private/qguiapplication_p.h>
#include <QtQuickTemplates2/private/qquickaction_p.h>

/*!
    \qmltype MenuItem
    \inherits QtObject
    \instantiates QQuickPlatformMenuItem
    \inqmlmodule Qt.labs.platform
    \since 5.8
    \brief A native menu item.

    The MenuItem type provides a QML API for native platform menu items.

    \image qtlabsplatform-menu.png

    A menu item consists of an \l {iconSource}{icon}, \l text, and \l shortcut.

    \code
    Menu {
        id: zoomMenu

        MenuItem {
            text: qsTr("Zoom In")
            shortcut: StandardKey.ZoomIn
            onTriggered: zoomIn()
        }

        MenuItem {
            text: qsTr("Zoom Out")
            shortcut: StandardKey.ZoomOut
            onTriggered: zoomOut()
        }
    }
    \endcode

    \labs

    \sa Menu, MenuItemGroup
*/

/*!
    \qmlsignal Qt.labs.platform::MenuItem::triggered()

    This signal is emitted when the menu item is triggered by the user.
*/

/*!
    \qmlsignal Qt.labs.platform::MenuItem::hovered()

    This signal is emitted when the menu item is hovered by the user.
*/

QQuickPlatformMenuItem::QQuickPlatformMenuItem(QObject *parent)
    : QObject(parent),
      m_complete(false),
      m_enabled(true),
      m_visible(true),
      m_separator(false),
      m_checkable(false),
      m_checked(false),
      m_role(QPlatformMenuItem::TextHeuristicRole),
      m_action(nullptr),
      m_menu(nullptr),
      m_subMenu(nullptr),
      m_group(nullptr),
      m_iconLoader(nullptr),
      m_handle(nullptr)
{
}

QQuickPlatformMenuItem::~QQuickPlatformMenuItem()
{
    if (m_menu)
        m_menu->removeItem(this);
    if (m_group)
        m_group->removeItem(this);
    delete m_iconLoader;
    m_iconLoader = nullptr;
    delete m_handle;
    m_handle = nullptr;
}

QPlatformMenuItem *QQuickPlatformMenuItem::handle() const
{
    return m_handle;
}

QPlatformMenuItem *QQuickPlatformMenuItem::create()
{
    if (!m_handle && m_menu && m_menu->handle()) {
        m_handle = m_menu->handle()->createMenuItem();

        // TODO: implement QCocoaMenu::createMenuItem()
        if (!m_handle)
            m_handle = QGuiApplicationPrivate::platformTheme()->createPlatformMenuItem();

        if (m_handle) {
            connect(m_handle, &QPlatformMenuItem::activated, this, &QQuickPlatformMenuItem::activate);
            connect(m_handle, &QPlatformMenuItem::hovered, this, &QQuickPlatformMenuItem::hovered);
        }
    }
    return m_handle;
}

void QQuickPlatformMenuItem::sync()
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
    m_handle->setHasExclusiveGroup(m_group && m_group->isExclusive());
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

/*!
    \readonly
    \qmlproperty Menu Qt.labs.platform::MenuItem::menu

    This property holds the menu that the item belongs to, or \c null if the
    item is not in a menu.
*/
QQuickPlatformMenu *QQuickPlatformMenuItem::menu() const
{
    return m_menu;
}

void QQuickPlatformMenuItem::setMenu(QQuickPlatformMenu *menu)
{
    if (m_menu == menu)
        return;

    m_menu = menu;
    emit menuChanged();
}

/*!
    \readonly
    \qmlproperty Menu Qt.labs.platform::MenuItem::subMenu

    This property holds the sub-menu that the item contains, or \c null if
    the item is not a sub-menu item.
*/
QQuickPlatformMenu *QQuickPlatformMenuItem::subMenu() const
{
    return m_subMenu;
}

void QQuickPlatformMenuItem::setSubMenu(QQuickPlatformMenu *menu)
{
    if (m_subMenu == menu)
        return;

    m_subMenu = menu;
    sync();
    emit subMenuChanged();
}

/*!
    \qmlproperty MenuItemGroup Qt.labs.platform::MenuItem::group

    This property holds the group that the item belongs to, or \c null if the
    item is not in a group.
*/
QQuickPlatformMenuItemGroup *QQuickPlatformMenuItem::group() const
{
    return m_group;
}

void QQuickPlatformMenuItem::setGroup(QQuickPlatformMenuItemGroup *group)
{
    if (m_group == group)
        return;

    bool wasEnabled = isEnabled();
    bool wasVisible = isVisible();

    if (group)
        group->addItem(this);

    m_group = group;
    sync();
    emit groupChanged();

    if (isEnabled() != wasEnabled)
        emit enabledChanged();
    if (isVisible() != wasVisible)
        emit visibleChanged();
}

/*!
    \qmlproperty bool Qt.labs.platform::MenuItem::enabled

    This property holds whether the item is enabled. The default value is \c true.

    Disabled items cannot be triggered by the user. They do not disappear from menus,
    but they are displayed in a way which indicates that they are unavailable. For
    example, they might be displayed using only shades of gray.

    When an item is disabled, it is not possible to trigger it through its \l shortcut.
*/
bool QQuickPlatformMenuItem::isEnabled() const
{
    return m_enabled && (!m_group || m_group->isEnabled());
}

void QQuickPlatformMenuItem::setEnabled(bool enabled)
{
    if (m_enabled == enabled)
        return;

    bool wasEnabled = isEnabled();
    m_enabled = enabled;
    sync();
    if (isEnabled() != wasEnabled)
        emit enabledChanged();
}

/*!
    \qmlproperty bool Qt.labs.platform::MenuItem::visible

    This property holds whether the item is visible. The default value is \c true.
*/
bool QQuickPlatformMenuItem::isVisible() const
{
    return m_visible && (!m_group || m_group->isVisible());
}

void QQuickPlatformMenuItem::setVisible(bool visible)
{
    if (m_visible == visible)
        return;

    bool wasVisible = isVisible();
    m_visible = visible;
    sync();
    if (isVisible() != wasVisible)
        emit visibleChanged();
}

/*!
    \qmlproperty bool Qt.labs.platform::MenuItem::separator

    This property holds whether the item is a separator line. The default value
    is \c false.

    \sa MenuSeparator
*/
bool QQuickPlatformMenuItem::isSeparator() const
{
    return m_separator;
}

void QQuickPlatformMenuItem::setSeparator(bool separator)
{
    if (m_separator == separator)
        return;

    m_separator = separator;
    sync();
    emit separatorChanged();
}

/*!
    \qmlproperty bool Qt.labs.platform::MenuItem::checkable

    This property holds whether the item is checkable.

    A checkable menu item has an on/off state. For example, in a word processor,
    a "Bold" menu item may be either on or off. A menu item that is not checkable
    is a command item that is simply executed, e.g. file save.

    The default value is \c false.

    \sa checked, MenuItemGroup
*/
bool QQuickPlatformMenuItem::isCheckable() const
{
    return m_checkable;
}

void QQuickPlatformMenuItem::setCheckable(bool checkable)
{
    if (m_checkable == checkable)
        return;

    m_checkable = checkable;
    if (m_action)
        m_action->setCheckable(checkable);
    sync();
    emit checkableChanged();
}

/*!
    \qmlproperty bool Qt.labs.platform::MenuItem::checked

    This property holds whether the item is checked (on) or unchecked (off).
    The default value is \c false.

    \sa checkable, MenuItemGroup
*/
bool QQuickPlatformMenuItem::isChecked() const
{
    return m_checked;
}

void QQuickPlatformMenuItem::setChecked(bool checked)
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

/*!
    \qmlproperty enumeration Qt.labs.platform::MenuItem::role

    This property holds the role of the item. The role determines whether
    the item should be placed into the application menu on macOS.

    Available values:
    \value MenuItem.NoRole The item should not be put into the application menu
    \value MenuItem.TextHeuristicRole The item should be put in the application menu based on the action's text (default)
    \value MenuItem.ApplicationSpecificRole The item should be put in the application menu with an application-specific role
    \value MenuItem.AboutQtRole The item handles the "About Qt" menu item.
    \value MenuItem.AboutRole The item should be placed where the "About" menu item is in the application menu. The text of
           the menu item will be set to "About <application name>". The application name is fetched from the
           \c{Info.plist} file in the application's bundle (See \l{Qt for macOS - Deployment}).
    \value MenuItem.PreferencesRole The item should be placed where the "Preferences..." menu item is in the application menu.
    \value MenuItem.QuitRole The item should be placed where the Quit menu item is in the application menu.

    Specifying the role only has effect on items that are in the immediate
    menus of a menubar, not in the submenus of those menus. For example, if
    you have a "File" menu in your menubar and the "File" menu has a submenu,
    specifying a role for the items in that submenu has no effect. They will
    never be moved to the application menu.
*/
QPlatformMenuItem::MenuRole QQuickPlatformMenuItem::role() const
{
    return m_role;
}

void QQuickPlatformMenuItem::setRole(QPlatformMenuItem::MenuRole role)
{
    if (m_role == role)
        return;

    m_role = role;
    sync();
    emit roleChanged();
}

/*!
    \qmlproperty string Qt.labs.platform::MenuItem::text

    This property holds the menu item's text.
*/
QString QQuickPlatformMenuItem::text() const
{
    return m_text;
}

void QQuickPlatformMenuItem::setText(const QString &text)
{
    if (m_text == text)
        return;

    m_text = text;
    sync();
    emit textChanged();
}

/*!
    \qmlproperty url Qt.labs.platform::MenuItem::iconSource
    \deprecated Use icon.source instead
*/
QUrl QQuickPlatformMenuItem::iconSource() const
{
    return icon().source();
}

void QQuickPlatformMenuItem::setIconSource(const QUrl& source)
{
    QQuickPlatformIcon newIcon = icon();
    if (source == newIcon.source())
        return;

    newIcon.setSource(source);
    iconLoader()->setIcon(newIcon);
    emit iconSourceChanged();
}

/*!
    \qmlproperty string Qt.labs.platform::MenuItem::iconName
    \deprecated Use icon.name instead
*/
QString QQuickPlatformMenuItem::iconName() const
{
    return icon().name();
}

void QQuickPlatformMenuItem::setIconName(const QString& name)
{
    QQuickPlatformIcon newIcon = icon();
    if (name == newIcon.name())
        return;

    newIcon.setName(name);
    iconLoader()->setIcon(newIcon);
    emit iconNameChanged();
}

/*!
    \qmlproperty keysequence Qt.labs.platform::MenuItem::shortcut

    This property holds the menu item's shortcut.

    The shortcut key sequence can be set to one of the
    \l{QKeySequence::StandardKey}{standard keyboard shortcuts}, or it can be
    specified by a string containing a sequence of up to four key presses
    that are needed to \l{triggered}{trigger} the shortcut.

    The default value is an empty key sequence.

    \code
    MenuItem {
        shortcut: "Ctrl+E,Ctrl+W"
        onTriggered: edit.wrapMode = TextEdit.Wrap
    }
    \endcode
*/
QVariant QQuickPlatformMenuItem::shortcut() const
{
    return m_shortcut;
}

void QQuickPlatformMenuItem::setShortcut(const QVariant& shortcut)
{
    if (m_shortcut == shortcut)
        return;

    m_shortcut = shortcut;
    sync();
    emit shortcutChanged();
}

/*!
    \qmlproperty font Qt.labs.platform::MenuItem::font

    This property holds the menu item's font.

    \sa text
*/
QFont QQuickPlatformMenuItem::font() const
{
    return m_font;
}

void QQuickPlatformMenuItem::setFont(const QFont& font)
{
    if (m_font == font)
        return;

    m_font = font;
    sync();
    emit fontChanged();
}

/*!
    \since Qt.labs.platform 1.1 (Qt 5.12)
    \qmlpropertygroup Qt.labs.platform::MenuItem::icon
    \qmlproperty url Qt.labs.platform::MenuItem::icon.source
    \qmlproperty string Qt.labs.platform::MenuItem::icon.name
    \qmlproperty bool Qt.labs.platform::MenuItem::icon.mask

    This property holds the menu item's icon.

    \code
    MenuItem {
        icon.mask: true
        icon.name: "edit-undo"
        icon.source: "qrc:/images/undo.png"
    }
    \endcode

    \sa QIcon::fromTheme()
*/
QQuickPlatformIcon QQuickPlatformMenuItem::icon() const
{
    if (!m_iconLoader)
        return QQuickPlatformIcon();

    return m_iconLoader->icon();
}

void QQuickPlatformMenuItem::setIcon(const QQuickPlatformIcon &icon)
{
    if (iconLoader()->icon() == icon)
        return;

    iconLoader()->setIcon(icon);
    emit iconChanged();
}

QQuickAction *QQuickPlatformMenuItem::action() const
{
    return m_action;
}

void QQuickPlatformMenuItem::setAction(QQuickAction *action)
{
    if (m_action == action)
        return;

    if (QQuickAction *oldAction = m_action) {
        disconnect(oldAction, &QQuickAction::triggered, this, &QQuickPlatformMenuItem::triggered);
        disconnect(oldAction, &QQuickAction::textChanged, this, &QQuickPlatformMenuItem::setText);
        disconnect(oldAction, &QQuickAction::enabledChanged, this, &QQuickPlatformMenuItem::setEnabled);
        disconnect(oldAction, &QQuickAction::checkedChanged, this, &QQuickPlatformMenuItem::setChecked);
        disconnect(oldAction, &QQuickAction::checkableChanged, this, &QQuickPlatformMenuItem::setCheckable);
        disconnect(oldAction, &QQuickAction::shortcutChanged, this, &QQuickPlatformMenuItem::setShortcut);
    }

    if (action) {
        connect(action, &QQuickAction::triggered, this, &QQuickPlatformMenuItem::triggered);
        connect(action, &QQuickAction::textChanged, this, &QQuickPlatformMenuItem::setText);
        connect(action, &QQuickAction::enabledChanged, this, &QQuickPlatformMenuItem::setEnabled);
        connect(action, &QQuickAction::checkedChanged, this, &QQuickPlatformMenuItem::setChecked);
        connect(action, &QQuickAction::checkableChanged, this, &QQuickPlatformMenuItem::setCheckable);
        connect(action, &QQuickAction::shortcutChanged, this, &QQuickPlatformMenuItem::setShortcut);

        setText(action->text());
        setChecked(action->isChecked());
        setCheckable(action->isCheckable());
        setEnabled(action->isEnabled());
    }

    m_action = action;
    sync();
    emit actionChanged();
}

/*!
    \qmlmethod void Qt.labs.platform::MenuItem::toggle()

    Toggles the \l checked state to its opposite state.
*/
void QQuickPlatformMenuItem::toggle()
{
    if (m_checkable)
        setChecked(!m_checked);
}

void QQuickPlatformMenuItem::classBegin()
{
}

void QQuickPlatformMenuItem::componentComplete()
{
    if (m_handle && m_iconLoader)
        m_iconLoader->setEnabled(true);
    m_complete = true;
    sync();
}

QQuickPlatformIconLoader *QQuickPlatformMenuItem::iconLoader() const
{
    if (!m_iconLoader) {
        QQuickPlatformMenuItem *that = const_cast<QQuickPlatformMenuItem *>(this);
        static int slot = staticMetaObject.indexOfSlot("updateIcon()");
        m_iconLoader = new QQuickPlatformIconLoader(slot, that);
        m_iconLoader->setEnabled(m_complete);
    }
    return m_iconLoader;
}

void QQuickPlatformMenuItem::activate()
{
    toggle();
    if (m_action && m_action->isEnabled())
        m_action->trigger(this);
    else if (m_enabled)
        emit triggered();
}

void QQuickPlatformMenuItem::updateIcon()
{
    if (!m_handle || !m_iconLoader)
        return;

    m_handle->setIcon(m_iconLoader->toQIcon());
    sync();
}