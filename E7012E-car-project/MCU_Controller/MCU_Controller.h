#ifndef _MCU_CONTROL_H_ 
#define _MCU_CONTROL_H_

void throttleControl(float speed);
void steeringControl(float angle);

void updateCarStatus(void);

#endif
