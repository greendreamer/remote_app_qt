#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>
namespace StatusConstants {
    const static QString disconnectedHTML = "<font color=\"red\">";
    const static QString connectingHTML = "<font color=\"orange\">";
    const static QString connectedHTML = "<font color=\"green\">";
    const static QString endHTML = "</font>";
}

namespace SystemConstants {
    const static int Exit_Code_Reboot = -128572932;
}
#endif // CONSTANTS_H
