#ifndef GAMEPADHANDLER_H
#define GAMEPADHANDLER_H

#include <QObject>
#include <QGamepadManager>
#include <QGamepad>

class GamepadHandler : public QObject
{
    Q_OBJECT
public:
    explicit GamepadHandler(QObject *parent = nullptr);
    bool checkForGamepads();
    void setFirstGamepad();
    void setIsGamepadFirstSet(bool status);
    bool isGamepadFirstSet();
    QGamepad* getFirstGamepad();

signals:

};

#endif // GAMEPADHANDLER_H
