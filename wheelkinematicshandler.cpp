#include "wheelkinematicshandler.h"
#include <math.h>
#include <algorithm>
#include "constants.h"
#define PI 3.14159265

WheelKinematicsHandler::WheelKinematicsHandler()
{

}

float WheelKinematicsHandler::calculateWheelDirection(float y, float x)
{
    float firstCalc = atan2(y,x);
    if(!(firstCalc == 0) && firstCalc/abs(firstCalc) == -1.0) {
        firstCalc = firstCalc + (2 * PI);
    }
    return firstCalc;
}

float WheelKinematicsHandler::calculateWheelMagnitude(float y, float x)
{

    return (std::clamp(((float)sqrt(pow(y, 2) + pow(x, 2))), MovementConstants::MinSpeed, MovementConstants::MaxSpeed));
}

float WheelKinematicsHandler::calculateFLWheelSpeed(float direction, float magnitude)
{
    return (std::clamp((((float) sin(direction + (1.0/4.0 * PI))) * magnitude), MovementConstants::MinSpeed, MovementConstants::MaxSpeed));
}

float WheelKinematicsHandler::calculateFRWheelSpeed(float direction, float magnitude)
{
    return (std::clamp((((float) sin(direction - (1.0/4.0 * PI))) * magnitude), MovementConstants::MinSpeed, MovementConstants::MaxSpeed));
}

float WheelKinematicsHandler::calculateBLWheelSpeed(float direction, float magnitude)
{
    return (std::clamp((((float) sin(direction + (1.0/4.0 * PI))) * magnitude), MovementConstants::MinSpeed, MovementConstants::MaxSpeed));
}

float WheelKinematicsHandler::calculateBRWheelSpeed(float direction, float magnitude)
{
    return (std::clamp((((float) sin(direction - (1.0/4.0 * PI))) * magnitude), MovementConstants::MinSpeed, MovementConstants::MaxSpeed));
}

float *WheelKinematicsHandler::calculateAllWheelSpeeds(float y, float x, float z)
{
    float direction = calculateWheelDirection(y, x);
    float magnitude = calculateWheelMagnitude(y, x);
    return calculateAllWheelSpeeds(direction, magnitude);
}

float *WheelKinematicsHandler::calculateAllWheelSpeeds(float direction, float magnitude)
{
    static float allSpeeds[4] = {calculateFLWheelSpeed(direction, magnitude),
                                 calculateFRWheelSpeed(direction, magnitude),
                                 calculateBLWheelSpeed(direction, magnitude),
                                 calculateBRWheelSpeed(direction, magnitude)};
    return allSpeeds;
}
