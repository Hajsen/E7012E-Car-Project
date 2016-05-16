#include "resourceManager.h"

float newAngle= 0.0f;
float newSpeed =0.0f;
float velocity =0.0f;

SensorStatus sensorStatus;

void resourceManager_startup()
{
	newAngle = 0.0f;
	newSpeed = 0.0f;
	velocity = 0.0f;

	sensorStatus.line_value=0;
	sensorStatus.forward_line_value=0;

}
