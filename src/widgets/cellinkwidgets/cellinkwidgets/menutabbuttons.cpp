#include "cellinkwidgets_stable.h"
#include "menutabbuttons.h"

#include "ui_menutabbuttons.h"
#include "cellinkwidgets/menubutton.h"



class MenuTabButtonsPrivate
{
public:
    MenuTabButtons* const q_ptr;
    QButtonGroup* m_buttons;

    Ui::MenuTabButtons m_ui{};
};

MenuTabButtons::MenuTabButtons(QWidget *parent) :
    QWidget(parent),
    d_ptr(new MenuTabButtonsPrivate{this, new QButtonGroup(this)})
{
    Q_D(MenuTabButtons);
    d->m_ui.setupUi(this);

    d->m_buttons->setExclusive(false);

    connect(d->m_buttons, qOverload<int>(&QButtonGroup::buttonClicked), this, [d] (auto selected) {
       for (auto& button : d->m_buttons->buttons()) {
           button->setChecked(button == d->m_buttons->button(selected));
       }
    });
};

MenuTabButtons::~MenuTabButtons() = default;


void MenuTabButtons::paintEvent(QPaintEvent *event)
{
    Q_D(MenuTabButtons);
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const auto rectangle = rect();
    QPen pen(palette().color(QPalette::Button), 5);
    painter.setPen(pen);
    painter.drawLine(rectangle.topLeft(), rectangle.bottomLeft());

    const auto selectedButton = d->m_buttons->checkedButton();
    if(selectedButton) {
        const auto position = selectedButton->pos().y();
        const auto height = selectedButton->height();
        pen.setColor(palette().color(QPalette::Highlight));
        painter.setPen(pen);
        painter.drawLine(rectangle.left(), position + 3, rectangle.left(), position + height - 3);
    }
}

QPushButton* MenuTabButtons::addButton(const QString enablePath, const QString selectedPath, const QString imageName)
{
    Q_D(MenuTabButtons);
    auto button = new MenuButton(this);

    QIcon icon;
    icon.addPixmap(enablePath.arg(imageName), QIcon::Normal, QIcon::Off);
    icon.addPixmap(selectedPath.arg(imageName), QIcon::Normal, QIcon::On);
    button->setIcon(icon);
    button->setIconSize(QSize(32, 32));
    button->setCheckable(true);
    button->setFlat(true);
    button->setAlignment("center");
    button->setObjectName(imageName);

    d->m_ui.buttonsContainer->addWidget(button);
    d->m_buttons->addButton(button);

    return button;
}

void MenuTabButtons::showSelection(bool show, const int index)
{
    Q_D(MenuTabButtons);
    const auto& buttons = d->m_buttons->buttons();
    for (auto i = 0; i < buttons.count(); ++i) {
        buttons.at(i)->setChecked(show && index == i);
    }
}
