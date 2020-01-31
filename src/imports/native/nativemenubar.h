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

#ifndef NATIVEMENUBAR_H
#define NATIVEMENUBAR_H

#include <QtCore/qobject.h>
#include <QtQml/qqmlparserstatus.h>
#include <QtQml/qqmllist.h>
#include <QtQml/qqml.h>

class QWindow;
class QPlatformMenuBar;
class NativeMenu;

class NativeMenuBar : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QQmlListProperty<QObject> data READ data FINAL)
    Q_PROPERTY(QQmlListProperty<NativeMenu> menus READ menus NOTIFY menusChanged FINAL)
    Q_PROPERTY(QWindow *window READ window WRITE setWindow NOTIFY windowChanged FINAL)
    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit NativeMenuBar(QObject *parent = nullptr);
    ~NativeMenuBar();

    QPlatformMenuBar *handle() const;

    QQmlListProperty<QObject> data();
    QQmlListProperty<NativeMenu> menus();

    QWindow *window() const;
    void setWindow(QWindow *window);

    Q_INVOKABLE void addMenu(NativeMenu *menu);
    Q_INVOKABLE void insertMenu(int index, NativeMenu *menu);
    Q_INVOKABLE void removeMenu(NativeMenu *menu);
    Q_INVOKABLE void clear();

Q_SIGNALS:
    void menusChanged();
    void windowChanged();

protected:
    void classBegin() override;
    void componentComplete() override;

    QWindow *findWindow() const;

    static void data_append(QQmlListProperty<QObject> *property, QObject *object);
    static int data_count(QQmlListProperty<QObject> *property);
    static QObject *data_at(QQmlListProperty<QObject> *property, int index);
    static void data_clear(QQmlListProperty<QObject> *property);

    static void menus_append(QQmlListProperty<NativeMenu> *property, NativeMenu *menu);
    static int menus_count(QQmlListProperty<NativeMenu> *property);
    static NativeMenu *menus_at(QQmlListProperty<NativeMenu> *property, int index);
    static void menus_clear(QQmlListProperty<NativeMenu> *property);

private:
    bool m_complete = false;
    QWindow *m_window = nullptr;
    QList<QObject *> m_data;
    QList<NativeMenu *> m_menus;
    QPlatformMenuBar *m_handle = nullptr;
};

QML_DECLARE_TYPE(NativeMenuBar)

#endif // NATIVEMENUBAR_H
