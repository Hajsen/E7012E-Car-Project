#include "PID/PID.h"
#include "MCU_Controller/MCU_Controller.h"

#include "MCU_Controller/HW_startup.h"

int main()
{
	// startup process
	startup();

	// should be last thing called before main loop
	//run();
	while(1);
}


// Calls all startup methods that need to be run before application runs.
// Allocate resources etc...
void startup()
{
	PID_startup();
}


// Called when all setup and settings has been made
void run()
{
	PID_run();
}

void asokdokasd(){int lol;}
