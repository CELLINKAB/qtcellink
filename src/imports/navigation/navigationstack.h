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

#ifndef NAVIGATIONSTACK_H
#define NAVIGATIONSTACK_H

#include "navigationgroup.h"
#include <QtQml/qjsvalue.h>
#include <QtQml/qqmlparserstatus.h>

class NavigationStack : public NavigationGroup, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(NavigationItem *currentItem READ currentItem NOTIFY currentChanged)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentChanged)
    Q_PROPERTY(QString currentName READ currentName WRITE setCurrentName NOTIFY currentChanged)
    Q_INTERFACES(QQmlParserStatus)

public:
    explicit NavigationStack(QObject *parent = nullptr);

    NavigationItem *currentItem() const;

    int currentIndex() const;
    void setCurrentIndex(int currentIndex);

    QString currentName() const;
    void setCurrentName(const QString &currentName);

public slots:
    void navigateAt(int index);
    void navigateTo(const QString &name);

signals:
    void currentChanged();
    void push(const QString &url, const QJSValue &properties);
    void pop(const QString &url, const QJSValue &properties);

protected:
    void classBegin() override;
    void componentComplete() override;

    void updateCurrentIndex();
    void updateCurrentName();

private:
    bool m_complete = true;
    int m_currentIndex = -1;
    QString m_currentName;
};

#endif // NAVIGATIONSTACK_H
