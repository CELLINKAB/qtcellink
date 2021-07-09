#include "cellinkwidgets_stable.h"
#include "spinbox.h"

namespace  {
    const QString spinboxStyle("QSpinBox {"
                                   "background: white;"
                                   "padding: 6px;"
                                   "border-width: 1px;"
                                   "border-style: solid;"
                                   "border-color: #D5D9E0;"
                                   "border-radius: 6px;"
                               "}");
    const QString upButtonStyle("QSpinBox::up-button {"
                                    "border-image: url(:/images/common/enabled/up_arrow.svg); "
                                    "border: 0px;"
                                "}"
                                "QSpinBox::up-button:disabled, QSpinBox::up-button:off {"
                                    "border-image: url(:/images/common/disabled/up_arrow.svg); "
                                    "border: 0px;"
                                "}");
    const QString downButtonStyle("QSpinBox::down-button {"
                                    "border-image: url(:/images/common/enabled/down_arrow.svg); "
                                    "border: 0px;"
                                  "}"
                                  "QSpinBox::down-button:disabled, QSpinBox::down-button:off {"
                                    "border-image: url(:/images/common/disabled/down_arrow.svg); "
                                    "border: 0px;"
                                  "}");
}

SpinBox::SpinBox(QWidget *parent) : QSpinBox(parent)
{
    setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    setStyleSheet(QString("%0 %1 %2").arg(spinboxStyle, upButtonStyle, downButtonStyle));
}

SpinBox::~SpinBox() = default;
