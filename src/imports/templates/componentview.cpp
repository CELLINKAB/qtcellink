/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
**
** This file is part of QtCellink.
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

#include "componentview.h"

ComponentView::ComponentView(QQuickItem* parent)
    : QQuickControl(parent)
{}

int ComponentView::count() const
{
    return m_components.count();
}

int ComponentView::currentIndex() const
{
    return m_currentIndex;
}

void ComponentView::setCurrentIndex(int currentIndex)
{
    if (m_currentIndex == currentIndex)
        return;

    if (isComponentComplete())
        currentIndexChange(currentIndex, m_currentIndex);
    m_currentIndex = currentIndex;
    emit currentIndexChanged();
}

QJSValue ComponentView::properties() const
{
    return m_properties;
}

void ComponentView::setProperties(const QJSValue& properties)
{
    if (m_properties.strictlyEquals(properties))
        return;

    m_properties = properties;
    emit propertiesChanged();
}

QQmlListProperty<QQmlComponent> ComponentView::components()
{
    return QQmlListProperty<QQmlComponent>(this,
                                           nullptr,
                                           components_append,
                                           components_count,
                                           components_at,
                                           components_clear);
}

QQmlComponent* ComponentView::componentAt(int index) const
{
    return m_components.value(index);
}

void ComponentView::addComponent(QQmlComponent* component)
{
    insertComponent(count(), component);
}

void ComponentView::insertComponent(int index, QQmlComponent* component)
{
    if (!component)
        return;

    m_components.insert(index, component);
    emit componentsChanged();
    emit countChanged();
}

void ComponentView::removeComponent(QQmlComponent* component)
{
    if (!m_components.removeAll(component))
        return;

    emit componentsChanged();
    emit countChanged();
}

QQmlComponent* ComponentView::takeComponent(int index)
{
    if (index < 0 || index >= m_components.count())
        return nullptr;

    QQmlComponent* component = m_components.takeAt(index);
    emit componentsChanged();
    emit countChanged();
    return component;
}

void ComponentView::clear()
{
    if (m_components.isEmpty())
        return;

    m_components.clear();
    emit componentsChanged();
    emit countChanged();
}

void ComponentView::componentComplete()
{
    QQuickControl::componentComplete();
    if (m_currentIndex != -1)
        currentIndexChange(m_currentIndex, -1);
}

void ComponentView::currentIndexChange(int newIndex, int oldIndex)
{
    QQmlComponent* component = componentAt(newIndex);
    if (!component)
        return;

    if (oldIndex == -1)
        emit init(component);
    else if (newIndex > oldIndex)
        emit push(component);
    else
        emit pop(component);
}

void ComponentView::components_append(QQmlListProperty<QQmlComponent>* property,
                                      QQmlComponent* component)
{
    if (!component)
        return;

    ComponentView* view = static_cast<ComponentView*>(property->object);
    view->addComponent(component);
}

QQmlComponent* ComponentView::components_at(QQmlListProperty<QQmlComponent>* property, int index)
{
    ComponentView* view = static_cast<ComponentView*>(property->object);
    return view->m_components.value(index);
}

void ComponentView::components_clear(QQmlListProperty<QQmlComponent>* property)
{
    ComponentView* view = static_cast<ComponentView*>(property->object);
    view->clear();
}

int ComponentView::components_count(QQmlListProperty<QQmlComponent>* property)
{
    ComponentView* view = static_cast<ComponentView*>(property->object);
    return view->count();
}
