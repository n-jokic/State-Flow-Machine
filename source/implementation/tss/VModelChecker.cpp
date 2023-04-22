//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#include "UniRndGen.h"
#include "ExpRndGen.h"
#include "Modeling.h"
#include "VModelChecker.h"

// Class VisModelChecker methods
void VisModelChecker::outputViolation (ModelElement* me, char* tpStr, char* str, bool error){
	if (me==0) return;
	writeNameType(me,tpStr);
	output("\n\t");
	if (error) output("Error: "); else output("Warning: ");
	output(str);
	output();
}
void VisModelChecker::visitUniformGenerator (UniformGenerator* e){
	if (e==0) return;
	if (e->getMeanValue()<0) output("\tMean value less than 0.\n");
}
void VisModelChecker::visitExpGenerator (ExpGenerator* e){
	if (e==0) return;
	if (e->getMeanValue()<0) output("\tMean value less than 0.\n");
}
void VisModelChecker::visitFlowSource (FlowSource* e){
	if (e==0) return;
	if (e->target==0) outputViolation(e,"Flow Source","No target for the flow source.",true);
	output();
}
void VisModelChecker::visitFlowSink (FlowSink* e){
	if (e==0) return;
	if (e->target!=0) outputViolation(e,"Flow Sink","Target of the flow sink has no effect.",true);
	output();
}
void VisModelChecker::visitPipe (Pipe* e){
	if (e==0) return;
	if (e->target==0) outputViolation(e,"Pipe","No target for the pipe.",true);
	RandomGenerator* rndGen = e->getRndGen();
	if (rndGen==0) outputViolation(e,"Pipe","No random generator.",true);
	output();
}
void VisModelChecker::visitQueuedServer (QueuedServer* e){
	if (e==0) return;
	if (e->target==0) outputViolation(e,"Queued Server","No target for the server.",true);
	RandomGenerator* rndGen = e->getRndGen();
	if (rndGen==0) outputViolation(e,"Pipe","No random generator.",true);
	output();
}

void VisModelChecker::visitSwitch1to3 (Switch1to3* e){
	if (e==0) return;
	if (e->target==0) outputViolation(e,"Switch","No straight target for the switch.",true);
	if (e->leftTarget==0) outputViolation(e,"Switch","No left target for the switch.",true);
	if (e->rightTarget==0) outputViolation(e,"Switch","No right target for the switch.",true);
	output();
}
void VisModelChecker::visitCrossSemaphore (CrossSemaphore* e){
	if (e==0) return;
	if (e->horSource[0]==0 && e->horSource[1]==0) outputViolation(e,"Cross Semaphore","No horizontal source for the semaphore.",false);
	if (e->verSource[0]==0 && e->verSource[1]==0) outputViolation(e,"Cross Semaphore","No vertical source for the semaphore.",false);
	output();
}