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

#ifndef OBJECT_H
#define OBJECT_H

#include <QtCellink/cellink.h>
#include <QtCore/qdatetime.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qobject.h>
#include <QtCore/qstring.h>

class Q_CELLINK_EXPORT Object : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool valid READ isValid NOTIFY validChanged)
    Q_PROPERTY(QString uuid READ uuid CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(bool modified READ isModified NOTIFY modifiedChanged)
    Q_PROPERTY(QString filePath READ filePath)

public:
    explicit Object(QObject *parent = nullptr);
    ~Object();

    bool isValid() const;
    void setValid(bool valid);

    QString uuid() const;
    void setUuid(const QString &uuid);
    void resetUuid();

    QString name() const;
    void setName(const QString &name);

    QDate date() const;
    void setDate(const QDate &date);

    bool isModified() const;
    void setModified(bool modified);
    Q_INVOKABLE void resetModified();

    bool isLazy() const;
    void setLazy(bool lazy);

    QJsonObject metaData() const;
    void setMetaData(const QJsonObject &metaData);

    QJsonObject saveState() const;
    void restoreState(const QJsonObject &json);

    QString filePath() const;

public slots:
    virtual bool load(const QString &filePath = QString());
    virtual bool save(const QString &filePath = QString());
    virtual bool cleanup(const QString &filePath = QString());

signals:
    void validChanged();
    void nameChanged();
    void dateChanged();
    void modified();
    void modifiedChanged();
    void metaDataChanged();
    void destroyed(Object *object);

protected:
    bool isInitialized() const;
    void beginInitialize();
    void endInitialize();

    virtual QJsonObject toJson() const;
    virtual void initFrom(const QJsonObject &json);

    virtual void modify();
    virtual void updateValid();

private:
    bool m_valid = true;
    bool m_modified = false;
    bool m_lazy = false;
    bool m_initialized = true;
    QString m_uuid;
    QString m_name;
    QDate m_date;
    QString m_filePath;
};

#endif // OBJECT_H
