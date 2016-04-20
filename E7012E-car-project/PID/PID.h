#ifndef PID_CAR_CONTROLLER
#define PID_CAR_CONTROLLER

void PID_startup();
void PID_run();
float calculateAnglePID(int reference, int position);
float calculateSpeedPID(float angle, int position);
int getPosition();



#endif

