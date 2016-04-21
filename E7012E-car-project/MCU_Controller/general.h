#ifndef _GENERAL_H_ 
#define _GENERAL_H_

#define MAX_ANGLE  45.0f
#define MIN_ANGLE  -45.0f
#define MAX_SPEED 10.0f
#define MIN_SPEED  0.0f

#define CLOCK_FREQUENCY 16000000
#define PRESCALER 8
#define ONE_MS (CLOCK_FREQUENCY/PRESCALER)/1000

//peripheral defines
#define SET_STEERING_PWM_REG OCR1B
#define SET_THROTTLING_PWM_REG OCR1A

#endif