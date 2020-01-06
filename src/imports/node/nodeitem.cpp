/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
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

#include "nodeitem.h"
#include "nodedelegate.h"

#include <QtGui/qguiapplication.h>
#include <QtGui/qstylehints.h>
#include <QtQuick/qsgnode.h>

#include <cmath>

static QModelIndex topLeft(const QModelIndex &a, const QModelIndex &b)
{
    return a.sibling(std::min(a.row(), b.row()), std::min(a.column(), b.column()));
}

static QModelIndex bottomRight(const QModelIndex &a, const QModelIndex &b)
{
    return a.sibling(std::max(a.row(), b.row()), std::max(a.column(), b.column()));
}

NodeItem::NodeItem(QQuickItem *parent) : QQuickItem(parent)
{
    setFlag(ItemHasContents);
    setAcceptedMouseButtons(Qt::LeftButton);
}

int NodeItem::count() const
{
    return rows() * columns();
}

int NodeItem::rows() const
{
    if (m_hasRows || !m_model)
        return m_rows;

    return m_model->rowCount();
}

void NodeItem::setRows(int rows)
{
    m_hasRows = true;
    int oldRows = NodeItem::rows();
    if (oldRows == rows)
        return;

    m_rows = rows;
    rowsChange();
}

QRect NodeItem::selection() const
{
    return m_selection;
}

void NodeItem::setSelection(const QRect &selection)
{
    if (m_selection == selection)
        return;

    m_selection = selection;
    emit selectionChanged();
}

int NodeItem::columns() const
{
    if (m_hasColumns || !m_model)
        return m_columns;

    return m_model->columnCount();
}

void NodeItem::setColumns(int columns)
{
    m_hasColumns = true;
    int oldColumns = NodeItem::columns();
    if (oldColumns == columns)
        return;

    m_columns = columns;
    columnsChange();
}

QObject *NodeItem::model() const
{
    return m_model;
}

void NodeItem::setModel(QObject *model)
{
    if (m_model == model)
        return;

    if (m_model) {
        disconnect(m_model, &QAbstractItemModel::dataChanged, this, &NodeItem::dataChange);
        disconnect(m_model, &QAbstractItemModel::rowsInserted, this, &NodeItem::rowsChange);
        disconnect(m_model, &QAbstractItemModel::rowsRemoved, this, &NodeItem::rowsChange);
        disconnect(m_model, &QAbstractItemModel::columnsInserted, this, &NodeItem::columnsChange);
        disconnect(m_model, &QAbstractItemModel::columnsRemoved, this, &NodeItem::columnsChange);
        disconnect(m_model, &QAbstractItemModel::modelReset, this, &NodeItem::modelReset);
    }

    QAbstractItemModel *aim = qobject_cast<QAbstractItemModel *>(model);
    if (aim) {
        connect(aim, &QAbstractItemModel::dataChanged, this, &NodeItem::dataChange);
        connect(aim, &QAbstractItemModel::rowsInserted, this, &NodeItem::rowsChange);
        connect(aim, &QAbstractItemModel::rowsRemoved, this, &NodeItem::rowsChange);
        connect(aim, &QAbstractItemModel::columnsInserted, this, &NodeItem::columnsChange);
        connect(aim, &QAbstractItemModel::columnsRemoved, this, &NodeItem::columnsChange);
        connect(aim, &QAbstractItemModel::modelReset, this, &NodeItem::modelReset);
    }

    m_model = aim;

    if (m_selectionModel)
        m_selectionModel->setModel(aim);

    modelReset();
    emit modelChanged();
}

NodeItem::SelectionMode NodeItem::selectionMode() const
{
    return m_selectionMode;
}

void NodeItem::setSelectionMode(SelectionMode selectionMode)
{
    if (m_selectionMode == selectionMode)
        return;

    m_selectionMode = selectionMode;
    emit selectionModeChanged();
}

QItemSelectionModel *NodeItem::selectionModel() const
{
    return m_selectionModel;
}

void NodeItem::setSelectionModel(QItemSelectionModel *selectionModel)
{
    if (m_selectionModel == selectionModel)
        return;

    if (m_selectionModel) {
        disconnect(m_selectionModel, &QItemSelectionModel::currentChanged, this, &NodeItem::currentChange);
        disconnect(m_selectionModel, &QItemSelectionModel::selectionChanged, this, &NodeItem::selectionChange);
    }

    if (selectionModel) {
        selectionModel->setModel(m_model);
        connect(selectionModel, &QItemSelectionModel::currentChanged, this, &NodeItem::currentChange);
        connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &NodeItem::selectionChange);
    }

    m_selectionModel = selectionModel;
    relayout();
    emit selectionModelChanged();
}

bool NodeItem::isSelecting() const
{
    return m_selecting;
}

void NodeItem::setSelecting(bool selecting)
{
    if (m_selecting == selecting)
        return;

    m_selecting = selecting;
    emit selectingChanged();
}

qreal NodeItem::nodeWidth() const
{
    return m_nodeWidth;
}

void NodeItem::setNodeWidth(qreal nodeWidth)
{
    if (qFuzzyCompare(m_nodeWidth, nodeWidth))
        return;

    m_nodeWidth = nodeWidth;
    relayout();
    updateImplicitSize();
    emit nodeWidthChanged();
}

qreal NodeItem::nodeHeight() const
{
    return m_nodeHeight;
}

void NodeItem::setNodeHeight(qreal nodeHeight)
{
    if (qFuzzyCompare(m_nodeHeight, nodeHeight))
        return;

    m_nodeHeight = nodeHeight;
    relayout();
    updateImplicitSize();
    emit nodeHeightChanged();
}

qreal NodeItem::nodeSpacing() const
{
    return m_nodeSpacing;
}

void NodeItem::setNodeSpacing(qreal nodeSpacing)
{
    if (qFuzzyCompare(m_nodeSpacing, nodeSpacing))
        return;

    m_nodeSpacing = nodeSpacing;
    relayout();
    updateImplicitSize();
    emit nodeSpacingChanged();
}

qreal NodeItem::nodeScale() const
{
    qreal scale = nodeScaleX();
    if (qFuzzyCompare(scale, 1.0))
        scale = nodeScaleY();
    return scale;
}

qreal NodeItem::nodeScaleX() const
{
    if (m_hasNodeScaleX)
        return m_nodeScaleX;

    return width() / implicitWidth();
}

void NodeItem::setNodeScaleX(qreal nodeScaleX)
{
    m_hasNodeScaleX = true;
    if (qFuzzyCompare(m_nodeScaleX, nodeScaleX))
        return;

    m_nodeScaleX = nodeScaleX;
    emit nodeScaleXChanged();
}

qreal NodeItem::nodeScaleY() const
{
    if (m_hasNodeScaleY)
        return m_nodeScaleY;

    return height() / implicitHeight();
}

void NodeItem::setNodeScaleY(qreal nodeScaleY)
{
    m_hasNodeScaleY = true;
    if (qFuzzyCompare(m_nodeScaleY, nodeScaleY))
        return;

    m_nodeScaleY = nodeScaleY;
    emit nodeScaleYChanged();
}

QQmlListProperty<NodeDelegate> NodeItem::delegates()
{
    return QQmlListProperty<NodeDelegate>(this, nullptr, delegates_append, delegates_count, delegates_at, delegates_clear);
}

bool NodeItem::isEnabled(const QModelIndex &index) const
{
    if (!m_model || !QQuickItem::isEnabled())
        return false;

    return m_model->flags(index).testFlag(Qt::ItemIsEnabled);
}

bool NodeItem::isCurrent(const QModelIndex &index) const
{
    if (!m_selectionModel)
        return false;

    return index == m_selectionModel->currentIndex();
}

bool NodeItem::isSelected(const QModelIndex &index) const
{
    if (!m_selectionModel)
        return false;

    return m_selectionModel->isSelected(index);
}

QModelIndex NodeItem::nodeAt(const QPointF &pos) const
{
    if (count() <= 0)
        return QModelIndex();

    int rows = NodeItem::rows();
    int columns = NodeItem::columns();

    qreal nw = m_nodeWidth * nodeScaleX();
    qreal nh = m_nodeHeight * nodeScaleY();
    qreal hsp = m_nodeSpacing * nodeScaleX();
    qreal vsp = m_nodeSpacing * nodeScaleY();

    qreal x = std::clamp(pos.x(), 0.0, width());
    qreal y = std::clamp(pos.y(), 0.0, height());

    int row = std::floor(y / (nh + vsp));
    int column = std::floor(x / (nw + hsp));
    return m_model->index(std::min(row, rows - 1), std::min(column, columns - 1));
}

QRectF NodeItem::nodeRect(const QModelIndex &index) const
{
    qreal nw = m_nodeWidth * nodeScaleX();
    qreal nh = m_nodeHeight * nodeScaleY();
    qreal hsp = m_nodeSpacing * nodeScaleX();
    qreal vsp = m_nodeSpacing * nodeScaleY();

    return QRectF(index.column() * nw + index.column() * hsp,
                  index.row() * nh + index.row() * vsp, nw, nh);
}

void NodeItem::selectAll()
{
    if (!m_selectionModel || !m_model)
        return;

    m_selectionModel->select(QItemSelection(m_model->index(0, 0), m_model->index(m_model->rowCount() - 1, m_model->columnCount() - 1)), QItemSelectionModel::Select);
}

void NodeItem::select(const QRect &selection)
{
    if (!m_selectionModel || !m_model)
        return;

    m_selectionModel->select(QItemSelection(m_model->index(selection.top(), selection.left()), m_model->index(selection.bottom(), selection.right())), QItemSelectionModel::ClearAndSelect);
}

void NodeItem::clearSelection()
{
    if (!m_selectionModel)
        return;

    m_selectionModel->clearSelection();
}

void NodeItem::cancelSelection()
{
    setKeepMouseGrab(false);
    if (m_selectionModel)
        m_selectionModel->clearCurrentIndex();
    stopPressAndHold();
    setSelecting(false);
}

void NodeItem::mousePressEvent(QMouseEvent *event)
{
    if (m_selectionMode == NoSelection || !m_selectionModel) {
        event->ignore();
        return;
    }

    QModelIndex index = nodeAt(event->pos());
    if (isEnabled(index)) {
        m_selectionModel->setCurrentIndex(index, QItemSelectionModel::Current);
        startPressAndHold();
        emit pressed(index);
    }
    event->accept();
}

void NodeItem::mouseMoveEvent(QMouseEvent *event)
{
    if (m_selectionMode == NoSelection || !m_selectionModel) {
        event->ignore();
        return;
    }

    QModelIndex index = nodeAt(event->pos());
    if (isEnabled(index)) {
        QModelIndex currentIndex = m_selectionModel->currentIndex();
        if (index != currentIndex) {
            stopPressAndHold();
            if (!keepMouseGrab())
                m_selectionModel->clearCurrentIndex();
        }
        if (index.isValid() && keepMouseGrab()) {
            if (m_selectionMode == MultiSelection)
                m_selectionModel->select(QItemSelection(topLeft(index, currentIndex), bottomRight(index, currentIndex)), QItemSelectionModel::ClearAndSelect);
            else
                m_selectionModel->setCurrentIndex(index, QItemSelectionModel::SelectCurrent);
            emit ensureVisible(nodeRect(index));
            emit activated(index);
        }
    }
    event->accept();
}

void NodeItem::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_selectionMode != NoSelection && m_selectionModel && !keepMouseGrab()) {
        QModelIndex index = nodeAt(event->pos());
        if (isEnabled(index)) {
            emit released(index);
            if (index == m_selectionModel->currentIndex()) {
                m_selectionModel->setCurrentIndex(index, QItemSelectionModel::SelectCurrent);
                emit clicked(index);
            }
            emit activated(index);
        }
    } else {
        cancelSelection();
    }
    event->setAccepted(m_selectionMode != NoSelection && m_selectionModel);
}

void NodeItem::mouseUngrabEvent()
{
    cancelSelection();
}

void NodeItem::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_pressTimer) {
        setSelecting(true);
        stopPressAndHold();
        setKeepMouseGrab(true);
        if (m_selectionModel) {
            QModelIndex index = m_selectionModel->currentIndex();
            if (isEnabled(index)) {
                m_selectionModel->select(index, QItemSelectionModel::SelectCurrent | QItemSelectionModel::Clear);
                emit ensureVisible(nodeRect(index));
                emit activated(index);
            }
        }
    }
}

void NodeItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    if (newGeometry.size() != oldGeometry.size())
        relayout();
}

void NodeItem::itemChange(ItemChange change, const ItemChangeData &data)
{
    QQuickItem::itemChange(change, data);
    if (change == ItemEnabledHasChanged)
        update();
}

class QuickItemNode : public QSGTransformNode
{
public:
    QList<QSGNode *> nodes;
};

class QuickViewNode : public QSGTransformNode
{
public:
    QuickViewNode(int rows, int columns) : m_rows(rows), m_nodes(rows * columns) { }

    QuickItemNode *itemNode(int row, int column) const
    {
        return m_nodes.value(row + column * m_rows);
    }

    void setItemNode(int row, int column, QuickItemNode *node)
    {
        m_nodes[row + column * m_rows] = node;
    }

private:
    int m_rows = 0;
    QVector<QuickItemNode *> m_nodes;
};

static void raiseNode(QSGNode *node)
{
    if (!node || !node->parent())
        return;

    QSGNode *parentNode = node->parent();
    parentNode->removeChildNode(node);
    parentNode->appendChildNode(node);
}

static void lowerNode(QSGNode *node)
{
    if (!node || !node->parent())
        return;

    QSGNode *parentNode = node->parent();
    parentNode->removeChildNode(node);
    parentNode->prependChildNode(node);
}

QSGNode *NodeItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    int count = NodeItem::count();
    int rows = NodeItem::rows();
    int columns = NodeItem::columns();

    QuickViewNode *viewNode = static_cast<QuickViewNode *>(oldNode);

    if (m_rebuild) {
        delete viewNode;
        viewNode = nullptr;

        if (count > 0) {
            viewNode = new QuickViewNode(rows, columns);

            for (int column = 0; column < columns; ++column) {
                for (int row = 0; row < rows; ++row) {
                    QuickItemNode *itemNode = new QuickItemNode;
                    viewNode->appendChildNode(itemNode);

                    QSGNode *parentNode = itemNode;
                    for (NodeDelegate *delegate : qAsConst(m_delegates)) {
                        QSGNode *node = delegate->createNode(this);
                        Q_ASSERT(node);
                        itemNode->nodes += node;
                        parentNode->appendChildNode(node);
                        parentNode = node;
                    }

                    viewNode->setItemNode(row, column, itemNode);
                }
            }
        }

        m_rebuild = false;
        m_relayout = true;
    }

    if (m_relayout) {
        for (int column = 0; column < columns; ++column) {
            for (int row = 0; row < rows; ++row) {
                QuickItemNode *itemNode = viewNode->itemNode(row, column);
                if (!itemNode)
                    continue;

                const QRectF geometry = nodeRect(m_model->index(row, column));
                itemNode->setMatrix(QTransform::fromTranslate(geometry.x(), geometry.y()));
            }
        }

        if (m_model)
            m_updates = QItemSelection(m_model->index(0, 0), m_model->index(rows - 1, columns - 1));

        m_relayout = false;
    }

    // lower deselected nodes
    if (!m_deselected.isEmpty()) {
        for (const QItemSelectionRange &range : m_deselected) {
            const QList<QModelIndex> indexes = range.indexes();
            for (const QModelIndex &index : indexes)
                lowerNode(viewNode->itemNode(index.row(), index.column()));
        }
        m_selected.clear();
    }

    // raise selected nodes
    if (!m_selected.isEmpty()) {
        for (const QItemSelectionRange &range : m_selected) {
            const QList<QModelIndex> indexes = range.indexes();
            for (const QModelIndex &index : indexes)
                raiseNode(viewNode->itemNode(index.row(), index.column()));
        }
        m_selected.clear();
    }

    // raise current node
    if (m_current.isValid()) {
        raiseNode(viewNode->itemNode(m_current.row(), m_current.column()));
        m_current = QModelIndex();
    }

    if (!m_updates.isEmpty()) {
        for (const QItemSelectionRange &range : m_updates) {
            for (int row = range.top(); row <= range.bottom(); ++row) {
                for (int column = range.left(); column <= range.right(); ++column) {
                    QuickItemNode *itemNode = viewNode->itemNode(row, column);
                    if (!itemNode || itemNode->nodes.count() != m_delegates.count())
                        continue;

                    const QModelIndex index = m_model->index(row, column);
                    if (!isEnabled(index))
                        lowerNode(itemNode);

                    for (int i = 0; i < m_delegates.count(); ++i) {
                        NodeDelegate *delegate = m_delegates.at(i);
                        delegate->updateNode(itemNode->nodes.at(i), index, this);
                    }
                }
            }
        }
        m_updates.clear();
    }

    return viewNode;
}

void NodeItem::modelReset()
{
    rebuild();
    updateImplicitSize();
    emit rowsChanged();
    emit columnsChanged();
    emit countChanged();
}

void NodeItem::rowsChange()
{
    rebuild();
    updateImplicitSize();
    emit rowsChanged();
    emit countChanged();
}

void NodeItem::columnsChange()
{
    rebuild();
    updateImplicitSize();
    emit columnsChanged();
    emit countChanged();
}

void NodeItem::dataChange(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    m_updates.merge(QItemSelection(topLeft, bottomRight), QItemSelectionModel::Select);
    update();
}

void NodeItem::currentChange(const QModelIndex &current, const QModelIndex &previous)
{
    m_updates.merge(QItemSelection(current, current), QItemSelectionModel::Select);
    m_updates.merge(QItemSelection(previous, previous), QItemSelectionModel::Select);
    m_current = current;
    update();
}

void NodeItem::selectionChange(const QItemSelection &selected, const QItemSelection &deselected)
{
    if (m_selectionModel) {
        QItemSelectionRange range = m_selectionModel->selection().value(0);
        setSelection(QRect(range.left(), range.top(), range.right() - range.left() + 1, range.bottom() - range.top() + 1));
    }

    m_updates.merge(selected, QItemSelectionModel::Select);
    m_updates.merge(deselected, QItemSelectionModel::Select);
    m_deselected = deselected;
    m_selected = selected;
    update();
}

void NodeItem::rebuild()
{
    if (m_rebuild)
        return;

    m_rebuild = true;
    update();
}

void NodeItem::relayout()
{
    if (m_relayout)
        return;

    m_relayout = true;
    update();
}

void NodeItem::fullUpdate()
{
    if (!m_model)
        return;

    m_updates = QItemSelection(m_model->index(0, 0), m_model->index(m_model->rowCount() - 1, m_model->columnCount() - 1));
    update();
}

void NodeItem::startPressAndHold()
{
    stopPressAndHold();
    m_pressTimer = startTimer(QGuiApplication::styleHints()->mousePressAndHoldInterval());
}

void NodeItem::stopPressAndHold()
{
    if (m_pressTimer <= 0)
        return;

    killTimer(m_pressTimer);
    m_pressTimer = 0;
}

void NodeItem::updateImplicitSize()
{
    int rows = NodeItem::rows();
    int columns = NodeItem::columns();
    setImplicitSize(m_nodeWidth * columns + m_nodeSpacing * (columns - 1),
                    m_nodeHeight * rows + m_nodeSpacing * (rows -1 ));
}

void NodeItem::delegates_append(QQmlListProperty<NodeDelegate> *property, NodeDelegate *delegate)
{
    NodeItem *item = static_cast<NodeItem *>(property->object);
    connect(delegate, &NodeDelegate::changed, item, &NodeItem::fullUpdate);
    item->m_delegates.append(delegate);
}

int NodeItem::delegates_count(QQmlListProperty<NodeDelegate> *property)
{
    NodeItem *item = static_cast<NodeItem *>(property->object);
    return item->m_delegates.count();
}

NodeDelegate *NodeItem::delegates_at(QQmlListProperty<NodeDelegate> *property, int index)
{
    NodeItem *item = static_cast<NodeItem *>(property->object);
    return item->m_delegates.value(index);
}

void NodeItem::delegates_clear(QQmlListProperty<NodeDelegate> *property)
{
    NodeItem *item = static_cast<NodeItem *>(property->object);
    for (NodeDelegate *delegate : qAsConst(item->m_delegates))
        disconnect(delegate, &NodeDelegate::changed, item, &NodeItem::fullUpdate);
    item->m_delegates.clear();
}
