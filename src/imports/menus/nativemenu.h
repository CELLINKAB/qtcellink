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

#ifndef NATIVEMENU_H
#define NATIVEMENU_H

#include <QtCore/qobject.h>
#include <QtCore/qurl.h>
#include <QtGui/qfont.h>
#include <QtGui/qpa/qplatformmenu.h>
#include <QtQml/qqml.h>
#include <QtQml/qqmllist.h>
#include <QtQml/qqmlparserstatus.h>
#include <QtQuickTemplates2/private/qquickicon_p.h>

class QIcon;
class QWindow;
class QQuickItem;
class QQuickAction;
class QPlatformMenu;
class QQmlV4Function;
class NativeMenuBar;
class NativeMenuItem;
class IconLoader;

class NativeMenu : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QQmlListProperty<QObject> data READ data FINAL)
    Q_PROPERTY(QQmlListProperty<NativeMenuItem> items READ items NOTIFY itemsChanged FINAL)
    Q_PROPERTY(NativeMenuBar* menuBar READ menuBar NOTIFY menuBarChanged FINAL)
    Q_PROPERTY(NativeMenu* parentMenu READ parentMenu NOTIFY parentMenuChanged FINAL)
    Q_PROPERTY(NativeMenuItem* menuItem READ menuItem CONSTANT FINAL)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged FINAL)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged FINAL)
    Q_PROPERTY(
        int minimumWidth READ minimumWidth WRITE setMinimumWidth NOTIFY minimumWidthChanged FINAL)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged FINAL)
    Q_PROPERTY(QQuickIcon icon READ icon WRITE setIcon NOTIFY iconChanged FINAL)
    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit NativeMenu(QObject* parent = nullptr);
    ~NativeMenu();

    QPlatformMenu* handle() const;
    QPlatformMenu* create();
    void destroy();
    void sync();

    QQmlListProperty<QObject> data();
    QQmlListProperty<NativeMenuItem> items();

    NativeMenuBar* menuBar() const;
    void setMenuBar(NativeMenuBar* menuBar);

    NativeMenu* parentMenu() const;
    void setParentMenu(NativeMenu* menu);

    NativeMenuItem* menuItem() const;

    bool isEnabled() const;
    void setEnabled(bool enabled);

    bool isVisible() const;
    void setVisible(bool visible);

    int minimumWidth() const;
    void setMinimumWidth(int width);

    QString title() const;
    void setTitle(const QString& title);

    QFont font() const;
    void setFont(const QFont& font);

    QQuickIcon icon() const;
    void setIcon(const QQuickIcon& icon);

    Q_INVOKABLE void addItem(NativeMenuItem* item);
    Q_INVOKABLE void insertItem(int index, NativeMenuItem* item);
    Q_INVOKABLE void removeItem(NativeMenuItem* item);

    Q_INVOKABLE void addMenu(NativeMenu* menu);
    Q_INVOKABLE void insertMenu(int index, NativeMenu* menu);
    Q_INVOKABLE void removeMenu(NativeMenu* menu);

    Q_INVOKABLE void addAction(QQuickAction* action);
    Q_INVOKABLE void insertAction(int index, QQuickAction* action);
    Q_INVOKABLE void removeAction(QQuickAction* action);

    Q_INVOKABLE void clear();

public Q_SLOTS:
    void popup(QQmlV4Function* args);
    void close();

Q_SIGNALS:
    void aboutToShow();
    void aboutToHide();
    void opened();
    void closed();

    void itemsChanged();
    void menuBarChanged();
    void parentMenuChanged();
    void titleChanged();
    void enabledChanged();
    void visibleChanged();
    void minimumWidthChanged();
    void fontChanged();
    void iconChanged();

protected:
    void classBegin() override;
    void componentComplete() override;

    IconLoader* iconLoader() const;

    QWindow* findWindow(QQuickItem* target, QPoint* offset) const;

    static void data_append(QQmlListProperty<QObject>* property, QObject* object);
    static int data_count(QQmlListProperty<QObject>* property);
    static QObject* data_at(QQmlListProperty<QObject>* property, int index);
    static void data_clear(QQmlListProperty<QObject>* property);

    static void items_append(QQmlListProperty<NativeMenuItem>* property, NativeMenuItem* item);
    static int items_count(QQmlListProperty<NativeMenuItem>* property);
    static NativeMenuItem* items_at(QQmlListProperty<NativeMenuItem>* property, int index);
    static void items_clear(QQmlListProperty<NativeMenuItem>* property);

private Q_SLOTS:
    void updateIcon();

private:
    void unparentSubmenus();

    bool m_complete = false;
    bool m_enabled = true;
    bool m_visible = true;
    int m_minimumWidth = -1;
    QString m_title;
    QFont m_font;
    QList<QObject*> m_data;
    QList<NativeMenuItem*> m_items;
    NativeMenuBar* m_menuBar = nullptr;
    NativeMenu* m_parentMenu = nullptr;
    mutable NativeMenuItem* m_menuItem = nullptr;
    mutable IconLoader* m_iconLoader = nullptr;
    QPlatformMenu* m_handle = nullptr;
};

QML_DECLARE_TYPE(NativeMenu)

#endif // NATIVEMENU_H
