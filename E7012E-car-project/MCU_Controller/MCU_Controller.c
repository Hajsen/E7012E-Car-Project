// PIN 6B 
//m/s (FIX AFTER LAB 4) 
// 3 modes, -1 0 and 1. 
// 321 is .1 ms
void throttleControl(int speed){
	if(speed<1 && -1<speed){
		OCR1A = 375 + (175*speed);
	}
}	

//PIN 5B
void steeringControl(int angle){
	//FOR DEMONSTRATION OF LAB

	if(angle<90 && -90<angle){
		OCR1B = 375 + (125*angle/90);
	}

	/**
	if(!(angle>90 & -90<angle)){
		//HOW LONG ITS HIGH, straight servo 1ms
		OCR1B = 375;
	}
	**/
}