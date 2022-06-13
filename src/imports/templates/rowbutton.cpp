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

#include "rowbutton.h"

#include <QtGui/qfontinfo.h>
#include <QtQuickTemplates2/private/qquickabstractbutton_p_p.h>
#include <QtQuickTemplates2/private/qquicktheme_p.h>

class RowButtonPrivate : public QQuickAbstractButtonPrivate
{
public:
    bool highlighted = false;
};

RowButton::RowButton(QQuickItem* parent)
    : QQuickAbstractButton(*(new RowButtonPrivate), parent)
{
    setCheckable(true);
    setAutoExclusive(true);
}

bool RowButton::isHighlighted() const
{
    Q_D(const RowButton);
    return d->highlighted;
}

void RowButton::setHighlighted(bool highlighted)
{
    Q_D(RowButton);
    if (highlighted == d->highlighted)
        return;

    d->highlighted = highlighted;
    emit highlightedChanged();
}

QFont RowButton::defaultFont() const
{
    // ### TODO: fonts for custom controls via QQuickTheme?
    return QQuickTheme::font(QQuickTheme::TabBar);
}

QPalette RowButton::defaultPalette() const
{
    return QQuickTheme::palette(QQuickTheme::TabBar);
}

#if QT_CONFIG(accessibility)
QAccessible::Role RowButton::accessibleRole() const
{
    return QAccessible::PageTab;
}
#endif
