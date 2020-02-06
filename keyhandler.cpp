#include "keyhandler.h"
#include <QKeyEvent>


KeyHandler::KeyHandler(QObject *parent) : QObject(parent)
{

}

void KeyHandler::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_W: ; break;
        case Qt::Key_A: "test"; break;
        case Qt::Key_S: "test"; break;
        case Qt::Key_D: "test"; break;
    }
}
