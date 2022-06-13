/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Quick Controls 2 module of Qt).
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

#ifndef ICONIMAGE_P_H
#define ICONIMAGE_P_H

#include <QtGui/private/qiconloader_p.h>
#include <QtQuick/private/qquickimage_p_p.h>

class IconImagePrivate : public QQuickImagePrivate
{
    Q_DECLARE_PUBLIC(IconImage)

public:
    void updateIcon();
    void updateFillMode();
    qreal calculateDevicePixelRatio() const;
    bool updateDevicePixelRatio(qreal targetDevicePixelRatio) override;

    QUrl source;
    QColor color = Qt::transparent;
    QThemeIconInfo icon;
    bool updatingIcon = false;
    bool isThemeIcon = false;
    bool updatingFillMode = false;
};

#endif // ICONIMAGE_P_H
