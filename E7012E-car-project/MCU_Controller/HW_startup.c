#include "avr/io.h"

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
	

}

void initGpioInputs(){
	PORTC = 0b00000000; //Reset all the pins to "OFF" position
	
	DDRC = 0 << DDC0; //Setting pins for the "INPUT" configuration
	DDRC = 0 << DDC1;
	DDRC = 0 << DDC2;
	DDRC = 0 << DDC3;
	DDRC = 0 << DDC4;
	DDRC = 0 << DDC5;
	DDRC = 0 << DDC6;
	DDRC = 0 << DDC7;
	
}

void initSettings(){
	//clk prescaler, 16
	//CLKPR = 4;
	//enable global interrupts
	//SREG = (1<<I);
}

// PB6/OC1B timer1/counter1 AF: (PWM)
// WGM1 1:0 = 3, fastPWM on counter 1 (wgn = wavegenerator)
// OCR1B output compare, match will give an interrupt or generate waveform on output
void InitializeSteeringPWM(){
	
	//Reset port and old configuration off PORTB
	PORTB = 0x00;
	DDRB = 0x00;

	DDRB |= 1<<DDB6;
	// 16Mhz 

	//set high on compare match
	TCCR1A = ((1<<COM1B1)|(1<<COM1B0)|(1<<WGM11)|(0<<WGM10));
	//fastPWM, prescaler 1024
	TCCR1B = ((1<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10));
	//output compare after 255ms
	ICR1 = 1562;
	OCR1B = 781;
	//reset timer
	TCNT1 = 0;
}

// PB4/OC2A timer2/counter2 AF: (PWM) 
// wgm3 1:0 = 3, fastPWM counter3
void InitializeThrottlePWM(){
	
	//output compare mode
	//DDRB |= 1<<DDB2;
	// 16Mhz 
	//fastPWM, prescaler 1024
	//TCCR2B = ((1<<WGM23) | (1<<WGM22) | (1<<CS22) | (0<<CS21) | (1<<CS20));
	//output compare after 5.5 seconds
	//OCR2B = 255;
	//reset timer
//	TCNT2 = 0;
}




void HW_startup(){
	//initGpioOutputs();
	//initGpioInputs();
	
	initSettings();
	motorPWM();
	//wheelPWM();

}




