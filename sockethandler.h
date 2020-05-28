#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <QObject>

class sockethandler : public QObject
{
    Q_OBJECT
public:
    explicit sockethandler(QObject *parent = nullptr);

signals:

};

#endif // SOCKETHANDLER_H
