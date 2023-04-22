#include "Sched.h"
// TODO: Include necessary headere files.

void buildModel () {
	
	/* Sample code for building digital network model. 

	PeriodicSignalSource* src1 = new PeriodicSignalSource(10);
	PeriodicSignalSource* src2 = new PeriodicSignalSource(20);
	
	AndCircuit *and = new AndCircuit(2);
	src1->connectTo (and, 0);
	src2->connectTo (and, 1);

	src1->switchOn();
	src2->switchOn();
	*/
}

void main(int argc, char* argv[]){
	buildModel();
	
	// TODO: Model report

	// Simulation:
	while (Scheduler::Instance()->getCurTime()<=5000.0)
		Scheduler::Instance()->processNow();
	
	// TODO: Simulation report
}
