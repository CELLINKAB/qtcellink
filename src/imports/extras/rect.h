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

#ifndef RECT_H
#define RECT_H

#include <QtCore/qobject.h>
#include <QtCore/qrect.h>

class Rect : public QObject
{
    Q_OBJECT

public:
    explicit Rect(QObject *parent = nullptr);

    Q_INVOKABLE static QPointF center(const QRectF &r) { return r.center(); }
    Q_INVOKABLE static QPointF topLeft(const QRectF &r) { return r.topLeft(); }
    Q_INVOKABLE static QPointF topRight(const QRectF &r) { return r.topRight(); }
    Q_INVOKABLE static QPointF bottomLeft(const QRectF &r) { return r.bottomLeft(); }
    Q_INVOKABLE static QPointF bottomRight(const QRectF &r) { return r.bottomRight(); }

    Q_INVOKABLE static QRectF adjusted(const QRectF &r, qreal dx1, qreal dy1, qreal dx2, qreal dy2) { return r.adjusted(dx1, dy1, dx2, dy2); }

    Q_INVOKABLE static bool contains(const QRectF &r, qreal x, qreal y) { return r.contains(x, y); }
    Q_INVOKABLE static bool contains(const QRectF &r, const QPointF &p) { return r.contains(p); }
    Q_INVOKABLE static bool contains(const QRectF &r1, const QRectF &r2) { return r1.contains(r2); }

    Q_INVOKABLE static QRectF intersected(const QRectF &r1, const QRectF &r2) { return r1.intersected(r2); }
    Q_INVOKABLE static bool intersects(const QRectF &r1, const QRectF &r2) { return r1.intersects(r2); }

    Q_INVOKABLE static bool isEmpty(const QRectF &r) { return r.isEmpty(); }
    Q_INVOKABLE static bool isNull(const QRectF &r) { return r.isNull(); }
    Q_INVOKABLE static bool isValid(const QRectF &r) { return r.isValid(); }

    Q_INVOKABLE static QRectF normalized(const QRectF &r) { return r.normalized(); }

    Q_INVOKABLE static QSizeF size(const QRectF &r) { return r.size(); }

    Q_INVOKABLE static QRectF toAlignedRect(const QRectF &r) { return r.toAlignedRect(); }
    Q_INVOKABLE static QRectF toRect(const QRectF &r) { return r.toRect(); }

    Q_INVOKABLE static QRectF translated(const QRectF &r, qreal dx, qreal dy) { return r.translated(dx, dy); }
    Q_INVOKABLE static QRectF translated(const QRectF &r, const QPointF &offset) { return r.translated(offset); }

    Q_INVOKABLE static QRectF transposed(const QRectF &r) { return r.transposed(); }

    Q_INVOKABLE static QRectF united(const QRectF &r1, const QRectF &r2) { return r1.united(r2); }
};

#endif // RECT_H
