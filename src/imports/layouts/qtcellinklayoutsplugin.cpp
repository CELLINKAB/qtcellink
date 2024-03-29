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

#include <QtQml/qqml.h>
#include <QtQml/qqmlextensionplugin.h>

#include "layoutgroup.h"

class QtCellinkLayoutsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtCellinkLayoutsPlugin(QObject* parent = nullptr);

    void registerTypes(const char* uri) override;
};

QtCellinkLayoutsPlugin::QtCellinkLayoutsPlugin(QObject* parent)
    : QQmlExtensionPlugin(parent)
{}

void QtCellinkLayoutsPlugin::registerTypes(const char* uri)
{
    qmlRegisterType<LayoutGroup>(uri, 1, 0, "LayoutGroup");
}

#include "qtcellinklayoutsplugin.moc"
