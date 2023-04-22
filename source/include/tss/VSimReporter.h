//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef VSimReporter_h
#define VSimReporter_h 

#include "VTxtOutputGen.h"

//A Visitor that traverses the model and generates 
//the simulation report at the current moment.
class VisSimulationReporter : public VisTxtOutputGenerator{
  public:
      //Constructor. Accepts an output stream to generate the report.
      VisSimulationReporter (ostream* output);
      //Visits the specific kind of object. Visitor DP.
      virtual void visitUniformGenerator (UniformGenerator* e);
      virtual void visitExpGenerator (ExpGenerator* e);
      virtual void visitFlowSource (FlowSource* e);
      virtual void visitFlowSink (FlowSink* e);
      virtual void visitPipe (Pipe* e);
      virtual void visitQueuedServer (QueuedServer* e);
      virtual void visitSwitch1to3 (Switch1to3* e);
      virtual void visitCrossSemaphore (CrossSemaphore* e);
  protected:
      //Helper. Visits a Flow Element. Writes its ID, name, description,
	  //the target's data, and the number of transported occurrences.
      virtual void visitFlowElement (FlowElement* fe, char* typeStr);
};

// Class VisSimulationReporter inline methods
inline VisSimulationReporter::VisSimulationReporter (ostream* output)
    : VisTxtOutputGenerator(output) {}

#endif
