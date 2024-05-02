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

protected:
    QGradientStops *gradientStops(const MultiGradient &multiGradient) const;

private:
    void setupParentNode(QSGNode *node, const QModelIndex &index, NodeItem *item);
};

#endif
