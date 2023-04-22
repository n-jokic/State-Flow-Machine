//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef Pipe_h
#define Pipe_h 

#include "AbstractConcepts.h"

//A pipe of flow with a random delay of the pass of each vehicle occurrence. 
//The transportation delay has an exponential distribution.
class Pipe : public RandomTimedFlowElement {
  public:
      //Constructor. Accepts the mean value of the exponential distribution.
	  //Creates an Exponential Random Generator and passes it to the constructor of the base class.
      Pipe (double meanValue = 1);
      //Accepts a Visitor. Visitor DP.
      virtual void accept (Visitor* vis);
      //Redefined. Generates a new vehicle occurrence on its output.
      virtual void notify (ID ); 	// Auxiliary identification of the event.
      //Additional Public Declarations

  protected:
      //Redefined. Transports a vehicle with a random delay by raising an Event.
      virtual void process ();
      //Additional Protected Declarations

  private:
      //Additional Private Declarations

};

// Class Pipe inline methods

#endif
