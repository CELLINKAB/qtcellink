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

#ifndef MATERIAL_H
#define MATERIAL_H

#include <QtCore/qobject.h>
#include <QtGui/qcolor.h>

class Material : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor red READ red NOTIFY changed)
    Q_PROPERTY(QColor pink READ pink NOTIFY changed)
    Q_PROPERTY(QColor purple READ purple NOTIFY changed)
    Q_PROPERTY(QColor deepPurple READ deepPurple NOTIFY changed)
    Q_PROPERTY(QColor indigo READ indigo NOTIFY changed)
    Q_PROPERTY(QColor blue READ blue NOTIFY changed)
    Q_PROPERTY(QColor lightBlue READ lightBlue NOTIFY changed)
    Q_PROPERTY(QColor cyan READ cyan NOTIFY changed)
    Q_PROPERTY(QColor teal READ teal NOTIFY changed)
    Q_PROPERTY(QColor green READ green NOTIFY changed)
    Q_PROPERTY(QColor lightGreen READ lightGreen NOTIFY changed)
    Q_PROPERTY(QColor lime READ lime NOTIFY changed)
    Q_PROPERTY(QColor yellow READ yellow NOTIFY changed)
    Q_PROPERTY(QColor amber READ amber NOTIFY changed)
    Q_PROPERTY(QColor orange READ orange NOTIFY changed)
    Q_PROPERTY(QColor deepOrange READ deepOrange NOTIFY changed)
    Q_PROPERTY(QColor brown READ brown NOTIFY changed)
    Q_PROPERTY(QColor gray READ gray NOTIFY changed)
    Q_PROPERTY(QColor blueGray READ blueGray NOTIFY changed)
    Q_PROPERTY(Shade shade READ shade WRITE setShade NOTIFY changed)

public:
    explicit Material(QObject *parent = nullptr);

    QColor red() const { return color(Red); }
    QColor pink() const { return color(Pink); }
    QColor purple() const { return color(Purple); }
    QColor deepPurple() const { return color(DeepPurple); }
    QColor indigo() const { return color(Indigo); }
    QColor blue() const { return color(Blue); }
    QColor lightBlue() const { return color(LightBlue); }
    QColor cyan() const { return color(Cyan); }
    QColor teal() const { return color(Teal); }
    QColor green() const { return color(Green); }
    QColor lightGreen() const { return color(LightGreen); }
    QColor lime() const { return color(Lime); }
    QColor yellow() const { return color(Yellow); }
    QColor amber() const { return color(Amber); }
    QColor orange() const { return color(Orange); }
    QColor deepOrange() const { return color(DeepOrange); }
    QColor brown() const { return color(Brown); }
    QColor gray() const { return color(Gray); }
    QColor blueGray() const { return color(BlueGray); }

    enum Color {
        Red,
        Pink,
        Purple,
        DeepPurple,
        Indigo,
        Blue,
        LightBlue,
        Cyan,
        Teal,
        Green,
        LightGreen,
        Lime,
        Yellow,
        Amber,
        Orange,
        DeepOrange,
        Brown,
        Gray,
        BlueGray
    };
    Q_ENUM(Color)

    enum Shade {
        Shade50,
        Shade100,
        Shade200,
        Shade300,
        Shade400,
        Shade500,
        Shade600,
        Shade700,
        Shade800,
        Shade900,
        ShadeA100,
        ShadeA200,
        ShadeA400,
        ShadeA700,
    };
    Q_ENUM(Shade)

    Shade shade() const;
    void setShade(Shade shade);

    Q_INVOKABLE QColor color(Color color) const;
    Q_INVOKABLE QColor color(Color color, Shade shade) const;

signals:
    void changed();

private:
    Shade m_shade = Shade500;
};

#endif // MATERIAL_H
