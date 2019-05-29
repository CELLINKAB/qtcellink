/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
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
#include <QtCore/qcoreapplication.h>
#include <QtCore/qcommandlineparser.h>
#include <QtQuickControls2/qquickstyle.h>
#include <QtQuickControls2/private/qquickstyleselector_p.h>
#include "progressindicator.h"

class QtCellinkControlsPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtCellinkControlsPlugin(QObject *parent = nullptr);

    void registerTypes(const char *uri) override;

private:
    QUrl typeUrl(const QUrl &fileUrl) const;
    QUrl typeUrl(const QString &fileName) const;
};

QtCellinkControlsPlugin::QtCellinkControlsPlugin(QObject *parent)
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

void QtCellinkControlsPlugin::registerTypes(const char *uri)
{
    QQuickStyleSelector selector;
    const QString style = QQuickStyle::name();
    if (!style.isEmpty())
        selector.addSelector(style);
    selector.addSelector(QStringLiteral("Controls"));
    selector.setPaths(QQuickStyle::stylePathList());

    qmlRegisterType(typeUrl(selector.select(QStringLiteral("ButtonRow.qml"))), uri, 1, 0, "ButtonRow");
    qmlRegisterType(typeUrl(selector.select(QStringLiteral("DoubleSpinBox.qml"))), uri, 1, 0, "DoubleSpinBox");
    qmlRegisterType(typeUrl(selector.select(QStringLiteral("FlipView.qml"))), uri, 1, 0, "FlipView");
    qmlRegisterType(typeUrl(selector.select(QStringLiteral("ProgressIndicator.qml"))), uri, 1, 0, "ProgressIndicator");
    qmlRegisterType(typeUrl(selector.select(QStringLiteral("RowButton.qml"))), uri, 1, 0, "RowButton");
    qmlRegisterType(typeUrl(selector.select(QStringLiteral("SplitView.qml"))), uri, 1, 0, "SplitView");
    qmlRegisterType(typeUrl(selector.select(QStringLiteral("TitleSeparator.qml"))), uri, 1, 0, "TitleSeparator");

    if (useNative()) {
        qmlRegisterType(typeUrl(QStringLiteral("NativeMenu.qml")), uri, 1, 0, "Menu");
        qmlRegisterType(typeUrl(QStringLiteral("NativeMenuBar.qml")), uri, 1, 0, "MenuBar");
        qmlRegisterType(typeUrl(QStringLiteral("NativeMenuItem.qml")), uri, 1, 0, "MenuItem");
        qmlRegisterType(typeUrl(QStringLiteral("NativeMenuSeparator.qml")), uri, 1, 0, "MenuSeparator");
    } else {
        qmlRegisterType(typeUrl(QStringLiteral("QuickMenu.qml")), uri, 1, 0, "Menu");
        qmlRegisterType(typeUrl(QStringLiteral("QuickMenuBar.qml")), uri, 1, 0, "MenuBar");
        qmlRegisterType(typeUrl(QStringLiteral("QuickMenuItem.qml")), uri, 1, 0, "MenuItem");
        qmlRegisterType(typeUrl(QStringLiteral("QuickMenuSeparator.qml")), uri, 1, 0, "MenuSeparator");
    }

    QByteArray import = QByteArray(uri) + ".impl";
    qmlRegisterType<ProgressIndicator>(import, 1, 0, "ProgressIndicatorImpl");
}

QUrl QtCellinkControlsPlugin::typeUrl(const QUrl &fileUrl) const
{
    if (fileUrl.isLocalFile() || fileUrl.scheme() == QLatin1String("qrc"))
        return fileUrl;
    return typeUrl(fileUrl.toString());
}

QUrl QtCellinkControlsPlugin::typeUrl(const QString &fileName) const
{
    QUrl url = baseUrl();
    url.setPath(url.path() + QLatin1Char('/') + fileName);
    return url;
}

#include "qtcellinkcontrolsplugin.moc"