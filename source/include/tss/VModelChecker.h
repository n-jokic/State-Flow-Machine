//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef VModelChecker_h
#define VModelChecker_h 

#include "VTxtOutputGen.h"

//A Visitor that verifies the regularity of the model and reports violations to the output stream.
class VisModelChecker : public VisTxtOutputGenerator {
  public:
      //Constructor. Accepts an output stream to generate the report.
      VisModelChecker (ostream* output);
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
      //Helper. Displays an error or a warning for the given model element.
      virtual void outputViolation (ModelElement* me, char* tpStr, char* str, bool error = true);
};

// Class VisModelChecker inline methods 

inline VisModelChecker::VisModelChecker (ostream* output)
  : VisTxtOutputGenerator(output) {}

#endif
