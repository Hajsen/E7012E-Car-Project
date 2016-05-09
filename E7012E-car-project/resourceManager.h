// Keeps global static variables if needed
// Defines resources that is gloabaly needed
// Implements interface?? mabye

#ifndef _SENSOR_MESSAGE
#define _SENSOR_MESSAGE
#include "avr/io.h"

#define DEBUG_SET(x) PORTD = 1<<(((15-(2*x))%8)-(x>3?1:0))
#define DEBUG_ON(x) PORTD |= 1<<(((15-(2*x))%8)-(x>3?1:0))
#define DEBUG_OFF(x) PORTD &= !(1<<(((15-(2*x))%8)-(x>3?1:0)))
#define DEBUG(x) PORTD ^= 1<<(((15-(2*x))%8)-(x>3?1:0))
/*#ifdef _DEBUG_x_USED\
#error debug(x) used twice\
#else\
#define _DEBUG_x_USED\
PORTD ^= 1<<x;\
#endif*/


#define abs(x) ((x)<0 ? -(x) : (x))

#define MAX_INT 65535
#define RADIUS 23
#define DISTANCE (2*M_PI*RADIUS)/6


#define MAX_ANGLE 45.0f
#define MIN_ANGLE -45.0f
#define MAX_SPEED 1.0f
#define MIN_SPEED -1.0f

typedef struct// SensorStatus
{ 
	int line_value;
	int forward_line_value;
} SensorStatus;

extern SensorStatus sensorStatus;

extern float velocity;
extern float newSpeed;
extern float newAngle;

void resourceManager_startup();

#endif
