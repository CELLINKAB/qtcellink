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

#include "titleseparator.h"

#include <QtQuickTemplates2/private/qquickcontrol_p_p.h>

class TitleSeparatorPrivate : public QQuickControlPrivate
{
public:
    QString title;
};

TitleSeparator::TitleSeparator(QQuickItem* parent)
    : QQuickControl(*(new TitleSeparatorPrivate), parent)
{}

QString TitleSeparator::title() const
{
    Q_D(const TitleSeparator);
    return d->title;
}

void TitleSeparator::setTitle(QString& title)
{
    Q_D(TitleSeparator);
    if (title == d->title)
        return;

    d->title = title;
    emit titleChanged();
}

#if QT_CONFIG(accessibility)
QAccessible::Role TitleSeparator::accessibleRole() const
{
    return QAccessible::Separator;
}
#endif
