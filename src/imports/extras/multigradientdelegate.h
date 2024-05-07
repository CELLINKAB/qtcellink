#ifndef MULTIGRADIENTDELEGATE_H
#define MULTIGRADIENTDELEGATE_H

#include <QBrush>
#include <QCache>

#include <DxUi/uiglobal.h>

#include "nodedelegate.h"
#include "imultigradient.h"

class DX_UI_EXPORT MultiGradientDelegate : public ProgressDelegate
{
    Q_OBJECT

public:
    MultiGradientDelegate(QObject *parent = nullptr);

    void updateNode(QSGNode *node, const QModelIndex &index, NodeItem *item) override;
    QSGNode *createNode(NodeItem *item) override;

    const static QCache<uint, QGradientStops> &cache() { return m_cache; }

public:

public slots:
    void onItemSelectionChanged();

protected:
    QGradientStops *fullGradientStops(const MultiGradient &multiGradient);
    QGradientStops *bottomToTopGradientStops(const MultiGradient &multiGradient, const QModelIndex &index, NodeItem *item);

private:
    bool m_itemSelectionChanged = false;
    static QCache<uint, QGradientStops> m_cache;

private:
    qreal totalPercentageDivCount(const MultiGradient &multiGradient) const;
    qreal totalPercentage(const MultiGradient &multiGradient) const;
};

#endif
