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
	
	//0b01000000
	//1<<PINC7
	if((PINC & PINC7)){
	}
	if((PINC & PINC6)){
		
	}

	
}

void updateCarStatus(){
	//steeringControl(newAngle);
	throttleControl(newSpeed);
}
