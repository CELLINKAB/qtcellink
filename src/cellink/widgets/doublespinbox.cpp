#include "doublespinbox.h"

DoubleSpinBox::DoubleSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
    connect(this, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=](double value) {
        if (m_editing)
            emit valueEdited(value);
    });
}

void DoubleSpinBox::stepBy(int steps)
{
    m_editing =  true;
    QDoubleSpinBox::stepBy(steps);
    m_editing = false;
}
