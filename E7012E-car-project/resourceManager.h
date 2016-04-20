// Keeps global static variables if needed
// Defines resources that is gloabaly needed
// Implements interface?? mabye

#ifndef SENSOR_MESSAGE
#define SENSOR_MESSAGE

#define MAX_ANGLE  45
#define MIN_ANGLE  -45
#define MAX_SPEED 10
#define MIN_SPEED  0

typedef struct// SensorStatus
{ 
    int outer_left : 1;
	int outer_right : 1;
	
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
} SensorStatus;

SensorStatus current_status;
SensorStatus last_status;

void resourceManager_startup();

#endif
