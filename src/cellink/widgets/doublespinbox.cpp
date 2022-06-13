#include "doublespinbox.h"

DoubleSpinBox::DoubleSpinBox(QWidget* parent)
    : QDoubleSpinBox(parent)
{
    connect(this, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=](double value) {
        if (m_editing)
            emit valueEdited(value);
    });
    connect(this, &QAbstractSpinBox::editingFinished, [=]() { emit valueEdited(value()); });
}

bool DoubleSpinBox::invertedControls() const
{
    return m_inverted;
}

void DoubleSpinBox::setInvertedControls(bool invert)
{
    m_inverted = invert;
}

void DoubleSpinBox::stepBy(int steps)
{
    m_editing = true;
    QDoubleSpinBox::stepBy(m_inverted ? -steps : steps);
    m_editing = false;
}
