#include "avr/io.h"
#include "HW_startup.h"
#include "general.h"

#include "avr/interrupt.h"

void initGpioOutputs(){
	//USED for TESTING AND ERROR FIXING

	//init ports D "outputs" Powersupply for sensors
	PORTD = 0b00000000; //Reset all the pins to the "OFF" position
	
	DDRD |= 1 << DDD0; //Setting pins to the output configurations
	DDRD |= 1 << DDD1;
	DDRD |= 1 << DDD2;
	DDRD |= 1 << DDD3;
	DDRD |= 1 << DDD4;
	DDRD |= 1 << DDD5;
	DDRD |= 1 << DDD6;
	DDRD |= 1 << DDD7;

}

void initGpioInputs(){
	PORTC = 0b00000000; //Reset all the pins to "OFF" position
	PORTA = 0b00000000;	

	DDRC &= ~(1 << DDC0); //Setting pins for the "INPUT" configuration
	DDRC &= ~(1 << DDC1);
	DDRC &= ~(1 << DDC2);
	DDRC &= ~(1 << DDC3);
	DDRC &= ~(1 << DDC4);
	
	DDRC &= ~(1 << DDC6);
	DDRC &= ~(1 << DDC7);

	DDRA &= ~(1 << DDA0);
	DDRA &= ~(1 << DDA1);
	DDRA &= ~(1 << DDA2);
	DDRA &= ~(1 << DDA3);
	DDRA &= ~(1 << DDA4);
}


void InitializeSteeringAndThrottlePWM(){
	PORTB = 0x00;
	DDRB = 0x00;

	DDRB |= 1<<DDB6;
	DDRB |= 1<<DDB5;

	SET_COMPARE_MATCH_MODE_TIMER1A |= ((1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (0<<COM1B0) | (1<<WGM11) | (0<<WGM10));
	SET_COMPARE_MATCH_MODE_TIMER1B |= ((1<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10));

	TCNT1 = 0;
	
	SET_STEERING_PWM_REG = ONE_MS*1.5;
	SET_THROTTLING_PWM_REG = ONE_MS*1.5;
	SET_TOP_TCNT1 = ONE_MS*20;
}

void initializeTimerInterrupt(){

	
	SET_COMPARE_MATCH_MODE_TIMER1A |= ((1<<COM1C1)|(0<<COM1C0));

	//Setting time when the interrupt shall occur 5ms after the counter has restarted.
	SET_TIMER_INTERRUPT_REG = ONE_MS*19;

	//Enabling Timer 1 C compare interrupt
	TIMER1_INTERRUPT_REG |= (1 << OCIE1C);
	
	//Setting global interrupt bit so interrupts work
	sei();
}


void initializeTimerMeasurment(){
	//Initalize Timer 3 for measuring speed of car
	

	
	DDRE &= ~(1 << DDE7);

	//Enable input interrupt and overflow on timer 3
	TIMSK3 |= (1 << ICIE3);

	TIMSK3 |= (1 << TOIE3);
	//Setting clock prescaler to 8
	TCCR3B |= ((0 << CS32) | (1 << CS31) | (0 << CS30));	
	//Setting so input event triggers when it get a falling edge, also enabled Input Noise canceler
	TCCR3B |= (1 << ICNC3);
	TCCR3B |= (1 << ICES3);
	

	TCNT3 = 0;
	sei();
}


void HW_startup(){
	initGpioOutputs();
	initGpioInputs();
	
	InitializeSteeringAndThrottlePWM();
	initializeTimerInterrupt();	
	initializeTimerMeasurment();
}
