// PIN 6B 
//m/s (FIX AFTER LAB 4) 
void throttleControl(int speed){
	//MUUUUUUUUUUUUUUUUUUUTEX HÄR
	//enable the pin as compare output for controller
	DDRB |= 1<<DDB6;

	//HOW LONG ITS HIGH, 1.5ms for standing still
	OCR1B = 375;
	//PERIOD, 5.5ms (250 = 1ms)
	ICR1 = 1375;

	//disable pinout after correcting throttle speed
	DDRB &= ^(1<<DDB6);
}	

//PIN 5B
void steeringControl(int angle){
	if(!(angle>60 & -60<angle)){
		//MUUUUUUUUUUUUUUUUUUUTEX HÄR
		//enable the pin as compare output for servo
		DDRB |= 1<<DDB5;
		//HOW LONG ITS HIGH, straight servo 1ms
		OCR1B = 250;
		//PERIOD, 5.5ms (250 = 1ms)
		ICR1 = 5000;

		//disable pinout after correcting throttle speed
		DDRB &= ^(1<<DDB5);
	}
}