#ifndef STATUSHANDLER_H
#define STATUSHANDLER_H

#include <QObject>
#include <QAbstractButton>
#include <QLabel>
#include "settingsdialog.h"

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
    explicit StatusHandler(QObject *parent = nullptr, SettingsDialog *settings = nullptr,
                           QAbstractButton *refresh = nullptr,
                           QLabel *socketStatus = nullptr,
                           QLabel *cameraStatus = nullptr);

    void setSocketStatus(StatusIndicator status);
    StatusHandler::StatusIndicator getSocketStatus();
    void setCameraStatus(StatusIndicator status);
    StatusHandler::StatusIndicator getCameraStatus();
private:
    SettingsDialog *m_settings;
    QAbstractButton *b_refresh;
    QLabel *l_socketStatus;
    QLabel *l_cameraStatus;
signals:

};

#endif // STATUSHANDLER_H
