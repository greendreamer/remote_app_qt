#include "mainwindow.h"
#include "constants.h"

#include <QApplication>
#include <QSettings>
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[])
{
    int currentExitCode = 0;
    do {
        QApplication a(argc, argv);
//        qDebug() << QStyleFactory::keys();
//        a.setStyle(QStyleFactory::create("Fusion"));
        MainWindow w;
        w.showMaximized();
        currentExitCode = a.exec();
    } while(currentExitCode == SystemConstants::Exit_Code_Reboot);

    return currentExitCode;

}
