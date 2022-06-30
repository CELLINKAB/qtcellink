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

#include <QCommandLineParser>
#include <QtQml/qqml.h>
#include <QtQml/qqmlextensionplugin.h>
#include <QtQuickControls2/private/qquickstyleselector_p.h>
#include <QtQuickControls2/qquickstyle.h>

#include "progressindicator.h"

class QtCellinkControlsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtCellinkControlsPlugin(QObject* parent = nullptr);

    void registerTypes(const char* uri) override;

private:
    QUrl typeUrl(const QUrl& fileUrl) const;
    QUrl typeUrl(const QString& fileName) const;
};

QtCellinkControlsPlugin::QtCellinkControlsPlugin(QObject* parent)
    : QQmlExtensionPlugin(parent)
{}

static bool useNative()
{
    QCommandLineParser cmdLine;
    QCommandLineOption nativeOption(QStringLiteral("native"));
    QCommandLineOption nonNativeOption(QStringLiteral("no-native"));

    cmdLine.addOptions({nativeOption, nonNativeOption});
    cmdLine.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);

    // fails if we call the exe with unknown arguments unless filtered
    auto filteredArgs = qApp->arguments().filter(QRegExp(QStringLiteral("`(no-)?native$")));
    filteredArgs.push_front(qApp->arguments().front());

    cmdLine.process(filteredArgs);

    return true;
}

void QtCellinkControlsPlugin::registerTypes(const char* uri)
{
    QQuickStyleSelector selector;
    const QString style = QQuickStyle::name();
    if (!style.isEmpty())
        selector.addSelector(style);
    selector.addSelector(QStringLiteral("Controls"));
    selector.setPaths(QQuickStyle::stylePathList());

    qmlRegisterType(typeUrl(selector.select(QStringLiteral("ButtonRow.qml"))), uri, 1, 0, "ButtonRow");
    qmlRegisterType(typeUrl(selector.select(QStringLiteral("ComponentView.qml"))),
                    uri,
                    1,
                    0,
                    "ComponentView");
    qmlRegisterType(typeUrl(selector.select(QStringLiteral("DoubleSpinBox.qml"))),
                    uri,
                    1,
                    0,
                    "DoubleSpinBox");
    qmlRegisterType(typeUrl(selector.select(QStringLiteral("FlipView.qml"))), uri, 1, 0, "FlipView");
    qmlRegisterType(typeUrl(selector.select(QStringLiteral("ProgressIndicator.qml"))),
                    uri,
                    1,
                    0,
                    "ProgressIndicator");
    qmlRegisterType(typeUrl(selector.select(QStringLiteral("RowButton.qml"))), uri, 1, 0, "RowButton");
    qmlRegisterType(typeUrl(QStringLiteral("SplitView.qml")), uri, 1, 0, "SplitView");
    qmlRegisterType(typeUrl(selector.select(QStringLiteral("TitleSeparator.qml"))),
                    uri,
                    1,
                    0,
                    "TitleSeparator");

    QByteArray import = QByteArray(uri) + ".impl";
    qmlRegisterType<ProgressIndicatorImpl>(import, 1, 0, "ProgressIndicatorImpl");
}

QUrl QtCellinkControlsPlugin::typeUrl(const QUrl& fileUrl) const
{
    if (fileUrl.isLocalFile() || fileUrl.scheme() == QLatin1String("qrc"))
        return fileUrl;
    return typeUrl(fileUrl.toString());
}

QUrl QtCellinkControlsPlugin::typeUrl(const QString& fileName) const
{
    QUrl url = baseUrl();
    url.setPath(url.path() + QLatin1Char('/') + fileName);
    return url;
}

#include "qtcellinkcontrolsplugin.moc"
