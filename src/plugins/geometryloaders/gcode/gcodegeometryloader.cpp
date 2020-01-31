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

#include "gcodegeometryloader.h"

#include <Qt3DRender/qattribute.h>
#include <Qt3DRender/qbuffer.h>
#include <Qt3DRender/qgeometry.h>

Qt3DRender::QGeometry *GcodeGeometryLoader::geometry() const
{
    if (m_points.empty())
        return nullptr;

    const int size = m_points.count() * sizeof(QVector3D);
    const char *data = reinterpret_cast<const char *>(m_points.data());

    Qt3DRender::QGeometry *geometry = new Qt3DRender::QGeometry;
    Qt3DRender::QBuffer *buffer = new Qt3DRender::QBuffer(geometry);
    buffer->setData(QByteArray(data, size));

    Qt3DRender::QAttribute *attribute = new Qt3DRender::QAttribute(geometry);
    attribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    attribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    attribute->setVertexSize(3);
    attribute->setCount(m_points.count());
    attribute->setByteStride(sizeof(QVector3D));
    attribute->setBuffer(buffer);

    geometry->addAttribute(attribute);
    return geometry;
}

static inline qreal readFloat(const QByteArray &command)
{
    return command.mid(1).toFloat();
}

static bool readLine(const QByteArray &line, QVector3D &vec)
{
    if (line.isEmpty() || !line.startsWith("G1 "))
        return false;

    float e = 0;
    const QByteArrayList commands = line.split(' ');
    for (const QByteArray &command : commands) {
        if (command.isEmpty())
            continue;
        switch (command.front()) {
        case 'X':
            vec.setX(readFloat(command));
            break;
        case 'Y':
            vec.setY(readFloat(command));
            break;
        case 'Z':
            vec.setZ(readFloat(command));
            break;
        case 'E':
            e = readFloat(command);
            break;
        default:
            break;
        }
    }

    return e > 0;
}

static QVector<QVector3D> filterPoints(const QVector<QVector3D> &points, float from, float to)
{
    QVector<QVector3D> filtered;
    std::copy_if(points.cbegin(), points.cend(), std::back_inserter(filtered), [=](const QVector3D &vec){ return vec.z() >= from && vec.z() <= to; });
    return filtered;
}

static QPair<int, int> parseRange(const QString &subMesh)
{
    QPair<int, int> range = qMakePair(0, INT_MAX);
    bool ok = false;
    int index = subMesh.indexOf(QLatin1Char('-'));
    if (index == -1) {
        int layer = subMesh.toInt(&ok);
        if (ok)
            range = qMakePair(layer, layer);
    } else {
        int from = subMesh.mid(0, index).toInt(&ok);
        if (ok) {
            int to = subMesh.mid(index + 1).toInt(&ok);
            if (ok)
                range = qMakePair(from, to);
        }
    }
    return range;
}

bool GcodeGeometryLoader::load(QIODevice *device, const QString &subMesh)
{
    if (!device)
        return false;

    m_layers.clear();
    m_points.clear();

    float z = 0;
    QVector3D prev;
    QVector3D point;
    while (!device->atEnd()) {
        QByteArray line = device->readLine().trimmed();
        if (readLine(line, point)) {
            m_points += prev;
            m_points += point;
        }
        if (!qFuzzyCompare(z, point.z())) {
            m_layers += z;
            z = point.z();
        }
        prev = point;
    }

    if (!subMesh.isEmpty()) {
        // ### TODO: filter the layers on the fly while reading above
        QPair<int, int> range = parseRange(subMesh);
        float from = m_layers.value(range.first);
        float to = m_layers.value(range.second, std::numeric_limits<float>::max());
        m_points = filterPoints(m_points, from, to);
    }

    return !m_points.isEmpty();
}

QT_END_NAMESPACE
