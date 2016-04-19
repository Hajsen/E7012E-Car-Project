#include <avr/io.h> 

void main(void) { 
	init_settings();
	motorPWM();
	wheelPWM();
}

void init_settings(){
	//clk prescaler, 16
	CLKPR = 4;
	//enable global interrupts
	//SREG = (1<<I);
}

void gpio(){


}

// PB6/OC1B timer1/counter1 AF: (PWM)
// WGM1 1:0 = 3, fastPWM on counter 1 (wgn = wavegenerator)
// OCR1A output compare, match will give an interrupt or generate waveform on output
void motorPWM(){
	//output compare mode
	(DDRB |= 1<<6);
	// 16Mhz 
	//fastPWM, prescaler 1024
	TCCR1B = ((1<<WGM13) | (1<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10));
	//output compare after 5.5 seconds
	OCR1B = 1000 * 3;
}

// PB4/OC2A timer2/counter2 AF: (PWM) 
// wgm2 1:0 = 3, fastPWM counter2
void wheelPWM(){
	//output compare mode
	DDRB |= 1<<4;
	// 16Mhz 
	//fastPWM, prescaler 1024
	TCCR3B = ((1<<WGM33) | (1<<WGM32) | (1<<CS32) | (0<<CS31) | (1<<CS30));
	//output compare after 5.5 seconds
	OCR3B = 1000 * 2;
}

/**
//#include "iocan128.h"
#define TIME 100 
#define LED_TIME 40000 
#define LED_OK 10000
// Declare your global variables here

void Light(unsigned char a); 
void delay_us (unsigned int cntr);

int main(void) { 
	//  Input/Output Ports initialization 
	// Port A 
	DDRA=0x00; // PORTA=0x00;
	// Port B 
	DDRB=0x00; 
	PORTB=0x00;
	//Port C 
	PORTC = 0x01; 
	DDRC = 0x0f;
	while(1) {
	  PORTC=1;
	  for(int i=0;i<10;i++)
	  delay_us(LED_TIME);
	  PORTC=0;       
	  for(int i=0;i<10;i++)
	  delay_us(LED_TIME);        
	} 
}              
//function stop and set PC0(LED) 
void Light(unsigned char a) {
       unsigned char b;
	   for (b=0;b!=a;b++)     {
	          PORTC=1;
			  delay_us(LED_TIME);
			  PORTC=0;
			  delay_us(LED_TIME);             
		} 
}

//function Delay           
void delay_us (unsigned int cntr) { 
	while (--cntr != 0);
}
**/
