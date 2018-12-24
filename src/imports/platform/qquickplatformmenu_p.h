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

#ifndef QQUICKPLATFORMMENU_P_H
#define QQUICKPLATFORMMENU_P_H

#include <QtCore/qobject.h>
#include <QtCore/qurl.h>
#include <QtGui/qfont.h>
#include <QtGui/qpa/qplatformmenu.h>
#include <QtQml/qqmlparserstatus.h>
#include <QtQml/qqmllist.h>
#include <QtQml/qqml.h>

#include "qquickplatformicon_p.h"

QT_BEGIN_NAMESPACE

class QIcon;
class QWindow;
class QQuickItem;
class QQuickAction;
class QPlatformMenu;
class QQmlV4Function;
class QQuickPlatformMenuBar;
class QQuickPlatformMenuItem;
class QQuickPlatformIconLoader;

class QQuickPlatformMenu : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QQmlListProperty<QObject> data READ data FINAL)
    Q_PROPERTY(QQmlListProperty<QQuickPlatformMenuItem> items READ items NOTIFY itemsChanged FINAL)
    Q_PROPERTY(QQuickPlatformMenuBar *menuBar READ menuBar NOTIFY menuBarChanged FINAL)
    Q_PROPERTY(QQuickPlatformMenu *parentMenu READ parentMenu NOTIFY parentMenuChanged FINAL)
    Q_PROPERTY(QQuickPlatformMenuItem *menuItem READ menuItem CONSTANT FINAL)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged FINAL)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged FINAL)
    Q_PROPERTY(int minimumWidth READ minimumWidth WRITE setMinimumWidth NOTIFY minimumWidthChanged FINAL)
    Q_PROPERTY(QPlatformMenu::MenuType type READ type WRITE setType NOTIFY typeChanged FINAL)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QUrl iconSource READ iconSource WRITE setIconSource NOTIFY iconSourceChanged FINAL)
    Q_PROPERTY(QString iconName READ iconName WRITE setIconName NOTIFY iconNameChanged FINAL)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged FINAL)
    Q_PROPERTY(QQuickPlatformIcon icon READ icon WRITE setIcon NOTIFY iconChanged FINAL REVISION 1)
    Q_ENUMS(QPlatformMenu::MenuType)
    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit QQuickPlatformMenu(QObject *parent = nullptr);
    ~QQuickPlatformMenu();

    QPlatformMenu *handle() const;
    QPlatformMenu *create();
    void destroy();
    void sync();

    QQmlListProperty<QObject> data();
    QQmlListProperty<QQuickPlatformMenuItem> items();

    QQuickPlatformMenuBar *menuBar() const;
    void setMenuBar(QQuickPlatformMenuBar *menuBar);

    QQuickPlatformMenu *parentMenu() const;
    void setParentMenu(QQuickPlatformMenu *menu);

    QQuickPlatformMenuItem *menuItem() const;

    bool isEnabled() const;
    void setEnabled(bool enabled);

    bool isVisible() const;
    void setVisible(bool visible);

    int minimumWidth() const;
    void setMinimumWidth(int width);

    QPlatformMenu::MenuType type() const;
    void setType(QPlatformMenu::MenuType type);

    QString title() const;
    void setTitle(const QString &title);

    QUrl iconSource() const;
    void setIconSource(const QUrl &source);

    QString iconName() const;
    void setIconName(const QString &name);

    QFont font() const;
    void setFont(const QFont &font);

    QQuickPlatformIcon icon() const;
    void setIcon(const QQuickPlatformIcon &icon);

    Q_INVOKABLE void addItem(QQuickPlatformMenuItem *item);
    Q_INVOKABLE void insertItem(int index, QQuickPlatformMenuItem *item);
    Q_INVOKABLE void removeItem(QQuickPlatformMenuItem *item);

    Q_INVOKABLE void addMenu(QQuickPlatformMenu *menu);
    Q_INVOKABLE void insertMenu(int index, QQuickPlatformMenu *menu);
    Q_INVOKABLE void removeMenu(QQuickPlatformMenu *menu);

    Q_INVOKABLE void addAction(QQuickAction *action);
    Q_INVOKABLE void insertAction(int index, QQuickAction *action);
    Q_INVOKABLE void removeAction(QQuickAction *action);

    Q_INVOKABLE void clear();

public Q_SLOTS:
    void open(QQmlV4Function *args);
    void close();

Q_SIGNALS:
    void aboutToShow();
    void aboutToHide();

    void itemsChanged();
    void menuBarChanged();
    void parentMenuChanged();
    void titleChanged();
    void iconSourceChanged();
    void iconNameChanged();
    void enabledChanged();
    void visibleChanged();
    void minimumWidthChanged();
    void fontChanged();
    void typeChanged();
    Q_REVISION(1) void iconChanged();

protected:
    void classBegin() override;
    void componentComplete() override;

    QQuickPlatformIconLoader *iconLoader() const;

    QWindow *findWindow(QQuickItem *target, QPoint *offset) const;

    static void data_append(QQmlListProperty<QObject> *property, QObject *object);
    static int data_count(QQmlListProperty<QObject> *property);
    static QObject *data_at(QQmlListProperty<QObject> *property, int index);
    static void data_clear(QQmlListProperty<QObject> *property);

    static void items_append(QQmlListProperty<QQuickPlatformMenuItem> *property, QQuickPlatformMenuItem *item);
    static int items_count(QQmlListProperty<QQuickPlatformMenuItem> *property);
    static QQuickPlatformMenuItem *items_at(QQmlListProperty<QQuickPlatformMenuItem> *property, int index);
    static void items_clear(QQmlListProperty<QQuickPlatformMenuItem> *property);

private Q_SLOTS:
    void updateIcon();

private:
    void unparentSubmenus();

    bool m_complete;
    bool m_enabled;
    bool m_visible;
    int m_minimumWidth;
    QPlatformMenu::MenuType m_type;
    QString m_title;
    QFont m_font;
    QList<QObject *> m_data;
    QList<QQuickPlatformMenuItem *> m_items;
    QQuickPlatformMenuBar *m_menuBar;
    QQuickPlatformMenu *m_parentMenu;
    mutable QQuickPlatformMenuItem *m_menuItem;
    mutable QQuickPlatformIconLoader *m_iconLoader;
    QPlatformMenu *m_handle;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickPlatformMenu)
Q_DECLARE_METATYPE(QPlatformMenu::MenuType)

#endif // QQUICKPLATFORMMENU_P_H
