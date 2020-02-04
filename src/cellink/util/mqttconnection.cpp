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

#include "mqttconnection.h"
#include <QtCore/qloggingcategory.h>
#include <QtMqtt/qmqttclient.h>

Q_LOGGING_CATEGORY(lcMqtt, "qtcellink.mqtt")

static const int MqttPort = 1883;
static const int MqttTimeout = 10000;
static const int MqttReconnectInterval = 10000;
static const QString MqttHost = QStringLiteral("localhost");

MqttConnection::MqttConnection(QObject *parent)
    : Connection(parent), m_mqttClient(new QMqttClient(this))
{
    setPort(MqttPort);
    setAddress(MqttHost);
    setTimeout(MqttTimeout);
    setReconnectInterval(MqttReconnectInterval);

    m_mqttClient->setProtocolVersion(QMqttClient::ProtocolVersion::MQTT_3_1_1);

    connect(m_mqttClient, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        QString topicName = topic.name();
        qCDebug(lcMqtt) << "received:" << topicName << message;
        emit messageReceived(topicName, message);
    });

    connect(m_mqttClient, &QMqttClient::errorChanged, this, [this](QMqttClient::ClientError err) {
        if (err != QMqttClient::NoError && err < QMqttClient::TransportInvalid) {
            qCDebug(lcMqtt) << "error:" << err << m_mqttClient->hostname();
            emit error();
        }
    });

    connect(m_mqttClient, &QMqttClient::stateChanged, this, [this](QMqttClient::ClientState state) {
        setState(static_cast<Connection::State>(state));
    });
}

MqttConnection::~MqttConnection()
{
    close();
}

quint16 MqttConnection::port() const
{
    return m_mqttClient->port();
}

void MqttConnection::setPort(quint16 port)
{
    m_mqttClient->setPort(port);
}

bool MqttConnection::subscribe(const QString &topic, std::function<void()> callback)
{
    QMqttSubscription *subscription = m_mqttClient->subscribe(topic);
    if (!subscription) {
        qCDebug(lcMqtt) << "error subscribing to:" << topic;
        return false;
    }
    connect(subscription, &QMqttSubscription::stateChanged, this, [=](QMqttSubscription::SubscriptionState state) {
        switch (state) {
        case QMqttSubscription::Subscribed:
            qCDebug(lcMqtt) << "subscribed to:" << topic;
            emit subscribed(topic);
            if (callback)
                callback();
            break;
        case QMqttSubscription::Error:
            qCDebug(lcMqtt) << "error subscribing to:" << topic;
            break;
        default:
            break;
        }
    });
    qCDebug(lcMqtt) << "subscribing to:" << topic;
    return true;
}

void MqttConnection::unsubscribe(const QString &topic)
{
    m_mqttClient->unsubscribe(topic);
}

void MqttConnection::publish(const MqttMessage &message)
{
    if (message.topic.isEmpty())
        return;

    qCDebug(lcMqtt) << "published" << message.topic << message.payload;
    m_mqttClient->publish(message.topic, message.payload, message.qos, message.retain);
}

void MqttConnection::publish(const QString &topic, const QByteArray &message)
{
    publish({topic, message});
}

void MqttConnection::unpublish(const QString &topic)
{
    if (topic.isEmpty())
        return;

    qCDebug(lcMqtt) << "unpublished" << topic;
    m_mqttClient->publish(topic, QByteArray(), 0, true);
}

MqttMessage MqttConnection::willMessage() const
{
    return { m_mqttClient->willTopic(), m_mqttClient->willMessage(), m_mqttClient->willQoS(), m_mqttClient->willRetain() };
}

void MqttConnection::setWillMessage(const MqttMessage &message)
{
    m_mqttClient->setWillTopic(message.topic);
    m_mqttClient->setWillMessage(message.payload);
    m_mqttClient->setWillRetain(message.retain);
    m_mqttClient->setWillQoS(message.qos);
}

void MqttConnection::setWillMessage(const QString &topic, const QByteArray &message)
{
    setWillMessage({topic, message});
}

void MqttConnection::doOpen()
{
    if (m_mqttClient->state() != QMqttClient::Disconnected)
        return;

    m_mqttClient->setHostname(address());
    m_mqttClient->connectToHost();
}

void MqttConnection::doClose()
{
    if (m_mqttClient->state() == QMqttClient::Disconnected)
        return;

    m_mqttClient->disconnectFromHost();
}

const QLoggingCategory &MqttConnection::loggingCategory() const
{
    return lcMqtt();
}
