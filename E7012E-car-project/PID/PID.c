#include "PID.h"

#include "math.h"

static float const Ki = 0.3;
static float const Kp = 0.3;
static float const Kd = 0.3;
static int   const EPSILON = 1;
static float const MAX = 10;
static float const MIN = 0;
static float const dt = 0.01;

// allocate resources 
float calculateOutput(int reference, int position)
{
	// declare variables
	static float pre_error;
	static float integral;
	float derivative;
	float error;
	float output;
	
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
	if(error > EPSILON)
	{
		integral = integral + error * dt;
	}
	derivative = ( error - pre_error ) / dt;
	output = Kp*error + Ki*integral + Kd * derivative;

	// Keep output within allowed range
	if(output > MAX)
	{
		output = MAX;
	}
	else if(output < MIN)
	{
		output = MIN;
	}

	pre_error = error;

	return output;
}

void PID_startup()
{
}

// run controller
void PID_run()
{
	while(1)
	{
		// wait for mutex to be unlocked after "dt" time
		calculateOutput(0, getPosition());
	}
}

int getPosition()
{
	// read data from 
	return 0;
}


