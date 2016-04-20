#include "avr/io.h"
#include "HW_startup.h"

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

// PB6/OC1B timer1/counter1 AF: fast PWM
// WGM1 1:0 = 3, fastPWM on counter 1 (wgn = wavegenerator)
// OCR1B output compare, match will give an interrupt or generate waveform on output
void InitializeSteeringAndThrottlePWM(){
	
	//Reset port and old configuration off PORTB
	PORTB = 0x00;
	DDRB = 0x00;

	//set output compare on pin 6b(channel B) 
	DDRB |= 1<<DDB6;
	//5b (channel A)
	DDRB |= 1<<DDB5;

	// 16Mhz 
	//set high on compare match mode 14 (ICRn as TOP)
	SET_COMPARE_MATCH_MODE_TIMER1A = ((1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0)|(1<<WGM11)|(0<<WGM10));
	//fastPWM, prescaler 8 => 2 000 000 hz
	SET_COMPARE_MATCH_MODE_TIMER1B = ((1<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10));

	//reset timer
	TCNT1 = 0;
	//HOW LONG ITS HIGH ON CHANNEL B, straight servo 1.5ms (3000 = 1.5ms)
	SET_STEERING_PWM_REG = 3000;
	//HOW LONG ITS HIGH ON CHANNEL A, standing still throttle 1.5ms
	SET_THROTTLING_PWM_REG = 3000;
	//PERIOD (TOP), 20ms 
	SET_TOP_TCNT1 = 40000;
}

void HW_startup(){
	//initGpioOutputs();
	//initGpioInputs();
	
	InitializeSteeringAndThrottlePWM();
	//motorPWM();
	//wheelPWM();

}
