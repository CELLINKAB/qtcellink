#ifndef SPINBOX_H
#define SPINBOX_H

#include "cellinkwidgets_global.h"
#include <QSpinBox>

class CELLINKWIDGETS_EXPORT SpinBox : public QSpinBox
{
    Q_OBJECT

public:
    explicit SpinBox(QWidget *parent = nullptr);
    ~SpinBox() override;
};

#endif // SPINBOX_H
