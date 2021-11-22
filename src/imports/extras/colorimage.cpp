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

#include "colorimage.h"

#include <QtQuick/private/qquickimagebase_p_p.h>

ColorImage::ColorImage(QQuickItem* parent)
    : QQuickImage(parent)
{}

QColor ColorImage::color() const
{
    return m_color;
}

void ColorImage::setColor(const QColor& color)
{
    if (m_color == color)
        return;

    m_color = color;
    if (isComponentComplete())
        load();
    emit colorChanged();
}

void ColorImage::resetColor()
{
    setColor(Qt::transparent);
}

QColor ColorImage::defaultColor() const
{
    return m_defaultColor;
}

void ColorImage::setDefaultColor(const QColor& color)
{
    if (m_defaultColor == color)
        return;

    m_defaultColor = color;
    emit defaultColorChanged();
}

void ColorImage::resetDefaultColor()
{
    setDefaultColor(Qt::transparent);
}

void ColorImage::pixmapChange()
{
    QQuickImage::pixmapChange();
    if (m_color.alpha() > 0 && m_color != m_defaultColor) {
        QQuickImageBasePrivate* d = static_cast<QQuickImageBasePrivate*>(QQuickItemPrivate::get(this));
        QImage image = d->pix.image();
        if (!image.isNull()) {
            QPainter painter(&image);
            painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
            painter.fillRect(image.rect(), m_color);
            d->pix.setImage(image);
        }
    }
}
