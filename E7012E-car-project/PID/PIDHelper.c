#include <math.h>
#include "PIDHelper.h"
#include "resourcemanager.h"

int overflow_counter = 0;
int time_before_overflow = 0;
int time_previous = 0;
int time_recent = 0;
int delta_time = 0;
int velocity = 0;

void ISR(TIMER3_CAPT_vect){
	time_recent = ICR3;

	//If overflow has happened
	if(overflow_counter > 0){
		//reset timer overflow
		delta_time = time_recent + (overflow_counter-1)*MAX_INT + time_before_overflow;
		overflow_counter = 0;
	}
	else{
		delta_time = time_recent - time_previous;
	}

	//cm/ms
	velocity = (distance/delta_time)/1000;	
	ICR2 = velocity;

}

//interrupt on overflow
isr(TIMER3_OVF_vect){
	if(overflow_counter == 0){
		time_before_overflow = MAX_INT - time_previous;	
	}

	overflow_counter++;
}

void setCarVelocity(){
	
}