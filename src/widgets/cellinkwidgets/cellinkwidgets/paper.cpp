#include "cellinkwidgets_stable.h"

#include "styleinterface.h"
#include "cellinkwidgets/paper.h"

class PaperPrivate {
public:
    QPen m_borderPen {};
    bool m_borderEnabled = false;
    bool m_clickable = false;
    QGraphicsDropShadowEffect* m_shadowEffect = nullptr;
    Style::Shadow m_shadowType = Style::Shadow::Default;
};

Paper::Paper(QWidget *parent, Style::Shadow shadowType)
    : QWidget(parent)
    , d_ptr(new PaperPrivate)
{
    if (auto appStyle = qobject_cast<IStyle*>(style())) {
        d_ptr->m_shadowEffect = appStyle->createShadowEffect(shadowType, this);
        if (d_ptr->m_shadowEffect) {
            setGraphicsEffect(d_ptr->m_shadowEffect);
        }
    } else {
        // warn once
        static auto s_warned = false;
        if (!s_warned) {
            qWarning() << "Failed to set graphics effect as current style" << style() << "is not an IStyle";
            s_warned = true;
        }
    }

    setMinimumSize(0,0);
}

Paper::~Paper() = default;

void Paper::setBorderEnabled(bool enabled)
{
    Q_D(Paper);

    if (enabled == d->m_borderEnabled) {
        return;
    }

    d->m_borderEnabled = enabled;
    emit borderEnabledChanged(enabled);
    update();
}

bool Paper::isBorderEnabled() const { return d_ptr->m_borderEnabled; }

void Paper::setBorderPen(QPen borderPen)
{
    d_ptr->m_borderPen = std::move(borderPen);
    emit borderPenChanged(d_ptr->m_borderPen);
    update();
}

bool Paper::isClickable() const
{
    return d_ptr->m_clickable;
}

void Paper::setClickable(bool clickable)
{
    Q_D(Paper);

    d->m_clickable = clickable;
    if(clickable) {
        setCursor(Qt::PointingHandCursor);
    }
}

void Paper::paintEvent(QPaintEvent *event)
{
    Q_D(Paper);

    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath fillPath;
    const auto radius = 7;
    const auto width = size().width();
    const auto height = size().height();
    fillPath.addRoundedRect(QRect(0, 0, width, height), radius, radius);
    painter.fillPath(fillPath, palette().window());

    if (d->m_borderEnabled) {
        painter.setPen(d->m_borderPen);
        QPainterPath borderPath;
        int penWidth = d->m_borderPen.width();
        borderPath.addRoundedRect(QRect(penWidth / 2, penWidth / 2, width - penWidth, height - penWidth), radius, radius);
        painter.drawPath(borderPath);
    }
}

void Paper::mouseReleaseEvent(QMouseEvent* event)
{
    if (d_ptr->m_clickable && (event->button() == Qt::LeftButton)) {
        emit clicked();
        event->accept();
        return;
    }

    QWidget::mouseReleaseEvent(event);
}

QPen Paper::borderPen() const
{
    return d_ptr->m_borderPen;
}
