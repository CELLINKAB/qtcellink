#ifndef SPINBOX_H
#define SPINBOX_H

#include <QtCellink/cellink.h>
#include <QtWidgets/qspinbox.h>

class Q_CELLINK_EXPORT SpinBox : public QSpinBox
{
    Q_OBJECT

public:
    explicit SpinBox(QWidget *parent = nullptr);

    void stepBy(int steps) override;

signals:
    void valueEdited(int value);

private:
    bool m_editing = false;
};

#endif // SPINBOX_H
