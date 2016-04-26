#include <math.h>

//INTERRUPT on pulse
//MUST NOT FORGET TO INIT TIME_PREVIOUS TO A DEFAULT VALUE
//interrupt from on input
void ISR(TIMER3_CAPT_vect){
	int delta_time = 0;
	TIME_RECENT = ICR3;

	//(mm)
	//distance between magnets

	//If overflow has happened
	if(OVERFLOW_COUNTER > 0){
		//reset timer overflow
		delta_time = TIME_RECENT + (OVERFLOW_COUNTER-1)*MAX_INT + TIME_BEFORE_OVERFLOW;
		OVERFLOW_COUNTER = 0;
	}
	else{
		delta_time = TIME_RECENT - TIME_PREVIOUS;
	}

	//ms
	int time = delta_time/1000;
	//cm/ms
	VELOCITY = distance/time;	

}

//interrupt on overflow
isr(TIMER3_OVF_vect){
	if(OVERFLOW_COUNTER == 0){
		TIME_BEFORE_OVERFLOW = MAX_INT - TIME_PREVIOUS;	
	}

	OVERFLOW_COUNTER++;
}

void carVelocity(){
	
}