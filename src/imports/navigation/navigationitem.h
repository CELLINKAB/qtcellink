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

#ifndef NAVIgationITEM_H
#define NAVIgationITEM_H

#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtQml/qjsvalue.h>

class NavigationItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(bool fullScreen READ isFullScreen WRITE setFullScreen NOTIFY fullScreenChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QJSValue properties READ properties WRITE setProperties NOTIFY propertiesChanged)

public:
    explicit NavigationItem(QObject *parent = nullptr);

    bool isEnabled() const;
    void setEnabled(bool enabled);

    bool isFullScreen() const;
    void setFullScreen(bool fullScreen);

    QString name() const;
    void setName(const QString &name);

    QString title() const;
    void setTitle(const QString &title);

    QString icon() const;
    void setIcon(const QString &icon);

    QString url() const;
    void setUrl(const QString &url);

    QJSValue properties() const;
    void setProperties(const QJSValue &properties);

public slots:
    void trigger();

signals:
    void enabledChanged();
    void fullScreenChanged();
    void nameChanged();
    void titleChanged();
    void iconChanged();
    void urlChanged();
    void propertiesChanged();
    void triggered();

private:
    bool m_enabled = true;
    bool m_fullScreen = false;
    QString m_name;
    QString m_title;
    QString m_icon;
    QString m_url;
    QJSValue m_properties;
};

#endif // NAVIgationITEM_H
