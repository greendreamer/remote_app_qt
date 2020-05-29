#include <QMessageBox>
#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "confighandler.h"
#include "constants.h"

ConfigHandler *config;

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    config = new ConfigHandler(this);
    //get data from config and but into appropriate boxes
    QString configData = config->getData();
    QStringList splitConfigData = configData.split("\n");
    //TODO find a better way to handle this
    for (int i=0; i < splitConfigData.size(); i++) {
        switch(i)
        {
            case 0: ui->socketIP_Box->setText(splitConfigData.at(i)); break;
            case 1: ui->socketPort_Box->setText(splitConfigData.at(i)); break;
            case 2:
                if(splitConfigData.at(i) == "true") {
                    ui->socketEn_check->setChecked(true);
                } else {
                    ui->socketEn_check->setChecked(false);
                } break;
            case 3:
                if(splitConfigData.at(i) == "true") {
                    ui->socketDetailed_check->setChecked(true);
                } else {
                    ui->socketDetailed_check->setChecked(false);
                } break;
            case 4: ui->cameraIP_Box->setText(splitConfigData.at(i)); break;
            case 5: ui->cameraPort_Box->setText(splitConfigData.at(i)); break;
            case 6:
                 if(splitConfigData.at(i) == "true") {
                     ui->cameraEn_check->setChecked(true);
                } else {
                     ui->cameraEn_check->setChecked(false);
                } break;
        }
    }

    //Set global variables to current text values from loaded config
    setSocket_IP(ui->socketIP_Box->text());
    setSocket_Port(ui->socketPort_Box->text());
    if(ui->socketEn_check->isChecked()) {
        setSocket_En("true");
    } else {
        setSocket_En("false");
    }

    setCamera_IP(ui->cameraIP_Box->text());
    setCamera_Port(ui->cameraPort_Box->text());
    if(ui->cameraEn_check->isChecked()) {
        setCamera_En("true");
    } else {
        setCamera_En("false");
    }

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

//Getters
QString SettingsDialog::getSocket_IP() const { return Socket_IP; }
QString SettingsDialog::getSocket_Port() const { return Socket_Port; }
QString SettingsDialog::getSocket_En() const { return Socket_En; }
QString SettingsDialog::getSocket_Detailed() const { return Socket_Detailed; }

QString SettingsDialog::getCamera_IP() const { return Camera_IP; }
QString SettingsDialog::getCamera_Port() const { return Camera_Port; }
QString SettingsDialog::getCamera_En() const { return Camera_En; }
//Setters
void SettingsDialog::setSocket_IP(const QString &value) { Socket_IP = value; }
void SettingsDialog::setSocket_Port(const QString &value) { Socket_Port = value; }
void SettingsDialog::setSocket_En(const QString &value) { Socket_En = value; }
void SettingsDialog::setSocket_Detailed(const QString &value) { Socket_Detailed = value; }

void SettingsDialog::setCamera_IP(const QString &value) { Camera_IP = value; }
void SettingsDialog::setCamera_Port(const QString &value) { Camera_Port = value; }
void SettingsDialog::setCamera_En(const QString &value) { Camera_En = value; }

//Event Triggers
void SettingsDialog::on_b_cancel_pressed() {
    close();
}
void SettingsDialog::on_b_apply_pressed() { config->setData(this->getAllTyped()), close(), slotReboot(); }

//TODO Limit what users can put into text
void SettingsDialog::on_socketIP_Box_editingFinished() {
    setSocket_IP(ui->socketIP_Box->text());
}
void SettingsDialog::on_socketPort_Box_editingFinished() {
    setSocket_Port(ui->socketPort_Box->text());
}
void SettingsDialog::on_cameraIP_Box_editingFinished() {
    setCamera_IP(ui->cameraIP_Box->text());
}
void SettingsDialog::on_cameraPort_Box_editingFinished() {
    setCamera_Port(ui->cameraPort_Box->text());
}

void SettingsDialog::on_socketEn_check_stateChanged(int arg1)
{
    if (arg1 == 2) {
        setSocket_En("true");
    } else {
        setSocket_En("false");
    }
}

void SettingsDialog::on_socketDetailed_check_stateChanged(int arg1)
{
    if (arg1 == 2) {
        setSocket_Detailed("true");
    } else {
        setSocket_Detailed("false");
    }
}

void SettingsDialog::on_cameraEn_check_stateChanged(int arg1)
{
    if (arg1 == 2) {
        setCamera_En("true");
    } else {
        setCamera_En("false");
    }
}

void SettingsDialog::slotReboot()
{
    qApp->exit(SystemConstants::Exit_Code_Reboot);
}

QString SettingsDialog::getAllTyped() const {
    const QString delim = "\n";
    //SIP, SP, SEN, SDE, CIP, CP, CEN
    return (getSocket_IP() + delim + getSocket_Port() + delim + getSocket_En() + delim + getSocket_Detailed() + delim+ getCamera_IP() + delim + getCamera_Port() + delim + getCamera_En());
}
