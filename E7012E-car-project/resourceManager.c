#include "resourceManager.h"

float newAngle;
float newSpeed;
float velocity;

SensorStatus sensorStatus;

void resourceManager_startup()
{
	newAngle = 0;
	newSpeed = 0;
	velocity = 0;

	sensorStatus.line_value=0;
	sensorStatus.forward_line_value=0;

}
