#include "avr/io.h"
#include <avr/interrupt.h>
#include <math.h>


#include "PID\PID.h"
#include "MCU_Controller\MCU_Controller.h"
#include "MCU_Controller\HW_startup.h"
#include "..\resourceManager.h"


double overflow_counter = 0;
double time_before_overflow = 0;
double time_previous = 0;
double time_current = 0;
double delta_time = 0;



//Interrupt function (Here is where the interrupt does work)

ISR(TIMER1_COMPC_vect){
	//read sensors
	readSteeringSensors();
	PID_run();
	updateCarStatus();
	
}


ISR(TIMER3_CAPT_vect){
	time_current = ICR3;

	toggleMCUled();

	

	//If overflow has happened
	if(overflow_counter > 0){
		//reset timer overflow
		delta_time = time_current + (overflow_counter-1)*MAX_INT + time_before_overflow;
		overflow_counter = 0;
		
	}
	else{
		delta_time = time_current - time_previous;
	}

	
	//m/s
	velocity = (DISTANCE/delta_time)/1000.0f;

	time_previous = time_current;
	
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
	resourceManager_startup();
}



int main(){
	// startup process
	
	PORTB = 0b00000000;
	volatile int i,j;
	// Wait for Motor controller to ...
	for(i = 0; i<1000;++i)
	{
		for(j = 0; j<1000;++j)
		{
			j--;
			j++;
			//Do nothing
		}
	}
	startup();


	// should be last thing called before main loop
	//run();
	
	steeringControl(-45); 	//pb5
	throttleControl(0.2f); 	//pb6

	while(1);
}

