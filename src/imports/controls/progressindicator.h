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

#ifndef PROGRESSINDICATOR_H
#define PROGRESSINDICATOR_H

#include <QtQuick/qquickitem.h>
#include <QtGui/qcolor.h>

class ProgressIndicatorImpl : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor FINAL)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth FINAL)
    Q_PROPERTY(bool running READ isRunning WRITE setRunning FINAL)
    Q_PROPERTY(qreal value READ value WRITE setValue FINAL)

public:
    explicit ProgressIndicatorImpl(QQuickItem *parent = nullptr);

    QColor color() const;
    void setColor(QColor color);

    int lineWidth() const;
    void setLineWidth(int width);

    bool isRunning() const;
    void setRunning(bool running);

    qreal value() const;
    void setValue(qreal value);

    int elapsed() const;

protected:
    void itemChange(ItemChange change, const ItemChangeData &data) override;
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

private:
    bool m_running = false;
    int m_elapsed = 0;
    qreal m_value = 0;
    QColor m_color;
    int m_lineWidth = 8;
};

#endif // PROGRESSINDICATOR_H
