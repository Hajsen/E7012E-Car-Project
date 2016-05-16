#include "avr/io.h"
#include "MCU_Controller.h"
#include "general.h"
#include "..\resourceManager.h"

// PIN 5B 
//m/s (FIX AFTER LAB 4) 
// 3 modes, -1 0 and 1. 
// 321 is .1 ms

int bogus_line = 0;


//-----------TESTING-------------------------
void toggleMCUled(){
	DDRE |= (1 << DDE4);
	PORTE ^= (1 << PORTE4);
}
//----------------------------------
void throttleControl(float speed){
	if(speed>MAX_SPEED)
	{
		speed=MAX_SPEED;
	}
	if(speed<MIN_SPEED)
	{
		speed=MIN_SPEED;
	}
	if(speed<=MAX_SPEED && MIN_SPEED<=speed){
		SET_THROTTLING_PWM_REG = 3000 - (1400*speed);
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

	// Read pin 6/7 on Port C
	int sensor_forward = ((PINC)>>PINC6) & 0b11;
	
	float new_forward_line = ((1 & (sensor_forward)) -(1 & (sensor_forward>>1)));
	if(bogus_line==1 && new_forward_line==0)
	{
		if(sensor_forward==0)
		{
			bogus_line = 0;
		}
		else
		{
			bogus_line = 2;
		}
	}
	if(bogus_line==2 && ((sensorStatus.forward_line_value>=2.0f && new_forward_line<0)||(sensorStatus.forward_line_value<=-2.0f && new_forward_line>0)))
	{
		bogus_line = 1;
	}
	if(sensor_forward!=0 && !bogus_line)
	{
		//If forward sensor is on, calculate positive negative or zero value
		if((sensorStatus.forward_line_value>=2.0f && new_forward_line<0)||(sensorStatus.forward_line_value<=-2.0f && new_forward_line>0))
		{
			bogus_line = 1;
		}
		else
		{	
			sensorStatus.forward_line_value = new_forward_line;
		}
	}
	else
	{
		//If no forward sensor is on, make sure the value has the same sign as the last value.
		if(sensorStatus.forward_line_value<0)
		{
			sensorStatus.forward_line_value = -2.0f;
		}
		if(sensorStatus.forward_line_value>0)
		{
			sensorStatus.forward_line_value = 2.0f;
		}
		//If it was zero, it will stay at zero.
	}

	//sensorStatus.2 = ();
	int sensors_on = 0;

	// Read first 5 pins on port A and C
	int sensor_left  = 	(PINA) & 0b11111;	
	int sensor_right = 	(PINC) & 0b11111;
	int i = 0;
	float total_value = 0;
	for(i = 1; sensor_right>0; ++i)
	{		
		if(sensor_right&1)
		{
			++sensors_on;
		}
		total_value += (sensor_right&1)*(5-i);
		sensor_right>>=1;
	}
	for(i = 1; sensor_left>0; ++i)
	{
		if(sensor_left&1)
		{
			++sensors_on;
		}
		total_value -=(sensor_left&1)*(5-i);
		sensor_left>>=1;
	}
	float average_value = total_value/sensors_on;
	
	//Use old value if sensor data is poor
	if(sensors_on>1 && abs(average_value-sensorStatus.line_value)<3.0f)
	{
		sensorStatus.line_value = average_value;
	}
	
	DEBUG_SET((int)(4.0f+sensorStatus.line_value));
}

void updateCarStatus(){
	steeringControl(newAngle);
	throttleControl(newSpeed);

}
