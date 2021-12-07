/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Quick Templates 2 module of Qt).
**
** QtCellink is free software: you can redistribute it and/or modify it
** under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QtCellink is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with QtCellink. If not, see <https://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "progressindicator.h"
#include <QtQuickTemplates2/private/qquickcontrol_p_p.h>

class ProgressIndicatorPrivate : public QQuickControlPrivate
{
public:
    bool running = true;
    qreal value = 0;
};

ProgressIndicator::ProgressIndicator(QQuickItem *parent)
    : QQuickControl(*(new ProgressIndicatorPrivate), parent)
{
}

bool ProgressIndicator::isRunning() const
{
    Q_D(const ProgressIndicator);
    return d->running;
}

void ProgressIndicator::setRunning(bool running)
{
    Q_D(ProgressIndicator);
    if (d->running == running)
        return;

    d->running = running;
    emit runningChanged();
}

qreal ProgressIndicator::value() const
{
    Q_D(const ProgressIndicator);
    return d->value;
}

void ProgressIndicator::setValue(qreal value)
{
    Q_D(ProgressIndicator);
    if (qFuzzyCompare(d->value, value))
        return;

    d->value = value;
    emit valueChanged();
}

void ProgressIndicator::contentItemChange(QQuickItem *newItem, QQuickItem *oldItem)
{
    QQuickControl::contentItemChange(newItem, oldItem);

    if (oldItem)
        disconnect(oldItem, SIGNAL(started()), this, SIGNAL(started()));
    if (newItem)
        connect(newItem, SIGNAL(started()), this, SIGNAL(started()));
}

#if QT_CONFIG(quicktemplates2_multitouch)
void ProgressIndicator::touchEvent(QTouchEvent *event)
{
    event->ignore(); // QTBUG-61785
}
#endif

#if QT_CONFIG(accessibility)
QAccessible::Role ProgressIndicator::accessibleRole() const
{
    return QAccessible::Indicator;
}
#endif
