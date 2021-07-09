#include "cellinkwidgets_stable.h"
#include "comboboxdelegate.h"
#include "combobox.h"

#include <QPainter>

class ComboBoxPrivate {
public:
    QString m_placeholderText;
    QColor m_borderColor;
};

ComboBox::ComboBox(QWidget *parent) :
    QComboBox(parent),
    d_ptr(new ComboBoxPrivate)
{
    auto delegate = new ComboBoxDelegate(this);
    delegate->setSelectedIndex(currentIndex()); // Start index
    setItemDelegate(delegate);
    setBorderColor(Qt::black);
    connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged), delegate, &ComboBoxDelegate::setSelectedIndex);
}

ComboBox::~ComboBox() = default;

void ComboBox::setPlaceholderText(QString text)
{
    Q_D(ComboBox);

    if (d->m_placeholderText == text) {
        return;
    }

    d->m_placeholderText = std::move(text);
    emit placeholderTextChanged(d->m_placeholderText);
}

QString ComboBox::placeholderText() const
{
    return d_ptr->m_placeholderText;
}

void ComboBox::setBorderColor(const QColor borderColor)
{
    Q_D(ComboBox);

    if (d->m_borderColor == borderColor) {
        return;
    }
    d->m_borderColor = std::move(borderColor);
}

void ComboBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOptionComboBox opt;
    initStyleOption(&opt);

    // We disable the subcontrol SC_ComboBoxArrow, and draw our own manually instead
    opt.subControls &= ~QStyle::SC_ComboBoxArrow;

    QPainter painter(this);

    painter.setPen(palette().color(QPalette::Text));
    style()->drawComplexControl(QStyle::CC_ComboBox, &opt, &painter, this);

    if (currentIndex() < 0) {
        opt.palette.setBrush(QPalette::ButtonText, opt.palette.brush(QPalette::ButtonText).color().lighter());
        opt.currentText = d_ptr->m_placeholderText;
    }
    // Draw the icon and text
    style()->drawControl(QStyle::CE_ComboBoxLabel, &opt, &painter, this);

    // Draw the arrow icon
    QStyleOption arrowOpt;
    const auto arrowRect = style()->subControlRect(QStyle::CC_ComboBox, &opt, QStyle::SC_ComboBoxArrow, this);
    arrowOpt.rect = arrowRect.marginsRemoved(QMargins(4, 4, 4, 4)); // Shrink a bit
    style()->drawPrimitive(QStyle::PE_IndicatorArrowDown, &arrowOpt, &painter, this);
}
