/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
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
#include <QtCore/qcoreapplication.h>
#include <QtCore/qcommandlineparser.h>
#include <QtCore/qloggingcategory.h>

#include "nativemenubar.h"
#include "nativemenu.h"
#include "nativemenuitem.h"
#include "nativemenuseparator.h"

Q_LOGGING_CATEGORY(lcMenus, "cellink.menus")

class CellinkControlsPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    CellinkControlsPlugin(QObject *parent = nullptr);

    void registerTypes(const char *uri) override;

private:
    QUrl typeUrl(const QString &fileName) const;
};

CellinkControlsPlugin::CellinkControlsPlugin(QObject *parent)
    : QQmlExtensionPlugin(parent)
{
}

static bool useNative()
{
    QCommandLineParser cmdLine;
    QCommandLineOption nativeOption(QStringLiteral("native"));
    QCommandLineOption nonNativeOption(QStringLiteral("no-native"));
    cmdLine.addOptions({nativeOption, nonNativeOption});
    cmdLine.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    cmdLine.process(QCoreApplication::arguments());

#if defined(Q_OS_MACOS) || defined(Q_OS_WIN)
    // native menus by default on macOS and Windows
    return !cmdLine.isSet(nonNativeOption);
#else
    // non-native menus by default on Linux
    return cmdLine.isSet(nativeOption);
#endif
}

void CellinkControlsPlugin::registerTypes(const char *uri)
{
    qmlRegisterType(typeUrl(QStringLiteral("DoubleSpinBox.qml")), uri, 1, 0, "DoubleSpinBox");
    qmlRegisterType(typeUrl(QStringLiteral("SplitView.qml")), uri, 1, 0, "SplitView");
    qmlRegisterType(typeUrl(QStringLiteral("TitleSeparator.qml")), uri, 1, 0, "TitleSeparator");

    if (useNative()) {
        qCInfo(lcMenus) << "Registering native menus";
        qmlRegisterType<NativeMenu>(uri, 1, 0, "Menu");
        qmlRegisterType<NativeMenuBar>(uri, 1, 0, "MenuBar");
        qmlRegisterType<NativeMenuItem>(uri, 1, 0, "MenuItem");
        qmlRegisterType<NativeMenuSeparator>(uri, 1, 0, "MenuSeparator");
    } else {
        qCInfo(lcMenus) << "Registering Qt Quick menus";
        qmlRegisterType(typeUrl(QStringLiteral("Menu.qml")), uri, 1, 0, "Menu");
        qmlRegisterType(typeUrl(QStringLiteral("MenuBar.qml")), uri, 1, 0, "MenuBar");
        qmlRegisterType(typeUrl(QStringLiteral("MenuItem.qml")), uri, 1, 0, "MenuItem");
        qmlRegisterType(typeUrl(QStringLiteral("MenuSeparator.qml")), uri, 1, 0, "MenuSeparator");
    }
}

QUrl CellinkControlsPlugin::typeUrl(const QString &fileName) const
{
    QUrl url = baseUrl();
    url.setPath(url.path() + QLatin1Char('/') + fileName);
    return url;
}

#include "cellinkcontrolsplugin.moc"
