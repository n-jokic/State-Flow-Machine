//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#include "UniRndGen.h"
#include "ExpRndGen.h"
#include "Modeling.h"
#include <iostream>
using namespace std;
#include "VModelDocumenter.h"

// Class VisModelDocumenter methods
void VisModelDocumenter::visitModelElement (ModelElement* me, char* typeStr){
	if (me==0) return;
	output("\n\n");
	writeNameType(me,typeStr);
	output();
	writeDescrLn(me);
}
void VisModelDocumenter::visitFlowElement (FlowElement* fe, char* typeStr){
	if (fe==0) return;
	visitModelElement(fe,typeStr);
	output("Target: ");
	if (fe->target) {
		output("[ID="); 
		if (out) (*out)<<fe->target->getID()<<"] ";
		output(fe->target->getName());
	}
	output();
}
void VisModelDocumenter::visitUniformGenerator (UniformGenerator* e){
	if (e==0) return;
	output("Uniform random generator: ");
	output("Mean value = ");
	if (out) (*out)<<e->getMeanValue();
	output();
}
void VisModelDocumenter::visitExpGenerator (ExpGenerator* e){
	if (e==0) return;
	output("Exponential random generator: ");
	output("Mean value = ");
	if (out) (*out)<<e->getMeanValue();
	output();
}
void VisModelDocumenter::visitFlowSource (FlowSource* e){
	visitFlowElement(e,"Flow Source");
	if (e->getRndGen()) e->getRndGen()->accept(this);
}
void VisModelDocumenter::visitFlowSink (FlowSink* e){
	visitFlowElement(e,"Flow Sink");
}
void VisModelDocumenter::visitPipe (Pipe* e){
	visitFlowElement(e,"Pipe");
	if (e->getRndGen()) e->getRndGen()->accept(this);
}
void VisModelDocumenter::visitQueuedServer (QueuedServer* e){
	visitFlowElement(e,"Queued Server");
	if (e->getRndGen()) e->getRndGen()->accept(this);
}
void VisModelDocumenter::visitSwitch1to3 (Switch1to3* e){
	visitFlowElement(e,"Switch 1 to 3");
	if (e->leftTarget && out) (*out)<<"Left turn target: "<<e->leftTarget->getID()<<"\n";
	if (out) (*out)<<"Left turn probability: "<<e->getLTProb()<<"\n";
	if (e->rightTarget && out) (*out)<<"Right turn target: "<<e->rightTarget->getID()<<"\n";
	if (out) (*out)<<"Right turn probability: "<<e->getRTProb()<<"\n";
}
void VisModelDocumenter::visitCrossSemaphore (CrossSemaphore* e){
	visitModelElement(e,"Cross Semaphore");
	if (out) (*out)<<"Horizontal direction time: "<<e->getTimeHorizontal()<<"\n";
	if (out) (*out)<<"Vertical direction time: "<<e->getTimeVertical()<<"\n";
}