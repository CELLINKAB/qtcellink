/****************************************************************************
**
** Copyright (C) 2019 J-P Nurmi <jpnurmi@gmail.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink.
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

#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>
#include <QtCore/qloggingcategory.h>

#include "qquickplatformmenu_p.h"
#include "qquickplatformmenubar_p.h"
#include "qquickplatformmenuitem_p.h"
#include "qquickplatformmenuitemgroup_p.h"
#include "qquickplatformmenuseparator_p.h"

#include "qquickplatformicon_p.h"

Q_LOGGING_CATEGORY(qtLabsPlatformMenus, "qt.labs.platform.menus")

class CellinkPlatformPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    CellinkPlatformPlugin(QObject *parent = nullptr);
    void registerTypes(const char *uri) override;
};

CellinkPlatformPlugin::CellinkPlatformPlugin(QObject *parent) : QQmlExtensionPlugin(parent)
{
}

void CellinkPlatformPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<QQuickPlatformMenu>(uri, 1, 0, "Menu");
    qmlRegisterType<QQuickPlatformMenuBar>(uri, 1, 0, "MenuBar");
    qmlRegisterType<QQuickPlatformMenuItem>(uri, 1, 0, "MenuItem");
    qmlRegisterType<QQuickPlatformMenuItemGroup>(uri, 1, 0, "MenuItemGroup");
    qmlRegisterType<QQuickPlatformMenuSeparator>(uri, 1, 0, "MenuSeparator");
    qRegisterMetaType<QPlatformMenu::MenuType>();

    qmlRegisterType<QQuickPlatformIcon>();
    qRegisterMetaType<QQuickPlatformIcon>();
}

#include "cellinkplatformplugin.moc"
