#include "cellinkwidgets_stable.h"

#include "popupbutton.h"
#include "ui_popupbutton.h"

#include "direpo.h"
#include "cellinkwidgets/qtdialogs.h"
#include "cellinkwidgets/utils.h"
#include "misc.h"

#include "cellinkstyles/style.h"

class PopupButtonPrivate
{
    Q_DECLARE_PUBLIC(PopupButton);

public:
    void activate()
    {
        Q_Q(PopupButton);

        QDialog* popup = nullptr;

        if (m_popup) {
            popup = m_popup;
        } else if (m_popupClass) {
            popup = safe_cast<QDialog*>(m_popupClass->newInstance(Q_ARG(QWidget*, q)));
            CI_ASSERT(popup && "m_popupClass missing Q_INVOKABLE (QWidget*) constructor?!");
            q->connect(popup, &QDialog::finished, popup, &QObject::deleteLater);
        } else {
            qCritical() << "Neither popup nor popupClass set for" << q;
            return;
        }

        if (!popup->isVisible()) {
            emit q->aboutToShowPopup(popup);

            const auto defaultPen = q->borderPen();
            auto highlightPen = defaultPen;
            highlightPen.setColor(Style::mainBlue);
            q->setBorderPen(highlightPen);
            q->connect(popup, &QDialog::finished, q, [defaultPen,q]() {
                q->setBorderPen(defaultPen);
            });
            Utils::moveWidgetWithMargin(q, popup, m_popupAlignment, m_xMargin, m_yMargin);
            m_qtDialogs->execDialog(popup);
        }

        emit q->selected();
    }

    PopupButton* const q_ptr;
    QtDialogs* const m_qtDialogs;

    QPointer<QDialog> m_popup {};
    const QMetaObject* m_popupClass {};
    Ui::PopupButton m_ui {};

    Qt::Alignment m_popupAlignment { Qt::AlignCenter | Qt::AlignHCenter };
    int m_xMargin {};
    int m_yMargin {};
};

PopupButton::PopupButton(QWidget *parent, InjectedPtr<QtDialogs> qtDialogs) :
    Paper(parent, Style::Shadow::None),
    d_ptr(new PopupButtonPrivate{this, qtDialogs})
{
    d_ptr->m_ui.setupUi(this);
    setBorderPen(QPen(palette().shadow(), 1));
    setBorderEnabled(true);
}

PopupButton::~PopupButton() = default;

void PopupButton::setPopup(QDialog *popup, Qt::Alignment popupAlignment, int xMargin, int yMargin)
{
    Q_D(PopupButton);

    d->m_popup = popup;
    d->m_popupClass = nullptr;
    d->m_popupAlignment = popupAlignment;
    d->m_xMargin = xMargin;
    d->m_yMargin = yMargin;

    emit popupChanged(d->m_popup);
    emit popupClassChanged(d->m_popupClass);
}

void PopupButton::setPopupClass(const QMetaObject& meta, Qt::Alignment popupAlignment, int xMargin, int yMargin)
{
    Q_D(PopupButton);

    d->m_popup = nullptr;
    d->m_popupClass = &meta;
    d->m_popupAlignment = popupAlignment;
    d->m_xMargin = xMargin;
    d->m_yMargin = yMargin;

    emit popupChanged(d->m_popup);
    emit popupClassChanged(d->m_popupClass);
}


QDialog *PopupButton::popup() const
{
    return d_ptr->m_popup;
}

void PopupButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(PopupButton);
    event->accept();
    d->activate();
}

void PopupButton::setText(const QString &text)
{
    d_ptr->m_ui.textLabel->setText(text);
}

QString PopupButton::text() const
{
    return d_ptr->m_ui.textLabel->text();
}

void PopupButton::click()
{
    d_ptr->activate();
}
