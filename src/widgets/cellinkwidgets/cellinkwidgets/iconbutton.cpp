#include "cellinkwidgets_stable.h"

#include "iconbutton.h"
#include "ui_iconbutton.h"

class IconButtonPrivate
{
    Q_DECLARE_PUBLIC(IconButton);

public:
    IconButton* const q_ptr;
    Ui::IconButton m_ui {};
};

IconButton::IconButton(QWidget *parent) :
    QPushButton(parent),
    d_ptr(new IconButtonPrivate{this})
{
    Q_D(IconButton);
    d->m_ui.setupUi(this);

    connect(d->m_ui.iconButton, &QPushButton::pressed, this, &QPushButton::pressed);
    connect(d->m_ui.iconButton, &QPushButton::released, this, &QPushButton::released);
}

IconButton::~IconButton() = default;

QString IconButton::text() const
{
    return d_ptr->m_ui.textLabel->text();
}

void IconButton::setText(const QString &text)
{
    Q_D(IconButton);
    d->m_ui.textLabel->setText(text);
}

void IconButton::setIcon(const QIcon& icon)
{
    Q_D(IconButton);
    d->m_ui.iconButton->setIcon(icon);
}
