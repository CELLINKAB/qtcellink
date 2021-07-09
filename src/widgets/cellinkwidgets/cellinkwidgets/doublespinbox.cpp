#include "cellinkwidgets_stable.h"
#include "doublespinbox.h"

namespace  {
    const QString spinBoxStyle("QDoubleSpinBox {"
                                   "background: qlineargradient(x1:0, x2:1, stop:0.08 %1, stop: 0.081 white, stop:1 white); "
                                   "padding: 6px;"
                                   "border: 1px solid #D5D9E0; "
                                   "border-radius: 6px; "
                               "}");
    const QString upButtonStyle("QDoubleSpinBox::up-button {"
                                    "border-image: url(:/images/common/enabled/up_arrow.svg); "
                                    "border: 0px; "
                                "}"
                                "QDoubleSpinBox::up-button:disabled, QDoubleSpinBox::up-button:off {"
                                    "border-image: url(:/images/common/disabled/up_arrow.svg); "
                                    "border: 0px;"
                                "}");
    const QString downButtonStyle("QDoubleSpinBox::down-button {"
                                    "border-image: url(:/images/common/enabled/down_arrow.svg); "
                                    "border: 0px;"
                                  "}"
                                  "QDoubleSpinBox::down-button:disabled, QDoubleSpinBox::down-button:off {"
                                    "border-image: url(:/images/common/disabled/down_arrow.svg); "
                                    "border: 0px;"
                                  "}");
}

DoubleSpinBox::DoubleSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
    setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    connect(this, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DoubleSpinBox::doubleValueChanged);
}

DoubleSpinBox::~DoubleSpinBox() = default;

void DoubleSpinBox::setPrefixColor(QString prefixColor)
{
    if (m_prefixColor == prefixColor)
        return;

    setStyleSheet(QString("%0 %1 %2").arg(spinBoxStyle.arg(prefixColor), upButtonStyle, downButtonStyle));
    m_prefixColor = std::move(prefixColor);
    emit prefixColorChanged(m_prefixColor);
}

QValidator::State DoubleSpinBox::validate(QString &input, int &pos) const
{
    if(QDoubleSpinBox::validate(input, pos) == QValidator::Acceptable)
        return QValidator::Acceptable;

    fixInputDecimal(input);

    return QDoubleSpinBox::validate(input, pos);
}

void DoubleSpinBox::fixInputDecimal(QString &input) const
{
    auto decimalPoint = QLocale().decimalPoint();
    input.remove(suffix());
    auto list = input.split(decimalPoint);
    Q_ASSERT(list.size() <= 2);
    if(list.size() > 1)
    {
        auto decimalInput = list.last();
        const auto integerInput = list.first();
        if(decimalInput.size() > decimals())
            decimalInput.remove(decimals(), decimalInput.size() - decimals());
        input = integerInput + decimalPoint + decimalInput + suffix();
    }
}
