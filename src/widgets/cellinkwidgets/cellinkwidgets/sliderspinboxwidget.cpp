#include "cellinkwidgets_stable.h"

#include "sliderspinboxwidget.h"
#include "ui_sliderspinboxwidget.h"


class SliderSpinBoxWidgetPrivate
{
    Q_DECLARE_PUBLIC(SliderSpinBoxWidget);

public:
    void setValue(const int value)
    {
        Q_Q(SliderSpinBoxWidget);
        if (m_value != value) {
            m_value = value;
            m_ui.slider->setValue(m_value);
            m_ui.spinBox->setValue(m_value);
            q->valueChanged(m_value);
        }
    }

    void setChecked(const bool checked)
    {
        m_ui.checkBox->setChecked(checked);
        m_ui.slider->setEnabled(checked);
        m_ui.spinBox->setEnabled(checked);
    }

    SliderSpinBoxWidget* const q_ptr;
    Ui::SliderSpinBoxWidget m_ui {};
    int m_value = 0;
};


SliderSpinBoxWidget::SliderSpinBoxWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new SliderSpinBoxWidgetPrivate{this})
{
    Q_D(SliderSpinBoxWidget);
    d->m_ui.setupUi(this);

    d->setChecked(false);
    connect(d->m_ui.slider, &QSlider::valueChanged, this, [d] (auto value){ d->setValue(value); });
    connect(d->m_ui.spinBox, qOverload<int>(&SpinBox::valueChanged), this, [d] (auto value) {
        d->setValue(value);
    });
    connect(d->m_ui.checkBox, &QCheckBox::stateChanged, this, [d, this] (auto state) {
        const auto enabled = state == Qt::CheckState::Checked;
        d->setChecked(enabled);
        emit checkChanged(enabled);
    });
}

SliderSpinBoxWidget::~SliderSpinBoxWidget() = default;

int SliderSpinBoxWidget::value() const
{
    return d_ptr->m_ui.slider->value();
}

void SliderSpinBoxWidget::setValue(const int value)
{
    Q_D(SliderSpinBoxWidget);
    d->setValue(value);
}

bool SliderSpinBoxWidget::isChecked() const
{
    return d_ptr->m_ui.checkBox->isChecked();
}

void SliderSpinBoxWidget::setChecked(const bool checked)
{
    Q_D(SliderSpinBoxWidget);
    d->setChecked(checked);
}
