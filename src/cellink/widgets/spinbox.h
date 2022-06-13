#ifndef SPINBOX_H
#define SPINBOX_H

#include "qtcellink/src/cellink/core/cellink.h"

#include <QtWidgets/qspinbox.h>

class Q_CELLINK_EXPORT SpinBox : public QSpinBox
{
    Q_OBJECT
    Q_PROPERTY(bool invertedControls READ invertedControls WRITE setInvertedControls)

public:
    explicit SpinBox(QWidget* parent = nullptr);

    bool invertedControls() const;
    void setInvertedControls(bool invert);

    void stepBy(int steps) override;

signals:
    void valueEdited(int value);

private:
    bool m_editing = false;
    bool m_inverted = false;
};

#endif // SPINBOX_H
