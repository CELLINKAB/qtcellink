/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
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

#ifndef QQUICKPLATFORMICONLOADER_P_H
#define QQUICKPLATFORMICONLOADER_P_H

#include <QtCore/qurl.h>
#include <QtCore/qstring.h>
#include <QtGui/qicon.h>
#include <QtQuick/private/qquickpixmapcache_p.h>

#include "qquickplatformicon_p.h"

class QObject;

class QQuickPlatformIconLoader : public QQuickPixmap
{
public:
    QQuickPlatformIconLoader(int slot, QObject *parent);

    bool isEnabled() const;
    void setEnabled(bool enabled);

    QIcon toQIcon() const;

    QQuickPlatformIcon icon() const;
    void setIcon(const QQuickPlatformIcon &icon);

private:
    void loadIcon();

    QObject *m_parent;
    int m_slot = -1;
    bool m_enabled = false;
    QQuickPlatformIcon m_icon;
};

#endif // QQUICKPLATFORMICONLOADER_P_H
