//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#include "UniRndGen.h"
#include "ExpRndGen.h"
#include "Modeling.h"
#include <iostream>
using namespace std;
#include "VSimReporter.h"

// Class VisSimulationReporter methods (implementation)
void VisSimulationReporter::visitFlowElement (FlowElement* fe, char* typeStr){
	if (fe==0) return;
	output("\n\n");
	writeNameType(fe,typeStr);
	output("\nTotal occurrences: ");
	if (out) (*out)<<fe->getNumOfOccurrences()<<"\n";
}
void VisSimulationReporter::visitUniformGenerator (UniformGenerator* e) {}
void VisSimulationReporter::visitExpGenerator (ExpGenerator* e) {}
void VisSimulationReporter::visitFlowSource (FlowSource* e){
	visitFlowElement(e,"Flow Source");
}
void VisSimulationReporter::visitFlowSink (FlowSink* e){
	visitFlowElement(e,"Flow Sink");
}
void VisSimulationReporter::visitPipe (Pipe* e){
	visitFlowElement(e,"Pipe");
}
void VisSimulationReporter::visitQueuedServer (QueuedServer* e){
	if (e==0) return;
	visitFlowElement(e,"Queued Server");
	if (out) {
		(*out)<<"Currently serving: "<<e->isCurrentlyServing()<<"\n";
		(*out)<<"Current queue size: "<<e->getQueueSize()<<"\n";
		(*out)<<"Maximum queue size: "<<e->getMaxQueueSize()<<"\n";
	}
}
void VisSimulationReporter::visitSwitch1to3 (Switch1to3* e){
	visitFlowElement(e,"Switch 1 to 3");
}
void VisSimulationReporter::visitCrossSemaphore (CrossSemaphore* e) {}