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

#ifndef NODEITEM_H
#define NODEITEM_H

#include <QtQuick/qquickitem.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qitemselectionmodel.h>
#include <QtQml/qqmllist.h>

class NodeDelegate;

class NodeItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)
    Q_PROPERTY(QRect selection READ selection NOTIFY selectionChanged)
    Q_PROPERTY(QObject *model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(SelectionMode selectionMode READ selectionMode WRITE setSelectionMode NOTIFY selectionModeChanged)
    Q_PROPERTY(QItemSelectionModel *selectionModel READ selectionModel WRITE setSelectionModel NOTIFY selectionModelChanged)
    Q_PROPERTY(bool pressed READ isPressed NOTIFY pressedChanged)
    Q_PROPERTY(bool selecting READ isSelecting NOTIFY selectingChanged)
    Q_PROPERTY(qreal nodeWidth READ nodeWidth WRITE setNodeWidth NOTIFY nodeWidthChanged)
    Q_PROPERTY(qreal nodeHeight READ nodeHeight WRITE setNodeHeight NOTIFY nodeHeightChanged)
    Q_PROPERTY(qreal nodeSpacing READ nodeSpacing WRITE setNodeSpacing NOTIFY nodeSpacingChanged)
    Q_PROPERTY(qreal nodeScaleX READ nodeScaleX WRITE setNodeScaleX NOTIFY nodeScaleXChanged)
    Q_PROPERTY(qreal nodeScaleY READ nodeScaleY WRITE setNodeScaleY NOTIFY nodeScaleYChanged)
    Q_PROPERTY(QQmlListProperty<NodeDelegate> delegates READ delegates)

public:
    explicit NodeItem(QQuickItem *parent = nullptr);

    int count() const;

    int rows() const;
    void setRows(int rows);

    int columns() const;
    void setColumns(int columns);

    QRect selection() const;
    void setSelection(const QRect &selection);

    QObject *model() const;
    void setModel(QObject *model);

    enum SelectionMode { NoSelection, SingleSelection, MultiSelection };
    Q_ENUM(SelectionMode)

    SelectionMode selectionMode() const;
    void setSelectionMode(SelectionMode selectionMode);

    QItemSelectionModel *selectionModel() const;
    void setSelectionModel(QItemSelectionModel *selectionModel);

    bool isPressed() const;
    void setPressed(bool pressed);

    bool isSelecting() const;
    void setSelecting(bool selecting);

    qreal nodeWidth() const;
    void setNodeWidth(qreal nodeWidth);

    qreal nodeHeight() const;
    void setNodeHeight(qreal nodeHeight);

    qreal nodeSpacing() const;
    void setNodeSpacing(qreal nodeSpacing);

    qreal nodeScale() const;

    qreal nodeScaleX() const;
    void setNodeScaleX(qreal nodeScaleX);

    qreal nodeScaleY() const;
    void setNodeScaleY(qreal nodeScaleY);

    QQmlListProperty<NodeDelegate> delegates();

    bool isEnabled(const QModelIndex &index) const;
    bool isCurrent(const QModelIndex &index) const;
    bool isSelected(const QModelIndex &index) const;

    virtual QModelIndex nodeAt(const QPointF &pos) const;
    virtual QRectF nodeRect(const QModelIndex &index) const;

public slots:
    void selectAll();
    void select(const QRect &selection);
    void clearSelection();
    void cancelSelection();

signals:
    void countChanged();
    void rowsChanged();
    void columnsChanged();
    void selectionChanged();
    void modelChanged();
    void selectionModeChanged();
    void selectionModelChanged();
    void pressedChanged();
    void selectingChanged();
    void nodeWidthChanged();
    void nodeHeightChanged();
    void nodeSpacingChanged();
    void nodeScaleXChanged();
    void nodeScaleYChanged();
    void pressed(const QModelIndex &index);
    void released(const QModelIndex &index);
    void activated(const QModelIndex &index);
    void clicked(const QModelIndex &index);
    void ensureVisible(const QRectF &rect);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseUngrabEvent() override;
    void timerEvent(QTimerEvent *event) override;

    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    void itemChange(ItemChange change, const ItemChangeData &data) override;
    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *data) override;

    virtual void modelReset();
    virtual void rowsChange();
    virtual void columnsChange();
    virtual void dataChange(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    virtual void currentChange(const QModelIndex &current, const QModelIndex &previous);
    virtual void selectionChange(const QItemSelection &selected, const QItemSelection &deselected);

    void rebuild();
    void relayout();
    void fullUpdate();
    void startPressAndHold();
    void stopPressAndHold();
    void updateImplicitSize();

private:
    static void delegates_append(QQmlListProperty<NodeDelegate> *property, NodeDelegate *delegate);
    static int delegates_count(QQmlListProperty<NodeDelegate> *property);
    static NodeDelegate *delegates_at(QQmlListProperty<NodeDelegate> *property, int index);
    static void delegates_clear(QQmlListProperty<NodeDelegate> *property);

    bool m_rebuild = true;
    bool m_relayout = true;
    bool m_hasNodeScaleX = false;
    bool m_hasNodeScaleY = false;
    bool m_hasRows = false;
    bool m_hasColumns = false;
    bool m_pressed = false;
    bool m_selecting = false;
    int m_rows = 0;
    int m_columns = 0;
    int m_pressTimer = 0;
    qreal m_nodeWidth = 10;
    qreal m_nodeHeight = 10;
    qreal m_nodeSpacing = 0;
    qreal m_nodeScaleX = 1;
    qreal m_nodeScaleY = 1;
    QAbstractItemModel *m_model = nullptr;
    SelectionMode m_selectionMode = NoSelection;
    QItemSelectionModel *m_selectionModel = nullptr;
    QList<NodeDelegate *> m_delegates;
    QModelIndex m_current;
    QItemSelection m_updates;
    QItemSelection m_selected;
    QItemSelection m_deselected;
    QRect m_selection;
};

#endif // NODEITEM_H
