#include "avr/io.h"

void systemClock(){

}


void initGpioOutputs(){
	//init ports A "outputs" Powersupply for sensors
	PORTA = 0b00000000; //Reset all the pins to the "OFF" position
	
	DDRA ^= 1 << DDA0; //Setting pins to the correct configurations
	DDRA ^= 1 << DDA1;
	DDRA ^= 1 << DDA2;
	DDRA ^= 1 << DDA3;
	DDRA ^= 1 << DDA4;
	DDRA ^= 1 << DDA5;
	DDRA ^= 1 << DDA6;
	DDRA ^= 1 << DDA7;

	PORTA ^= 1 << PORTA0; //Set pin PA0 to ON
	PORTA ^= 1 << PORTA1; //Set pin PA1 to ON
	

	//init ports B "Inputs" Input values from sensors.
	PORTB = 0b00000000;
	DDRB = 0b00000000;

}

void initGpioInputs(){
	PORTC = 0b00000000; //Reset all the pins to "OFF" position
	
	DDRC ^= 0 << DDC0; //Setting pins for the "INPUT" configuration
	DDRC ^= 0 << DDC1;
	DDRC ^= 0 << DDC2;
	DDRC ^= 0 << DDC3;
	DDRC ^= 0 << DDC4;
	DDRC ^= 0 << DDC5;
	DDRC ^= 0 << DDC6;
	DDRC ^= 0 << DDC7;
	
}

//PB6 timer1/counter1 AF:OC1B (PWM)
void motorPWM(){

}

//PB4 timer2/counter2 AF:OC2A (PWM) 
void wheelPWM(){

}

void HW_startup(){
	initGpioOutputs();
	initGpioInputs();
}
