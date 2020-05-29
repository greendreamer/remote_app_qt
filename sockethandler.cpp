#include "sockethandler.h"

QUdpSocket *movementSocket = new QUdpSocket();

SocketHandler::SocketHandler(QObject *parent) : QObject(parent)
{
}

void SocketHandler::socketShutdown()
{
    movementSocket->close();
}

bool SocketHandler::sendMovementData(const QString &data)
{
    if(getSocketState() == QAbstractSocket::SocketState::ConnectedState) {
        QByteArray datagram;
        datagram.append(data);
        movementSocket->write(datagram);
        return true;
    } else { return false; }
}

void SocketHandler::connectToServer(const QString &address, const QString &port)
{
//    movementSocket = new QUdpSocket(this);
    movementSocket->bind(QHostAddress(address), port.toUShort());
    movementSocket->connectToHost(address, port.toUShort());
}

QAbstractSocket::SocketState SocketHandler::getSocketState()
{
    return (movementSocket->state());
}
