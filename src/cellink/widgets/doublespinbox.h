#ifndef DOUBLESPINBOX_H
#define DOUBLESPINBOX_H

#include "qtcellink/src/cellink/core/cellink.h"

#include <QtWidgets/qspinbox.h>

namespace cellink {

class Q_CELLINK_EXPORT DoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
    Q_PROPERTY(bool invertedControls READ invertedControls WRITE setInvertedControls)

public:
    explicit DoubleSpinBox(QWidget* parent = nullptr);

    bool invertedControls() const;
    void setInvertedControls(bool invert);

    void stepBy(int steps) override;

signals:
    void valueEdited(double value);

private:
    bool m_editing = false;
    bool m_inverted = false;
};

} // namespace cellink

#endif // DOUBLESPINBOX_H
