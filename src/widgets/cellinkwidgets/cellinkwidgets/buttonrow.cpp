#include "cellinkwidgets_stable.h"

#include "buttonrow.h"
#include "cellinkwidgets/utils.h"

class ButtonRowPrivate {
    Q_DECLARE_PUBLIC(ButtonRow)
public:
    ButtonRow* const q_ptr;

    QVector<RowButton*> m_buttons{};
    int m_currentIndex = -1;
};

ButtonRow::ButtonRow(QWidget *parent) :
    QWidget(parent),
    d_ptr(new ButtonRowPrivate{this})
{
    setLayout(new QHBoxLayout(this));
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->setSpacing(0);
    setCursor(Qt::PointingHandCursor);
    setMinimumHeight(30);
}

ButtonRow::~ButtonRow() = default;

void ButtonRow::addButton(const QString &text, bool enabled)
{
    Q_D(ButtonRow);

    auto button = new RowButton(this);
    d->m_buttons.append(button);
    const auto index = d->m_buttons.size() - 1;

    connect(button, &RowButton::released, this, [this, d, button](){
        for (int i = 0; i < d->m_buttons.size(); i++) {
            // Set all buttons but the clicked one to unchecked
            d->m_buttons[i]->setChecked(d->m_buttons[i] == button);
            if (d->m_buttons[i] == button) {
                setCurrentIndex(i);
            }
        }
    });

    button->setIndex(index);
    button->setText(text);
    button->setEnabled(enabled);

    if (d->m_currentIndex == index)
        button->setChecked(true);

    if (d->m_currentIndex < 0 && enabled)
        setCurrentIndex(index);

    layout()->addWidget(button);
}

void ButtonRow::addButtons(const QStringList &texts)
{
    for (const auto& text : texts) {
        addButton(text);
    }
}

void ButtonRow::updateButton(const int index, const QString& text)
{
    Q_D(ButtonRow);

    if (index < 0 || index >= d->m_buttons.size()) {
        qCritical() << __FUNCTION__ << "Invalid index:" << index << text;
        return;
    }

    d->m_buttons.at(index)->setText(text);
}

void ButtonRow::updateSelectedColor(const int index, QColor selectedColor)
{
    Q_D(ButtonRow);

    if (index < 0 || index >= d->m_buttons.size()) {
        qCritical() << __FUNCTION__ << "Invalid index:" << index << selectedColor.name();
        return;
    }

    d->m_buttons.at(index)->setStyleSheet(QString("selection-background-color: %1").arg(selectedColor.name()));
}

void ButtonRow::setCurrentIndex(int index)
{
    Q_D(ButtonRow);

    if (d->m_currentIndex == index) {
        return;
    }

    if (d->m_currentIndex >= 0)
        d->m_buttons[d->m_currentIndex ]->setChecked(false);

    d->m_currentIndex = index;

    if (index >= 0)
        d->m_buttons[index]->setChecked(true);

    emit currentIndexChanged(index);
}

int ButtonRow::currentIndex() const
{
    Q_D(const ButtonRow);
    return d->m_currentIndex;
}

void ButtonRow::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    const auto rect = QRect(0, 0, size().width(), size().height());
    const auto radius = 4;
    painter.setPen(QPen(palette().windowText(), 1));
    painter.drawRoundedRect(rect, radius, radius);

}

void ButtonRow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    // Create mask to clip child buttons to the rounded rect boundary
    // This is done in resizeEvent since the widget is resized when we add buttons
    Utils::setRoundedMask(this);
}

QString ButtonRow::text(int index) const
{
    Q_D(const ButtonRow);

    if (index < 0 || index >= d->m_buttons.size())
        return {};

    return d->m_buttons[index]->text();
}

QString ButtonRow::currentText() const
{
    return text(currentIndex());
}

void ButtonRow::setButtonEnabled(int index, bool enabled)
{
    Q_D(const ButtonRow);

    if (index < 0 || index >= d->m_buttons.size())
        return;

    d->m_buttons[index]->setEnabled(enabled);

    // activate next button if this one can't be selected anymore
    if (index == currentIndex() && !enabled) {
        auto it = std::find_if(d->m_buttons.begin(), d->m_buttons.end(), [](const auto &b) { return b->isEnabled(); });
        setCurrentIndex(it != d->m_buttons.end() ? std::distance(d->m_buttons.begin(), it) : -1);
    }
}

int ButtonRow::count() const { return d_ptr->m_buttons.size(); }

void ButtonRow::showButton(const QString& text, bool show)
{
    Q_D(ButtonRow);
    for (auto button : d->m_buttons) {
        if (button->text() == text) {
            button->setVisible(show);
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

class RowButtonPrivate {
    Q_DECLARE_PUBLIC(RowButton)
public:
    RowButton* const q_ptr;

    int m_index = 0;
};

RowButton::RowButton(QWidget *parent) :
    QToolButton(parent),
    d_ptr(new RowButtonPrivate{this})
{
    setCheckable(true);
    setContentsMargins(0, 0, 0, 0);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

RowButton::~RowButton() = default;

void RowButton::setIndex(int index)
{
    Q_D(RowButton);

    if (d->m_index == index) {
        return;
    }

    d->m_index = index;
    emit indexChanged();
}

int RowButton::index() const
{
    Q_D(const RowButton);
    return d->m_index;
}

void RowButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    Q_D(RowButton);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const auto rect = QRect(0, 0, size().width(), size().height());

    if (isChecked())
        painter.fillRect(rect, isEnabled() ? palette().highlight() : palette().mid());

    painter.setPen(QPen(Qt::black, 1));
    if (d->m_index != 0) {
        // All row buttons except the leftmost draw their left border
        painter.drawLine(0, 0, 0, rect.height());
    }

    QStyleOptionToolButton opt;
    initStyleOption(&opt);
    if (isChecked()) {
        opt.palette.setBrush(QPalette::ButtonText, palette().highlightedText());
    }
    style()->drawComplexControl(QStyle::CC_ToolButton, &opt, &painter, this);
}

QSize RowButton::minimumSizeHint() const
{
    auto size = QToolButton::minimumSizeHint();
    size.rheight() = std::min(size.height(), 20);
    return size;
}
