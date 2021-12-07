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

#ifndef PROGRESSINDICATOR_H
#define PROGRESSINDICATOR_H

#include <QtGui/qcolor.h>
#include <QtQuickTemplates2/private/qquickcontrol_p.h>

class ProgressIndicatorPrivate;

class ProgressIndicator : public QQuickControl
{
    Q_OBJECT
    Q_PROPERTY(bool running READ isRunning WRITE setRunning NOTIFY runningChanged FINAL)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged FINAL)

public:
    explicit ProgressIndicator(QQuickItem* parent = nullptr);

    bool isRunning() const;
    void setRunning(bool running);

    qreal value() const;
    void setValue(qreal value);

Q_SIGNALS:
    void runningChanged();
    void valueChanged();
    void started();
    void stopped();

protected:
#if QT_CONFIG(quicktemplates2_multitouch)
    void touchEvent(QTouchEvent* event) override;
#endif

#if QT_CONFIG(accessibility)
    QAccessible::Role accessibleRole() const override;
#endif

    void contentItemChange(QQuickItem* newItem, QQuickItem* oldItem) override;

private:
    Q_DISABLE_COPY(ProgressIndicator)
    Q_DECLARE_PRIVATE(ProgressIndicator)
};

#endif // PROGRESSINDICATOR_H
