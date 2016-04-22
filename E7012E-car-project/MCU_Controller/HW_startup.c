#include "avr/io.h"
#include "HW_startup.h"
#include "general.h"

#include "avr/interrupt.h"

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

	PORTA |= 1 << PORTA0; //Set pin PA0 to ON
	PORTA |= 1 << PORTA1; //Set pin PA1 to ON
	

}

void initGpioInputs(){
	PORTC = 0b00000000; //Reset all the pins to "OFF" position
	
	DDRC |= 0 << DDC0; //Setting pins for the "INPUT" configuration
	DDRC |= 0 << DDC1;
	DDRC |= 0 << DDC2;
	DDRC |= 0 << DDC3;
	DDRC |= 0 << DDC4;
	DDRC |= 0 << DDC5;
	DDRC |= 0 << DDC6;
	DDRC |= 0 << DDC7;
	
}

void initSettings(){
	//clk prescaler, 16
	//CLKPR = 4;
	//enable global interrupts
	//SREG = (1<<I);
}

void InitializeSteeringAndThrottlePWM(){
	PORTB = 0x00;
	DDRB = 0x00;

	DDRB |= 1<<DDB6;
	DDRB |= 1<<DDB5;

	SET_COMPARE_MATCH_MODE_TIMER1A |= ((1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0)|(1<<WGM11)|(0<<WGM10));
	SET_COMPARE_MATCH_MODE_TIMER1B |= ((1<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10));

	TCNT1 = 0;
	SET_STEERING_PWM_REG = ONE_MS*1.5;
	SET_THROTTLING_PWM_REG = ONE_MS*1.5;
	SET_TOP_TCNT1 = ONE_MS*20;
}

void initializeTimerInterrupt(){

	
	SET_COMPARE_MATCH_MODE_TIMER1A |= ((1<<COM1C1)|(0<<COM1C0));

	//Setting time when the interrupt shall occur
	SET_TIMER_INTERRUPT_REG = ONE_MS*1.5;

	//Enabling Timer 1 C compare interrupt
	TIMER1_INTERRUPT_REG |= (1 << OCIE1C);
	
	//Setting global interrupt bit so interrupts work
	sei();

}


void initializeTimerMeasurment(){
	//Initalize Timer 3 for measuring speed of car
	TCNT3 = 0;

	//Enable input interrupt on timer 3
	TIMSK3 |= (1 << ICIE3);
	//Setting clock prescaler to 8
	TCCR3B |= ((0 << CS32) | (1 << CS31) | (0 << CS30));	
	//Setting so input event triggers when it get a high edge, also enabled Input Noise canceler
	TCCR3B |= ((1 << ICNC3)|(1 << ICES3));

	

}


void HW_startup(){
	initGpioOutputs();
	initGpioInputs();
	
	InitializeSteeringAndThrottlePWM();
	initializeTimerInterrupt();	
	initializeTimerMeasurment();
}
