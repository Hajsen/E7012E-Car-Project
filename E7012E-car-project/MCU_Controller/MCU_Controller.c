#include "avr/io.h"
#include "MCU_Controller.h"

// PIN 5B 
//m/s (FIX AFTER LAB 4) 
// 3 modes, -1 0 and 1. 
// 321 is .1 ms
void throttleControl(int speed){
	if(speed<1 && -1<speed){
		SET_THROTTLING_PWM_REG = 375 + (175*speed);
	}
}	

//PIN 6B
void steeringControl(int angle){
	//FOR DEMONSTRATION OF LAB
	
	if(angle<90 && -90<angle){
		SET_STEERING_PWM_REG = 375 + (125*angle)/90;
	}

	/**
	if(!(angle>90 & -90<angle)){
		//HOW LONG ITS HIGH, straight servo 1ms
		OCR1B = 375;
	}
	**/
}
