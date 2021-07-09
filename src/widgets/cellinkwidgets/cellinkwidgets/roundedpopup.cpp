#include "cellinkwidgets_stable.h"
#include "roundedpopup.h"
#include "ui_rondedpopup.h"

#include "cellinkwidgets/utils.h"

namespace
{
constexpr auto MASK_RADIUS = 6;
}

class RoundedPopupPrivate : public QObject
{
    Q_DECLARE_PUBLIC(RoundedPopup);

public:
    RoundedPopupPrivate(RoundedPopup* q, RoundedPopup::ResizeFlags resize) :
        q_ptr(q)
    {
        m_ui.setupUi(q_ptr);
        m_ui.topLeftGrip->installEventFilter(this);
        m_ui.topRightGrip->installEventFilter(this);
        m_ui.bottomLeftGrip->installEventFilter(this);
        m_ui.bottomRightGrip->installEventFilter(this);

        m_ui.topLeftGrip->setEnabled(resize & RoundedPopup::TopLeft);
        m_ui.topRightGrip->setEnabled(resize & RoundedPopup::TopRight);
        m_ui.bottomLeftGrip->setEnabled(resize & RoundedPopup::BottomLeft);
        m_ui.bottomRightGrip->setEnabled(resize & RoundedPopup::BottomRight);
    }

    bool eventFilter(QObject*, QEvent* event)
    {
        // We do not want to paint QSizeGrips
        if (event->type() == QEvent::Paint) {
            return true;
        }

        return false;
    }

    RoundedPopup* const q_ptr;
    Ui::Dialog m_ui;
};

RoundedPopup::RoundedPopup(QWidget* parent) :
    RoundedPopup(NoResize, parent)
{}

RoundedPopup::RoundedPopup(ResizeFlags resize, QWidget* parent):
    QDialog(parent, Qt::Popup),
    d_ptr(new RoundedPopupPrivate{ this, resize })
{}

RoundedPopup::~RoundedPopup() = default;

QWidget* RoundedPopup::getContentWidget() const { return d_ptr->m_ui.content; }

void RoundedPopup::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    Utils::setRoundedMask(this, MASK_RADIUS);
}

void RoundedPopup::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    // activate so virtual keyboard would appear on necessary child widgets
    raise();
    activateWindow();
}
