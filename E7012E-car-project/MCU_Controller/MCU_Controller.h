void throttleControl(float speed);
void steeringControl(float angle);

//peripheral defines
#define SET_STEERING_PWM_REG OCR1B
#define SET_THROTTLING_PWM_REG OCR1A
