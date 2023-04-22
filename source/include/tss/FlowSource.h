//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef FlowSource_h
#define FlowSource_h 

#include "AbstractConcepts.h"

//Source of discrete random traffic flow with exponential distribution.
class FlowSource : public RandomTimedFlowElement, public IFlowSource{
  public:
      //Constructor. Accepts a mean value of the exponential distribution. Creates an Exponential Random Generator
      //and passes it to the constructor of the base class. Generates an initial vehicle occurrence.
      FlowSource (double meanValue = 1);
      //Accepts a Visitor. Visitor DP.
      virtual void accept (Visitor* vis);
      //Redefined. Does nothing (ignores input flow).
      virtual void acceptFlow ();
      //Redefined. Generates a new vehicle occurrence on its output and raises a new Event for another occurrence.
      virtual void notify (ID); 	// Auxiliary identification of the event.
      //Switch the source on - the source can generate or transport the flow.
      virtual void switchOn ();
      //Switch the source off - the source does not generate or transport the flow any more.
      virtual void switchOff ();
      //Is the source switched on?
      virtual bool isOn ();
      //Additional Public Declarations
  protected:
      //Additional Protected Declarations
  private:
      //Data Members for Class Attributes - On/off switch of the source.
      bool onOff;
      //Additional Private Declarations

};

// Class FlowSource inline methods
inline void FlowSource::acceptFlow () {}
inline void FlowSource::switchOn () {
	onOff = true;
}
inline void FlowSource::switchOff (){
	onOff = false;
}
inline bool FlowSource::isOn (){
	return onOff;
}

#endif
