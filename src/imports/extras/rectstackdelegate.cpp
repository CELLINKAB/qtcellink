#include "rectstackdelegate.h"
#include "irectstack.h"
#include "nodeitem.h"

#include <QtQuick/private/qsgadaptationlayer_p.h>
#include <QtQuick/private/qsgdefaultinternalrectanglenode_p.h>

RectStackDelegate::RectStackDelegate(QObject *parent) :
    ProgressDelegate(parent)
{

}

void RectStackDelegate::setupChildNodes(const RectStack *rectStack, QSGNode *node, const QModelIndex index, NodeItem *item)
{
    QSGInternalRectangleNode *parentNode = static_cast<QSGInternalRectangleNode *>(node);
    QRectF parentRect = nodeRect(index, item);

    QRectF prevRect = parentRect;
    qreal originTop = parentRect.y();
    qreal totalHeightAccumulated = 0;
    bool totalHeightReached = false;

    for (const QPair<qreal, QColor> &fractionAndColor : rectStack->data) {
        qreal fraction = fractionAndColor.first;
        qreal currentChildHeight = fraction * parentRect.height();
        totalHeightAccumulated += currentChildHeight;
        QColor color = fractionAndColor.second;

        QRectF childRect = prevRect;
        childRect.setY(originTop + prevRect.height() - currentChildHeight);
        childRect.setHeight(currentChildHeight);
        prevRect.setHeight(prevRect.height() - currentChildHeight);

        QSGDefaultInternalRectangleNode *childNode = new QSGDefaultInternalRectangleNode;
        parentNode->appendChildNode(childNode);

        // we reached parent's max height
        if (totalHeightAccumulated >= parentRect.height()) {
            childRect.setY(originTop);
            totalHeightReached = true;
        }
        childNode->setRect(childRect);
        childNode->setColor(color);
        childNode->setAntialiasing(true);
        childNode->update();

        if (totalHeightReached)
            break;
    }
}

void RectStackDelegate::updateNode(QSGNode *node, const QModelIndex &index, NodeItem *item)
{
    IRectStack *model = dynamic_cast<IRectStack*>(item->model());

    Q_ASSERT(model);
    Q_ASSERT(node);
    Q_ASSERT(item);

    int rectStackRole = model->rectStackRole();
    RectStack rectStack = index.data(rectStackRole).value<RectStack>();
    QSGInternalRectangleNode *parentNode = static_cast<QSGInternalRectangleNode *>(node);

    if (parentNode->childCount())
        parentNode->removeAllChildNodes();

    bool isSelected = item->selectionModel()->isSelected(index);
    bool showAllLiquids = index.data(rectStackRole + 1).toBool();

    if (rectStack.data.size() > 0 && (isSelected || showAllLiquids)) {
        setupChildNodes(&rectStack, parentNode, index, item);
        setupParentNode(node, index, item);
    } else {
        ProgressDelegate::updateNode(node, index, item);
    }
}

void RectStackDelegate::setParentNodeGradient(QSGNode *node, const QModelIndex &index, NodeItem *item)
{
    QSGInternalRectangleNode *parentNode = static_cast<QSGInternalRectangleNode *>(node);
    if (QGradientStops *stops = nodeGradientStops(index, item)) {
        parentNode->setGradientStops(*stops);
        parentNode->setGradientVertical(nodeGradientOrientation(index, item) == Qt::Vertical);
    } else {
        parentNode->setGradientStops(QGradientStops());
        parentNode->setColor(nodeColor(index, item));
    }
}

void RectStackDelegate::setupParentNode(QSGNode *node, const QModelIndex &index, NodeItem *item)
{
    QSGInternalRectangleNode *parentNode = static_cast<QSGInternalRectangleNode *>(node);
    QRectF parentRect = nodeRect(index, item);
    parentNode->setRect(parentRect);
    parentNode->setRadius(nodeRadius(index, item));
    parentNode->setPenColor(nodeBorderColor(index, item));
    parentNode->setPenWidth(nodeBorderWidth(index, item));
    setParentNodeGradient(node, index, item);

    parentNode->update();
}
