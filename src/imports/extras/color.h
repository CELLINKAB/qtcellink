/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Quick Controls 2 module of Qt).
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

#ifndef COLOR_H
#define COLOR_H

#include <QtCore/qobject.h>
#include <QtGui/qcolor.h>

class Color : public QObject
{
    Q_OBJECT

public:
    explicit Color(QObject* parent = nullptr);

    Q_INVOKABLE QColor transparent(const QColor& color, qreal opacity) const;
    Q_INVOKABLE QColor blend(const QColor& a, const QColor& b, qreal factor) const;
    Q_INVOKABLE QColor hue(const QColor& color, qreal factor) const;
};

#endif // COLOR_H
