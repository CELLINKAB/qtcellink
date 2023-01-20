#include "spinbox.h"

namespace cellink {

SpinBox::SpinBox(QWidget* parent)
    : QSpinBox(parent)
{
    connect(this, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
        if (m_editing)
            emit valueEdited(value);
    });
    connect(this, &QAbstractSpinBox::editingFinished, [=]() { emit valueEdited(value()); });
}

bool SpinBox::invertedControls() const
{
    return m_inverted;
}

void SpinBox::setInvertedControls(bool invert)
{
    m_inverted = invert;
    emit invertedControlsChanged(invert);
}

void SpinBox::stepBy(int steps)
{
    m_editing = true;
    QSpinBox::stepBy(m_inverted ? -steps : steps);
    m_editing = false;
}

} // namespace cellink
