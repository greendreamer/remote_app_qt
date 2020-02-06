#ifndef STATUSHANDLER_H
#define STATUSHANDLER_H

#include <QObject>
#include <QAbstractButton>
#include <QLabel>

class StatusHandler : public QObject
{
    Q_OBJECT
public:
    enum StatusIndicator
    {
        DISCONNECTED,
        CONNECTED,
        CONNECTING
    };
    explicit StatusHandler(QObject *parent = nullptr, QAbstractButton *refresh = nullptr, QLabel *status = nullptr);
    void setStatus(const QString text);
    QString getStatus() const;
private:
    QAbstractButton *b_refresh;
    QLabel *l_connectionStatus;
signals:

};

#endif // STATUSHANDLER_H
