/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** This file is part of QtCellink (based on the Qt Labs Platform module of Qt).
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

#ifndef ICONLOADER_H
#define ICONLOADER_H

#include <QtCore/qstring.h>
#include <QtCore/qurl.h>
#include <QtGui/qicon.h>
#include <QtQuick/private/qquickpixmapcache_p.h>
#include <QtQuickTemplates2/private/qquickicon_p.h>

class QObject;

class IconLoader : public QQuickPixmap
{
public:
    IconLoader(int slot, QObject* parent);

    bool isEnabled() const;
    void setEnabled(bool enabled);

    QIcon toQIcon() const;

    QQuickIcon icon() const;
    void setIcon(const QQuickIcon& icon);

private:
    void loadIcon();

    QObject* m_parent = nullptr;
    int m_slot = -1;
    bool m_enabled = false;
    QQuickIcon m_icon;
};

#endif // ICONLOADER_H
