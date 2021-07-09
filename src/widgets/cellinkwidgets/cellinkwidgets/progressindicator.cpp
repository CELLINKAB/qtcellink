#include "cellinkwidgets_stable.h"
#include "progressindicator.h"

namespace
{
const auto SPAN_ANIMATION_DURATION = 700;
const auto ROTATION_ANIMATION_DURATION = SPAN_ANIMATION_DURATION * 6;
const auto TARGET_ROTATION = 720;
const auto ONE_DEGREE = 16;
const auto MIN_SWEEP_SPAN = 10.0 * ONE_DEGREE;
const auto MAX_SWEEP_SPAN = 300.0 * ONE_DEGREE;
}

class ProgressIndicatorPrivate
{
public:
    QColor m_color = Qt::white;
    int m_lineWidth = 6;
    int m_lastStartAngle = 0;
    int m_lastEndAngle = 0;
    qreal m_devicePixelRatio = 1.0;
    qreal m_progress = 0.0;
};

ProgressIndicator::ProgressIndicator(QWidget* parent):
    QWidget(parent),
    d_ptr{new ProgressIndicatorPrivate} {}

ProgressIndicator::~ProgressIndicator() = default;

void ProgressIndicator::paintEvent(QPaintEvent *event)
{
    Q_D(ProgressIndicator);
    Q_UNUSED(event);

    const auto w = width();
    const auto h = height();
    const auto size = qMin(w, h);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(d->m_color);

    QPen pen;
    pen.setColor(d->m_color);
    pen.setWidth(d->m_lineWidth * d->m_devicePixelRatio);
    painter.setPen(pen);

    // xOffset/yOffset to keep the indicator centered
    const auto xOffset = (width() - size) / 2;
    const auto yOffset = (height() - size) / 2;

    const QRectF arcBounds = QRectF(d->m_devicePixelRatio * xOffset + pen.width() / 2 + 1,
                                    d->m_devicePixelRatio * yOffset + pen.width() / 2 + 1,
                                    d->m_devicePixelRatio * size - pen.width() - 1,
                                    d->m_devicePixelRatio * size - pen.width() - 1);

    const auto time = d->m_progress * ROTATION_ANIMATION_DURATION;
    const auto spanPercentageComplete = (static_cast<int>(time) % SPAN_ANIMATION_DURATION) / static_cast<qreal>(SPAN_ANIMATION_DURATION);
    const auto iteration = static_cast<int>(time / SPAN_ANIMATION_DURATION);
    auto startAngle = 0;
    auto endAngle = 0;

    if (iteration % 2 == 0) {
        if (d->m_lastStartAngle > 360 * ONE_DEGREE)
            d->m_lastStartAngle -= 360 * ONE_DEGREE;

        // The start angle is only affected by the rotation animation for the "grow" phase.
        startAngle = d->m_lastStartAngle;
        QEasingCurve angleCurve(QEasingCurve::OutQuad);
        const auto percentage = angleCurve.valueForProgress(spanPercentageComplete);
        endAngle = d->m_lastStartAngle + MIN_SWEEP_SPAN + percentage * (MAX_SWEEP_SPAN - MIN_SWEEP_SPAN);
        d->m_lastEndAngle = endAngle;
    } else {
        // Both the start angle *and* the span are affected by the "shrink" phase.
        QEasingCurve angleCurve(QEasingCurve::InQuad);
        const auto percentage = angleCurve.valueForProgress(spanPercentageComplete);
        startAngle = d->m_lastEndAngle - MAX_SWEEP_SPAN + percentage * (MAX_SWEEP_SPAN - MIN_SWEEP_SPAN);
        endAngle = d->m_lastEndAngle;
        d->m_lastStartAngle = startAngle;
    }

    // The current angle of the rotation animation.
    const auto rotation = ONE_DEGREE * d->m_progress * -TARGET_ROTATION;
    startAngle -= rotation;
    endAngle -= rotation;
    const auto angleSpan = endAngle - startAngle;
    painter.drawArc(arcBounds, -startAngle, -angleSpan);

    painter.end();
}

QColor ProgressIndicator::color() const
{
    return d_ptr->m_color;
}

void ProgressIndicator::setColor(QColor color)
{
    Q_D(ProgressIndicator);
    if (d->m_color == color)
        return;

    d->m_color = color;
    update();
}

int ProgressIndicator::lineWidth() const
{
    return d_ptr->m_lineWidth;
}

void ProgressIndicator::setLineWidth(int width)
{
    Q_D(ProgressIndicator);
    if (d->m_lineWidth == width)
        return;

    d->m_lineWidth = width;
    update();
}

qreal ProgressIndicator::progress() const
{
    return d_ptr->m_progress;
}

void ProgressIndicator::setProgress(qreal progress)
{
    Q_D(ProgressIndicator);
    if (d->m_progress == progress)
        return;

    d->m_progress = progress;
    update();
}

void ProgressIndicator::cycleProgress(int refreshRate)
{
    Q_D(ProgressIndicator);
    d->m_progress += (static_cast<qreal>(refreshRate) / ROTATION_ANIMATION_DURATION);
    if(d->m_progress > 1.0) {
        d->m_progress = 0.0;
    }
    update();
}

