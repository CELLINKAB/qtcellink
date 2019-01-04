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

void CellinkControlsPlugin::registerTypes(const char *uri)
{
    qmlRegisterType(typeUrl(QStringLiteral("DoubleSpinBox.qml")), uri, 1, 0, "DoubleSpinBox");
    qmlRegisterType(typeUrl(QStringLiteral("SplitView.qml")), uri, 1, 0, "SplitView");
}

QUrl CellinkControlsPlugin::typeUrl(const QString &fileName) const
{
    QUrl url = baseUrl();
    url.setPath(url.path() + QLatin1Char('/') + fileName);
    return url;
}

#include "cellinkcontrolsplugin.moc"
