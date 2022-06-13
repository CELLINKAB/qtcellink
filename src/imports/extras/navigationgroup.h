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

#ifndef NAVIGATIONGROUP_H
#define NAVIGATIONGROUP_H

#include <QtCore/qobject.h>
#include <QtQml/qqmllist.h>

class NavigationItem;

class NavigationGroup : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY itemsChanged)
    Q_PROPERTY(QQmlListProperty<QObject> data READ data)
    Q_PROPERTY(QQmlListProperty<NavigationItem> items READ items NOTIFY itemsChanged)
    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit NavigationGroup(QObject* parent = nullptr);

    int count() const;
    QQmlListProperty<QObject> data();
    QQmlListProperty<NavigationItem> items();

    Q_INVOKABLE NavigationItem* itemAt(int index) const;
    Q_INVOKABLE int indexOf(NavigationItem* item) const;
    Q_INVOKABLE int find(const QString& name) const;
    Q_INVOKABLE void addItem(NavigationItem* item);

public slots:
    void clear();
    void trigger(const QString& name);
    void triggerAt(int index);

signals:
    void itemsChanged();
    void confirm(NavigationItem* item);
    void triggered(NavigationItem* item);

private:
    static void data_append(QQmlListProperty<QObject>* property, QObject* object);
    static int data_count(QQmlListProperty<QObject>* property);
    static QObject* data_at(QQmlListProperty<QObject>* property, int index);
    static void data_clear(QQmlListProperty<QObject>* property);

    static void items_append(QQmlListProperty<NavigationItem>* property, NavigationItem* item);
    static int items_count(QQmlListProperty<NavigationItem>* property);
    static NavigationItem* items_at(QQmlListProperty<NavigationItem>* property, int index);
    static void items_clear(QQmlListProperty<NavigationItem>* property);

    QList<NavigationItem*> m_items;
    QObjectList m_data;
};

#endif // NAVIGATIONGROUP_H
