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

#include "progressindicator.h"

#include <QtCore/qmath.h>
#include <QtCore/qeasingcurve.h>
#include <QtGui/qpainter.h>
#include <QtQuick/qsgimagenode.h>
#include <QtQuick/qquickwindow.h>
#include <QtQuickControls2/private/qquickanimatednode_p.h>

/*
    Relevant Android code:

    - core/res/res/anim/progress_indeterminate_rotation_material.xml contains
      the rotation animation data.
    - core/res/res/anim/progress_indeterminate_material.xml contains the trim
      animation data.
    - core/res/res/interpolator/trim_start_interpolator.xml and
      core/res/res/interpolator/trim_end_interpolator.xml contain the start
      and end trim path interpolators.
    - addCommand() in core/java/android/util/PathParser.java has a list of the
      different path commands available.
*/

static const int SpanAnimationDuration = 700;
static const int RotationAnimationDuration = SpanAnimationDuration * 6;
static const int TargetRotation = 720;
static const int OneDegree = 16;
static const qreal MinSweepSpan = 10 * OneDegree;
static const qreal MaxSweepSpan = 300 * OneDegree;

class ProgressIndicatorNode : public QQuickAnimatedNode
{
public:
    ProgressIndicatorNode(ProgressIndicatorImpl *item);

    void sync(QQuickItem *item) override;

protected:
    void updateProgress(qreal progress);
    void updateCurrentTime(int time) override;

private:
    int m_lastStartAngle = 0;
    int m_lastEndAngle = 0;
    qreal m_width = 0;
    qreal m_height = 0;
    qreal m_devicePixelRatio = 1;
    QColor m_color;
    int m_lineWidth = 0;
};

ProgressIndicatorNode::ProgressIndicatorNode(ProgressIndicatorImpl *item) : QQuickAnimatedNode(item)
{
    setLoopCount(Infinite);
    setCurrentTime(item->elapsed());
    setDuration(RotationAnimationDuration);

    QSGImageNode *textureNode = item->window()->createImageNode();
    textureNode->setOwnsTexture(true);
    appendChildNode(textureNode);

    // A texture seems to be required here, but we don't have one yet, as we haven't drawn anything,
    // so just use a blank image.
    QImage blankImage(item->width(), item->height(), QImage::Format_ARGB32_Premultiplied);
    blankImage.fill(Qt::transparent);
    textureNode->setTexture(item->window()->createTextureFromImage(blankImage));
}

void ProgressIndicatorNode::updateProgress(qreal progress)
{
    const qreal w = m_width;
    const qreal h = m_height;
    const qreal size = qMin(w, h);
    const qreal dx = (w - size) / 2;
    const qreal dy = (h - size) / 2;

    QImage image(size * m_devicePixelRatio, size * m_devicePixelRatio, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(m_color);

    QPen pen;
    QSGImageNode *textureNode = static_cast<QSGImageNode *>(firstChild());
    pen.setColor(m_color);
    pen.setWidth(m_lineWidth * m_devicePixelRatio);
    painter.setPen(pen);

    const QRectF arcBounds = QRectF(pen.width() / 2 + 1, pen.width() / 2 + 1,
                                    m_devicePixelRatio * size - pen.width() - 1,
                                    m_devicePixelRatio * size - pen.width() - 1);

    if (isRunning()) {
        int time = progress * RotationAnimationDuration;
        const qreal spanPercentageComplete = (time % SpanAnimationDuration) / qreal(SpanAnimationDuration);
        const int iteration = time / SpanAnimationDuration;
        qreal startAngle = 0;
        qreal endAngle = 0;

        if (iteration % 2 == 0) {
            if (m_lastStartAngle > 360 * OneDegree)
                m_lastStartAngle -= 360 * OneDegree;

            // The start angle is only affected by the rotation animation for the "grow" phase.
            startAngle = m_lastStartAngle;
            QEasingCurve angleCurve(QEasingCurve::OutQuad);
            const qreal percentage = angleCurve.valueForProgress(spanPercentageComplete);
            endAngle = m_lastStartAngle + MinSweepSpan + percentage * (MaxSweepSpan - MinSweepSpan);
            m_lastEndAngle = endAngle;
        } else {
            // Both the start angle *and* the span are affected by the "shrink" phase.
            QEasingCurve angleCurve(QEasingCurve::InQuad);
            const qreal percentage = angleCurve.valueForProgress(spanPercentageComplete);
            startAngle = m_lastEndAngle - MaxSweepSpan + percentage * (MaxSweepSpan - MinSweepSpan);
            endAngle = m_lastEndAngle;
            m_lastStartAngle = startAngle;
        }

        // The current angle of the rotation animation.
        const qreal rotation = OneDegree * progress * -TargetRotation;
        startAngle -= rotation;
        endAngle -= rotation;
        const int angleSpan = endAngle - startAngle;
        painter.drawArc(arcBounds, -startAngle, -angleSpan);
    } else {
        painter.drawArc(arcBounds, 90 * OneDegree, -360 * OneDegree * progress);
    }

    painter.end();

    textureNode->setRect(QRectF(dx, dy, size, size));
    textureNode->setTexture(window()->createTextureFromImage(image));
}

void ProgressIndicatorNode::updateCurrentTime(int time)
{
    updateProgress(time / qreal(RotationAnimationDuration));
}

void ProgressIndicatorNode::sync(QQuickItem *item)
{
    ProgressIndicatorImpl *indicator = static_cast<ProgressIndicatorImpl *>(item);
    m_color = indicator->color();
    m_width = indicator->width();
    m_height = indicator->height();
    m_devicePixelRatio = indicator->window()->effectiveDevicePixelRatio();
    m_lineWidth = indicator->lineWidth();

    if (!indicator->isRunning()) {
        updateProgress(indicator->value());
        if (!isRunning())
            setCurrentTime(SpanAnimationDuration);
    }
}

ProgressIndicatorImpl::ProgressIndicatorImpl(QQuickItem *parent) : QQuickItem(parent)
{
    setFlag(ItemHasContents);
}

QColor ProgressIndicatorImpl::color() const
{
    return m_color;
}

void ProgressIndicatorImpl::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    update();
}

int ProgressIndicatorImpl::lineWidth() const
{
    return m_lineWidth;
}

void ProgressIndicatorImpl::setLineWidth(int width)
{
    if (m_lineWidth == width)
        return;

    m_lineWidth = width;
    update();
}

bool ProgressIndicatorImpl::isRunning() const
{
    return m_running;
}

void ProgressIndicatorImpl::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    update();
}

qreal ProgressIndicatorImpl::value() const
{
    return m_value;
}

void ProgressIndicatorImpl::setValue(qreal value)
{
    if (qFuzzyCompare(m_value, value))
        return;

    m_value = value;
    update();
}

int ProgressIndicatorImpl::elapsed() const
{
    return m_elapsed;
}

void ProgressIndicatorImpl::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &data)
{
    QQuickItem::itemChange(change, data);
    if (change == ItemVisibleHasChanged)
        update();
}

QSGNode *ProgressIndicatorImpl::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    ProgressIndicatorNode *node = static_cast<ProgressIndicatorNode *>(oldNode);
    if (isVisible() && width() > 0 && height() > 0) {
        if (!node)
            node = new ProgressIndicatorNode(this);
        if (m_running)
            node->start();
        else
            node->stop();
        node->sync(this);
    } else {
        m_elapsed = node ? node->currentTime() : 0;
        delete node;
        node = nullptr;
    }
    return node;
}
