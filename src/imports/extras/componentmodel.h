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

#ifndef COMPONENTMODEL_H
#define COMPONENTMODEL_H

#include <QtCore/qglobal.h>
#include <QtQml/qqmllist.h>
#include <QtQml/qqmlparserstatus.h>
#include <QtQmlModels/private/qqmlobjectmodel_p.h>

class QQmlComponent;
class QQmlContext;

/*!
    \class ComponentModel
    \ingroup mini-qml
    \brief Provides means to manage a collection of components.

    ...
*/
class ComponentModel : public QQmlObjectModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(QVariantMap properties READ properties WRITE setProperties)
    Q_PROPERTY(QQmlListProperty<QQmlComponent> components READ components)
    Q_CLASSINFO("DefaultProperty", "components")
    Q_INTERFACES(QQmlParserStatus)

public:
    explicit ComponentModel(QObject* parent = nullptr);

    bool isActive() const;
    void setActive(bool active);

    QVariantMap properties() const;
    void setProperties(const QVariantMap& properties);

    QQmlListProperty<QQmlComponent> components();

public slots:
    void reload();

signals:
    void activeChanged();

protected:
    void classBegin() override;
    void componentComplete() override;

private slots:
    void reloadLater();

private:
    QObject* create(QQmlComponent* component);

    static void components_append(QQmlListProperty<QQmlComponent>* property,
                                  QQmlComponent* component);
    static QQmlComponent* components_at(QQmlListProperty<QQmlComponent>* property, int index);
    static void components_clear(QQmlListProperty<QQmlComponent>* property);
    static int components_count(QQmlListProperty<QQmlComponent>* property);

    bool m_active = true;
    bool m_complete = true;
    bool m_reloading = false;
    QVariantMap m_properties;
    QList<QQmlComponent*> m_components;
};

#endif // COMPONENTMODEL_H
