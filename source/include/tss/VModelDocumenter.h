//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef VModelDocumenter_h
#define VModelDocumenter_h 

#include "VTxtOutputGen.h"

//A Visitor that traverses the model and generates the documentation.
class VisModelDocumenter : public VisTxtOutputGenerator {
  public:
      //Constructor. Accepts an output stream to generate the report.
      VisModelDocumenter (ostream* output);
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
      //Helper. Visits a Model Element. Writes its ID, name, and description.
      virtual void visitModelElement (ModelElement* me, char* typeStr);
      //Helper. Visits a Flow Element. Writes its ID, name, description,
	  //the target's data, and the number of transported occurrences.
      virtual void visitFlowElement (FlowElement* fe, char* typeStr);
};

// Class VisModelDocumenter inline methods
inline VisModelDocumenter::VisModelDocumenter (ostream* output)
: VisTxtOutputGenerator(output) {}

#endif
