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
        QRectF rect = nodeRect(index, item);
        rectNode->setRect(rect);
        rectNode->setRadius(nodeRadius(index, item));

        QGradientStops *gradients = gradientStops(multiGradient);
        rectNode->setGradientStops(*gradients);
        rectNode->setGradientVertical(nodeGradientOrientation(index, item) == Qt::Vertical);

        rectNode->setPenColor(nodeBorderColor(index, item));
        rectNode->setPenWidth(nodeBorderWidth(index, item));
        rectNode->update();

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
            position = std::clamp(position, 0.0, 1.0);

            // Adding a stop at position 1.0 is redundant,
            // the engine will automatically fill from last position until 1.0,
            // if there is no other stop in between.
            // it also produces weird positioned gradients in some cases
            if (!qFuzzyCompare(position, 1.0))
                stops->append(qMakePair(position, it->second));

        }
        cache.insert(multiGradient.cacheKey, stops);
    }

    return cache[multiGradient.cacheKey];
}
