#include "PID.h"
#include "MCU_Controller.h"

#include "HW_setup.h"

int main()
{
	// startup process
	startup();

	// should be last thing called before main loop
	run();
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
