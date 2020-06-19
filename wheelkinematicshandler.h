#ifndef WHEELKINEMATICSHANDLER_H
#define WHEELKINEMATICSHANDLER_H

#include <QObject>

class WheelKinematicsHandler
{
public:
    WheelKinematicsHandler();
    float calculateWheelDirection(float y,float x);
    float calculateWheelMagnitude(float y, float x);
    float calculateFLWheelSpeed(float direction, float magnitude);
    float calculateFRWheelSpeed(float direction, float magnitude);
    float calculateBLWheelSpeed(float direction, float magnitude);
    float calculateBRWheelSpeed(float direction, float magnitude);
    float *calculateAllWheelSpeeds(float y, float x, float z);
    float *calculateAllWheelSpeeds(float direction, float magnitude);

};

#endif // WHEELKINEMATICSHANDLER_H
