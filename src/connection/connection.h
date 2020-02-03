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
