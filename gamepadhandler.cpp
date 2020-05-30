#include "gamepadhandler.h"

QGamepadManager *gamepadManager = QGamepadManager::instance();
QGamepad *m_gamepad;
QList<int> gamepads;
bool gamepadFirstSet = false;

GamepadHandler::GamepadHandler(QObject *parent) : QObject(parent)
{

}

bool GamepadHandler::checkForGamepads()
{
    gamepads = gamepadManager->connectedGamepads();
    if (gamepads.isEmpty()) {
        return false;
    } else {
        return true;
    }
}

void GamepadHandler::setFirstGamepad()
{
    m_gamepad = new QGamepad(*gamepads.begin(), this);
    setIsGamepadFirstSet(true);
}

void GamepadHandler::setIsGamepadFirstSet(bool status)
{
    gamepadFirstSet = status;
}

bool GamepadHandler::isGamepadFirstSet()
{
    return gamepadFirstSet;
}

QGamepad* GamepadHandler::getFirstGamepad()
{
    return m_gamepad;
}


