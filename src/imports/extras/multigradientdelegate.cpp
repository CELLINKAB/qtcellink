#include "multigradientdelegate.h"
#include "imultigradient.h"
#include "nodeitem.h"
#include "targetliquidmodel.h"

#include <DxUi/liquid.h>
#include <DxUi/targetliquid.h>

#include <QtQuick/private/qsgadaptationlayer_p.h>
#include <QtQuick/private/qsgdefaultinternalrectanglenode_p.h>
#include <QCache>
#include <QVector>


QCache<uint, QGradientStops> MultiGradientDelegate::m_cache;

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

    QSGInternalRectangleNode *rectNode = static_cast<QSGInternalRectangleNode *>(node);

    IMultiGradient::Gradients grads = model->multiGradientData(index);
    if (grads.data.size() > 0) {
        QRectF rect = nodeRect(index, item);
        rectNode->setRect(rect);
        rectNode->setRadius(nodeRadius(index, item));

        QGradientStops *gradients = getGradients(index, grads, item);

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

QGradientStops *MultiGradientDelegate::getGradients(const QModelIndex &index, IMultiGradient::Gradients &gradients, NodeItem *item)
{
    QGradientStops *stops = new QGradientStops;
    qreal normalizedFractionSum = 0;

    // distribute the excess fraction (subtract from fractions bigger than min)
    if (gradients.totalAdjustedFraction > 1.0) {
        qreal excessFraction = gradients.totalAdjustedFraction - 1.0;
        qreal adjustedFraction = gradients.totalAdjustedFraction - gradients.minGradientFraction * gradients.data.count();

        for (auto it = gradients.data.begin(); it != gradients.data.end(); it++) {
            if (it->first > gradients.minGradientFraction) {
                qreal adjustment = (excessFraction * (it->first - gradients.minGradientFraction) / adjustedFraction);
                it->first -= adjustment;
            }
            normalizedFractionSum += it->first;
        }
    } else {
        normalizedFractionSum = gradients.totalAdjustedFraction;
    }

    qreal prevY = 1.0 - normalizedFractionSum;

    stops->append(qMakePair(0.0, nodeColor(index, item)));
    stops->append(qMakePair(prevY, nodeColor(index, item)));

    for (auto it = gradients.data.rbegin(); it != gradients.data.rend(); it++) {
        if (it->second->isValid()) {
            stops->append(qMakePair(prevY, it->second->liquid()->color()));
            prevY += std::clamp(it->first, gradients.minGradientFraction, 1.0);

            if (!qFuzzyCompare(prevY, 1.0) && !qFuzzyIsNull(prevY))
                stops->append(qMakePair(prevY, it->second->liquid()->color()));
        }
    }

    return stops;
}
