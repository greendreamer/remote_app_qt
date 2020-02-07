#include "mainwindow.h"
#include "constants.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    int currentExitCode = 0;
    do {
        QApplication a(argc, argv);
        MainWindow w;
        w.showMaximized();
        currentExitCode = a.exec();
    } while(currentExitCode == SystemConstants::Exit_Code_Reboot);

    return currentExitCode;

}
