#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include <QObject>
#include <QtGui>

class KeyHandler : public QObject
{
    Q_OBJECT
public:
    explicit KeyHandler(QObject *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

signals:

};

#endif // KEYHANDLER_H
