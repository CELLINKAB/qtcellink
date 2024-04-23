#ifndef RECTSTACKDELEGATE_H
#define RECTSTACKDELEGATE_H

#include <DxUi/uiglobal.h>

#include "nodedelegate.h"
#include "irectstack.h"

class DX_UI_EXPORT RectStackDelegate : public ProgressDelegate
{
    Q_OBJECT

public:
    RectStackDelegate(QObject *parent = nullptr);

    void updateNode(QSGNode *node, const QModelIndex &index, NodeItem *item) override;

private:
    void setParentNodeGradient(QSGNode *node, const QModelIndex &index, NodeItem *item);
    void setupParentNode(QSGNode *node, const QModelIndex &index, NodeItem *item);
    void setupChildNodes(const RectStack *rectStack, QSGNode *node, const QModelIndex index, NodeItem *item);
};

#endif
