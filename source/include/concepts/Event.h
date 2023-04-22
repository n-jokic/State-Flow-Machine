//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef Event_h
#define Event_h 

#include "Interfaces.h"

//A discrete occurrence in time, dedicated to an ITimed	Element.
class Event {
  public:
      //Static. Raises an Event and sends it to the simulation engine. Accepts the target,
	  //the time (relative to the current moment), and the ID of the Event.
      static void create (ITimedElement* targetElement, Time tm, ID id = 0);
      //Returns the ID of the Event.
      virtual ID getID ();
      //Returns the target of the Event.
      virtual ITimedElement* getTarget ();
      //Returns the scheduled time of the Event (relative to the previous Event in the Scheduler's list).
      virtual Time getTime ();
      //Sets the scheduled time of the Event (relative to the previous Event in the Scheduler's list).
      virtual void setTime (Time newTime);
      //Returns the next scheduled Event in the Scheduler's list.
      virtual Event* getNext ();
      //Sets the next scheduled Event in the Scheduler's list.
      virtual void setNext (Event* nxt);
  protected:
      //Constructor. Accepts the target, the time (relative to the current moment), and the ID of the Event.
      Event (ITimedElement* targetElement, Time tm, ID i = 0);
    // Additional Protected Declarations
  private:
      //Auxiliary identification of the occurrence.
      ID id;
      //The time at which the Event is scheduled to occur. Relative to the previous Event 
	  //in the Scheduler's list, or to the current moment, if it is the first in the list.
      Time time;
      Event *next;
      ITimedElement *target;
};

// Class Event inline methods 
inline void Event::create (ITimedElement* targetElement, Time tm, ID id){
	new Event(targetElement,tm,id);
}
inline ID Event::getID (){
	return id;
}
inline ITimedElement* Event::getTarget (){
	return target;
}
inline Time Event::getTime (){
	return time;
}
inline void Event::setTime (Time newTime){
	time = newTime;
}
inline Event* Event::getNext (){
	return next;
}
inline void Event::setNext (Event* nxt){
	next = nxt;
}

#endif
