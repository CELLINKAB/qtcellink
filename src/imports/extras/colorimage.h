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

#ifndef COLORIMAGE_H
#define COLORIMAGE_H

#include <QtGui/qcolor.h>
#include <QtQuick/private/qquickimage_p.h>

class ColorImage : public QQuickImage
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor RESET resetColor NOTIFY colorChanged FINAL)
    Q_PROPERTY(QColor defaultColor READ defaultColor WRITE setDefaultColor RESET resetDefaultColor NOTIFY defaultColorChanged FINAL)

public:
    explicit ColorImage(QQuickItem *parent = nullptr);

    QColor color() const;
    void setColor(const QColor &color);
    void resetColor();

    QColor defaultColor() const;
    void setDefaultColor(const QColor &color);
    void resetDefaultColor();

Q_SIGNALS:
    void colorChanged();
    void defaultColorChanged();

protected:
    void pixmapChange() override;

private:
    QColor m_color = Qt::transparent;
    QColor m_defaultColor = Qt::transparent;
};

#endif // COLORIMAGE_H
