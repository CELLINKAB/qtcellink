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

    QList<TargetLiquid *> liquids = model->multiGradientData(index);
    if (liquids.size() > 0) {
        QRectF rect = nodeRect(index, item);
        rectNode->setRect(rect);
        rectNode->setRadius(nodeRadius(index, item));

        QGradientStops *gradients = getGradients(index, liquids, item);

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

QGradientStops *MultiGradientDelegate::getGradients(const QModelIndex &index, const QList<TargetLiquid *> &liquids, NodeItem *item)
{
    QGradientStops *stops = new QGradientStops;
    qreal minGradientHeight = 0.05;

    qreal maxVolumeWithinAllWells = index.data(TargetLiquidModel::MaxVolume).toDouble();
    qreal prevY = 1.0 - minGradientHeight - totalPercentage(index, liquids, maxVolumeWithinAllWells);
    prevY = std::clamp(prevY, 0.0, 1.0);

    stops->append(qMakePair(0.0, nodeColor(index, item)));
    stops->append(qMakePair(prevY, nodeColor(index, item)));

    for (auto it = liquids.rbegin(); it != liquids.rend(); it++) {
        qreal volume = (*it)->volumeAt(index.row(), index.column());
        stops->append(qMakePair(prevY, (*it)->liquid()->color()));
        prevY += std::clamp(volume / maxVolumeWithinAllWells, minGradientHeight, 1.0);

        if (!qFuzzyCompare(prevY, 1.0) && !qFuzzyIsNull(prevY))
            stops->append(qMakePair(prevY, (*it)->liquid()->color()));
    }

    return stops;
}

qreal MultiGradientDelegate::targetLiquidsTotalVolume(const QModelIndex &index, const QList<TargetLiquid *> &targetLiquids) const
{
    qreal totalVolume = 0;
    for (const TargetLiquid *targetLiquid : targetLiquids)
        totalVolume += targetLiquid->volumeAt(index.row(), index.column());

    return totalVolume;
}

qreal MultiGradientDelegate::totalPercentage(const QModelIndex &index, const QList<TargetLiquid *> &targetLiquids, qreal maxVolume) const
{
    qreal totalPercentage = 0;

    for (const TargetLiquid *targetLiquid : targetLiquids) {
        totalPercentage += targetLiquid->volumeAt(index.row(), index.column()) /  maxVolume;
    }

    return totalPercentage;
}

qreal MultiGradientDelegate::maxWellVolume(const QModelIndex &index) const
{
    qreal maxVolume = 0;
    for (int i = 0; i < index.model()->rowCount(); i++) {
        for (int j = 0; j < index.model()->columnCount(); j++) {
            bool ok;
            qreal totalWellVolumeAtIndex = index.model()->index(i, j).data(TargetLiquidModel::MaxVolume).toDouble(&ok);
            if (!ok)
                continue;

            if (totalWellVolumeAtIndex > maxVolume)
                maxVolume = totalWellVolumeAtIndex;
        }
    }

    return maxVolume;
}
