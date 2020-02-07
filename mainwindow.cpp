#include <string>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "logger.h"
#include "confighandler.h"
#include "statushandler.h"

Logger *logger;
SettingsDialog *settingsDialog;
StatusHandler *statusHandler;

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

    connect(ui->b_keyboardUp, SIGNAL (pressed()), this, SLOT (slotReboot()));
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

            case Qt::Key_F1: ui->b_keyboardAction_1->setDown(true), on_b_keyboardAction_1_pressed(); break;
            case Qt::Key_F2: ui->b_keyboardAction_2->setDown(true), on_b_keyboardAction_2_pressed(); break;
            case Qt::Key_F3: ui->b_keyboardAction_3->setDown(true), on_b_keyboardAction_3_pressed(); break;
            case Qt::Key_F4: ui->b_keyboardAction_4->setDown(true), on_b_keyboardAction_4_pressed(); break;
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
void MainWindow::on_b_keyboardUp_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Up pressed"); }
void MainWindow::on_b_keyboardLeft_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Left pressed"); }
void MainWindow::on_b_keyboardDown_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Down pressed"); }
void MainWindow::on_b_keyboardRight_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Right pressed"); }
//----------------
void MainWindow::on_b_keyboardUp_released() { logger->write(Logger::Level::DEBUG, "Keyboard Up released"); }
void MainWindow::on_b_keyboardLeft_released() { logger->write(Logger::Level::DEBUG, "Keyboard Left released"); }
void MainWindow::on_b_keyboardDown_released() { logger->write(Logger::Level::DEBUG, "Keyboard Down released"); }
void MainWindow::on_b_keyboardRight_released() { logger->write(Logger::Level::DEBUG, "Keyboard Right released"); }

//Keyboard Action Keys
void MainWindow::on_b_keyboardAction_1_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 1 pressed"), statusHandler->setSocketStatus(StatusHandler::StatusIndicator::DISCONNECTED); }
void MainWindow::on_b_keyboardAction_2_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 2 pressed"), statusHandler->setSocketStatus(StatusHandler::StatusIndicator::CONNECTED); }
void MainWindow::on_b_keyboardAction_3_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 3 pressed"), statusHandler->setCameraStatus(StatusHandler::StatusIndicator::DISCONNECTED); }
void MainWindow::on_b_keyboardAction_4_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 4 pressed"), statusHandler->setCameraStatus(StatusHandler::StatusIndicator::CONNECTED); }

//Keyboard speed throttle
void MainWindow::on_s_keyboardThrottle_sliderMoved(int position) { ui->l_keyboardThrottle->setText(QStringLiteral("Throttle: %1%").arg(position)); }


//Controller Movement Sliders
void MainWindow::on_s_leftJoystickX_Throttle_sliderMoved(int position) { ui->l_leftJoystickX->setText(QStringLiteral("X-Axis: %1%").arg(position)); }
void MainWindow::on_s_leftJoystickY_Throttle_sliderMoved(int position) { ui->l_leftJoystickY->setText(QStringLiteral("Y-Axis: %1%").arg(position)); }
void MainWindow::on_s_leftTrigger_Throttle_sliderMoved(int position) { ui->l_leftTrigger->setText(QStringLiteral("Trigger: %1%").arg(position)); }
//---------------
void MainWindow::on_s_rightJoystickX_Throttle_sliderMoved(int position) { ui->l_rightJoystickX->setText(QStringLiteral("X-Axis: %1%").arg(position)); }
void MainWindow::on_s_rightJoystickY_Throttle_sliderMoved(int position) { ui->l_rightJoystickY->setText(QStringLiteral("Y-Axis: %1%").arg(position)); }
void MainWindow::on_s_rightTrigger_Throttle_sliderMoved(int position) { ui->l_rightTrigger->setText(QStringLiteral("Trigger: %1%").arg(position)); }

//Joystick Action Keys
void MainWindow::on_b_joystickAction_1_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 1 pressed"); }
void MainWindow::on_b_joystickAction_2_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 2 pressed"); }
void MainWindow::on_b_joystickAction_3_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 3 pressed"); }
void MainWindow::on_b_joystickAction_4_pressed() { logger->write(Logger::Level::DEBUG, "Keyboard Action 4 pressed"); }

//Joystick speed throttle
void MainWindow::on_s_joystickThrottle_sliderMoved(int position) { ui->l_joystickThrottle->setText(QStringLiteral("Throttle: %1%").arg(position)); }
