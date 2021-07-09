#include "cellinkwidgets_stable.h"
#include "comboboxdelegate.h"

ComboBoxDelegate::ComboBoxDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{ }

ComboBoxDelegate::~ComboBoxDelegate() = default;

void ComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto newOpt(option);
    if (index.row() == m_selectedIndex) {
        // Bold text and add check icon to the row
        newOpt.font.setBold(true);
        const auto iconPath = ":/images/common/checkmark.svg";
        Q_ASSERT(QFile::exists(iconPath));
        QIcon icon(iconPath);
        newOpt.icon = icon;
        newOpt.decorationSize = QSize(11, 9);
        newOpt.decorationAlignment = Qt::AlignCenter;
        newOpt.features |= QStyleOptionViewItem::HasDecoration;
        newOpt.decorationPosition = QStyleOptionViewItem::Right;
    }
    // Removes focus rect but does not remove background highlighted color when hovering
    newOpt.state.setFlag(QStyle::State_HasFocus, false);

    QStyledItemDelegate::paint(painter, newOpt, index);
}

void ComboBoxDelegate::setSelectedIndex(int index) {
    m_selectedIndex = index;
}

QSize ComboBoxDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QFontMetrics metrics(option.font);
    const auto heightPadding = 8;
    return QSize(QStyledItemDelegate::sizeHint(option, index).width(), metrics.height() + heightPadding * 2);
}
