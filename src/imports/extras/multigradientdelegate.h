#ifndef MULTIGRADIENTDELEGATE_H
#define MULTIGRADIENTDELEGATE_H

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

public slots:
    void onItemSelectionChanged();

protected:
    QGradientStops *fullGradientStops(const MultiGradient &multiGradient) const;
    QGradientStops *bottomToTopGradientStops(const MultiGradient &multiGradient, const QModelIndex &index, NodeItem *item);

private:
    bool m_itemSelectionChanged = false;

private:
    qreal totalPercentageDivCount(const MultiGradient &multiGradient) const;
    qreal totalPercentage(const MultiGradient &multiGradient) const;
};

#endif
