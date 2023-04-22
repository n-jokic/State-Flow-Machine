//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *
#ifndef QueServer_h
#define QueServer_h 

#include "AbstractConcepts.h"

//A server that processes occurrences with a random delay, and with an unbounded queue in front.
//The service delay has an exponential distribution. The on/off 'gate' is in front of the server,
//i.e. it opens and closes the	entrance to the server from the queue.

class QueuedServer : public RandomTimedFlowElement, public IFlowSource{
  public:
      //Constructor. Accepts the mean value of the exponential distribution.
	  //Creates an Exponential Random Generator and passes it to the constructor of the base class.
      QueuedServer (double meanValue = 1);
      //Accepts a Visitor. Visitor DP.
      virtual void accept (Visitor* vis);
      //Redefined. Generates a new vehicle occurrence on its output, and takes another one to the server,
	  //if the queue is not empty (by rising an Event).
      virtual void notify (ID ); //Auxiliary identification of the event.
      //Switch the source on - the server can serve the flow.
      virtual void switchOn ();
      //Switch the source off - the server does not serve the flow any more.
      virtual void switchOff ();
      //Is the server switched on?
      virtual bool isOn ();
      //Is the server currently serving?
      virtual bool isCurrentlyServing ();
      //Returns the number of the queued vehicles.
      virtual unsigned long getQueueSize ();
      //Returns the maximal recorded number of the queued vehicles.
      virtual unsigned long getMaxQueueSize ();
  protected:
      //Redefined. Puts a vehicle in the queue, and passes it to
	  //the server if it is idle (by rising an Event).
      virtual void process ();
  private:
      //Data Members for Class Attributes - On/off switch of the server.
      bool onOff;
      //Current size of the queue.
      unsigned long queSize;
      //Is the server serving an occurrence.
      bool isServing;
      //The maximal recorded queue size.
      unsigned long maxQueSize;
};

// Class QueuedServer inline methods
inline void QueuedServer::switchOff (){
	onOff = false;
}
inline bool QueuedServer::isOn (){
	return onOff;
}
inline bool QueuedServer::isCurrentlyServing (){
	return isServing;
}
inline unsigned long QueuedServer::getQueueSize (){
	return queSize;
}
inline unsigned long QueuedServer::getMaxQueueSize (){
	return maxQueSize;
}

#endif
