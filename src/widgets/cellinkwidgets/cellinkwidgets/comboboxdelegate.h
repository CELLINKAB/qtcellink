#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QStyledItemDelegate>
#include "cellinkwidgets_global.h"

class CELLINKWIDGETS_EXPORT ComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ComboBoxDelegate(QWidget *parent = nullptr);
    ~ComboBoxDelegate() override;

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

public slots:
    void setSelectedIndex(int index);

private:
    int m_selectedIndex = -1;
};

#endif // COMBOBOXDELEGATE_H
