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

#include <Qt3DRender/private/qgeometryloaderfactory_p.h>

#include "amfgeometryloader.h"

static inline QString amf() { return QStringLiteral("amf"); }

class DefaultGeometryLoaderPlugin : public Qt3DRender::QGeometryLoaderFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QGeometryLoaderFactory_iid FILE "amf.json")

public:
    QStringList keys() const override
    {
        return QStringList() << amf();
    }

    Qt3DRender::QGeometryLoaderInterface *create(const QString &ext) override
    {
        if (ext.compare(amf(), Qt::CaseInsensitive) == 0)
            return new AmfGeometryLoader;
        return nullptr;
    }
};

#include "amfgeometryloaderplugin.moc"
