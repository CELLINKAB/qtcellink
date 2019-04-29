/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
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

#include "color.h"
#include <cmath>

Color::Color(QObject *parent) :
    QObject(parent)
{
}

QColor Color::transparent(const QColor &color, qreal opacity) const
{
    return QColor(color.red(), color.green(), color.blue(),
                  int(qreal(255) * qBound(qreal(0), opacity, qreal(1))));
}

QColor Color::blend(const QColor &a, const QColor &b, qreal factor) const
{
    if (factor <= 0.0)
        return a;
    if (factor >= 1.0)
        return b;

    QColor color;
    color.setRedF(a.redF() * (1.0 - factor) + b.redF() * factor);
    color.setGreenF(a.greenF() * (1.0 - factor) + b.greenF() * factor);
    color.setBlueF(a.blueF() * (1.0 - factor) + b.blueF() * factor);
    return color;
}

QColor Color::hue(const QColor &color, qreal factor) const
{
    QColor base = color.toHsl();
    return QColor::fromHslF(std::fmod(std::abs(base.hueF() + factor), 1.0), base.saturationF(), base.lightnessF());
}
