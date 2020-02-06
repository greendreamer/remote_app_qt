#include "statushandler.h"

StatusHandler::StatusHandler(QObject *parent,
                             QAbstractButton *refresh,
                             QLabel *status) : QObject(parent)
{
    b_refresh = refresh;
    l_connectionStatus = status;
}

void StatusHandler::setStatus(const QString text)
{
    l_connectionStatus->setText(text);
}

QString StatusHandler::getStatus() const
{
    return l_connectionStatus->text();
}
