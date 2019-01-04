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

#include "doublespinbox.h"

class CellinkTemplatesPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    CellinkTemplatesPlugin(QObject *parent = nullptr);
    void registerTypes(const char *uri) override;
};

CellinkTemplatesPlugin::CellinkTemplatesPlugin(QObject *parent) : QQmlExtensionPlugin(parent)
{
}

void CellinkTemplatesPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<DoubleSpinBox>(uri, 1, 0, "DoubleSpinBox");
    qmlRegisterType<DoubleSpinButton>();
}

#include "cellinktemplatesplugin.moc"
