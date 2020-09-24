#include "spinbox.h"

SpinBox::SpinBox(QWidget *parent) : QSpinBox(parent)
{
    connect(this, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
        if (m_editing)
            emit valueEdited(value);
    });
    connect(this, &QAbstractSpinBox::editingFinished, [=]() {
        emit valueEdited(value());
    });
}

void SpinBox::stepBy(int steps)
{
    m_editing =  true;
    QSpinBox::stepBy(steps);
    m_editing = false;
}
