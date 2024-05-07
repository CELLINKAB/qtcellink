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

        QGradientStops *gradients = nullptr;
        if (multiGradient.gradientType == MultiGradient::Full)
            gradients = fullGradientStops(multiGradient);
        else if (multiGradient.gradientType == MultiGradient::BottomToPosition)
            gradients = bottomToTopGradientStops(multiGradient, index, item);

        rectNode->setGradientStops(*gradients);
        rectNode->setGradientVertical(nodeGradientOrientation(index, item) == Qt::Vertical);

        rectNode->setPenColor(nodeBorderColor(index, item));
        rectNode->setPenWidth(nodeBorderWidth(index, item));
        rectNode->update();

    } else {
        ProgressDelegate::updateNode(node, index, item);
    }
}

QSGNode *MultiGradientDelegate::createNode(NodeItem *item)
{
    connect(item, &NodeItem::selectionChanged, this, &MultiGradientDelegate::onItemSelectionChanged);
    return ProgressDelegate::createNode(item);
}

void MultiGradientDelegate::onItemSelectionChanged()
{
    m_itemSelectionChanged = true;
}

QGradientStops *MultiGradientDelegate::fullGradientStops(const MultiGradient &multiGradient) const
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

QGradientStops *MultiGradientDelegate::bottomToTopGradientStops(const MultiGradient &multiGradient, const QModelIndex &index, NodeItem *item)
{
    static QCache<uint, QGradientStops> cache;

//    if (m_itemSelectionChanged) {
//        cache.clear();
//        m_itemSelectionChanged = false;
//    }

//    if (!cache.contains(multiGradient.cacheKey)) {
        QGradientStops *stops = new QGradientStops;
//        qreal totalPDivCount = totalPercentageDivCount(multiGradient);
        qreal position = 1.0 - multiGradient.data.last().first;
        qreal totalP = totalPercentage(multiGradient);
        position = std::clamp(position, 0.0, 1.0);

        stops->append(qMakePair(0.0, nodeColor(index, item)));
        stops->append(qMakePair(position, nodeColor(index, item)));

        for (auto it = multiGradient.data.rbegin(); it != multiGradient.data.rend(); it++) {
            stops->append(qMakePair(position, it->second));
            position += it->first / totalP;
            position = std::clamp(position, 0.0, 1.0);

            // Adding a stop at position 1.0 is redundant,
            // the engine will automatically fill from last position until 1.0,
            // if there is no other stop in between.
            // it also produces weird positioned gradients in some cases
            if (!qFuzzyCompare(position, 1.0))
                stops->append(qMakePair(position, it->second));

        }
//        cache.insert(multiGradient.cacheKey, stops);
//    }

//    return cache[multiGradient.cacheKey];
        return stops;
}

qreal MultiGradientDelegate::totalPercentageDivCount(const MultiGradient &multiGradient) const
{
    qreal total = 0;
    for (const auto &gradient : multiGradient.data) {
        total += gradient.first;
    }

    return total / multiGradient.data.size();
}

qreal MultiGradientDelegate::totalPercentage(const MultiGradient &multiGradient) const
{
    qreal total = 0;
    for (const auto &gradient : multiGradient.data) {
        total += gradient.first;
    }

    return total;
}
