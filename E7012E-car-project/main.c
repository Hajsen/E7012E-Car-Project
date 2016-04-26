#include "avr/io.h"
#include <avr/interrupt.h>


#include "PID\PID.h"
#include "MCU_Controller\MCU_Controller.h"
#include "MCU_Controller\HW_startup.h"
#include "PIDhelper.h"

#include "PIDHelper.h"


void toggleMCUled(){
	DDRE |= (1 << DDE4);
	
	PORTE ^= (1 << PORTA4);
}

//Interrupt function (Here is where the interrupt does work)

ISR(TIMER1_COMPC_vect){
	
	PORTA |= 1 << PORTA7; //Toggles led

}


ISR(TIMER3_CAPT_vect){
		
	toggleMCUled();
}


ISR(TIMER3_OVF_vect){


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

