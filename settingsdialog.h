#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    //Socket
    QString getSocket_IP() const;
    QString getSocket_Port() const;
    QString getSocket_En() const;

    void setSocket_IP(const QString &value);
    void setSocket_Port(const QString &value);
    void setSocket_En(const QString &value);

    //Camera
    QString getCamera_IP() const;
    QString getCamera_Port() const;
    QString getCamera_En() const;

    void setCamera_IP(const QString &value);
    void setCamera_Port(const QString &value);
    void setCamera_En(const QString &value);



private slots:
    void on_b_cancel_pressed();
    void on_b_apply_pressed();
    void on_socketIP_Box_editingFinished();
    void on_socketPort_Box_editingFinished();
    void on_cameraIP_Box_editingFinished();
    void on_cameraPort_Box_editingFinished();

    void on_socketEn_check_stateChanged(int arg1);

    void on_cameraEn_check_stateChanged(int arg1);

public slots:
    QString getAllTyped() const;
private:
    QString Socket_IP = "Socket IP Placeholder";
    QString Socket_Port = "Socket Port Placeholder";
    QString Socket_En = "false";

    QString Camera_IP = "Camera IP Placeholder";
    QString Camera_Port = "Camera Port Placeholder";
    QString Camera_En = "false";

    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
