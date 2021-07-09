#include "cellinkwidgets_stable.h"

#include "menubutton.h"
#include "misc.h"

namespace  {
    const QString buttonStyle("QPushButton { \
                                border: none; \
                                text-align: %1; \
                              } ");
    const QString checkedButtonStyle("QPushButton:checked{ \
                                        border: none; \
                                        text-align: %1; \
                                        color: #236EDF; \
                                    }");
}

MenuButton::MenuButton(QWidget *parent) :
    QPushButton(parent)
{
    setAlignment("center");
}

MenuButton::~MenuButton() = default;

void MenuButton::setAlignment(QString alignmnent)
{
    if (!Misc::updateProperty(this, alignmnent, m_alignment, &MenuButton::alignmentChanged))
        return;

    const auto regular = buttonStyle.arg(alignmnent);
    const auto checked = checkedButtonStyle.arg(alignmnent);
    const auto stylesheet = QStringLiteral("%1 %2").arg(regular, checked);

    setStyleSheet(stylesheet);
}
