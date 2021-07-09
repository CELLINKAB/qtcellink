#include "cellinkwidgets_stable.h"
#include "numberoffsetwidget.h"
#include "ui_numberoffsetwidget.h"

namespace  {
    const auto BUTTON_FORMAT = "%.%1f";

    enum ButtonEnum {
        LeftButton = 0,
        MidButton = 1,
        RightButton = 2
    };
}

class NumberOffsetWidgetPrivate
{
    Q_DECLARE_PUBLIC(NumberOffsetWidget);

public:

    void updateDecimals(const int decimals)
    {
        m_ui.valueSpinBox->setDecimals(decimals);
        for(int i = 0; i < m_offsets.count(); ++i)
            updateOffset(i, m_offsets[i].toDouble());
    }

    void setVisibleOffsets(bool visible)
    {
        m_ui.horizontalLayout->setSpacing(visible ? 10 : 0);
        m_visibleOffsets = visible;
        m_ui.offsetButtons->setVisible(visible);
    }

    void updateOffset(const int index, const double offset)
    {
        const auto decimals = m_ui.valueSpinBox->decimals();

        const auto text = decimals ? QString::asprintf(QString(BUTTON_FORMAT).arg(decimals).toStdString().c_str(), offset)
                        : QString::number(offset);

        m_offsets[index] = text;
        m_ui.offsetButtons->updateButton(index, m_offsets[index]);
        m_ui.valueSpinBox->setSingleStep(m_ui.offsetButtons->currentText().toDouble());
    }

    void updateValue(double difference)
    {
        Q_Q(NumberOffsetWidget);
        difference *= m_ui.valueSpinBox->singleStep();
        const auto newValue = m_ui.valueSpinBox->value() + difference;
        m_ui.valueSpinBox->setValue(newValue);
        // return current value instead of set value in case it reached min or max
        emit q->valueChanged(m_ui.valueSpinBox->value());
    }

    NumberOffsetWidget* const q_ptr;

    Ui::NumberOffsetWidget m_ui{};
    QStringList m_offsets = {"0.01", "0.05", "0.10"};
    bool m_visibleOffsets = false;
    bool m_alwaysHidden = false;
    QString m_pixmapPath{};
};

NumberOffsetWidget::NumberOffsetWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new NumberOffsetWidgetPrivate{this})
{
    Q_D(NumberOffsetWidget);
    d->m_ui.setupUi(this);

    connect(d->m_ui.valueSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &NumberOffsetWidget::valueChanged);
    connect(d->m_ui.subtractButton, &QPushButton::clicked, [d](){
        d->updateValue(-1);
    });
    connect(d->m_ui.addButton, &QPushButton::clicked, [d](){
        d->updateValue(1);
    });

    d->m_ui.offsetButtons->addButtons(d->m_offsets);
    d->m_ui.offsetButtons->setCurrentIndex(1);

    connect(d->m_ui.offsetButtons, &ButtonRow::currentIndexChanged, [d](int newIndex){
        d->m_ui.valueSpinBox->setSingleStep(d->m_offsets[newIndex].toDouble());
    });

    auto palette = d->m_ui.spinboxWidget->palette();
    palette.setBrush(QPalette::Window, Qt::white);
    d->m_ui.spinboxWidget->setPalette(palette);
    d->m_ui.imageWidget->setVisible(false);

}

NumberOffsetWidget::~NumberOffsetWidget() = default;

double NumberOffsetWidget::minimum() const { return d_ptr->m_ui.valueSpinBox->minimum(); }

double NumberOffsetWidget::maximum() const { return d_ptr->m_ui.valueSpinBox->maximum(); }

int NumberOffsetWidget::decimals() const { return d_ptr->m_ui.valueSpinBox->decimals(); }

QString NumberOffsetWidget::suffix() const { return d_ptr->m_ui.valueSpinBox->suffix(); }

double NumberOffsetWidget::offset1() const { return d_ptr->m_offsets[LeftButton].toDouble(); }

double NumberOffsetWidget::offset2() const { return d_ptr->m_offsets[MidButton].toDouble(); }

double NumberOffsetWidget::offset3() const { return d_ptr->m_offsets[RightButton].toDouble(); }

QString NumberOffsetWidget::pixmap() const { return d_ptr->m_pixmapPath; };

double NumberOffsetWidget::value() const { return d_ptr->m_ui.valueSpinBox->value(); }

void NumberOffsetWidget::setValue(double value) { d_ptr->m_ui.valueSpinBox->setValue(value); }

void NumberOffsetWidget::setOffset1(double offset1) { d_ptr->updateOffset(LeftButton, offset1); }

void NumberOffsetWidget::setOffset2(double offset2) { d_ptr->updateOffset(MidButton, offset2); }

void NumberOffsetWidget::setOffset3(double offset3) { d_ptr->updateOffset(RightButton, offset3); }

double NumberOffsetWidget::currentOffset() const { return d_ptr->m_ui.offsetButtons->currentText().toDouble(); }

void NumberOffsetWidget::setMinimum(double min) { d_ptr->m_ui.valueSpinBox->setMinimum(min); }

void NumberOffsetWidget::setMaximum(double max) { d_ptr->m_ui.valueSpinBox->setMaximum(max); }

void NumberOffsetWidget::setDecimals(int decimals) { d_ptr->updateDecimals(decimals); }

void NumberOffsetWidget::setSuffix(QString suffix) { d_ptr->m_ui.valueSpinBox->setSuffix(suffix); }

QDoubleSpinBox* NumberOffsetWidget::spinbox() const { return d_ptr->m_ui.valueSpinBox; }

void NumberOffsetWidget::setPixmap(const QString pixmap)
{
    d_ptr->m_ui.imageWidget->setVisible(true);
    d_ptr->m_ui.imageLabel->setPixmap(pixmap);
}

bool NumberOffsetWidget::isVisibleOffset() const { return d_ptr->m_visibleOffsets; }

void NumberOffsetWidget::setVisibleOffset(const bool visible) { d_ptr->setVisibleOffsets(visible); }

void NumberOffsetWidget::setAlwaysHidden()
{
    d_ptr->m_alwaysHidden = true;
    hide();
    emit alwaysHidden();
}

void NumberOffsetWidget::paintEvent(QPaintEvent *event)
{
    Q_D(NumberOffsetWidget);
    QWidget::paintEvent(event);

    QPainter painter(this);

    // Draw the border
    QPainterPath borderPath;
    const int radius = 4;
    borderPath.addRoundedRect(d->m_ui.spinboxWidget->geometry(), radius, radius);
    painter.setPen(QPen(Qt::darkGray, 1));
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPath(borderPath);
}

void NumberOffsetWidget::showEvent(QShowEvent *event)
{
    Q_D(NumberOffsetWidget);
    d->m_alwaysHidden ? hide() : QWidget::showEvent(event);
}
