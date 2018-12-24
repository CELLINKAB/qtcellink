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

#ifndef QQUICKPLATFORMMENUSEPARATOR_P_H
#define QQUICKPLATFORMMENUSEPARATOR_P_H

#include "qquickplatformmenuitem_p.h"

QT_BEGIN_NAMESPACE

class QQuickPlatformMenuSeparator : public QQuickPlatformMenuItem
{
    Q_OBJECT

public:
    explicit QQuickPlatformMenuSeparator(QObject *parent = nullptr);
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickPlatformMenuSeparator)

#endif // QQUICKPLATFORMMENUSEPARATOR_P_H
