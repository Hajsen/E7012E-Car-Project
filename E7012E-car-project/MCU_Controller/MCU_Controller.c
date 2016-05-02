#include "avr/io.h"
#include "MCU_Controller.h"
#include "general.h"
#include "..\resourceManager.h"

// PIN 5B 
//m/s (FIX AFTER LAB 4) 
// 3 modes, -1 0 and 1. 
// 321 is .1 ms




//-----------TESTING-------------------------
void toggleMCUled(){
	DDRE |= (1 << DDE4);
	PORTE ^= (1 << PORTE4);
}
//----------------------------------
void throttleControl(float speed){
	if(speed<=1.0f && -1.0f<=speed){
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
}

void readSteeringSensors(){
	//PINC 0-4 == Höger
	//PINA 0-4 == Vänster
	//PINC 6-7 == Mitten
	previous_sensorStatus = current_sensorStatus;

	volatile int lol = (1 & (PINA >> PINA0));
	current_sensorStatus.sensor_left1 = (1 & (PINA >> PINA0));
	current_sensorStatus.sensor_left2 = (1 & (PINA >> PINA1));
	current_sensorStatus.sensor_left3 = (1 & (PINA >> PINA2));
	current_sensorStatus.sensor_left4 = (1 & (PINA >> PINA3));
	current_sensorStatus.sensor_left5 = (1 & (PINA >> PINA4));

	if(current_sensorStatus.sensor_left1 == 1){
		velocity = 1;
	}

	current_sensorStatus.sensor_middle1 = (1 & (PINC >> PINC6));
	current_sensorStatus.sensor_middle2 = (1 & (PINC >> PINC7));
	
	current_sensorStatus.sensor_right1 = (1 & (PINC >> PINC0));
	current_sensorStatus.sensor_right2 = (1 & (PINC >> PINC1));
	current_sensorStatus.sensor_right3 = (1 & (PINC >> PINC2));
	current_sensorStatus.sensor_right4 = (1 & (PINC >> PINC3));
	current_sensorStatus.sensor_right5 = (1 & (PINC >> PINC4));
	
}

void updateCarStatus(){
	//steeringControl(newAngle);
	throttleControl(newSpeed);
}
