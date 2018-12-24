/****************************************************************************
**
** Copyright (C) 2019 J-P Nurmi <jpnurmi@gmail.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Labs Platform module of Qt).
**
** QtCellink is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.

** QtCellink is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with QtCellink. If not, see <https://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "qquickplatformmenuseparator_p.h"

QT_BEGIN_NAMESPACE

/*!
    \qmltype MenuSeparator
    \inherits MenuItem
    \instantiates QQuickPlatformMenuSeparator
    \inqmlmodule Qt.labs.platform
    \since 5.8
    \brief A native menu separator.

    The MenuSeparator type is provided for convenience. It is a MenuItem
    that has the \l {MenuItem::}{separator} property set to \c true by default.

    \image qtlabsplatform-menubar.png

    \labs

    \sa Menu, MenuItem
*/

QQuickPlatformMenuSeparator::QQuickPlatformMenuSeparator(QObject *parent)
    : QQuickPlatformMenuItem(parent)
{
    setSeparator(true);
}

QT_END_NAMESPACE
