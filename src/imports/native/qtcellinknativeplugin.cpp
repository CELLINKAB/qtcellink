/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
**
** This file is part of QtCellink.
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

#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>
#include <QtCore/qloggingcategory.h>

#include "nativemenubar.h"
#include "nativemenu.h"
#include "nativemenuitem.h"
#include "nativemenuseparator.h"

Q_LOGGING_CATEGORY(lcMenus, "qtcellink.menus")

class QtCellinkNativePlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtCellinkNativePlugin(QObject *parent = nullptr);
    void registerTypes(const char *uri) override;
};

QtCellinkNativePlugin::QtCellinkNativePlugin(QObject *parent) : QQmlExtensionPlugin(parent)
{
}

void QtCellinkNativePlugin::registerTypes(const char *uri)
{
    qmlRegisterType<NativeMenu>(uri, 1, 0, "NativeMenu");
    qmlRegisterType<NativeMenuBar>(uri, 1, 0, "NativeMenuBar");
    qmlRegisterType<NativeMenuItem>(uri, 1, 0, "NativeMenuItem");
    qmlRegisterType<NativeMenuSeparator>(uri, 1, 0, "NativeMenuSeparator");
}

#include "qtcellinknativeplugin.moc"
