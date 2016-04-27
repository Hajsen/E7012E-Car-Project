#ifndef _CONTROL_H_ 
#define _CONTROL_H_

//Defining Hardware init functions
void HW_startup();

//some masks
#define SET_TOP_TCNT1 ICR1
#define SET_COMPARE_MATCH_MODE_TIMER1A TCCR1A
#define SET_COMPARE_MATCH_MODE_TIMER1B TCCR1B
#define TIMER1_INTERRUPT_REG TIMSK1


#endif
