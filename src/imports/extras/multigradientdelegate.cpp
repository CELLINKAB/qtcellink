#include "multigradientdelegate.h"
#include "imultigradient.h"
#include "nodeitem.h"

#include <QtQuick/private/qsgadaptationlayer_p.h>
#include <QtQuick/private/qsgdefaultinternalrectanglenode_p.h>
#include <QCache>
#include <QVector>

MultiGradientDelegate::MultiGradientDelegate(QObject *parent) :
    ProgressDelegate(parent)
{

}

void MultiGradientDelegate::updateNode(QSGNode *node, const QModelIndex &index, NodeItem *item)
{
    IMultiGradient *model = dynamic_cast<IMultiGradient*>(item->model());

    Q_ASSERT(model);
    Q_ASSERT(node);
    Q_ASSERT(item);

    int multiGradientRole = model->multiGradientRole();
    QSGInternalRectangleNode *rectNode = static_cast<QSGInternalRectangleNode *>(node);

    MultiGradient multiGradient = index.data(multiGradientRole).value<MultiGradient>();
    if (multiGradient.data.size() > 0) {
        QGradientStops *gradients = gradientStops(multiGradient);
        rectNode->setGradientStops(*gradients);
        rectNode->setGradientVertical(nodeGradientOrientation(index, item) == Qt::Vertical);
        setupParentNode(node, index, item);
    } else {
        ProgressDelegate::updateNode(node, index, item);
    }
}

QGradientStops *MultiGradientDelegate::gradientStops(const MultiGradient &multiGradient) const
{
    static QCache<uint, QGradientStops> cache;

    if (!cache.contains(multiGradient.cacheKey)) {
        QGradientStops *stops = new QGradientStops;

        qreal position = 0;
        for (auto it = multiGradient.data.rbegin(); it != multiGradient.data.rend(); it++) {
            stops->append(qMakePair(position, it->second));
            position += it->first;
            stops->append(qMakePair(position, it->second));
        }
        cache.insert(multiGradient.cacheKey, stops);
    }

    return cache[multiGradient.cacheKey];
}

void MultiGradientDelegate::setupParentNode(QSGNode *node, const QModelIndex &index, NodeItem *item)
{
    QSGInternalRectangleNode *parentNode = static_cast<QSGInternalRectangleNode *>(node);
    QRectF parentRect = nodeRect(index, item);
    parentNode->setRect(parentRect);
    parentNode->setRadius(nodeRadius(index, item));
    parentNode->setPenColor(nodeBorderColor(index, item));
    parentNode->setPenWidth(nodeBorderWidth(index, item));

    parentNode->update();
}
