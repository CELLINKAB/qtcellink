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

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtCellink/cellink.h>
#include <QtCore/qobject.h>
#include <QtCore/qstring.h>

class Q_CELLINK_EXPORT Connection : public QObject
{
    Q_OBJECT

public:
    explicit Connection(QObject *parent = nullptr);

    bool isConnected() const;
    bool isConnecting() const;
    bool isDisconnected() const;

    enum State { Disconnected, Connecting, Connected, Waiting };

    State state() const;
    void setState(State state);

    QString address() const;
    void setAddress(const QString &address);

    int timeout() const;
    void setTimeout(int timeout);

    int reconnectInterval() const;
    void setReconnectInterval(int interval);

public slots:
    void open();
    void close();

signals:
    void connected();
    void connecting();
    void disconnected();
    void waiting();
    void stateChanged();
    void timedout();
    void error();

protected:
    virtual void doOpen() = 0;
    virtual void doClose() = 0;
    virtual const QLoggingCategory &loggingCategory() const = 0;

    void startTimeout();
    void stopTimeout();
    void startReconnect();
    void stopReconnect();
    void timerEvent(QTimerEvent *event) override;

private:
    bool m_closed = false;
    int m_timer = 0;
    int m_timeout = 0;
    int m_reconnectTimer = 0;
    int m_reconnectInterval = 0;
    State m_state = Disconnected;
    QString m_address;
};

#endif // CONNECTION_H
