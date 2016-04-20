#ifndef _CONTROL_H_ 
#define _CONTROL_H_

//Defining Hardware init functions
void HW_startup();

//peripheral defines
#define SET_STEERING_PWM_REG OCR1B
#define SET_THROTTLING_PWM_REG OCR1A

//some masks
#define SET_TOP_TCNT1 ICR1
#define SET_COMPARE_MATCH_MODE_TIMER1A TCCR1A
#define SET_COMPARE_MATCH_MODE_TIMER1B TCCR1B

#endif
