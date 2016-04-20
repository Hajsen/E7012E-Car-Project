#include "avr/io.h"
#include "MCU_Controller.h"

// PIN 5B 
//m/s (FIX AFTER LAB 4) 
// 3 modes, -1 0 and 1. 
// 321 is .1 ms
void throttleControl(float speed){
	if(speed<1.0f && -1.0f<speed){
		SET_THROTTLING_PWM_REG = 3000 + (1400*speed);
	}
}	

//PIN 6B
void steeringControl(float angle){
	//FOR DEMONSTRATION OF LAB
	if(angle>45.0f)
	{
		return steeringControl(45.0f);
	}
	else if(angle<-45.0f)
	{
		return steeringControl(-45.0f);
	}
	else if(angle<=45.0f && -45.0f<=angle){
		SET_STEERING_PWM_REG = 3000 + (1000*angle)/45.0f;
	}

	/**
	if(!(angle>90 & -90<angle)){
		//HOW LONG ITS HIGH, straight servo 1ms
		OCR1B = 375;
	}
	**/
}
