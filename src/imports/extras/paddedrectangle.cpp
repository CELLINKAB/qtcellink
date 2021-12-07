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

#include "paddedrectangle.h"

#include <QtQuick/private/qsgadaptationlayer_p.h>

PaddedRectangle::PaddedRectangle(QQuickItem *parent) :
    QQuickRectangle(parent)
{
}

qreal PaddedRectangle::padding() const
{
    return m_padding;
}

void PaddedRectangle::setPadding(qreal padding)
{
    if (!qFuzzyCompare(m_padding, padding)) {
        m_padding = padding;
        update();
        emit paddingChanged();
        if (m_hasTopPadding)
            emit topPaddingChanged();
        if (!m_hasLeftPadding)
            emit leftPaddingChanged();
        if (!m_hasRightPadding)
            emit rightPaddingChanged();
        if (!m_hasBottomPadding)
            emit bottomPaddingChanged();
    }
}

void PaddedRectangle::resetPadding()
{
    setPadding(0);
}

qreal PaddedRectangle::topPadding() const
{
    return m_hasTopPadding ? m_topPadding : m_padding;
}

void PaddedRectangle::setTopPadding(qreal padding)
{
    setTopPadding(padding, true);
}

void PaddedRectangle::resetTopPadding()
{
    setTopPadding(0, false);
}

qreal PaddedRectangle::leftPadding() const
{
    return m_hasLeftPadding ? m_leftPadding : m_padding;
}

void PaddedRectangle::setLeftPadding(qreal padding)
{
    setLeftPadding(padding, true);
}

void PaddedRectangle::resetLeftPadding()
{
    setLeftPadding(0, false);
}

qreal PaddedRectangle::rightPadding() const
{
    return m_hasRightPadding ? m_rightPadding : m_padding;
}

void PaddedRectangle::setRightPadding(qreal padding)
{
    setRightPadding(padding, true);
}

void PaddedRectangle::resetRightPadding()
{
    setRightPadding(0, false);
}

qreal PaddedRectangle::bottomPadding() const
{
    return m_hasBottomPadding ? m_bottomPadding : m_padding;
}

void PaddedRectangle::setBottomPadding(qreal padding)
{
    setBottomPadding(padding, true);
}

void PaddedRectangle::resetBottomPadding()
{
    setBottomPadding(0, false);
}

void PaddedRectangle::setTopPadding(qreal padding, bool has)
{
    qreal oldPadding = topPadding();
    m_hasTopPadding = has;
    m_topPadding = padding;
    if (!qFuzzyCompare(oldPadding, padding)) {
        update();
        emit topPaddingChanged();
    }
}

void PaddedRectangle::setLeftPadding(qreal padding, bool has)
{
    qreal oldPadding = leftPadding();
    m_hasLeftPadding = has;
    m_leftPadding = padding;
    if (!qFuzzyCompare(oldPadding, padding)) {
        update();
        emit leftPaddingChanged();
    }
}

void PaddedRectangle::setRightPadding(qreal padding, bool has)
{
    qreal oldPadding = rightPadding();
    m_hasRightPadding = has;
    m_rightPadding = padding;
    if (!qFuzzyCompare(oldPadding, padding)) {
        update();
        emit rightPaddingChanged();
    }
}

void PaddedRectangle::setBottomPadding(qreal padding, bool has)
{
    qreal oldPadding = bottomPadding();
    m_hasBottomPadding = has;
    m_bottomPadding = padding;
    if (!qFuzzyCompare(oldPadding, padding)) {
        update();
        emit bottomPaddingChanged();
    }
}

QSGNode *PaddedRectangle::updatePaintNode(QSGNode *node, UpdatePaintNodeData *data)
{
    QSGTransformNode *transformNode = static_cast<QSGTransformNode *>(node);
    if (!transformNode)
        transformNode = new QSGTransformNode;

    QSGInternalRectangleNode *rectNode = static_cast<QSGInternalRectangleNode *>(QQuickRectangle::updatePaintNode(transformNode->firstChild(), data));

    if (rectNode) {
        if (!transformNode->firstChild())
            transformNode->appendChildNode(rectNode);

        qreal top = topPadding();
        qreal left = leftPadding();
        qreal right = rightPadding();
        qreal bottom = bottomPadding();

        if (!qFuzzyIsNull(top) || !qFuzzyIsNull(left) || !qFuzzyIsNull(right) || !qFuzzyIsNull(bottom)) {
            QMatrix4x4 m;
            m.translate(left, top);
            transformNode->setMatrix(m);

            qreal w = qMax<qreal>(0.0, width() -left-right);
            qreal h = qMax<qreal>(0.0, height() -top-bottom);

            rectNode->setRect(QRectF(0, 0, w, h));
            rectNode->update();
        }
    }
    return transformNode;
}
