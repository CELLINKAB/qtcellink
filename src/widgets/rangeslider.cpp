/****************************************************************************
 **
 ** Copyright (C) 2019 CELLINK AB <info@cellink.com>
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is based on the QxtSpanSlider class from the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/
#include "rangeslider.h"

#include <QtGui/qevent.h>
#include <QtWidgets/qstylepainter.h>
#include <QtWidgets/qstyleoption.h>

class RangeSliderPrivate
{
    Q_DECLARE_PUBLIC(RangeSlider)

public:
    void init(RangeSlider *slider);
    void initStyleOption(QStyleOptionSlider* option, RangeSlider::RangeHandle handle = RangeSlider::UpperHandle) const;
    int pick(const QPoint& pt) const
    {
        return q_func()->orientation() == Qt::Horizontal ? pt.x() : pt.y();
    }
    int pixelPosToRangeValue(int pos) const;
    void handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, RangeSlider::RangeHandle handle);
    void drawHandle(QStylePainter* painter, RangeSlider::RangeHandle handle) const;
    void setupPainter(QPainter* painter, Qt::Orientation orientation, qreal x1, qreal y1, qreal x2, qreal y2) const;
    void drawRange(QStylePainter* painter, const QRect& rect) const;
    void triggerAction(QAbstractSlider::SliderAction action, bool main);
    void swapControls();
    void movePressedHandle();

    bool firstMovement = false;
    bool blockTracking = false;
    int lower = 0;
    int upper = 0;
    int lowerPos = 0;
    int upperPos = 0;
    int offset = 0;
    int position = 0;
    RangeSlider::RangeHandle lastPressed = RangeSlider::NoHandle;
    RangeSlider::RangeHandle mainControl = RangeSlider::LowerHandle;
    QStyle::SubControl lowerPressed = QStyle::SC_None;
    QStyle::SubControl upperPressed = QStyle::SC_None;
    RangeSlider::HandleMovementMode movement = RangeSlider::FreeMovement;
    RangeSlider *q_ptr = nullptr;
};

void RangeSliderPrivate::init(RangeSlider *slider)
{
    q_ptr = slider;
    QObject::connect(slider, SIGNAL(sliderReleased()), slider, SLOT(movePressedHandle()));
}

void RangeSliderPrivate::initStyleOption(QStyleOptionSlider *option, RangeSlider::RangeHandle handle) const
{
    Q_Q(const RangeSlider);
    q->initStyleOption(option);
    option->sliderPosition = (handle == RangeSlider::LowerHandle ? lowerPos : upperPos);
    option->sliderValue = (handle == RangeSlider::LowerHandle ? lower : upper);
}

int RangeSliderPrivate::pixelPosToRangeValue(int pos) const
{
    Q_Q(const RangeSlider);
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    int sliderMin = 0;
    int sliderMax = 0;
    int sliderLength = 0;
    const QRect gr = q->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, q);
    const QRect sr = q->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, q);
    if (q->orientation() == Qt::Horizontal) {
        sliderLength = sr.width();
        sliderMin = gr.x();
        sliderMax = gr.right() - sliderLength + 1;
    } else {
        sliderLength = sr.height();
        sliderMin = gr.y();
        sliderMax = gr.bottom() - sliderLength + 1;
    }
    return QStyle::sliderValueFromPosition(q->minimum(), q->maximum(), pos - sliderMin, sliderMax - sliderMin, opt.upsideDown);
}

void RangeSliderPrivate::handleMousePress(const QPoint &pos, QStyle::SubControl &control, int value, RangeSlider::RangeHandle handle)
{
    Q_Q(RangeSlider);
    QStyleOptionSlider opt;
    initStyleOption(&opt, handle);
    const QStyle::SubControl oldControl = control;
    control = q->style()->hitTestComplexControl(QStyle::CC_Slider, &opt, pos, q);
    const QRect sr = q->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, q);
    if (control == QStyle::SC_SliderHandle) {
        position = value;
        offset = pick(pos - sr.topLeft());
        lastPressed = handle;
        q->setSliderDown(true);
        emit q->sliderPressed(handle);
    }
    if (control != oldControl)
        q->update(sr);
}

void RangeSliderPrivate::setupPainter(QPainter *painter, Qt::Orientation orientation, qreal x1, qreal y1, qreal x2, qreal y2) const
{
    Q_Q(const RangeSlider);
    QColor highlight = q->palette().color(QPalette::Highlight);
    QLinearGradient gradient(x1, y1, x2, y2);
    gradient.setColorAt(0, highlight.darker(120));
    gradient.setColorAt(1, highlight.lighter(108));
    painter->setBrush(gradient);

    if (orientation == Qt::Horizontal)
        painter->setPen(QPen(highlight.darker(130), 0));
    else
        painter->setPen(QPen(highlight.darker(150), 0));
}

void RangeSliderPrivate::drawRange(QStylePainter *painter, const QRect &rect) const
{
    Q_Q(const RangeSlider);
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    // area
    QRect groove = q->style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, q);
    if (opt.orientation == Qt::Horizontal)
        groove.adjust(0, 0, -1, 0);
    else
        groove.adjust(0, 0, 0, -1);

    // pen  &brush
    painter->setPen(QPen(q->palette().color(QPalette::Dark).lighter(110), 0));
    if (opt.orientation == Qt::Horizontal)
        setupPainter(painter, opt.orientation, groove.center().x(), groove.top(), groove.center().x(), groove.bottom());
    else
        setupPainter(painter, opt.orientation, groove.left(), groove.center().y(), groove.right(), groove.center().y());

    // draw groove
    painter->drawRect(rect.intersected(groove));
}

void RangeSliderPrivate::drawHandle(QStylePainter *painter, RangeSlider::RangeHandle handle) const
{
    QStyleOptionSlider opt;
    initStyleOption(&opt, handle);
    opt.subControls = QStyle::SC_SliderHandle;
    QStyle::SubControl pressed = (handle == RangeSlider::LowerHandle ? lowerPressed : upperPressed);
    if (pressed == QStyle::SC_SliderHandle) {
        opt.activeSubControls = pressed;
        opt.state |= QStyle::State_Sunken;
    }
    painter->drawComplexControl(QStyle::CC_Slider, opt);
}

void RangeSliderPrivate::triggerAction(QAbstractSlider::SliderAction action, bool main)
{
    Q_Q(RangeSlider);
    int value = 0;
    bool no = false;
    bool up = false;
    const int min = q->minimum();
    const int max = q->maximum();
    const RangeSlider::RangeHandle altControl = (mainControl == RangeSlider::LowerHandle ? RangeSlider::UpperHandle : RangeSlider::LowerHandle);

    blockTracking = true;

    switch (action) {
    case QAbstractSlider::SliderSingleStepAdd:
        if ((main && mainControl == RangeSlider::UpperHandle) || (!main && altControl == RangeSlider::UpperHandle)) {
            value = qBound(min, upper + q->singleStep(), max);
            up = true;
            break;
        }
        value = qBound(min, lower + q->singleStep(), max);
        break;
    case QAbstractSlider::SliderSingleStepSub:
        if ((main && mainControl == RangeSlider::UpperHandle) || (!main && altControl == RangeSlider::UpperHandle)) {
            value = qBound(min, upper - q->singleStep(), max);
            up = true;
            break;
        }
        value = qBound(min, lower - q->singleStep(), max);
        break;
    case QAbstractSlider::SliderToMinimum:
        value = min;
        if ((main && mainControl == RangeSlider::UpperHandle) || (!main && altControl == RangeSlider::UpperHandle))
            up = true;
        break;
    case QAbstractSlider::SliderToMaximum:
        value = max;
        if ((main && mainControl == RangeSlider::UpperHandle) || (!main && altControl == RangeSlider::UpperHandle))
            up = true;
        break;
    case QAbstractSlider::SliderMove:
        if ((main && mainControl == RangeSlider::UpperHandle) || (!main && altControl == RangeSlider::UpperHandle))
            up = true;
        Q_FALLTHROUGH();
    case QAbstractSlider::SliderNoAction:
        no = true;
        break;
    default:
        qWarning("RangeSliderPrivate::triggerAction: Unknown action");
        break;
    }

    if (!no && !up) {
        if (movement == RangeSlider::NoCrossing)
            value = qMin(value, upper);
        else if (movement == RangeSlider::NoOverlapping)
            value = qMin(value, upper - 1);

        if (movement == RangeSlider::FreeMovement && value > upper) {
            swapControls();
            q->setUpperPosition(value);
        } else {
            q->setLowerPosition(value);
        }
    } else if (!no) {
        if (movement == RangeSlider::NoCrossing)
            value = qMax(value, lower);
        else if (movement == RangeSlider::NoOverlapping)
            value = qMax(value, lower + 1);

        if (movement == RangeSlider::FreeMovement && value < lower) {
            swapControls();
            q->setLowerPosition(value);
        } else {
            q->setUpperPosition(value);
        }
    }

    blockTracking = false;
    q->setLowerValue(lowerPos);
    q->setUpperValue(upperPos);
}

void RangeSliderPrivate::swapControls()
{
    qSwap(lower, upper);
    qSwap(lowerPressed, upperPressed);
    lastPressed = (lastPressed == RangeSlider::LowerHandle ? RangeSlider::UpperHandle : RangeSlider::LowerHandle);
    mainControl = (mainControl == RangeSlider::LowerHandle ? RangeSlider::UpperHandle : RangeSlider::LowerHandle);
}

void RangeSliderPrivate::movePressedHandle()
{
    switch (lastPressed) {
        case RangeSlider::LowerHandle:
            if (lowerPos != lower) {
                bool main = (mainControl == RangeSlider::LowerHandle);
                triggerAction(QAbstractSlider::SliderMove, main);
            }
            break;
        case RangeSlider::UpperHandle:
            if (upperPos != upper) {
                bool main = (mainControl == RangeSlider::UpperHandle);
                triggerAction(QAbstractSlider::SliderMove, main);
            }
            break;
        default:
            break;
    }
}

RangeSlider::RangeSlider(QWidget *parent) : QSlider(parent), d_ptr(new RangeSliderPrivate)
{
    Q_D(RangeSlider);
    d->init(this);
}

RangeSlider::RangeSlider(Qt::Orientation orientation, QWidget *parent) : QSlider(orientation, parent), d_ptr(new RangeSliderPrivate)
{
    Q_D(RangeSlider);
    d->init(this);
}

RangeSlider::~RangeSlider()
{
}

RangeSlider::HandleMovementMode RangeSlider::handleMovementMode() const
{
    Q_D(const RangeSlider);
    return d->movement;
}

void RangeSlider::setHandleMovementMode(RangeSlider::HandleMovementMode mode)
{
    Q_D(RangeSlider);
    d->movement = mode;
}

int RangeSlider::lowerValue() const
{
    Q_D(const RangeSlider);
    return qMin(d->lower, d->upper);
}

void RangeSlider::setLowerValue(int lower)
{
    Q_D(RangeSlider);
    setValues(lower, d->upper);
}

int RangeSlider::upperValue() const
{
    Q_D(const RangeSlider);
    return qMax(d->lower, d->upper);
}

void RangeSlider::setUpperValue(int upper)
{
    Q_D(RangeSlider);
    setValues(d->lower, upper);
}

void RangeSlider::setValues(int lower, int upper)
{
    Q_D(RangeSlider);
    const int low = qBound(minimum(), qMin(lower, upper), maximum());
    const int upp = qBound(minimum(), qMax(lower, upper), maximum());
    if (low != d->lower || upp != d->upper) {
        if (low != d->lower) {
            d->lower = low;
            d->lowerPos = low;
            emit lowerValueChanged(low);
        }
        if (upp != d->upper) {
            d->upper = upp;
            d->upperPos = upp;
            emit upperValueChanged(upp);
        }
        emit valuesChanged(d->lower, d->upper);
        update();
    }
}

int RangeSlider::lowerPosition() const
{
    Q_D(const RangeSlider);
    return d->lowerPos;
}

void RangeSlider::setLowerPosition(int lower)
{
    Q_D(RangeSlider);
    if (d->lowerPos != lower) {
        d->lowerPos = lower;
        if (!hasTracking())
            update();
        if (isSliderDown())
            emit lowerPositionChanged(lower);
        if (hasTracking() && !d->blockTracking) {
            bool main = (d->mainControl == RangeSlider::LowerHandle);
            d->triggerAction(SliderMove, main);
        }
    }
}

int RangeSlider::upperPosition() const
{
    Q_D(const RangeSlider);
    return d->upperPos;
}

void RangeSlider::setUpperPosition(int upper)
{
    Q_D(RangeSlider);
    if (d->upperPos != upper) {
        d->upperPos = upper;
        if (!hasTracking())
            update();
        if (isSliderDown())
            emit upperPositionChanged(upper);
        if (hasTracking() && !d->blockTracking) {
            bool main = (d->mainControl == RangeSlider::UpperHandle);
            d->triggerAction(SliderMove, main);
        }
    }
}

void RangeSlider::keyPressEvent(QKeyEvent *event)
{
    Q_D(RangeSlider);
    QSlider::keyPressEvent(event);

    bool main = true;
    SliderAction action = SliderNoAction;
    switch (event->key()) {
    case Qt::Key_Left:
        main = (orientation() == Qt::Horizontal);
        action = !invertedAppearance() ? SliderSingleStepSub : SliderSingleStepAdd;
        break;
    case Qt::Key_Right:
        main = (orientation() == Qt::Horizontal);
        action = !invertedAppearance() ? SliderSingleStepAdd : SliderSingleStepSub;
        break;
    case Qt::Key_Up:
        main = (orientation() == Qt::Vertical);
        action = invertedControls() ? SliderSingleStepSub : SliderSingleStepAdd;
        break;
    case Qt::Key_Down:
        main = (orientation() == Qt::Vertical);
        action = invertedControls() ? SliderSingleStepAdd : SliderSingleStepSub;
        break;
    case Qt::Key_Home:
        main = (d->mainControl == RangeSlider::LowerHandle);
        action = SliderToMinimum;
        break;
    case Qt::Key_End:
        main = (d->mainControl == RangeSlider::UpperHandle);
        action = SliderToMaximum;
        break;
    default:
        event->ignore();
        break;
    }

    if (action)
        d->triggerAction(action, main);
}

void RangeSlider::mousePressEvent(QMouseEvent *event)
{
    Q_D(RangeSlider);
    if (minimum() == maximum() || (event->buttons() ^ event->button())) {
        event->ignore();
        return;
    }

    d->handleMousePress(event->pos(), d->upperPressed, d->upper, RangeSlider::UpperHandle);
    if (d->upperPressed != QStyle::SC_SliderHandle)
        d->handleMousePress(event->pos(), d->lowerPressed, d->lower, RangeSlider::LowerHandle);

    d->firstMovement = true;
    event->accept();
}

void RangeSlider::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(RangeSlider);
    if (d->lowerPressed != QStyle::SC_SliderHandle && d->upperPressed != QStyle::SC_SliderHandle) {
        event->ignore();
        return;
    }

    QStyleOptionSlider opt;
    d->initStyleOption(&opt);
    const int m = style()->pixelMetric(QStyle::PM_MaximumDragDistance, &opt, this);
    int newPosition = d->pixelPosToRangeValue(d->pick(event->pos()) - d->offset);
    if (m >= 0) {
        const QRect r = rect().adjusted(-m, -m, m, m);
        if (!r.contains(event->pos()))
            newPosition = d->position;
    }

    // pick the preferred handle on the first movement
    if (d->firstMovement) {
        if (d->lower == d->upper) {
            if (newPosition < lowerValue()) {
                d->swapControls();
                d->firstMovement = false;
            }
        } else {
            d->firstMovement = false;
        }
    }

    if (d->lowerPressed == QStyle::SC_SliderHandle) {
        if (d->movement == NoCrossing)
            newPosition = qMin(newPosition, upperValue());
        else if (d->movement == NoOverlapping)
            newPosition = qMin(newPosition, upperValue() - 1);

        if (d->movement == FreeMovement && newPosition > d->upper) {
            d->swapControls();
            setUpperPosition(newPosition);
        } else {
            setLowerPosition(newPosition);
        }
    } else if (d->upperPressed == QStyle::SC_SliderHandle) {
        if (d->movement == NoCrossing)
            newPosition = qMax(newPosition, lowerValue());
        else if (d->movement == NoOverlapping)
            newPosition = qMax(newPosition, lowerValue() + 1);

        if (d->movement == FreeMovement && newPosition < d->lower) {
            d->swapControls();
            setLowerPosition(newPosition);
        } else {
            setUpperPosition(newPosition);
        }
    }
    event->accept();
}

void RangeSlider::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(RangeSlider);
    QSlider::mouseReleaseEvent(event);
    setSliderDown(false);
    d->lowerPressed = QStyle::SC_None;
    d->upperPressed = QStyle::SC_None;
    update();
}

void RangeSlider::paintEvent(QPaintEvent *event)
{
    Q_D(RangeSlider);
    Q_UNUSED(event);
    QStylePainter painter(this);

    // groove & ticks
    QStyleOptionSlider opt;
    d->initStyleOption(&opt);
    opt.sliderValue = 0;
    opt.sliderPosition = 0;
    opt.subControls = QStyle::SC_SliderGroove | QStyle::SC_SliderTickmarks;
    painter.drawComplexControl(QStyle::CC_Slider, opt);

    // handle rects
    opt.sliderPosition = d->lowerPos;
    const QRect lr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    const int lrv  = d->pick(lr.center());
    opt.sliderPosition = d->upperPos;
    const QRect ur = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    const int urv  = d->pick(ur.center());

    // span
    const int minv = qMin(lrv, urv);
    const int maxv = qMax(lrv, urv);
    const QPoint c = QRect(lr.center(), ur.center()).center();
    QRect spanRect;
    if (orientation() == Qt::Horizontal) {
        spanRect = QRect(QPoint(minv, c.y() - 2), QPoint(maxv, c.y() + 1));
#ifdef Q_OS_MAC
        spanRect.translate(0, 5);
#endif
    } else {
        spanRect = QRect(QPoint(c.x() - 2, minv), QPoint(c.x() + 1, maxv));
#ifdef Q_OS_MAC
        spanRect.translate(5, 0);
#endif
    }
    d->drawRange(&painter, spanRect);

    // handles
    switch (d->lastPressed) {
    case RangeSlider::LowerHandle:
        d->drawHandle(&painter, RangeSlider::UpperHandle);
        d->drawHandle(&painter, RangeSlider::LowerHandle);
        break;
    case RangeSlider::UpperHandle:
    default:
        d->drawHandle(&painter, RangeSlider::LowerHandle);
        d->drawHandle(&painter, RangeSlider::UpperHandle);
        break;
    }
}

void RangeSlider::sliderChange(SliderChange change)
{
    Q_D(RangeSlider);
    if (change == SliderRangeChange)
        setValues(d->lower, d->upper); // force within the range
    QSlider::sliderChange(change);
}

#include "moc_rangeslider.cpp"
