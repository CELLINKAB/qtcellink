#ifndef MULTIGRADIENTDELEGATE_H
#define MULTIGRADIENTDELEGATE_H

#include <QBrush>
#include <QCache>

#include <DxUi/uiglobal.h>

#include "nodedelegate.h"
#include "multigradientinterface.h"

class Q_DECL_EXPORT MultiGradientDelegate : public ProgressDelegate
{
    Q_OBJECT

public:
    explicit MultiGradientDelegate(QObject *parent = nullptr);

    void updateNode(QSGNode *node, const QModelIndex &index, NodeItem *item) override;
    QSGNode *createNode(NodeItem *item) override;

    const static QCache<uint, QGradientStops> &cache() { return m_cache; }

public slots:
    void onItemSelectionChanged();

protected:
    QGradientStops *getGradients(const QModelIndex &index, MultiGradientInterface::Gradients &gradients, NodeItem *item);

private:
    bool m_itemSelectionChanged = false;
    static QCache<uint, QGradientStops> m_cache;
};

#endif
