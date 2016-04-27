#ifndef _MCU_CONTROL_H_ 
#define _MCU_CONTROL_H_

void toggleMCUled();

void throttleControl(float speed);
void steeringControl(float angle);

void readSteeringSensors();

void updateCarStatus(void);

#endif
