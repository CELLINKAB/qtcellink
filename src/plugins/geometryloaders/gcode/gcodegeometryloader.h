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

#ifndef GCODEGEOMETRYLOADER_H
#define GCODEGEOMETRYLOADER_H

#include <Qt3DRender/private/qgeometryloaderinterface_p.h>
#include <QtCore/qvector.h>
#include <QtGui/qvector3d.h>

class GcodeGeometryLoader : public Qt3DRender::QGeometryLoaderInterface
{
public:
    Qt3DRender::QGeometry* geometry() const override;
    bool load(QIODevice* device, const QString& subMesh = QString()) override;

private:
    QList<float> m_layers;
    QVector<QVector3D> m_points;
};

#endif // GCODEGEOMETRYLOADER_H
