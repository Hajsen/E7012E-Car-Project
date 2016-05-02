#include "resourceManager.h"

float newAngle;
float newSpeed;
float velocity;

SensorStatus current_sensorStatus;
SensorStatus previous_sensorStatus;

void resourceManager_startup()
{
	newAngle = 0;
	newSpeed = 0;
	velocity = 0;

	current_sensorStatus.sensor_left1 = 0;
	current_sensorStatus.sensor_left2 = 0;
	current_sensorStatus.sensor_left3 = 0;
	current_sensorStatus.sensor_left4 = 0;
	current_sensorStatus.sensor_left5 = 0;

	current_sensorStatus.sensor_middle1 = 0;
	current_sensorStatus.sensor_middle2 = 0;
	
	current_sensorStatus.sensor_right1 = 0;
	current_sensorStatus.sensor_right2 = 0;
	current_sensorStatus.sensor_right3 = 0;
	current_sensorStatus.sensor_right4 = 0;
	current_sensorStatus.sensor_right5 = 0;

	previous_sensorStatus.sensor_left1 = 0;
	previous_sensorStatus.sensor_left2 = 0;
	previous_sensorStatus.sensor_left3 = 0;
	previous_sensorStatus.sensor_left4 = 0;
	previous_sensorStatus.sensor_left5 = 0;

	previous_sensorStatus.sensor_middle1 = 0;
	previous_sensorStatus.sensor_middle2 = 0;
	
	previous_sensorStatus.sensor_right1 = 0;
	previous_sensorStatus.sensor_right2 = 0;
	previous_sensorStatus.sensor_right3 = 0;
	previous_sensorStatus.sensor_right4 = 0;
	previous_sensorStatus.sensor_right5 = 0;


}
