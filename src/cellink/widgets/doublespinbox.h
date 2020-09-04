#ifndef DOUBLESPINBOX_H
#define DOUBLESPINBOX_H

#include <QtCellink/cellink.h>
#include <QtWidgets/qspinbox.h>

class Q_CELLINK_EXPORT DoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:
    explicit DoubleSpinBox(QWidget *parent = nullptr);

    void stepBy(int steps) override;

signals:
    void valueEdited(double value);

private:
    bool m_editing = false;
};

#endif // DOUBLESPINBOX_H
