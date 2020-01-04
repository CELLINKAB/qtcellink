/****************************************************************************
**
** Copyright (C) 2019 CELLINK AB <info@cellink.com>
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

#ifndef COMPONENTVIEW_H
#define COMPONENTVIEW_H

#include <QtQuickTemplates2/private/qquickcontrol_p.h>
#include <QtQml/qjsvalue.h>

class ComponentView : public QQuickControl
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QJSValue properties READ properties WRITE setProperties NOTIFY propertiesChanged)
    Q_PROPERTY(QQmlListProperty<QQmlComponent> components READ components NOTIFY componentsChanged)
    Q_CLASSINFO("DefaultProperty", "components")

public:
    explicit ComponentView(QQuickItem *parent = nullptr);

    int count() const;

    int currentIndex() const;
    void setCurrentIndex(int currentIndex);

    QJSValue properties() const;
    void setProperties(const QJSValue &properties);

    QQmlListProperty<QQmlComponent> components();

    Q_INVOKABLE QQmlComponent *componentAt(int index) const;
    Q_INVOKABLE void addComponent(QQmlComponent *component);
    Q_INVOKABLE void insertComponent(int index, QQmlComponent *component);
    Q_INVOKABLE void removeComponent(QQmlComponent *component);
    Q_INVOKABLE QQmlComponent *takeComponent(int index);

public Q_SLOTS:
    void clear();

Q_SIGNALS:
    void countChanged();
    void currentIndexChanged();
    void propertiesChanged();
    void componentsChanged();
    void init(QQmlComponent *component);
    void push(QQmlComponent *component);
    void pop(QQmlComponent *component);

protected:
    void componentComplete() override;
    virtual void currentIndexChange(int newIndex, int oldIndex);

private:
    static void components_append(QQmlListProperty<QQmlComponent> *property, QQmlComponent *component);
    static QQmlComponent *components_at(QQmlListProperty<QQmlComponent> *property, int index);
    static void components_clear(QQmlListProperty<QQmlComponent> *property);
    static int components_count(QQmlListProperty<QQmlComponent> *property);

    int m_currentIndex = -1;
    QJSValue m_properties;
    QList<QQmlComponent *> m_components;
};

QML_DECLARE_TYPE(ComponentView)

#endif // COMPONENTVIEW_H
