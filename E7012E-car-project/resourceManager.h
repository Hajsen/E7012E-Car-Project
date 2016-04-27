// Keeps global static variables if needed
// Defines resources that is gloabaly needed
// Implements interface?? mabye

#ifndef _SENSOR_MESSAGE
#define _SENSOR_MESSAGE

#define REFERENCE_SPEED 2.0f
#define MAX_INT 0xFFFF
#define RADIUS 23
#define DISTANCE (2*M_PI*RADIUS)/6

typedef struct// SensorStatus
{ 
    int outer_left : 1;
	
	int sensor_left1 : 1;
	int sensor_left2 : 1;
	int sensor_left3 : 1;
	int sensor_left4 : 1;
	int sensor_left5 : 1;
	int sensor_left6 : 1;

	int sensor_middle1 : 1;
	int sensor_middle2 : 1;
	int sensor_middle3 : 1;
	int sensor_middle4 : 1;
	int sensor_middle5 : 1;
	int sensor_middle6 : 1;

	int sensor_right1 : 1;
	int sensor_right2 : 1;
	int sensor_right3 : 1;
	int sensor_right4 : 1;
	int sensor_right5 : 1;
	int sensor_right6 : 1;

	int outer_right : 1;

} SensorStatus;

extern SensorStatus current_sensorStatus;
extern SensorStatus previous_sensorStatus;

extern float velocity;
extern float newSpeed;
extern float newAngle;

void resourceManager_startup();

#endif
