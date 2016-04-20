#ifndef _MCU_CONTROL_H_ 
#define _MCU_CONTROL_H_

void throttleControl(int speed);
void steeringControl(int angle);

//peripheral defines
#define SET_STEERING_PWM_REG OCR1B
#define SET_THROTTLING_PWM_REG OCR1A


#endif
