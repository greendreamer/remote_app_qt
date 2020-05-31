#include <string>
#include <QDebug>
#include <QTimer>
#include <QGamepadManager>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "logger.h"
#include "confighandler.h"
#include "statushandler.h"
#include "sockethandler.h"
#include "gamepadhandler.h"
#include "constants.h"

Logger *logger;
SettingsDialog *settingsDialog;
StatusHandler *statusHandler;
SocketHandler *socketHandler;
GamepadHandler *gamepadHandler;
bool setupConnections = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString logFileName = "./log.txt";
    logger = new Logger(this, logFileName, ui->loggerOutput);
    logger->write(Logger::Level::INFO, "Logger Initilized!");

    settingsDialog = new SettingsDialog(this);
    settingsDialog->setModal((true));

    statusHandler = new StatusHandler(this, settingsDialog, ui->b_refresh, ui->l_socket_status, ui->l_camera_status);
    QTimer *updateStatusTimer = new QTimer(this);
    connect(updateStatusTimer, SIGNAL(timeout()), this, SLOT(updateAll()));
    updateStatusTimer->start(100);

    logger->write(Logger::Level::INFO, "Movement Socket connecting to: " + settingsDialog->getSocket_IP() + ":" + settingsDialog->getSocket_Port() + " ...");

    socketHandler->connectToServer(settingsDialog->getSocket_IP(),settingsDialog->getSocket_Port());

    if (!(socketHandler->getSocketState() == QAbstractSocket::SocketState::ConnectedState)) {
        logger->write(Logger::Level::ERROR, "Movement Socket cannot connect to: " + settingsDialog->getSocket_IP() + ":" + settingsDialog->getSocket_Port());
    } else {
        logger->write(Logger::Level::INFO, "Movement Socket connected!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat() == false)
    {
        switch(event->key())
        {
            case Qt::Key_W: ui->b_keyboardUp->setDown(true), on_b_keyboardUp_pressed(); break;
            case Qt::Key_A: ui->b_keyboardLeft->setDown(true), on_b_keyboardLeft_pressed(); break;
            case Qt::Key_S: ui->b_keyboardDown->setDown(true), on_b_keyboardDown_pressed(); break;
            case Qt::Key_D: ui->b_keyboardRight->setDown(true), on_b_keyboardRight_pressed(); break;
            case Qt::Key_Q: ui->b_keyboardTurnLeft->setDown(true), on_b_keyboardTurnLeft_pressed(); break;
            case Qt::Key_E: ui->b_keyboardTurnRight->setDown(true), on_b_keyboardTurnRight_pressed(); break;
            case Qt::Key_U: on_increaseThrottle_pressed(); break;
            case Qt::Key_J: on_decreaseThrottle_pressed(); break;

            case Qt::Key_F1: ui->b_keyboardAction_1->setDown(true), on_b_keyboardAction_1_pressed(); break;
            case Qt::Key_F2: ui->b_keyboardAction_2->setDown(true), on_b_keyboardAction_2_pressed(); break;
            case Qt::Key_F3: ui->b_keyboardAction_3->setDown(true), on_b_keyboardAction_3_pressed(); break;
            case Qt::Key_F4: ui->b_keyboardAction_4->setDown(true), on_b_keyboardAction_4_pressed(); break;
        }
        switch(socketHandler->getSocketState())
        {
            case QAbstractSocket::SocketState::BoundState: logger->write(Logger::Level::WARNING, "Bound"); break;
            case QAbstractSocket::SocketState::ClosingState: logger->write(Logger::Level::WARNING, "Closing"); break;
            case QAbstractSocket::SocketState::ConnectedState: logger->write(Logger::Level::WARNING, "Connected"); break;
            case QAbstractSocket::SocketState::ListeningState: logger->write(Logger::Level::WARNING, "Listening"); break;
            case QAbstractSocket::SocketState::ConnectingState: logger->write(Logger::Level::WARNING, "Bound"); break;
            case QAbstractSocket::SocketState::HostLookupState: logger->write(Logger::Level::WARNING, "HostLookup"); break;
            case QAbstractSocket::SocketState::UnconnectedState: logger->write(Logger::Level::WARNING, "Unconnected"); break;
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat() == false)
    {
        switch(event->key())
        {
            case Qt::Key_W: ui->b_keyboardUp->setDown(false), on_b_keyboardUp_released(); break;
            case Qt::Key_A: ui->b_keyboardLeft->setDown(false), on_b_keyboardLeft_released(); break;
            case Qt::Key_S: ui->b_keyboardDown->setDown(false), on_b_keyboardDown_released(); break;
            case Qt::Key_D: ui->b_keyboardRight->setDown(false), on_b_keyboardRight_released(); break;
            case Qt::Key_Q: ui->b_keyboardTurnLeft->setDown(false), on_b_keyboardTurnLeft_released(); break;
            case Qt::Key_E: ui->b_keyboardTurnRight->setDown(false), on_b_keyboardTurnRight_released(); break;

            case Qt::Key_F1: ui->b_keyboardAction_1->setDown(false); break;
            case Qt::Key_F2: ui->b_keyboardAction_2->setDown(false); break;
            case Qt::Key_F3: ui->b_keyboardAction_3->setDown(false); break;
            case Qt::Key_F4: ui->b_keyboardAction_4->setDown(false); break;
        }
    }
}


void MainWindow::on_toolButton_clicked()
{
    settingsDialog->exec();
}

//Keyboard Movement Keys
void MainWindow::on_b_keyboardUp_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Up pressed"); kup = 1.0; sendKeyboardData(); }
void MainWindow::on_b_keyboardLeft_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Left pressed"); kleft = -1.0; sendKeyboardData(); }
void MainWindow::on_b_keyboardDown_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Down pressed"); kdown = -1.0; sendKeyboardData(); }
void MainWindow::on_b_keyboardRight_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Right pressed"); kright = 1.0; sendKeyboardData(); }
void MainWindow::on_b_keyboardTurnLeft_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Turn Left pressed"); kturnLeft = -1.0; sendKeyboardData(); }
void MainWindow::on_b_keyboardTurnRight_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Turn Right pressed"); kturnRight = 1.0; sendKeyboardData(); }

void MainWindow::on_increaseThrottle_pressed() { logger->write(Logger::Level::DEBUG, "Increased maximum"); ui->s_keyboardThrottle->setValue(ui->s_keyboardThrottle->value() + 10); on_s_keyboardThrottle_sliderMoved(ui->s_keyboardThrottle->value()); }
void MainWindow::on_decreaseThrottle_pressed() { logger->write(Logger::Level::DEBUG, "Decreased maximum"); ui->s_keyboardThrottle->setValue(ui->s_keyboardThrottle->value() - 10); on_s_keyboardThrottle_sliderMoved(ui->s_keyboardThrottle->value()); }
//----------------
void MainWindow::on_b_keyboardUp_released() { logger->write(Logger::Level::DEBUG, "Keyboard Up released"); kup = 0.0; sendKeyboardData(); }
void MainWindow::on_b_keyboardLeft_released() { logger->write(Logger::Level::DEBUG, "Keyboard Left released"); kleft = 0.0; sendKeyboardData(); }
void MainWindow::on_b_keyboardDown_released() { logger->write(Logger::Level::DEBUG, "Keyboard Down released"); kdown = 0.0; sendKeyboardData(); }
void MainWindow::on_b_keyboardRight_released() { logger->write(Logger::Level::DEBUG, "Keyboard Right released"); kright = 0.0; sendKeyboardData(); }
void MainWindow::on_b_keyboardTurnLeft_released() { logger->write(Logger::Level::DEBUG, "Keyboard Turn Left released"); kturnLeft = 0.0; sendKeyboardData(); }
void MainWindow::on_b_keyboardTurnRight_released() { logger->write(Logger::Level::DEBUG, "Keyboard Turn Right released"); kturnRight = 0.0; sendKeyboardData(); }

//Keyboard Action Keys
void MainWindow::on_b_keyboardAction_1_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 1 pressed"), statusHandler->setSocketStatus(StatusHandler::StatusIndicator::DISCONNECTED); }
void MainWindow::on_b_keyboardAction_2_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 2 pressed"), statusHandler->setSocketStatus(StatusHandler::StatusIndicator::CONNECTED); }
void MainWindow::on_b_keyboardAction_3_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 3 pressed"), statusHandler->setCameraStatus(StatusHandler::StatusIndicator::DISCONNECTED); }
void MainWindow::on_b_keyboardAction_4_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 4 pressed"), statusHandler->setCameraStatus(StatusHandler::StatusIndicator::CONNECTED); }

//Keyboard speed throttle
void MainWindow::on_s_keyboardThrottle_sliderMoved(int position) { ui->l_keyboardThrottle->setText(QStringLiteral("Maximum: %1%").arg(position)); }

//Keyboard others
void MainWindow::sendKeyboardData()
{
    if (!(socketHandler->sendMovementData(
              QString::number(kup+kdown) + "," + QString::number(kleft+kright) + "," + QString::number(kturnLeft+kturnRight))))
    {
        logger->write(Logger::Level::WARNING, "Could not send data");
    }
}

//Controller Movement Sliders
void MainWindow::on_s_leftJoystickX_Throttle_sliderMoved(int position) { on_s_leftJoystickX_Throttle_sliderMovedf(float(position)/float(100)); }
void MainWindow::on_s_leftJoystickY_Throttle_sliderMoved(int position) { on_s_leftJoystickY_Throttle_sliderMovedf(float(position)/float(100)); }
void MainWindow::on_s_leftJoystickX_Throttle_sliderMovedf(float position) { jx = position; sendJoystickData(); }
void MainWindow::on_s_leftJoystickY_Throttle_sliderMovedf(float position) { jy = position; sendJoystickData(); }
//void MainWindow::on_s_leftTrigger_Throttle_sliderMoved(int position) { sendJoystickData(); }
//---------------
void MainWindow::on_s_rightJoystickX_Throttle_sliderMoved(int position) { on_s_rightJoystickX_Throttle_sliderMovedf(float(position)/float(100)); }
void MainWindow::on_s_rightJoystickX_Throttle_sliderMovedf(float position) { jz = position; sendJoystickData(); }
//void MainWindow::on_s_rightJoystickY_Throttle_sliderMoved(int position) { sendJoystickData(); }
//void MainWindow::on_s_rightTrigger_Throttle_sliderMoved(int position) { sendJoystickData(); }

//Joystick Action Keys
void MainWindow::on_b_joystickAction_1_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 1 pressed"); }
void MainWindow::on_b_joystickAction_2_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 2 pressed"); }
void MainWindow::on_b_joystickAction_3_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 3 pressed"); }
void MainWindow::on_b_joystickAction_4_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 4 pressed"); }

//Joystick speed throttle
void MainWindow::on_s_joystickThrottle_sliderMoved(int position) { ui->l_joystickThrottle->setText(QStringLiteral("Maximum: %1%").arg(position)); }

//Joystick others
void MainWindow::sendJoystickData()
{
    if (!(socketHandler->sendMovementData(
              QString::number(jy) + "," + QString::number(jx) + "," + QString::number(jz))))
    {
        logger->write(Logger::Level::WARNING, "Could not send data");
    }
}

//Status related
void MainWindow::on_b_refresh_pressed() { slotReboot(); }

void MainWindow::updateAll() {
    statusHandler->updateStatus(socketHandler->getSocketState(), QAbstractSocket::SocketState::UnconnectedState, true);
    if (gamepadHandler->checkForGamepads() && !gamepadHandler->isGamepadFirstSet())
    {
        gamepadHandler->setFirstGamepad();
    }

    if(gamepadHandler->isGamepadFirstSet() && !setupConnections) {
        connect(gamepadHandler->getFirstGamepad(), &QGamepad::axisLeftXChanged, this, [this](double value)
        {
            /*logger->write(Logger::Level::DEBUG, "Left X: " + QString::number(value));*/
            on_s_leftJoystickX_Throttle_sliderMovedf(float(value));
            ui->s_leftJoystickX_Throttle->setValue(value*100);
        });
        connect(gamepadHandler->getFirstGamepad(), &QGamepad::axisLeftYChanged, this, [this](double value)
        {
            /*logger->write(Logger::Level::DEBUG, "Left Y: " + QString::number(-value));*/
            on_s_leftJoystickY_Throttle_sliderMovedf(float(-value));
            ui->s_leftJoystickY_Throttle->setValue(-value*100);
        });
        connect(gamepadHandler->getFirstGamepad(), &QGamepad::axisRightXChanged, this, [this](double value)
        {
            /*logger->write(Logger::Level::DEBUG, "Right X: " + QString::number(value));*/
            on_s_rightJoystickX_Throttle_sliderMovedf(float(value));
            ui->s_rightJoystickX_Throttle->setValue(value*100);
        });
        connect(gamepadHandler->getFirstGamepad(), &QGamepad::axisRightYChanged, this, [this](double value){ /*logger->write(Logger::Level::DEBUG, "Right Y: " + QString::number(-value));*/ /*on_s_rightJoystickY_Throttle_sliderMoved(-value*100)*/; ui->s_rightJoystickY_Throttle->setValue(-value*100);});

        connect(gamepadHandler->getFirstGamepad(), &QGamepad::buttonL2Changed, this, [this](double value){ /*logger->write(Logger::Level::DEBUG, "Left Trigger: " + QString::number(value));*/ /*on_s_leftTrigger_Throttle_sliderMoved(value*100);*/ ui->s_leftTrigger_Throttle->setValue(value*100);});
        connect(gamepadHandler->getFirstGamepad(), &QGamepad::buttonR2Changed, this, [this](double value){ /*logger->write(Logger::Level::DEBUG, "Right Trigger: " + QString::number(value));*/ /*on_s_rightTrigger_Throttle_sliderMoved(value*100);*/ ui->s_rightTrigger_Throttle->setValue(value*100);});
        connect(gamepadHandler->getFirstGamepad(), &QGamepad::buttonAChanged, this, [this](bool value){ui->b_joystickAction_1->setDown(value);});
        connect(gamepadHandler->getFirstGamepad(), &QGamepad::buttonBChanged, this, [this](bool value){ui->b_joystickAction_2->setDown(value);});
        connect(gamepadHandler->getFirstGamepad(), &QGamepad::buttonYChanged, this, [this](bool value){ui->b_joystickAction_3->setDown(value);});
        connect(gamepadHandler->getFirstGamepad(), &QGamepad::buttonXChanged, this, [this](bool value){ui->b_joystickAction_4->setDown(value);});
        connect(gamepadHandler->getFirstGamepad(), &QGamepad::buttonUpChanged, this, [this](bool value){if(value) {ui->s_joystickThrottle->setValue(ui->s_joystickThrottle->value() + 10); on_s_joystickThrottle_sliderMoved(ui->s_joystickThrottle->value());}});
        connect(gamepadHandler->getFirstGamepad(), &QGamepad::buttonDownChanged, this, [this](bool value){if(value) {ui->s_joystickThrottle->setValue(ui->s_joystickThrottle->value() - 10); on_s_joystickThrottle_sliderMoved(ui->s_joystickThrottle->value());}});
        setupConnections = true;
    }
}

void MainWindow::slotReboot() {
    qApp->exit(SystemConstants::Exit_Code_Reboot);
}
