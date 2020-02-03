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
