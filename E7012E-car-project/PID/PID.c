#include "PID.h"
#include "..\resourceManager.h"
#include "../MCU_Controller/general.h"
#include "../MCU_Controller/MCU_Controller.h"
#include "math.h"


#define REFERENCE_ANGLE_CORRECTION  2.0f
#define REFERENCE_SPEED_CORRECTION  0.5f
#define REFERENCE_SPEED_CORRECTION_FORWARD  2.0f
#define REFERENCE_VELOCITY 5.0f

static float const Ki_ANGLE = 0.3f;
static float const Kp_ANGLE = 5.0f;
static float const Kd_ANGLE = 0.0f;
static float const Ki_SPEED = 1.0f;
static float const Kp_SPEED = 0.3f;
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
		float angle_measurement = sensorStatus.line_value;
		float velocity_reference = REFERENCE_VELOCITY
			- REFERENCE_SPEED_CORRECTION_FORWARD*abs(sensorStatus.forward_line_value)
			- REFERENCE_SPEED_CORRECTION*abs(sensorStatus.line_value);
		newAngle = calculateAnglePID(angle_reference, angle_measurement);
		newSpeed = calculateSpeedPID(velocity_reference, velocity);		
}


/*
*
* PID for wheel angle
*
*/
float calculateAnglePID(float reference, float position)
{	
	/*int pos = abs(position);
	DEBUG_SET(pos);*/

	// declare variables
	static float pre_error=0;
	static float integral=0;
	float new_integral;
	float derivative;
	float error;
	float angle;
	
	// calculate error
	error = reference - position;
	

	derivative = ( error - pre_error ) / dt;
	angle = Kp_ANGLE*error + Ki_ANGLE*integral + Kd_ANGLE * derivative;


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
float calculateSpeedPID(float reference, float velocity)
{

	// declare variables
	static float pre_error=0;
	static float integral=0;
	float new_integral;
	float derivative;
	float error;
	float speed;
	// calculate error
	error = velocity-reference;
	error = error>0.0f?error:-error;





	new_integral = integral + error * dt;

	

	derivative = ( error - pre_error ) / dt;
	speed = Kp_SPEED*error + Ki_SPEED*new_integral + Kd_SPEED* derivative;

	if((speed < MAX_SPEED && integral<new_integral)
		|| (speed > MIN_SPEED && integral>new_integral))
	{
		integral = new_integral;
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

