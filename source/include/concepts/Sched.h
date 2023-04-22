//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef Sched_h
#define Sched_h 

#include "Types.h"

class Event;

//The scheduler of the Events sorted in chronological order. Singleton.
class Scheduler {
  public:
      //Returns the singleton instance of this class. Static.
      //Singleton DP.
      static Scheduler* Instance ();
      //Accepts a new Event to be scheduled. Puts it into the chronological list of Events.
      virtual void put (Event* ev);
      //Returns the current simulation time (simulation clock).
      virtual Time getCurTime ();
      //Processes one step of simulation, by handling the Events that are scheduled first and 
	  //at the same moment. Returns true if there is more Events left after the processing.
      virtual bool processNow ();
  protected:
      //Constructor. Singleton DP.
      Scheduler ();
      //Processes the first scheduled Event (if any) by handling it. Returns true if 
	  //there is more Events scheduled at the same moment left after the processing.
      virtual bool processOneEvent ();
  private:
      //Current time (internal simulation clock).
      Time curTime;
      Event *first;
};

// Class Scheduler inline methods 
inline Scheduler::Scheduler (): curTime(0), first(0) {}
inline Time Scheduler::getCurTime (){
	return curTime;
}

#endif
