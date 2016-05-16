#include "PID.h"
#include "..\resourceManager.h"
#include "../MCU_Controller/general.h"
#include "../MCU_Controller/MCU_Controller.h"
#include "math.h"


#define REFERENCE_ANGLE_CORRECTION  0.5f
#define REFERENCE_SPEED_CORRECTION 0.235f
#define REFERENCE_SPEED_CORRECTION_FORWARD  0.93f
#define REFERENCE_VELOCITY 5.0f
#define REFERENCE_FACTOR 0.29f
#define MIN_REFERENCE_SPEED 3.0f
#define MIN_DX 0.001


static float const Ki_ANGLE = 0.0f;
static float const Kp_ANGLE = 8.4f;
static float const Kd_ANGLE = 0.8f;
static float const Ki_SPEED = 0.1f;
static float const Kp_SPEED = 0.2f;
static float const Kd_SPEED = 0.0f;


static float const dt = 0.02;

// allocate resources 
void PID_startup()
{
}

// run controller
void PID_run()
{
		
		float angle_reference = -sensorStatus.forward_line_value*REFERENCE_ANGLE_CORRECTION;
		if((sensorStatus.forward_line_value<-1 && sensorStatus.line_value>1.5)||(sensorStatus.forward_line_value>1 && sensorStatus.line_value<-1.5))
		{
			angle_reference-=sensorStatus.forward_line_value*REFERENCE_ANGLE_CORRECTION*2.2;
		}
		float angle_measurement = sensorStatus.line_value;
		float velocity_reference = REFERENCE_FACTOR * ( REFERENCE_VELOCITY
			- REFERENCE_SPEED_CORRECTION_FORWARD*abs(sensorStatus.forward_line_value)
			- REFERENCE_SPEED_CORRECTION*abs(sensorStatus.line_value));

		velocity_reference  = max(velocity_reference, REFERENCE_FACTOR * MIN_REFERENCE_SPEED);
		
		newAngle = calculateAnglePID(angle_reference, angle_measurement, velocity);
		newSpeed = calculateSpeedPID(velocity_reference, velocity);		
}


/*
*
* PID for wheel angle
*
*/
float calculateAnglePID(float reference, float position, float vel)
{

	// declare variables
	static float pre_error=0;
	static float integral=0;
	static float avg_derivative = 0;
	float new_integral;
	float derivative = 0;
	float error;
	float angle;
	
	// calculate error
	error = reference - position;
	float dx = max(dt*vel,MIN_DX);
	avg_derivative *= 0.9;
	if(dx>0.00001f)//Prevent division by 0
	{
		derivative = ( error - pre_error ) / dx;
		avg_derivative += derivative * 0.02;
	}
	new_integral = integral + dx*error;
	angle = Kp_ANGLE*error + Ki_ANGLE*new_integral + Kd_ANGLE * avg_derivative;


	// Anti windup integral
	if((angle < MAX_ANGLE && integral<new_integral)
		|| (angle > MIN_ANGLE && integral>new_integral))
	{
		integral = new_integral;
	}

	// Keep output within allowed range
	if(angle > MAX_ANGLE)
	{
		angle = MAX_ANGLE;
	}
	else if(angle < MIN_ANGLE)
	{
		angle = MIN_ANGLE;
	}

	pre_error = error;

	return angle;
}


/*
*
* PID for motor speed
*
*/
float calculateSpeedPID(float reference, float vel)
{

	// declare variables
	static float pre_error=0;
	static float integral=0;
	float new_integral;
	float derivative=0;
	float error;
	float speed;
	// calculate error
	error = reference-vel;
	//error = error>0.0f?error:-error;



	float dx = max(dt*vel,MIN_DX);


	new_integral = integral + error * dt;

	
	if(dx>0.00001f)//Prevent division by 0
	{
		derivative = ( error - pre_error ) / dt;
	}
	speed = Kp_SPEED*error + Ki_SPEED*new_integral + Kd_SPEED* derivative;

	if((speed < MAX_SPEED && new_integral>integral)
		|| (speed > MIN_SPEED && new_integral<integral))
	{
		integral = new_integral;
	}
	else
	{
		DEBUG(0);
	}
	// Keep output within allowed range
	if(speed > MAX_SPEED)
	{
		speed = MAX_SPEED;
	}
	else if(speed < MIN_SPEED)
	{
		speed = MIN_SPEED;
	}

	pre_error = error;

	return speed;
}

