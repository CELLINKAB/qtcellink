#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "cellinkwidgets_global.h"
#include <QProgressBar>

class CELLINKWIDGETS_EXPORT ProgressBar : public QProgressBar
{
    Q_OBJECT

public:
    explicit ProgressBar(QWidget *parent = nullptr);
    ~ProgressBar() override;
};

#endif // PROGRESSBAR_H
