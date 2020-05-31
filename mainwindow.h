#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void on_increaseThrottle_pressed();
    void on_decreaseThrottle_pressed();
    void sendKeyboardData();
    void sendJoystickData();

private slots:
    void on_toolButton_clicked();

    void on_s_joystickThrottle_sliderMoved(int position);

    void on_s_leftJoystickX_Throttle_sliderMoved(int position);
    void on_s_leftJoystickX_Throttle_sliderMovedf(float position);
    void on_s_leftJoystickY_Throttle_sliderMoved(int position);
    void on_s_leftJoystickY_Throttle_sliderMovedf(float position);
    //void on_s_leftTrigger_Throttle_sliderMoved(int position);

    void on_s_rightJoystickX_Throttle_sliderMoved(int position);
    void on_s_rightJoystickX_Throttle_sliderMovedf(float position);
    //void on_s_rightJoystickY_Throttle_sliderMoved(int position);
    //void on_s_rightTrigger_Throttle_sliderMoved(int position);

    void on_s_keyboardThrottle_sliderMoved(int position);

    void on_b_keyboardAction_1_pressed();
    void on_b_keyboardAction_2_pressed();
    void on_b_keyboardAction_3_pressed();
    void on_b_keyboardAction_4_pressed();

    void on_b_joystickAction_1_pressed();
    void on_b_joystickAction_2_pressed();
    void on_b_joystickAction_3_pressed();
    void on_b_joystickAction_4_pressed();

    void on_b_keyboardUp_pressed();
    void on_b_keyboardLeft_pressed();
    void on_b_keyboardDown_pressed();
    void on_b_keyboardRight_pressed();
    void on_b_keyboardTurnLeft_pressed();
    void on_b_keyboardTurnRight_pressed();

    void on_b_keyboardUp_released();
    void on_b_keyboardLeft_released();
    void on_b_keyboardDown_released();
    void on_b_keyboardRight_released();
    void on_b_keyboardTurnLeft_released();
    void on_b_keyboardTurnRight_released();

    void on_b_refresh_pressed();

    void slotReboot();
    void updateAll();

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    float kup = 0.0;
    float kdown = 0.0;
    float kleft = 0.0;
    float kright = 0.0;
    float kturnLeft = 0.0;
    float kturnRight = 0.0;

    float jy = 0.0;
    float jx = 0.0;
    float jz = 0.0;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
