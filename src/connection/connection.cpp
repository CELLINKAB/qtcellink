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

#include "connection.h"
#include <QtCore/qcoreevent.h>
#include <QtCore/qloggingcategory.h>

Connection::Connection(QObject *parent) : QObject(parent)
{
}

bool Connection::isConnected() const
{
    return m_state == Connected;
}

bool Connection::isConnecting() const
{
    return m_state == Connecting;
}

bool Connection::isDisconnected() const
{
    return m_state == Disconnected;
}

Connection::State Connection::state() const
{
    return m_state;
}

void Connection::setState(State state)
{
    if (m_state == state)
        return;

    m_state = state;
    switch (state) {
    case Connected:
        qCDebug(loggingCategory()) << "connected to:" << m_address;
        emit connected();
        stopTimeout();
        break;
    case Connecting:
        qCDebug(loggingCategory()) << "connecting to:" << m_address;
        emit connecting();
        startTimeout();
        break;
    case Disconnected:
        qCDebug(loggingCategory()) << "disconnected from:" << m_address;
        emit disconnected();
        stopTimeout();
        startReconnect();
        break;
    case Waiting:
        qCDebug(loggingCategory()) << "waiting:" << m_reconnectInterval << "ms";
        emit waiting();
        break;
    default:
        break;
    }
    emit stateChanged();
}

QString Connection::address() const
{
    return m_address;
}

void Connection::setAddress(const QString &address)
{
    m_address = address;
}

int Connection::timeout() const
{
    return m_timeout;
}

void Connection::setTimeout(int timeout)
{
    m_timeout = timeout;
}

int Connection::reconnectInterval() const
{
    return m_reconnectInterval;
}

void Connection::setReconnectInterval(int interval)
{
    m_reconnectInterval = interval;
}

void Connection::open()
{
    m_closed = false;
    doOpen();
}

void Connection::close()
{
    m_closed = true;
    stopReconnect();
    doClose();
}

void Connection::startTimeout()
{
    if (m_timer != 0)
        killTimer(m_timer);

    if (m_timeout > 0)
        m_timer = startTimer(m_timeout);
}

void Connection::stopTimeout()
{
    if (m_timer == 0)
        return;

    killTimer(m_timer);
    m_timer = 0;
}

void Connection::startReconnect()
{
    stopReconnect();

    if (!m_closed && m_reconnectInterval > 0) {
        m_reconnectTimer = startTimer(m_reconnectInterval);
        setState(Waiting);
    }
}

void Connection::stopReconnect()
{
    if (m_reconnectTimer == 0)
        return;

    killTimer(m_reconnectTimer);
    m_reconnectTimer = 0;
}

void Connection::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timer) {
        qCDebug(loggingCategory()) << "timeout connecting to:" << m_address;
        emit timedout();
        stopTimeout();
        close();
    } else if (event->timerId() == m_reconnectTimer) {
        stopReconnect();
        open();
    }
}
