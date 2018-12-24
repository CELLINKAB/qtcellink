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

#ifndef QQUICKPLATFORMMENUBAR_P_H
#define QQUICKPLATFORMMENUBAR_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qobject.h>
#include <QtQml/qqmlparserstatus.h>
#include <QtQml/qqmllist.h>
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE

class QWindow;
class QPlatformMenuBar;
class QQuickPlatformMenu;

class QQuickPlatformMenuBar : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QQmlListProperty<QObject> data READ data FINAL)
    Q_PROPERTY(QQmlListProperty<QQuickPlatformMenu> menus READ menus NOTIFY menusChanged FINAL)
    Q_PROPERTY(QWindow *window READ window WRITE setWindow NOTIFY windowChanged FINAL)
    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit QQuickPlatformMenuBar(QObject *parent = nullptr);
    ~QQuickPlatformMenuBar();

    QPlatformMenuBar *handle() const;

    QQmlListProperty<QObject> data();
    QQmlListProperty<QQuickPlatformMenu> menus();

    QWindow *window() const;
    void setWindow(QWindow *window);

    Q_INVOKABLE void addMenu(QQuickPlatformMenu *menu);
    Q_INVOKABLE void insertMenu(int index, QQuickPlatformMenu *menu);
    Q_INVOKABLE void removeMenu(QQuickPlatformMenu *menu);
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

    static void menus_append(QQmlListProperty<QQuickPlatformMenu> *property, QQuickPlatformMenu *menu);
    static int menus_count(QQmlListProperty<QQuickPlatformMenu> *property);
    static QQuickPlatformMenu *menus_at(QQmlListProperty<QQuickPlatformMenu> *property, int index);
    static void menus_clear(QQmlListProperty<QQuickPlatformMenu> *property);

private:
    bool m_complete;
    QWindow *m_window;
    QList<QObject *> m_data;
    QList<QQuickPlatformMenu *> m_menus;
    QPlatformMenuBar *m_handle;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickPlatformMenuBar)

#endif // QQUICKPLATFORMMENUBAR_P_H
