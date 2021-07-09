#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H

#include "cellinkwidgets_global.h"
#include <QCheckBox>

class CELLINKWIDGETS_EXPORT ToggleSwitch : public QCheckBox
{
    Q_OBJECT

public:
    ToggleSwitch(QWidget *parent = 0);
    ~ToggleSwitch() override;
};

#endif // TOGGLESWITCH_H
