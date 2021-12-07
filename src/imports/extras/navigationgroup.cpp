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

#include "navigationgroup.h"

#include "navigationitem.h"

NavigationGroup::NavigationGroup(QObject* parent)
    : QObject(parent)
{}

int NavigationGroup::count() const
{
    return m_items.count();
}

QQmlListProperty<QObject> NavigationGroup::data()
{
    return QQmlListProperty<QObject>(this, nullptr, data_append, data_count, data_at, data_clear);
}

QQmlListProperty<NavigationItem> NavigationGroup::items()
{
    return QQmlListProperty<NavigationItem>(this,
                                            nullptr,
                                            items_append,
                                            items_count,
                                            items_at,
                                            items_clear);
}

NavigationItem* NavigationGroup::itemAt(int index) const
{
    return m_items.value(index);
}

int NavigationGroup::indexOf(NavigationItem* item) const
{
    return m_items.indexOf(item);
}

int NavigationGroup::find(const QString& name) const
{
    for (int i = 0; i < m_items.count(); ++i) {
        if (m_items.at(i)->name() == name)
            return i;
    }
    return -1;
}

void NavigationGroup::addItem(NavigationItem* item)
{
    connect(item, &NavigationItem::triggered, this, &NavigationGroup::triggered);
    m_items.append(item);
    emit itemsChanged();
}

void NavigationGroup::clear()
{
    if (m_items.isEmpty())
        return;

    for (NavigationItem* item : qAsConst(m_items))
        item->disconnect(this);

    m_items.clear();
    emit itemsChanged();
}

void NavigationGroup::trigger(const QString& name)
{
    triggerAt(find(name));
}

void NavigationGroup::triggerAt(int index)
{
    NavigationItem* item = itemAt(index);
    if (!item)
        return;

    if (item->confirm())
        emit confirm(item);
    else
        item->trigger();
}

void NavigationGroup::data_append(QQmlListProperty<QObject>* property, QObject* object)
{
    NavigationGroup* group = static_cast<NavigationGroup*>(property->object);
    if (NavigationItem* item = qobject_cast<NavigationItem*>(object))
        group->addItem(item);
    else
        group->m_data.append(object);
}

int NavigationGroup::data_count(QQmlListProperty<QObject>* property)
{
    NavigationGroup* group = static_cast<NavigationGroup*>(property->object);
    return group->m_data.count();
}

QObject* NavigationGroup::data_at(QQmlListProperty<QObject>* property, int index)
{
    NavigationGroup* group = static_cast<NavigationGroup*>(property->object);
    return group->m_data.value(index);
}

void NavigationGroup::data_clear(QQmlListProperty<QObject>* property)
{
    NavigationGroup* group = static_cast<NavigationGroup*>(property->object);
    return group->m_data.clear();
}

void NavigationGroup::items_append(QQmlListProperty<NavigationItem>* property, NavigationItem* item)
{
    NavigationGroup* group = static_cast<NavigationGroup*>(property->object);
    return group->addItem(item);
}

int NavigationGroup::items_count(QQmlListProperty<NavigationItem>* property)
{
    NavigationGroup* group = static_cast<NavigationGroup*>(property->object);
    return group->count();
}

NavigationItem* NavigationGroup::items_at(QQmlListProperty<NavigationItem>* property, int index)
{
    NavigationGroup* group = static_cast<NavigationGroup*>(property->object);
    return group->itemAt(index);
}

void NavigationGroup::items_clear(QQmlListProperty<NavigationItem>* property)
{
    NavigationGroup* group = static_cast<NavigationGroup*>(property->object);
    group->clear();
}
