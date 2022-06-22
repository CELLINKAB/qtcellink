
/****************************************************************************
**
** Copyright (C) 2021 CELLINK AB <info@cellink.com>
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

#include "componentmodel.h"

#include <QtQml/qqmlcomponent.h>
#include <QtQml/qqmlcontext.h>

ComponentModel::ComponentModel(QObject* parent)
    : QQmlObjectModel(parent)
{}

bool ComponentModel::isActive() const
{
    return m_active;
}

void ComponentModel::setActive(bool active)
{
    if (m_active == active)
        return;

    m_active = active;
    reloadLater();
    emit activeChanged();
}

QVariantMap ComponentModel::properties() const
{
    return m_properties;
}

void ComponentModel::setProperties(const QVariantMap& properties)
{
    if (m_properties == properties)
        return;

    m_properties = properties;
    reloadLater();
}

QQmlListProperty<QQmlComponent> ComponentModel::components()
{
    return QQmlListProperty<QQmlComponent>(this,
                                           nullptr,
                                           components_append,
                                           components_count,
                                           components_at,
                                           components_clear);
}

void ComponentModel::reload()
{
    if (!m_complete)
        return;

    m_reloading = false;

    int n = count();
    if (n > 0)
        remove(0, n);

    if (!m_active)
        return;

    for (QQmlComponent* component : qAsConst(m_components))
        append(create(component));
}

void ComponentModel::classBegin()
{
    m_complete = false;
}

void ComponentModel::componentComplete()
{
    m_complete = true;
    if (m_active && !m_components.isEmpty())
        reload();
}

void ComponentModel::reloadLater()
{
    if (m_reloading || !m_complete)
        return;

    m_reloading = QMetaObject::invokeMethod(this, &ComponentModel::reload, Qt::QueuedConnection);
}

QObject* ComponentModel::create(QQmlComponent* component)
{
    QQmlContext* creationContext = component->creationContext();
    if (!creationContext)
        creationContext = qmlContext(this);
    QQmlContext* context = new QQmlContext(creationContext, this);
    for (auto it = m_properties.cbegin(); it != m_properties.cend(); ++it)
        context->setContextProperty(it.key(), it.value());
    return component->create(context);
}

void ComponentModel::components_append(QQmlListProperty<QQmlComponent>* property,
                                       QQmlComponent* component)
{
    if (!component)
        return;

    ComponentModel* model = qobject_cast<ComponentModel*>(property->object);
    model->m_components.append(component);
    if (model->m_active && model->m_complete)
        model->append(model->create(component));
}

QQmlComponent* ComponentModel::components_at(QQmlListProperty<QQmlComponent>* property, int index)
{
    ComponentModel* model = qobject_cast<ComponentModel*>(property->object);
    return model->m_components.value(index);
}

void ComponentModel::components_clear(QQmlListProperty<QQmlComponent>* property)
{
    ComponentModel* model = qobject_cast<ComponentModel*>(property->object);
    model->m_components.clear();
    model->reload();
}

int ComponentModel::components_count(QQmlListProperty<QQmlComponent>* property)
{
    ComponentModel* model = qobject_cast<ComponentModel*>(property->object);
    return model->m_components.count();
}
