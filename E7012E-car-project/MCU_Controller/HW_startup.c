#include "avr/io.h"

void systemClock(){

}


void initGpio(){
	//init ports A "outputs" Powersupply for sensors
	PORTA = 0b00000000;
	DDRA = 0b11111111;

	//init ports B "Inputs" Input values from sensors.
	PORTB = 0b00000000;
	DDRB = 0b00000000;

}

//PB6 timer1/counter1 AF:OC1B (PWM)
void motorPWM(){

}

//PB4 timer2/counter2 AF:OC2A (PWM) 
void wheelPWM(){

}

void HW_startup(){
	initGpio();

}
