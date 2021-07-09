#include "cellinkwidgets_stable.h"
#include "collapsebox.h"

#include "misc.h"

class CollapseBoxPrivate : public QObject
{
    Q_DECLARE_PUBLIC(CollapseBox);

public:
    explicit CollapseBoxPrivate(CollapseBox* q) : q_ptr(q) {}

    bool eventFilter(QObject* target, QEvent* event)
    {
        Q_UNUSED(target);

        switch(event->type()) {
        case QEvent::Type::ChildAdded:
        case QEvent::Type::ChildRemoved:
            handleChildEvent(static_cast<QChildEvent*>(event));
            return false;

        default:
            return false;
        }

    }

    void handleChildEvent(QChildEvent* event)
    {
        Q_Q(CollapseBox);

        if (auto w = qobject_cast<QWidget*>(event->child())) {
            if (event->added()) {
                m_childWidgets.append(w);
                w->setVisible(q->isChecked());
            } else if (event->removed()) {
                m_childWidgets.removeAll(w);
                w->setVisible(true);
            }
        } else {
            // As we can get a layout as child, which is only a QObject at this point,
            // we add event filters until we get a widget, which we can read directly instead.

            if (event->added()) {
                event->child()->installEventFilter(this);
            } else if (event->removed()) {
                event->child()->removeEventFilter(this);
            }
        }
    }

    void toggleChildren(bool on)
    {
        Q_Q(CollapseBox);

        if(q_ptr->layout() && !m_layoutMargins.has_value()) {
            m_layoutMargins = q_ptr->layout()->contentsMargins();
        }

        for(auto w : std::as_const(m_childWidgets))
            w->setVisible(on);

        for(auto l : q->findChildren<QLayout*>()) {
            l->invalidate();
            l->activate();
            l->update();
        }

        if(q_ptr->layout() && m_layoutMargins.has_value()) {
            q_ptr->layout()->setContentsMargins(on ? m_layoutMargins.value() : QMargins{});
        }

        q->adjustSize();
        q->update();

    }

    CollapseBox* const q_ptr;

    QVector<QWidget*> m_childWidgets {};
    std::optional<QMargins> m_layoutMargins {};
    CollapseBox::CheckboxType m_checkboxType { CollapseBox::Toggle };
    bool m_collapseDisablesFeature { false };
};



CollapseBox::CollapseBox(QWidget *parent) :
    QGroupBox(parent),
    d_ptr(new CollapseBoxPrivate{this})
{
    Q_D(CollapseBox);

    // may be (accidentally) overridden by designer
    setCheckable(true);
    setChecked(false);
    setFlat(true);

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    connect(this, &QGroupBox::toggled, [d, this](bool on) { d->toggleChildren(on); emit collapsedChanged(!on); });
}

CollapseBox::~CollapseBox() = default;

/// @reimp
QSize CollapseBox::minimumSizeHint() const
{
    // implementation taken from QGroupBox::minimumSizeHint()

    QStyleOptionGroupBox option;
    initStyleOption(&option);

    // begin added code - remove horizontal line
    option.lineWidth = 0;
    option.midLineWidth = 0;

    // don't show contents if not checked
    if (!isChecked()) {
        option.subControls &= ~QStyle::SC_GroupBoxContents;
        option.activeSubControls &= ~QStyle::SC_GroupBoxContents;
    }
    // end added code

    const auto metrics = fontMetrics();
    auto baseWidth = metrics.horizontalAdvance(title()) + metrics.horizontalAdvance(QLatin1Char(' '));
    auto baseHeight = metrics.height();

    if (isCheckable()) {
        baseWidth += style()->pixelMetric(QStyle::PM_IndicatorWidth, &option);
        baseWidth += style()->pixelMetric(QStyle::PM_CheckBoxLabelSpacing, &option);
        baseHeight = qMax(baseHeight, style()->pixelMetric(QStyle::PM_IndicatorHeight, &option));
    }

    auto size = style()->sizeFromContents(QStyle::CT_GroupBox, &option, QSize(baseWidth, baseHeight), this);

    return size.expandedTo(QWidget::minimumSizeHint());
}

void CollapseBox::childEvent(QChildEvent* event)
{
    QWidget::childEvent(event);
    d_ptr->handleChildEvent(event);
}

void CollapseBox::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    d_ptr->toggleChildren(isChecked());
}

[[nodiscard]] CollapseBox::CheckboxType CollapseBox::checkboxType() const
{
    return d_ptr->m_checkboxType;
}

void CollapseBox::setCheckboxType(CheckboxType value)
{
    if (Misc::updateProperty(this, value, d_ptr->m_checkboxType, &CollapseBox::checkboxTypeChanged)) {
        update();
    }
}

bool CollapseBox::collapseDisablesFeature() const
{
    return d_ptr->m_collapseDisablesFeature;
}

void CollapseBox::setCollapseDisablesFeature(bool disable)
{
    d_ptr->m_collapseDisablesFeature = disable;
}

