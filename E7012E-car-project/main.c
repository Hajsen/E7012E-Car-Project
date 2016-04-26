#include "avr/io.h"
#include <avr/interrupt.h>
#include <math.h>


#include "PID\PID.h"
#include "MCU_Controller\MCU_Controller.h"
#include "MCU_Controller\HW_startup.h"
#include "..\resourcemanager.h"


int overflow_counter = 0;
int time_before_overflow = 0;
int time_previous = 0;
int time_current = 0;
int delta_time = 0;

void toggleMCUled(){
	DDRE |= (1 << DDE4);
	
	PORTE ^= (1 << PORTA4);
}

//Interrupt function (Here is where the interrupt does work)

ISR(TIMER1_COMPC_vect){
	updateCarStatus();
	//PORTA |= 1 << PORTA7; //Toggles led

}


ISR(TIMER3_CAPT_vect){
	time_current = ICR3;

	//If overflow has happened
	if(overflow_counter > 0){
		//reset timer overflow
		delta_time = time_current + (overflow_counter-1)*MAX_INT + time_before_overflow;
		overflow_counter = 0;
	}
	else{
		delta_time = time_current - time_previous;
	}

	//cm/ms
	velocity = (DISTANCE/delta_time)/1000;	
}


ISR(TIMER3_OVF_vect){
	
	if(overflow_counter == 0){
		time_before_overflow = MAX_INT - time_previous;	
	}

	overflow_counter++;

}


// Calls all startup methods that need to be run before application runs.
// Allocate resources etc...
void startup()
{
	HW_startup();
	PID_startup();	
}


// Called when all setup and settings has been made
void run()
{
	PID_run();
}


int main(){
	// startup process
	startup();

	// should be last thing called before main loop
	//run();
	
	//steeringControl(45);
	//throttleControl(-0.25);

	while(1);
}

