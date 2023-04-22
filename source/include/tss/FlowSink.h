//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef FlowSink_h
#define FlowSink_h 

#include "AbstractConcepts.h"

//An element that accepts all incoming traffic flow and does not propagate it further
//meaning a termination of a flow branch.
class FlowSink : public FlowElement{
  public:
      //Constructor.
      FlowSink ();
      //Accepts a Visitor. Visitor DP.
      virtual void accept (Visitor* vis);
      //Additional Public Declarations

  protected:
      //Redefined. Sinks the input flow.
      virtual void process ();
      //Additional Protected Declarations
     
  private:
      //Additional Private Declarations

};

//Class FlowSink inline methods
inline FlowSink::FlowSink () {}
inline void FlowSink::process () {}

#endif
