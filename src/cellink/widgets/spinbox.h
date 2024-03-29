#ifndef SPINBOX_H
#define SPINBOX_H

#include "qtcellink/src/cellink/core/cellink.h"

#include <QtWidgets/qspinbox.h>

namespace cellink {

class Q_CELLINK_EXPORT SpinBox : public QSpinBox
{
    Q_OBJECT
    Q_PROPERTY(bool invertedControls READ invertedControls WRITE setInvertedControls NOTIFY
                   invertedControlsChanged)

public:
    explicit SpinBox(QWidget* parent = nullptr);

    bool invertedControls() const;
    void setInvertedControls(bool invert);

    void stepBy(int steps) override;

signals:
    void valueEdited(int value);
    void invertedControlsChanged(bool value);

private:
    bool m_editing = false;
    bool m_inverted = false;
};

} // namespace cellink

#endif // SPINBOX_H
