/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
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

#include "iconloader.h"

#include <QtCore/qobject.h>
#include <QtCore/qmetaobject.h>
#include <QtQml/qqml.h>

IconLoader::IconLoader(int slot, QObject *parent)
    : m_parent(parent),
      m_slot(slot)
{
    Q_ASSERT(slot != -1 && parent);
}

bool IconLoader::isEnabled() const
{
    return m_enabled;
}

void IconLoader::setEnabled(bool enabled)
{
    m_enabled = enabled;
    if (m_enabled)
        loadIcon();
}

QIcon IconLoader::toQIcon() const
{
    QIcon fallback = QPixmap::fromImage(image());
    return QIcon::fromTheme(m_icon.name(), fallback);
}

QQuickIcon IconLoader::icon() const
{
    return m_icon;
}

void IconLoader::setIcon(const QQuickIcon& icon)
{
    m_icon = icon;
    if (m_enabled)
        loadIcon();
}

void IconLoader::loadIcon()
{
    if (m_icon.source().isEmpty()) {
        clear(m_parent);
    } else {
        load(qmlEngine(m_parent), m_icon.source());
        if (m_slot != -1 && isLoading()) {
            connectFinished(m_parent, m_slot);
            m_slot = -1;
        }
    }

    if (!isLoading())
        m_parent->metaObject()->method(m_slot).invoke(m_parent);
}
