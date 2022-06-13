/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice,
**    this list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice,
**    this list of conditions and the following disclaimer in the documentation
**    and/or other materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors
**    may be used to endorse or promote products derived from this software
**    without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
** POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

#include "nodeview.h"

#include <cmath>

#include "nodeitem.h"

NodeView::NodeView(QQuickItem* parent)
    : QQuickFlickable(parent)
{
    setFlickableDirection(AutoFlickIfNeeded);

    setNodeItem(new NodeItem(contentItem()));

    connect(this, &QQuickFlickable::contentWidthChanged, this, &NodeView::resizeNodeItem);
    connect(this, &QQuickFlickable::contentHeightChanged, this, &NodeView::resizeNodeItem);
}

int NodeView::count() const
{
    if (!m_nodeItem)
        return 0;

    return m_nodeItem->count();
}

int NodeView::rows() const
{
    if (!m_nodeItem)
        return 0;

    return m_nodeItem->rows();
}

void NodeView::setRows(int rows)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setRows(rows);
}

int NodeView::columns() const
{
    if (!m_nodeItem)
        return 0;

    return m_nodeItem->columns();
}

void NodeView::setColumns(int columns)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setColumns(columns);
}

int NodeView::currentRow() const
{
    if (!m_nodeItem)
        return -1;

    return m_nodeItem->currentRow();
}

int NodeView::currentColumn() const
{
    if (!m_nodeItem)
        return -1;

    return m_nodeItem->currentColumn();
}

QObject* NodeView::model() const
{
    if (!m_nodeItem)
        return nullptr;

    return m_nodeItem->model();
}

void NodeView::setModel(QObject* model)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setModel(model);
}

QRect NodeView::selection() const
{
    if (!m_nodeItem)
        return QRect();

    return m_nodeItem->selection();
}

NodeView::SelectionMode NodeView::selectionMode() const
{
    if (!m_nodeItem)
        return NoSelection;

    return static_cast<SelectionMode>(m_nodeItem->selectionMode());
}

void NodeView::setSelectionMode(SelectionMode selectionMode)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setSelectionMode(static_cast<NodeItem::SelectionMode>(selectionMode));
}

QItemSelectionModel* NodeView::selectionModel() const
{
    if (!m_nodeItem)
        return nullptr;

    return m_nodeItem->selectionModel();
}

void NodeView::setSelectionModel(QItemSelectionModel* selectionModel)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setSelectionModel(selectionModel);
}

bool NodeView::isPressed() const
{
    if (!m_nodeItem)
        return false;

    return m_nodeItem->isPressed();
}

void NodeView::setPressed(bool pressed)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setPressed(pressed);
}

bool NodeView::isSelecting() const
{
    if (!m_nodeItem)
        return false;

    return m_nodeItem->isSelecting();
}

void NodeView::setSelecting(bool selecting)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setSelecting(selecting);
}

qreal NodeView::nodeWidth() const
{
    if (!m_nodeItem)
        return 0;

    return m_nodeItem->nodeWidth();
}

void NodeView::setNodeWidth(qreal nodeWidth)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setNodeWidth(nodeWidth);
}

qreal NodeView::nodeHeight() const
{
    if (!m_nodeItem)
        return 0;

    return m_nodeItem->nodeHeight();
}

void NodeView::setNodeHeight(qreal nodeHeight)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setNodeHeight(nodeHeight);
}

qreal NodeView::nodeSpacing() const
{
    if (!m_nodeItem)
        return 0;

    return m_nodeItem->nodeSpacing();
}

void NodeView::setNodeSpacing(qreal nodeSpacing)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setNodeSpacing(nodeSpacing);
}

qreal NodeView::nodeScaleX() const
{
    if (!m_nodeItem)
        return 0;

    return m_nodeItem->nodeScaleX();
}

void NodeView::setNodeScaleX(qreal nodeScaleX)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setNodeScaleX(nodeScaleX);
}

qreal NodeView::nodeScaleY() const
{
    if (!m_nodeItem)
        return 0;

    return m_nodeItem->nodeScaleY();
}

void NodeView::setNodeScaleY(qreal nodeScaleY)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setNodeScaleY(nodeScaleY);
}

int NodeView::selectionDelay() const
{
    if (!m_nodeItem)
        return 0;

    return m_nodeItem->selectionDelay();
}

void NodeView::setSelectionDelay(int selectionDelay)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setSelectionDelay(selectionDelay);
}

QQmlListProperty<NodeDelegate> NodeView::delegates()
{
    if (!m_nodeItem)
        return QQmlListProperty<NodeDelegate>();

    return m_nodeItem->delegates();
}

qreal NodeView::zoomFactor() const
{
    return m_zoomFactor;
}

QPointF NodeView::zoomPoint() const
{
    return m_zoomPoint;
}

qreal NodeView::minimumZoomFactor() const
{
    return m_minimumZoomFactor;
}

void NodeView::setMinimumZoomFactor(qreal factor)
{
    if (qFuzzyCompare(m_minimumZoomFactor, factor))
        return;

    m_minimumZoomFactor = factor;
    if (factor > m_zoomFactor)
        zoom(factor, m_zoomPoint);
    emit minimumZoomFactorChanged();
}

qreal NodeView::maximumZoomFactor() const
{
    return m_maximumZoomFactor;
}

void NodeView::setMaximumZoomFactor(qreal factor)
{
    if (qFuzzyCompare(m_maximumZoomFactor, factor))
        return;

    m_maximumZoomFactor = factor;
    if (factor < m_zoomFactor)
        zoom(factor, m_zoomPoint);
    emit maximumZoomFactorChanged();
}

NodeItem* NodeView::nodeItem() const
{
    return m_nodeItem;
}

void NodeView::setNodeItem(NodeItem* nodeItem)
{
    if (m_nodeItem == nodeItem)
        return;

    if (m_nodeItem) {
        m_nodeItem->setParentItem(nullptr);
        disconnect(m_nodeItem, &QQuickItem::implicitWidthChanged, this, &NodeView::updateContentSize);
        disconnect(m_nodeItem, &QQuickItem::implicitHeightChanged, this, &NodeView::updateContentSize);
        disconnect(m_nodeItem, &NodeItem::pressed, this, &NodeView::pressed);
        disconnect(m_nodeItem, &NodeItem::released, this, &NodeView::released);
        disconnect(m_nodeItem, &NodeItem::activated, this, &NodeView::activated);
        disconnect(m_nodeItem, &NodeItem::clicked, this, &NodeView::clicked);
        disconnect(m_nodeItem, &NodeItem::ensureVisible, this, &NodeView::ensureVisible);
        disconnect(m_nodeItem, &NodeItem::countChanged, this, &NodeView::countChanged);
        disconnect(m_nodeItem, &NodeItem::rowsChanged, this, &NodeView::rowsChanged);
        disconnect(m_nodeItem, &NodeItem::columnsChanged, this, &NodeView::columnsChanged);
        disconnect(m_nodeItem, &NodeItem::currentRowChanged, this, &NodeView::currentRowChanged);
        disconnect(m_nodeItem, &NodeItem::currentColumnChanged, this, &NodeView::currentColumnChanged);
        disconnect(m_nodeItem, &NodeItem::modelChanged, this, &NodeView::modelChanged);
        disconnect(m_nodeItem, &NodeItem::selectionChanged, this, &NodeView::selectionChanged);
        disconnect(m_nodeItem, &NodeItem::selectionModeChanged, this, &NodeView::selectionModeChanged);
        disconnect(m_nodeItem, &NodeItem::selectionModelChanged, this, &NodeView::selectionModelChanged);
        disconnect(m_nodeItem, &NodeItem::pressedChanged, this, &NodeView::pressedChanged);
        disconnect(m_nodeItem, &NodeItem::selectingChanged, this, &NodeView::selectingChanged);
        disconnect(m_nodeItem, &NodeItem::nodeWidthChanged, this, &NodeView::nodeWidthChanged);
        disconnect(m_nodeItem, &NodeItem::nodeHeightChanged, this, &NodeView::nodeHeightChanged);
        disconnect(m_nodeItem, &NodeItem::nodeSpacingChanged, this, &NodeView::nodeSpacingChanged);
        disconnect(m_nodeItem, &NodeItem::nodeScaleXChanged, this, &NodeView::nodeScaleXChanged);
        disconnect(m_nodeItem, &NodeItem::nodeScaleYChanged, this, &NodeView::nodeScaleYChanged);
    }

    if (nodeItem) {
        nodeItem->setParentItem(contentItem());
        connect(nodeItem, &QQuickItem::implicitWidthChanged, this, &NodeView::updateContentSize);
        connect(nodeItem, &QQuickItem::implicitHeightChanged, this, &NodeView::updateContentSize);
        connect(nodeItem, &NodeItem::pressed, this, &NodeView::pressed);
        connect(nodeItem, &NodeItem::released, this, &NodeView::released);
        connect(nodeItem, &NodeItem::activated, this, &NodeView::activated);
        connect(nodeItem, &NodeItem::clicked, this, &NodeView::clicked);
        connect(nodeItem, &NodeItem::ensureVisible, this, &NodeView::ensureVisible);
        connect(nodeItem, &NodeItem::countChanged, this, &NodeView::countChanged);
        connect(nodeItem, &NodeItem::rowsChanged, this, &NodeView::rowsChanged);
        connect(nodeItem, &NodeItem::columnsChanged, this, &NodeView::columnsChanged);
        connect(nodeItem, &NodeItem::currentRowChanged, this, &NodeView::currentRowChanged);
        connect(nodeItem, &NodeItem::currentColumnChanged, this, &NodeView::currentColumnChanged);
        connect(nodeItem, &NodeItem::modelChanged, this, &NodeView::modelChanged);
        connect(nodeItem, &NodeItem::selectionChanged, this, &NodeView::selectionChanged);
        connect(nodeItem, &NodeItem::selectionModeChanged, this, &NodeView::selectionModeChanged);
        connect(nodeItem, &NodeItem::selectionModelChanged, this, &NodeView::selectionModelChanged);
        connect(nodeItem, &NodeItem::pressedChanged, this, &NodeView::pressedChanged);
        connect(nodeItem, &NodeItem::selectingChanged, this, &NodeView::selectingChanged);
        connect(nodeItem, &NodeItem::nodeWidthChanged, this, &NodeView::nodeWidthChanged);
        connect(nodeItem, &NodeItem::nodeHeightChanged, this, &NodeView::nodeHeightChanged);
        connect(nodeItem, &NodeItem::nodeSpacingChanged, this, &NodeView::nodeSpacingChanged);
        connect(nodeItem, &NodeItem::nodeScaleXChanged, this, &NodeView::nodeScaleXChanged);
        connect(nodeItem, &NodeItem::nodeScaleYChanged, this, &NodeView::nodeScaleYChanged);
    }

    m_nodeItem = nodeItem;
    updateContentSize();
    emit nodeItemChanged();
    emit countChanged();
    emit rowsChanged();
    emit currentRowChanged();
    emit currentColumnChanged();
    emit columnsChanged();
    emit modelChanged();
    emit selectionChanged();
    emit selectionModelChanged();
    emit pressedChanged();
    emit selectingChanged();
    emit nodeWidthChanged();
    emit nodeHeightChanged();
    emit nodeSpacingChanged();
    emit nodeScaleXChanged();
    emit nodeScaleYChanged();
}

void NodeView::setCurrent(int row, int column)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setCurrent(row, column);
}

void NodeView::clearCurrent()
{
    if (!m_nodeItem)
        return;

    m_nodeItem->clearCurrent();
}

void NodeView::selectAll()
{
    if (!m_nodeItem)
        return;

    m_nodeItem->selectAll();
}

void NodeView::select(const QRect& selection)
{
    if (!m_nodeItem)
        return;

    m_nodeItem->select(selection);
}

void NodeView::clearSelection()
{
    if (!m_nodeItem)
        return;

    m_nodeItem->clearSelection();
}

void NodeView::cancelSelection()
{
    if (!m_nodeItem)
        return;

    m_nodeItem->cancelSelection();
}

static qreal calculateVelocity(qreal dist, qreal decel)
{
    qreal velocity = std::sqrt(std::abs(dist) * decel * 2);
    if (dist < 0)
        velocity = -velocity;
    return velocity;
}

void NodeView::ensureVisible(const QRectF& rect)
{
    int scrollMargin = 32;

    qreal cx = contentX();
    if (contentWidth() > width()) {
        if (cx >= rect.x() - scrollMargin)
            cx = std::max(0.0, rect.x() - scrollMargin);
        else if (cx + width() <= rect.x() + rect.width())
            cx = std::min(contentWidth() - width(), rect.x() + rect.width() - width() + scrollMargin);
    }

    qreal cy = contentY();
    if (contentHeight() > height()) {
        if (cy >= rect.y() - scrollMargin)
            cy = std::max(0.0, rect.y() - scrollMargin);
        else if (cy + height() <= rect.y() + rect.height() + scrollMargin)
            cy = std::min(contentHeight() - height(),
                          rect.y() + rect.height() - height() + scrollMargin);
    }

    qreal vx = calculateVelocity(contentX() - cx, flickDeceleration());
    qreal vy = calculateVelocity(contentY() - cy, flickDeceleration());
    flick(vx, vy);
}

void NodeView::zoom(qreal factor, const QPointF& point)
{
    factor = std::clamp(factor, m_minimumZoomFactor, m_maximumZoomFactor);
    if (qFuzzyCompare(m_zoomFactor, factor) && m_zoomPoint == point)
        return;

    m_zoomFactor = factor;
    m_zoomPoint = point;

    resizeContent(factor * m_nodeItem->implicitWidth(), factor * m_nodeItem->implicitHeight(), point);
    returnToBounds();
    emit zoomChanged(factor, point);
}

void NodeView::zoomIn(qreal factor)
{
    if (selectionArea().isEmpty()) {
        // no selection -> zoom towards viewport center
        zoom(m_zoomFactor + factor, viewportArea().center());
        return;
    }

    // zoom towards selection center
    zoom(m_zoomFactor + factor, selectionArea().center());

    // attempt to keep the selection within viewport
    QRectF selection = selectionArea();
    QRectF bounds(0, 0, contentWidth() - width(), contentHeight() - height());
    if (selection.left() < contentX())
        bounds.setRight(selection.left());
    else if (selection.right() > contentX() + width())
        bounds.setLeft(selection.right() - width());
    if (selection.top() < contentY())
        bounds.setBottom(selection.top());
    else if (selection.bottom() > contentY() + height())
        bounds.setTop(selection.bottom() - height());

    // keep within bounds
    setContentX(std::clamp(contentX(), bounds.left(), bounds.right()));
    setContentY(std::clamp(contentY(), bounds.top(), bounds.bottom()));
}

void NodeView::zoomOut(qreal factor)
{
    zoomIn(-factor);
}

void NodeView::resizeNodeItem()
{
    if (!m_nodeItem)
        return;

    m_nodeItem->setSize(QSizeF(contentWidth(), contentHeight()));
}

void NodeView::updateContentSize()
{
    if (!m_nodeItem)
        return;

    setContentWidth(m_nodeItem->implicitWidth());
    setContentHeight(m_nodeItem->implicitHeight());
}

void NodeView::wheelEvent(QWheelEvent* event)
{
    if (!isInteractive())
        return;

    const qreal deltasPerStep = QWheelEvent::DefaultDeltasPerStep;
    zoom(m_zoomFactor + event->angleDelta().y() / deltasPerStep,
         mapToItem(m_nodeItem, event->posF()));
}

QRectF NodeView::viewportArea() const
{
    return QRectF(contentX(), contentY(), width(), height());
}

QRectF NodeView::selectionArea() const
{
    QItemSelectionModel* selectionModel = NodeView::selectionModel();
    if (!selectionModel || !selectionModel->hasSelection())
        return QRectF();

    QItemSelectionRange range = selectionModel->selection().value(0);
    return QRectF(m_nodeItem->nodeRect(range.top(), range.left()).topLeft(),
                  m_nodeItem->nodeRect(range.bottom(), range.right()).bottomRight());
}
