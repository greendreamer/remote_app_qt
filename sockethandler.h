#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <QObject>
#include <QUdpSocket>

class SocketHandler : public QObject
{
    Q_OBJECT
public:
    explicit SocketHandler(QObject *parent = nullptr);
    bool sendMovementData(const QString &data);
    void connectToServer(const QString &address, const QString &port);
    void socketShutdown();

    QAbstractSocket::SocketState getSocketState();
signals:

};

#endif // SOCKETHANDLER_H
