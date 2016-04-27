#ifndef _PID_CAR_CONTROLLER
#define _PID_CAR_CONTROLLER
#include "general.h"
void PID_startup();
void PID_run(float reference);
float calculateAnglePID(float reference, float position);
float calculateSpeedPID(float velocity, float reference);
int getPosition();



#endif

