#ifndef _PID_CAR_CONTROLLER
#define _PID_CAR_CONTROLLER
#include "general.h"
void PID_startup();
void PID_run();
float calculateAnglePID(float reference, float position);
float calculateSpeedPID(float reference, float velocity);
int getPosition();



#endif

