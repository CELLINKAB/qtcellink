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

#ifndef QQUICKPLATFORMMENUITEM_P_H
#define QQUICKPLATFORMMENUITEM_P_H

#include <QtCore/qobject.h>
#include <QtCore/qurl.h>
#include <QtGui/qfont.h>
#include <QtGui/qpa/qplatformmenu.h>
#include <QtQml/qqmlparserstatus.h>
#include <QtQml/qqml.h>

#include "qquickplatformicon_p.h"

QT_BEGIN_NAMESPACE

class QQuickAction;
class QPlatformMenuItem;
class QQuickPlatformMenu;
class QQuickPlatformIconLoader;
class QQuickPlatformMenuItemGroup;

class QQuickPlatformMenuItem : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QQuickPlatformMenu *menu READ menu NOTIFY menuChanged FINAL)
    Q_PROPERTY(QQuickPlatformMenu *subMenu READ subMenu NOTIFY subMenuChanged FINAL)
    Q_PROPERTY(QQuickPlatformMenuItemGroup *group READ group WRITE setGroup NOTIFY groupChanged FINAL)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged FINAL)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged FINAL)
    Q_PROPERTY(bool separator READ isSeparator WRITE setSeparator NOTIFY separatorChanged FINAL)
    Q_PROPERTY(bool checkable READ isCheckable WRITE setCheckable NOTIFY checkableChanged FINAL)
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY checkedChanged FINAL)
    Q_PROPERTY(QPlatformMenuItem::MenuRole role READ role WRITE setRole NOTIFY roleChanged FINAL)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged FINAL)
    Q_PROPERTY(QUrl iconSource READ iconSource WRITE setIconSource NOTIFY iconSourceChanged FINAL)
    Q_PROPERTY(QString iconName READ iconName WRITE setIconName NOTIFY iconNameChanged FINAL)
    Q_PROPERTY(QVariant shortcut READ shortcut WRITE setShortcut NOTIFY shortcutChanged FINAL)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged FINAL)
    Q_PROPERTY(QQuickPlatformIcon icon READ icon WRITE setIcon NOTIFY iconChanged FINAL REVISION 1)
    Q_PROPERTY(QQuickAction *action READ action WRITE setAction NOTIFY actionChanged)
    Q_ENUMS(QPlatformMenuItem::MenuRole)

public:
    explicit QQuickPlatformMenuItem(QObject *parent = nullptr);
    ~QQuickPlatformMenuItem();

    QPlatformMenuItem *handle() const;
    QPlatformMenuItem *create();
    void sync();

    QQuickPlatformMenu *menu() const;
    void setMenu(QQuickPlatformMenu* menu);

    QQuickPlatformMenu *subMenu() const;
    void setSubMenu(QQuickPlatformMenu *menu);

    QQuickPlatformMenuItemGroup *group() const;
    void setGroup(QQuickPlatformMenuItemGroup *group);

    bool isEnabled() const;
    void setEnabled(bool enabled);

    bool isVisible() const;
    void setVisible(bool visible);

    bool isSeparator() const;
    void setSeparator(bool separator);

    bool isCheckable() const;
    void setCheckable(bool checkable);

    bool isChecked() const;
    void setChecked(bool checked);

    QPlatformMenuItem::MenuRole role() const;
    void setRole(QPlatformMenuItem::MenuRole role);

    QString text() const;
    void setText(const QString &text);

    QUrl iconSource() const;
    void setIconSource(const QUrl &source);

    QString iconName() const;
    void setIconName(const QString &name);

    QVariant shortcut() const;
    void setShortcut(const QVariant& shortcut);

    QFont font() const;
    void setFont(const QFont &font);

    QQuickPlatformIcon icon() const;
    void setIcon(const QQuickPlatformIcon &icon);

    QQuickAction *action() const;
    void setAction(QQuickAction *action);

public Q_SLOTS:
    void toggle();

Q_SIGNALS:
    void triggered();
    void hovered();

    void menuChanged();
    void subMenuChanged();
    void groupChanged();
    void enabledChanged();
    void visibleChanged();
    void separatorChanged();
    void checkableChanged();
    void checkedChanged();
    void roleChanged();
    void textChanged();
    void iconSourceChanged();
    void iconNameChanged();
    void shortcutChanged();
    void fontChanged();
    Q_REVISION(1) void iconChanged();
    void actionChanged();

protected:
    void classBegin() override;
    void componentComplete() override;

    QQuickPlatformIconLoader *iconLoader() const;

private Q_SLOTS:
    void activate();
    void updateIcon();

private:
    bool m_complete;
    bool m_enabled;
    bool m_visible;
    bool m_separator;
    bool m_checkable;
    bool m_checked;
    QPlatformMenuItem::MenuRole m_role;
    QString m_text;
    QVariant m_shortcut;
    QFont m_font;
    QQuickAction *m_action;
    QQuickPlatformMenu *m_menu;
    QQuickPlatformMenu *m_subMenu;
    QQuickPlatformMenuItemGroup *m_group;
    mutable QQuickPlatformIconLoader *m_iconLoader;
    QPlatformMenuItem *m_handle;

    friend class QQuickPlatformMenu;
    friend class QQuickPlatformMenuItemGroup;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickPlatformMenuItem)

#endif // QQUICKPLATFORMMENUITEM_P_H
