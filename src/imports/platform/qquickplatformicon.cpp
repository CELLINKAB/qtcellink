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

#include "qquickplatformicon_p.h"

QT_BEGIN_NAMESPACE

QUrl QQuickPlatformIcon::source() const
{
    return m_source;
}

void QQuickPlatformIcon::setSource(const QUrl& source)
{
    m_source = source;
}

QString QQuickPlatformIcon::name() const
{
    return m_name;
}

void QQuickPlatformIcon::setName(const QString& name)
{
    m_name = name;
}

bool QQuickPlatformIcon::isMask() const
{
    return m_mask;
}

void QQuickPlatformIcon::setMask(bool mask)
{
    m_mask = mask;
}

bool QQuickPlatformIcon::operator==(const QQuickPlatformIcon &other) const
{
    return m_source == other.m_source && m_name == other.m_name && m_mask == other.m_mask;
}

bool QQuickPlatformIcon::operator!=(const QQuickPlatformIcon &other) const
{
    return !(*this == other);
}

QT_END_NAMESPACE
