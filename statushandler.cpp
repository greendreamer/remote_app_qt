#include "statushandler.h"
#include "constants.h"

//QString disconnectedHTML = "<font color=\"red\">";
//QString connectingHTML = "<font color=\"yellow\">";
//QString connectedHTML = "<font color=\"green\">";
//QString endHTML = "</font><br>";

StatusHandler::StatusHandler(QObject *parent,
                             SettingsDialog *settings,
                             QAbstractButton *refresh,
                             QLabel *socketStatus,
                             QLabel *cameraStatus) : QObject(parent)
{
    m_settings = settings;
    b_refresh = refresh;
    l_socketStatus = socketStatus;
    l_cameraStatus = cameraStatus;

    //Init text as disconnected
    l_socketStatus->setTextFormat(Qt::RichText);
    setSocketStatus(StatusIndicator::DISCONNECTED);

    l_cameraStatus->setTextFormat(Qt::RichText);
    setCameraStatus(StatusIndicator::DISCONNECTED);
}
void StatusHandler::updateStatus(QAbstractSocket::SocketState socketStatus, QAbstractSocket::SocketState cameraStatus) {
    updateStatus(socketStatus, cameraStatus, false);
}

void StatusHandler::updateStatus(QAbstractSocket::SocketState socketStatus, QAbstractSocket::SocketState cameraStatus, bool detailed) {
    if (detailed) {
        switch(socketStatus)
        {
            case QAbstractSocket::SocketState::BoundState: setSocketStatus(StatusHandler::StatusIndicator::DISCONNECTED); break;
            case QAbstractSocket::SocketState::ClosingState: setSocketStatus(StatusHandler::StatusIndicator::CLOSING); break;
            case QAbstractSocket::SocketState::ConnectedState: setSocketStatus(StatusHandler::StatusIndicator::CONNECTED); break;
            case QAbstractSocket::SocketState::ConnectingState: setSocketStatus(StatusHandler::StatusIndicator::CONNECTING); break;
            case QAbstractSocket::SocketState::HostLookupState: setSocketStatus(StatusHandler::StatusIndicator::LOOKUP); break;
            case QAbstractSocket::SocketState::UnconnectedState: setSocketStatus(StatusHandler::StatusIndicator::DISCONNECTED); break;
            default: setSocketStatus(StatusHandler::StatusIndicator::DISCONNECTED);
        }
    } else {
        switch(socketStatus)
        {
            case QAbstractSocket::SocketState::ConnectedState: setSocketStatus(StatusHandler::StatusIndicator::CONNECTED); break;
            case QAbstractSocket::SocketState::ConnectingState: setSocketStatus(StatusHandler::StatusIndicator::CONNECTING); break;
            case QAbstractSocket::SocketState::UnconnectedState: setSocketStatus(StatusHandler::StatusIndicator::DISCONNECTED); break;
            default: setSocketStatus(StatusHandler::StatusIndicator::DISCONNECTED);
        }
    }

    switch(cameraStatus)
    {
        case QAbstractSocket::SocketState::ConnectedState: setCameraStatus(StatusHandler::StatusIndicator::CONNECTED); break;
        case QAbstractSocket::SocketState::ConnectingState: setCameraStatus(StatusHandler::StatusIndicator::CONNECTING); break;
        case QAbstractSocket::SocketState::UnconnectedState: setCameraStatus(StatusHandler::StatusIndicator::DISCONNECTED); break;
        default: setCameraStatus(StatusHandler::StatusIndicator::DISCONNECTED);
    }
}

void StatusHandler::setSocketStatus(StatusHandler::StatusIndicator status)
{
    QString html;
    switch (status) {
        case StatusIndicator::DISCONNECTED: html = StatusConstants::disconnectedHTML + "disconnected"; break;
        case StatusIndicator::CONNECTING: html = StatusConstants::connectingHTML + "connecting | " + m_settings->getSocket_IP() + ":" + m_settings->getSocket_Port(); break;
        case StatusIndicator::CONNECTED: html = StatusConstants::connectedHTML + "connected | " + m_settings->getSocket_IP() + ":" + m_settings->getSocket_Port(); break;
        case StatusIndicator::BOUND: html = StatusConstants::boundHTML + "bound | " + m_settings->getSocket_IP() + ":" + m_settings->getSocket_Port(); break;
        case StatusIndicator::LOOKUP: html = StatusConstants::lookupHTML + "lookup"; break;
        case StatusIndicator::CLOSING: html = StatusConstants::closingHTML + "closing | " + m_settings->getSocket_IP() + ":" + m_settings->getSocket_Port(); break;
        default: html = StatusConstants::disconnectedHTML; break;
    }
    l_socketStatus->setText(html + StatusConstants::endHTML);
}

StatusHandler::StatusIndicator StatusHandler::getSocketStatus()
{
    //TODO Verify that this works
    QString currentText = l_socketStatus->text();
    if (currentText == StatusConstants::connectingHTML) {
        return StatusIndicator::CONNECTING;
    } else if (currentText == StatusConstants::connectedHTML) {
        return StatusIndicator::CONNECTED;
    } else { return StatusIndicator::DISCONNECTED; }
}

void StatusHandler::setCameraStatus(StatusHandler::StatusIndicator status)
{
    QString html;
    switch (status) {
        case StatusIndicator::DISCONNECTED: html = StatusConstants::disconnectedHTML + "disconnected"; break;
        case StatusIndicator::CONNECTING: html = StatusConstants::connectingHTML + "connecting | " + m_settings->getCamera_IP() + ":" + m_settings->getCamera_Port(); break;
        case StatusIndicator::CONNECTED: html = StatusConstants::connectedHTML + "connected | " + m_settings->getCamera_IP() + ":" + m_settings->getCamera_Port(); break;
        default: html = StatusConstants::disconnectedHTML; break;
    }
    l_cameraStatus->setText(html + StatusConstants::endHTML);
}

StatusHandler::StatusIndicator StatusHandler::getCameraStatus()
{
    //TODO Verify that this works
    QString currentText = l_cameraStatus->text();
    if (currentText == StatusConstants::connectingHTML) {
        return StatusIndicator::CONNECTING;
    } else if (currentText == StatusConstants::connectedHTML) {
        return StatusIndicator::CONNECTED;
    } else { return StatusIndicator::DISCONNECTED; }
}
