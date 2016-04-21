#include "avr/io.h"
#include "MCU_Controller.h"
#include "general.h"

// m/s (FIX AFTER LAB 4) 
void throttleControl(float speed){
	if(speed < MAX_SPEED && speed > MIN_SPEED){
		SET_THROTTLING_PWM_REG = 1.5*ONE_MS + (0.7*ONE_MS*speed);
	}
}	

void steeringControl(float angle){
	if(angle <= MAX_ANGLE && MIN_ANGLE <= angle){
		SET_STEERING_PWM_REG = 1.5*ONE_MS + (0.5*ONE_MS*angle)/MAX_ANGLE;
	}
	else if(angle > MAX_ANGLE){
		return steeringControl(MAX_ANGLE);
	}
	else if(angle<MIN_ANGLE){
		return steeringControl(MIN_ANGLE);
	}
}
