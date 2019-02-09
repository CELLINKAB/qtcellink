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
#include <QtQml/qqmlengine.h>
#include <QtQml/qqml.h>

#include "color.h"
#include "colorimage.h"
#include "iconimage.h"
#include "iconlabel.h"
#include "mnemoniclabel.h"
#include "paddedrectangle.h"

class CellinkExtrasPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    explicit CellinkExtrasPlugin(QObject *parent = nullptr);

    void registerTypes(const char *uri) override;
};

CellinkExtrasPlugin::CellinkExtrasPlugin(QObject *parent)
    : QQmlExtensionPlugin(parent)
{
}

void CellinkExtrasPlugin::registerTypes(const char *uri)
{
    qmlRegisterSingletonType<Color>(uri, 1, 0, "Color", [](QQmlEngine *engine, QJSEngine *) -> QObject* { return new Color(engine); });
    qmlRegisterType<ColorImage>(uri, 1, 0, "ColorImage");
    qmlRegisterType<IconImage>(uri, 1, 0, "IconImage");
    qmlRegisterType<IconLabel>(uri, 1, 0, "IconLabel");
    qmlRegisterType<MnemonicLabel>(uri, 1, 0, "MnemonicLabel");
    qmlRegisterType<PaddedRectangle>(uri, 1, 0, "PaddedRectangle");
}

#include "cellinkextrasplugin.moc"
