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

#ifndef MQTTCONNECTION_H
#define MQTTCONNECTION_H

#include <QtCellink/cellink.h>
#include <QtCellink/connection.h>
#include <functional>

class QMqttClient;

class Q_CELLINK_EXPORT MqttConnection : public Connection
{
    Q_OBJECT

public:
    explicit MqttConnection(QObject *parent = nullptr);
    ~MqttConnection();

    quint16 port() const;
    void setPort(quint16 port);

    bool subscribe(const QString &topic, std::function<void()> callback = nullptr);
    virtual void publish(const QString &topic, const QByteArray &message = QByteArray(), bool retain = false);
    virtual void unpublish(const QString &topic);
    virtual void receive(const QString &topic, const QByteArray &message);

    bool willRetain() const;
    QString willTopic() const;
    QByteArray willMessage() const;
    void setWillMessage(const QString &topic, const QByteArray &message = QByteArray(), bool retain = false);

signals:
    void subscribed(const QString &topic);
    void received(const QString &topic, const QByteArray &message);

protected:
    void doOpen() override;
    void doClose() override;
    const QLoggingCategory &loggingCategory() const override;

private:
    QMqttClient *m_mqttClient = nullptr;
};

#endif // MQTTCONNECTION_H
