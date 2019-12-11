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

#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QtQuick/private/qquickflickable_p.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qitemselectionmodel.h>
#include <QtQml/qqmllist.h>
#include <climits>

class NodeItem;
class NodeDelegate;

class NodeView : public QQuickFlickable
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)
    Q_PROPERTY(QObject *model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QRect selection READ selection NOTIFY selectionChanged)
    Q_PROPERTY(SelectionMode selectionMode READ selectionMode WRITE setSelectionMode NOTIFY selectionModeChanged)
    Q_PROPERTY(QItemSelectionModel *selectionModel READ selectionModel WRITE setSelectionModel NOTIFY selectionModelChanged)
    Q_PROPERTY(bool selecting READ isSelecting NOTIFY selectingChanged)
    Q_PROPERTY(qreal nodeWidth READ nodeWidth WRITE setNodeWidth NOTIFY nodeWidthChanged)
    Q_PROPERTY(qreal nodeHeight READ nodeHeight WRITE setNodeHeight NOTIFY nodeHeightChanged)
    Q_PROPERTY(qreal nodeSpacing READ nodeSpacing WRITE setNodeSpacing NOTIFY nodeSpacingChanged)
    Q_PROPERTY(qreal nodeScaleX READ nodeScaleX WRITE setNodeScaleX NOTIFY nodeScaleXChanged)
    Q_PROPERTY(qreal nodeScaleY READ nodeScaleY WRITE setNodeScaleY NOTIFY nodeScaleYChanged)
    Q_PROPERTY(QQmlListProperty<NodeDelegate> delegates READ delegates)
    Q_PROPERTY(qreal zoomFactor READ zoomFactor NOTIFY zoomChanged)
    Q_PROPERTY(QPointF zoomPoint READ zoomPoint NOTIFY zoomChanged)
    Q_PROPERTY(qreal minimumZoomFactor READ minimumZoomFactor WRITE setMinimumZoomFactor NOTIFY minimumZoomFactorChanged)
    Q_PROPERTY(qreal maximumZoomFactor READ maximumZoomFactor WRITE setMaximumZoomFactor NOTIFY minimumZoomFactorChanged)
    Q_PROPERTY(NodeItem *nodeItem READ nodeItem WRITE setNodeItem NOTIFY nodeItemChanged)

public:
    explicit NodeView(QQuickItem *parent = nullptr);

    int count() const;

    int rows() const;
    void setRows(int rows);

    int columns() const;
    void setColumns(int columns);

    QObject *model() const;
    void setModel(QObject *model);

    QRect selection() const;

    enum SelectionMode { NoSelection, SingleSelection, MultiSelection };
    Q_ENUM(SelectionMode)

    SelectionMode selectionMode() const;
    void setSelectionMode(SelectionMode selectionMode);

    QItemSelectionModel *selectionModel() const;
    void setSelectionModel(QItemSelectionModel *selectionModel);

    bool isSelecting() const;
    void setSelecting(bool selecting);

    qreal nodeWidth() const;
    void setNodeWidth(qreal nodeWidth);

    qreal nodeHeight() const;
    void setNodeHeight(qreal nodeHeight);

    qreal nodeSpacing() const;
    void setNodeSpacing(qreal nodeSpacing);

    qreal nodeScaleX() const;
    void setNodeScaleX(qreal nodeScaleX);

    qreal nodeScaleY() const;
    void setNodeScaleY(qreal nodeScaleY);

    QQmlListProperty<NodeDelegate> delegates();

    qreal zoomFactor() const;
    QPointF zoomPoint() const;

    qreal minimumZoomFactor() const;
    void setMinimumZoomFactor(qreal factor);

    qreal maximumZoomFactor() const;
    void setMaximumZoomFactor(qreal factor);

    NodeItem *nodeItem() const;
    void setNodeItem(NodeItem *nodeItem);

public slots:
    void selectAll();
    void select(const QRect &selection);
    void clearSelection();
    void cancelSelection();
    void ensureVisible(const QRectF &rect);
    void zoom(qreal factor, const QPointF &point);
    void zoomIn(qreal factor = 0.1);
    void zoomOut(qreal factor = 0.1);

signals:
    void countChanged();
    void rowsChanged();
    void columnsChanged();
    void modelChanged();
    void selectionChanged();
    void selectionModeChanged();
    void selectionModelChanged();
    void selectingChanged();
    void nodeWidthChanged();
    void nodeHeightChanged();
    void nodeSpacingChanged();
    void nodeScaleXChanged();
    void nodeScaleYChanged();
    void nodeItemChanged();
    void minimumZoomFactorChanged();
    void maximumZoomFactorChanged();
    void zoomChanged(qreal factor, const QPointF &point);

protected slots:
    void resizeNodeItem();
    void updateContentSize();

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    QRectF viewportArea() const;
    QRectF selectionArea() const;

    qreal m_zoomFactor = 1.0;
    qreal m_minimumZoomFactor = 1.0;
    qreal m_maximumZoomFactor = std::numeric_limits<qreal>::max();
    QPointF m_zoomPoint;
    NodeItem *m_nodeItem = nullptr;
};

#endif // NODEVIEW_H
