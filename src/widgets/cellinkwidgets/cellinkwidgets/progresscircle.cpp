#include "cellinkwidgets_stable.h"
#include "progresscircle.h"
#include "cellinkstyles/style.h"

ProgressCircle::ProgressCircle(QWidget *parent) :
    QWidget(parent),
    m_value(0),
    m_maximum(0),
    m_innerRadius(0.9),
    m_outerRadius(1.0),
    m_color(Style::mainBlue),
    m_textColor(Style::mainBlue),
    m_visibleValue(0),
    m_valueAnimation(this, "visibleValue"),
    m_infiniteAnimation(this, "infiniteAnimationValue"),
    m_infiniteAnimationValue(0.0)
{
    m_infiniteAnimation.setLoopCount(-1);//infinite
    m_infiniteAnimation.setDuration(1000);
    m_infiniteAnimation.setStartValue(0.0);
    m_infiniteAnimation.setEndValue(1.0);
    m_infiniteAnimation.start();
}

ProgressCircle::~ProgressCircle() = default;

int ProgressCircle::value() const
{
    return m_value;
}

/**
 * @brief maximum
 * If maximum <= 0, widget shows infinite process;
 * @return
 */
int ProgressCircle::maximum() const
{
    return m_maximum;
}

/**
 * @brief innerRadius = [0.0 .. 1.0]
 * @return
 */
qreal ProgressCircle::innerRadius() const
{
    return m_innerRadius;
}

/**
 * @brief outerRadius = [0.0 .. 1.0]
 * @return
 */
qreal ProgressCircle::outerRadius() const
{
    return m_outerRadius;
}

QColor ProgressCircle::color() const
{
    return m_color;
}

void ProgressCircle::setValue(int value)
{
    if(value < 0) value = 0;

    if(m_value != value)
    {
        m_valueAnimation.stop();
        m_valueAnimation.setEndValue(value);
        m_valueAnimation.setDuration(250);
        m_valueAnimation.start();

        m_value = value;
        emit valueChanged(value);
    }
}

void ProgressCircle::setMaximum(int maximum)
{
    if(maximum < 0) maximum = 0;

    if(m_maximum != maximum)
    {
        m_maximum = maximum;
        update();
        emit maximumChanged(maximum);

        if(m_maximum == 0)
        {
            m_infiniteAnimation.start();
        }
        else
        {
            m_infiniteAnimation.stop();
        }
    }
}

void ProgressCircle::setInnerRadius(qreal innerRadius)
{
    if(innerRadius > 1.0) innerRadius = 1.0;
    if(innerRadius < 0.0) innerRadius = 0.0;

    if(m_innerRadius != innerRadius)
    {
        m_innerRadius = innerRadius;
        update();
    }
}

void ProgressCircle::setOuterRadius(qreal outerRadius)
{
    if(outerRadius > 1.0) outerRadius = 1.0;
    if(outerRadius < 0.0) outerRadius = 0.0;

    if(m_outerRadius != outerRadius)
    {
        m_outerRadius = outerRadius;
        update();
    }
}

void ProgressCircle::setColor(QColor color)
{
    if(color != m_color)
    {
        m_color = color;
        update();
    }
}

void ProgressCircle::setTextColor(QColor color)
{
    m_textColor = color;
}

namespace {

QRectF squared(QRectF rect)
{
    if(rect.width() > rect.height())
    {
        qreal diff = rect.width() - rect.height();
        return rect.adjusted(diff/2, 0, -diff/2, 0);
    }
    else
    {
        qreal diff = rect.height() - rect.width();
        return rect.adjusted(0, diff/2, 0, -diff/2);
    }
}

} // end anonymous namespace

void ProgressCircle::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPixmap pixmap;
    if (!QPixmapCache::find(key(), pixmap))
    {
        pixmap = generatePixmap();
        QPixmapCache::insert(key(), pixmap);
    }

    // Draw pixmap at center of item
    QPainter painter(this);
    painter.drawPixmap( 0.5 * ( width() - pixmap.width() ), 0.5 * ( height() - pixmap.height() ), pixmap );
    painter.setPen(m_textColor);
    painter.setFont(textFont());
    painter.drawText(rect(), Qt::AlignCenter, QString("%1 %").arg(m_value));
}

void ProgressCircle::setInfiniteAnimationValue(qreal value)
{
    m_infiniteAnimationValue = value;
    update();
}

void ProgressCircle::setVisibleValue(int value)
{
    if(m_visibleValue != value)
    {
        m_visibleValue = value;
        update();
    }
}

QFont ProgressCircle::textFont()
{
    QFont font;
    font.setWeight(QFont::Bold);
    font.setPixelSize(26);
    return font;
}

QString ProgressCircle::key() const
{
    return QString("%1,%2,%3,%4,%5,%6,%7,%8")
            .arg(m_infiniteAnimationValue)
            .arg(m_visibleValue)
            .arg(m_maximum)
            .arg(m_innerRadius)
            .arg(m_outerRadius)
            .arg(width())
            .arg(height())
            .arg(m_color.rgb())
            ;
}

QPixmap ProgressCircle::generatePixmap() const
{
    QPixmap pixmap(squared(rect()).size().toSize());
    pixmap.fill(QColor(0,0,0,0));
    QPainter painter(&pixmap);

    painter.setRenderHint(QPainter::Antialiasing, true);

    QRectF rect = pixmap.rect().adjusted(1,1,-1,-1);
    qreal margin = rect.width()*(1.0 - m_outerRadius)/2.0;
    rect.adjust(margin,margin,-margin,-margin);
    qreal innerRadius = m_innerRadius*rect.width()/2.0;

    //background grey circle
    painter.setBrush(QColor(225,225,225));
    painter.setPen(QColor(225,225,225));
    painter.drawPie(rect, 0, 360*16);

    painter.setBrush(m_color);
    painter.setPen(m_color);

    if(m_maximum == 0)
    {
        //draw as infinite process
        int startAngle = -m_infiniteAnimationValue * 360 * 16;
        int spanAngle = 0.15 * 360 * 16;
        painter.drawPie(rect, startAngle, spanAngle);
    }
    else
    {
        int value = qMin(m_visibleValue, m_maximum);
        int startAngle = 90 * 16;
        int spanAngle = -qreal(value) * 360 * 16 / m_maximum;

        painter.drawPie(rect, startAngle, spanAngle);
    }

    //inner circle and frame
    painter.setBrush(QColor(255,255,255));
    painter.setPen(QColor(0,0,0, 60));
    painter.drawEllipse(rect.center(), innerRadius, innerRadius);

    //outer frame
    painter.drawArc(rect, 0, 360*16);

    return pixmap;
}

qreal ProgressCircle::infiniteAnimationValue() const
{
    return m_infiniteAnimationValue;
}

int ProgressCircle::visibleValue() const
{
    return m_visibleValue;
}
