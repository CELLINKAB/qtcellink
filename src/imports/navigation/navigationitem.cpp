/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice,
**    this list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice,
**    this list of conditions and the following disclaimer in the documentation
**    and/or other materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors
**    may be used to endorse or promote products derived from this software
**    without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
** POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

#include "navigationitem.h"

NavigationItem::NavigationItem(QObject *parent) : QObject(parent)
{
}

bool NavigationItem::isEnabled() const
{
    return m_enabled;
}

void NavigationItem::setEnabled(bool enabled)
{
    if (m_enabled == enabled)
        return;

    m_enabled = enabled;
    emit enabledChanged();
}

bool NavigationItem::confirm() const
{
    return m_confirm;
}

void NavigationItem::setConfirm(bool confirm)
{
    if (m_confirm == confirm)
        return;

    m_confirm = confirm;
    emit confirmChanged();
}

bool NavigationItem::isFullScreen() const
{
    return m_fullScreen;
}

void NavigationItem::setFullScreen(bool fullScreen)
{
    if (m_fullScreen == fullScreen)
        return;

    m_fullScreen = fullScreen;
    emit fullScreenChanged();
}

QString NavigationItem::name() const
{
    return m_name;
}

void NavigationItem::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}

QString NavigationItem::title() const
{
    return m_title;
}

void NavigationItem::setTitle(const QString &title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged();
}

QString NavigationItem::icon() const
{
    return m_icon;
}

void NavigationItem::setIcon(const QString &icon)
{
    if (m_icon == icon)
        return;

    m_icon = icon;
    emit iconChanged();
}

QString NavigationItem::url() const
{
    return m_url;
}

void NavigationItem::setUrl(const QString &url)
{
    if (m_url == url)
        return;

    m_url = url;
    emit urlChanged();
}

QJSValue NavigationItem::properties() const
{
    return m_properties;
}

void NavigationItem::setProperties(const QJSValue &properties)
{
    if (m_properties.equals(properties))
        return;

    m_properties = properties;
    emit propertiesChanged();
}

void NavigationItem::trigger()
{
    if (!m_enabled)
        return;

    emit triggered(this);
}
