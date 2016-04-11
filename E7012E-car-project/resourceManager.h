// Keeps global static variables if needed
// Defines resources that is gloabaly needed
// Implements interface?? mabye

#ifndef SENSOR_MESSAGE
#define SENSOR_MESSAGE

struct sensor_sessage
{ 
    int outer_left;
	int outer_right;
	int sensor_left1;
	int sensor_left2;
	int sensor_left3;
	int sensor_left4;
	int sensor_left5;
	int sensor_left6;

	int sensor_middle1;
	int sensor_middle12;
	int sensor_middle13;
	int sensor_middle14;
	int sensor_middle15;
	int sensor_middle16;

	int sensor_right1;
	int sensor_right2;
	int sensor_right3;
	int sensor_right4;
	int sensor_right5;
	int sensor_right6;
}sensor_sessage;

#endif

void resourceManager_startup();
