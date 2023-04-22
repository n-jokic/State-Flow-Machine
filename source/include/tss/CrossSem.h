//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef CrossSem_h
#define CrossSem_h 

#include "AbstractConcepts.h"

enum CrossDir {horizontal, vertical};

//	A simple semaphore for a 2-way crossroad. Switches two directions alternatively.
class CrossSemaphore : public ControlElement, public ITimedElement{
  public:
      //Constructor. Accepts the times of vertical and horizontal directions being open.
      CrossSemaphore (Time timeVertical, Time timeHorizontal);
      //Accepts a Visitor. Visitor DP.
      virtual void accept (Visitor* vis);
      //Sets the times of vertical and horizontal directions being open.
      virtual void setTimes (Time timeVertical, Time timeHorizontal);
      //Returns the time of the vertical direction being open.
      virtual Time getTimeVertical ();
	  //Returns the time of the horizontal direction being open.
      virtual Time getTimeHorizontal ();
      //Returns the currently open direction: horizontal or	vertical.
      virtual CrossDir getCurDir ();
      //Redefined. Switches the direction of controlled Flow Sources.
      virtual void notify (ID);	// Auxiliary identification of the event.
	  //Data Members for Associations
      IFlowSource *  horSource[2];
      IFlowSource *  verSource[2];
  protected:
      //Additional Protected Declarations
  private:
      //Data Members for Class Attributes
      CrossDir curDir;
      //The time of the vertical direction being open.
      Time tVer;
      //The time of the horizontal direction being open.
	  Time tHor;
};

// Class CrossSemaphore inline methods
inline void CrossSemaphore::setTimes (Time timeVertical, Time timeHorizontal){
	if (timeVertical>0 && timeHorizontal>0) {
		tVer = timeVertical;
		tHor = timeHorizontal;
	}
}
inline Time CrossSemaphore::getTimeVertical (){
	return tVer;
}
inline Time CrossSemaphore::getTimeHorizontal (){
	return tHor;
}
inline CrossDir CrossSemaphore::getCurDir (){
	return curDir;
}

#endif
