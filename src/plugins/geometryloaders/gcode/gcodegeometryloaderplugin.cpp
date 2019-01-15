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

#include <Qt3DRender/private/qgeometryloaderfactory_p.h>

#include "gcodegeometryloader.h"

static inline QString gcode() { return QStringLiteral("gcode"); }

class DefaultGeometryLoaderPlugin : public Qt3DRender::QGeometryLoaderFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QGeometryLoaderFactory_iid FILE "gcode.json")

public:
    QStringList keys() const override
    {
        return QStringList() << gcode();
    }

    Qt3DRender::QGeometryLoaderInterface *create(const QString &ext) override
    {
        if (ext.compare(gcode(), Qt::CaseInsensitive) == 0)
            return new GcodeGeometryLoader;
        return nullptr;
    }
};

#include "gcodegeometryloaderplugin.moc"
