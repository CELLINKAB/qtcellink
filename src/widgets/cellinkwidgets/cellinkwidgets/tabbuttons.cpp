#include "cellinkwidgets_stable.h"

#include "tabbuttons.h"
#include "ui_tabbuttons.h"

#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QStyle>

class TabButtonPrivate
{
    Q_DECLARE_PUBLIC(TabButton)

public:
    TabButton* const q_ptr;

    Ui::TabButton m_ui {};
    bool m_isSelected = false;
};

TabButton::TabButton(QString text, const QString &size, const QString &iconPath, QWidget *parent) :
    TabButton(std::move(text), size, iconPath, parent, new TabButtonPrivate{this})
{ }

TabButton::TabButton(QString text, const QString& size, const QString& iconPath, QWidget *parent, TabButtonPrivate* data) :
    QWidget(parent),
    d_ptr(data)
{
    Q_D(TabButton);

    d->m_ui.setupUi(this);
    d->m_ui.surfaceLabel->setText(text);
    d->m_ui.sizeLabel->setText(size);
    d->m_ui.containerWidget->layout()->setAlignment(d->m_ui.thumbnailWidget, Qt::AlignCenter);
    d->m_ui.containerWidget->setBorderPen(QPen(palette().highlight(), 2));
    d->m_ui.thumbnailWidget->load(iconPath);
}


TabButton::~TabButton() = default;

QSize TabButton::sizeHint() const
{
    return QSize(90, 125);
}

bool TabButton::isSelected() const
{
    Q_D(const TabButton);
    return d->m_isSelected;
}

void TabButton::setSelected(bool selected)
{
    Q_D(TabButton);

    if (selected == d->m_isSelected) {
        return;
    }

    d->m_isSelected = selected;

    emit selectedChanged();
    if (d->m_isSelected)
        emit buttonSelected(this);

    // Change surfaceLabel color if selected/unselected
    QPalette surfaceLabelPalette = d->m_ui.surfaceLabel->palette();
    d->m_ui.surfaceLabel->setForegroundRole(selected ? QPalette::Highlight : QPalette::WindowText);
    d->m_ui.surfaceLabel->setPalette(surfaceLabelPalette);

    d->m_ui.containerWidget->setBorderEnabled(d_ptr->m_isSelected);

    update();
}


void TabButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    setSelected(true);
    emit clicked();
}

void TabButton::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    const auto ratio = 60.0f/66.0f;
    d_ptr->m_ui.containerWidget->setFixedHeight(int(d_ptr->m_ui.containerWidget->width() * ratio));
}

void TabButton::click()
{
    setSelected(true);
    emit clicked();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DropletTabButtonPrivate : public TabButtonPrivate
{
    Q_DECLARE_PUBLIC(DropletTabButton)

public:
    DropletTabButtonPrivate(DropletTabButton* q, PrintType type) :
        TabButtonPrivate{q}, m_type(type)
    { }

    const PrintType m_type;
};

DropletTabButton::DropletTabButton(PrintType type, const QString& size,
                                   const QString& iconPath, QWidget *parent) :
    TabButton(toTrString(type), size, iconPath, parent, new DropletTabButtonPrivate(this, type))
{
    CI_ASSERT((type & PrintType::AnyDroplet) != 0);
}

DropletTabButton::~DropletTabButton() = default;

PrintType DropletTabButton::type() const
{
    Q_D(const DropletTabButton);

    return d->m_type;
}

