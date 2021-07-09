#include "cellinkwidgets_stable.h"

#include "progressbar.h"
#include "cellinkstyles/style.h"

namespace {
    const QString stylesheet = "QProgressBar{ \
                           background-color: %0; \
                           border: 0px; \
                           border-radius: 5px; \
                       } \
                       QProgressBar::chunk { \
                           background-color: %1; \
                           border: 0px; \
                           border-radius: 5px; \
                       } ";
}

ProgressBar::ProgressBar(QWidget *parent) : QProgressBar(parent)
{
    QTimer::singleShot(0, this, [this]() {
        setStyleSheet(stylesheet.arg(Style::discreteGray.name(), Style::mainBlue.name()));
    });
}

ProgressBar::~ProgressBar() = default;
