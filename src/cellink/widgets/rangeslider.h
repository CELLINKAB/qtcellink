/****************************************************************************
 **
 ** Copyright (C) 2020 CELLINK AB <info@cellink.com>
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
#ifndef RANGESLIDER_H
#define RANGESLIDER_H

#include <QtWidgets/qslider.h>
#include <QtCellink/cellink.h>

class RangeSliderPrivate;

class Q_CELLINK_EXPORT RangeSlider : public QSlider
{
    Q_OBJECT
    Q_PROPERTY(int lowerValue READ lowerValue WRITE setLowerValue)
    Q_PROPERTY(int upperValue READ upperValue WRITE setUpperValue)
    Q_PROPERTY(int lowerPosition READ lowerPosition WRITE setLowerPosition)
    Q_PROPERTY(int upperPosition READ upperPosition WRITE setUpperPosition)
    Q_PROPERTY(HandleMovementMode handleMovementMode READ handleMovementMode WRITE setHandleMovementMode)
    Q_ENUMS(HandleMovementMode)

public:
    explicit RangeSlider(QWidget *parent = nullptr);
    explicit RangeSlider(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~RangeSlider();

    enum HandleMovementMode
    {
        FreeMovement,
        NoCrossing,
        NoOverlapping
    };

    enum RangeHandle
    {
        NoHandle,
        LowerHandle,
        UpperHandle
    };

    HandleMovementMode handleMovementMode() const;
    void setHandleMovementMode(HandleMovementMode mode);

    int lowerValue() const;
    int upperValue() const;

    int lowerPosition() const;
    int upperPosition() const;

public Q_SLOTS:
    void setLowerValue(int lower);
    void setUpperValue(int upper);
    void setValues(int lower, int upper);

    void setLowerPosition(int lower);
    void setUpperPosition(int upper);

Q_SIGNALS:
    void valuesChanged(int lower, int upper);
    void lowerValueChanged(int lower);
    void upperValueChanged(int upper);

    void lowerPositionChanged(int lower);
    void upperPositionChanged(int upper);

    void sliderPressed(RangeHandle handle);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void sliderChange(SliderChange change) override;

private:
    Q_DISABLE_COPY(RangeSlider)
    Q_DECLARE_PRIVATE(RangeSlider)
    QScopedPointer<RangeSliderPrivate> d_ptr;
};

#endif // RANGESLIDER_H
