#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>
namespace StatusConstants {
    const static QString disconnectedHTML = "<font color=\"red\">";
    const static QString connectingHTML = "<font color=\"orange\">";
    const static QString connectedHTML = "<font color=\"green\">";
    const static QString closingHTML = "<font color=\"maroon\">";
    const static QString boundHTML = "<font color=\"blue\">";
    const static QString lookupHTML = "<font color=\"cyan\">";
    const static QString endHTML = "</font>";
}
namespace SystemConstants {
    const static int Exit_Code_Reboot = -128572932;
}

namespace MovementConstants {
    const static float MaxSpeed = 1.0;
    const static float MinSpeed = -1.0;
}
#endif // CONSTANTS_H
