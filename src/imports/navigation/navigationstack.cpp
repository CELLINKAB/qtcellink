/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
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

#include "navigationstack.h"
#include "navigationitem.h"

NavigationStack::NavigationStack(QObject *parent) : NavigationGroup(parent)
{
    connect(this, &NavigationGroup::triggered, [&](NavigationItem *item) {
        int index = indexOf(item);
        if (index > m_currentIndex)
            emit push(item->url(), item->properties());
        else
            emit pop(item->url(), item->properties());
        m_currentIndex = index;
        updateCurrentName();
        emit currentChanged();
    });
}

NavigationItem *NavigationStack::currentItem() const
{
    return itemAt(m_currentIndex);
}

int NavigationStack::currentIndex() const
{
    return m_currentIndex;
}

void NavigationStack::setCurrentIndex(int currentIndex)
{
    if (m_currentIndex == currentIndex)
        return;

    if (m_complete) {
        navigateAt(currentIndex);
        return;
    }

    m_currentIndex = currentIndex;
    updateCurrentName();
    emit currentChanged();
}

QString NavigationStack::currentName() const
{
    return m_currentName;
}

void NavigationStack::setCurrentName(const QString &currentName)
{
    if (m_currentName == currentName)
        return;

    if (m_complete) {
        navigateTo(currentName);
        return;
    }

    m_currentName = currentName;
    updateCurrentIndex();
    emit currentChanged();
}

void NavigationStack::navigateAt(int index)
{
    triggerAt(index);
}

void NavigationStack::navigateTo(const QString &name)
{
    trigger(name);
}

void NavigationStack::classBegin()
{
    m_complete = false;
}

void NavigationStack::componentComplete()
{
    m_complete = true;
    if (!m_currentName.isEmpty())
        navigateTo(m_currentName);
    else if (m_currentIndex != -1)
        navigateAt(m_currentIndex);
}

void NavigationStack::updateCurrentIndex()
{
    m_currentIndex = find(m_currentName);
}

void NavigationStack::updateCurrentName()
{
    NavigationItem *item = currentItem();
    m_currentName = item ? item->name() : QString();
}
