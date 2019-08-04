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
#ifndef RANGESLIDER_P_H
#define RANGESLIDER_P_H

#include <QtWidgets/qstyle.h>
#include "rangeslider.h"

QT_FORWARD_DECLARE_CLASS(QStylePainter)
QT_FORWARD_DECLARE_CLASS(QStyleOptionSlider)

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

#endif // RANGESLIDER_P_H
