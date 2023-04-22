//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *
#ifndef Interfaces_h
#define Interfaces_h 

#include "Types.h"

//Interface of Flow Elements representing flow sources that can be switched on and off.
class IFlowSource {
  public:
      //Switch the source on - the source can generate or transport the flow.
      virtual void switchOn () = 0;
      //Switch the source off - the source does not generate or transport the flow any more.
      virtual void switchOff () = 0;
      //Is the source switched on?
      virtual bool isOn () = 0;
  protected:
    // Additional Protected Declarations
  private:
    // Additional Private Declarations
};

//Interface of a Model Element that has a time delay of some service,
//for which it should accept a time-scheduled Event from the simulation engine.
class ITimedElement {
  public:
      //Notifies the receiver of the Event that the requested time delay has elapsed,
	  //or the time-scheduled Event has	occurred.
      virtual void notify (ID id) = 0;	// Auxiliary identification of the Event.
  protected:
    // Additional Protected Declarations
  private:
    // Additional Private Declarations
};

// Class IFlowSource 

// Class ITimedElement 

#endif
