#include "PID.h"

#include "math.h"

static float const Ki_ANGLE = 0.3;
static float const Kp_ANGLE = 0.3;
static float const Kd_ANGLE = 0.3;
static float const Ki_SPEED = 0.3;
static float const Kp_SPEED = 0.3;
static float const Kd_SPEED = 0.3;
static int   const EPSILON_ANGLE = 1;
static int   const EPSILON_SPEED = 1;
static float const MAX_ANGLE = 90;
static float const MIN_ANGLE = -90;
static float const MAX_SPEED = 10;
static float const MIN_SPEED = 0;
static float const dt = 0.01;

// allocate resources 
void PID_startup()
{
}

// run controller
void PID_run()
{
	float angle;
	float speed;
	int position;

	while(1)
	{
		position = getPosition();
		// wait for mutex to be unlocked after "dt" time
		angle = calculateAnglePID(0, position);
		speed = calculateSpeedPID(angle, position);
		//setWheelAngle(angle);
		//setMotorSpeed(speed);
	}
}

// read data from SensorStatus
int getPosition()
{
	
	return 1;
}


/*
*
* PID for wheel angle
*
*/
float calculateAnglePID(int reference, int position)
{
	// declare variables
	static float pre_error;
	static float integral;
	float new_integral;
	float derivative;
	float error;
	float angle;
	
	// if not is number set to 0
	if(!isnan(pre_error))
	{
		pre_error = 0;
	}
	if(!isnan(integral))
	{
		integral = 0;
	}
	
	// calculate error
	error = reference - position;
	
	// only calculate integral if error is large enough
	if(error > EPSILON_ANGLE)
	{
		new_integral = integral + error * dt;
	}
	// Anti windup integral
	if(new_integral < MAX_ANGLE && new_integral > MIN_ANGLE)
	{
		integral = new_integral;
	}

	derivative = ( error - pre_error ) / dt;
	angle = Kp_ANGLE*error + Ki_ANGLE*integral + Kd_ANGLE * derivative;

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
float calculateSpeedPID(float angle, int position)
{
	// declare variables
	static float pre_error;
	static float integral;
	float new_integral;
	float derivative;
	float error;
	float speed;
	
	// if not is number set to 0
	if(!isnan(pre_error))
	{
		pre_error = 0;
	}
	if(!isnan(integral))
	{
		integral = 0;
	}
	
	// calculate error
	error = angle - position;
	
	// only calculate integral if error is large enough
	if(error > EPSILON_SPEED)
	{
		new_integral = integral + error * dt;
	}
	// Anti windup integral
	if(new_integral < MAX_SPEED&& new_integral > MIN_SPEED)
	{
		integral = new_integral;
	}

	derivative = ( error - pre_error ) / dt;
	speed = Kp_SPEED*error + Ki_SPEED*integral + Kd_SPEED* derivative;

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

