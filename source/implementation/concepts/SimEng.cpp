//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#include "Event.h"
#include "Sched.h"

class ITimedElement;

// Class Event methods 
Event::Event (ITimedElement* targetElement, Time tm, ID i)
    : id(i), time(tm), next(0), target(targetElement){
		Scheduler::Instance()->put(this);
}

// Class Scheduler methods
Scheduler* Scheduler::Instance (){
	static Scheduler instance;
	return &instance;
}
void Scheduler::put (Event* ev){
	if (ev==0) return;
	Time time = ev->getTime();
	Event* nxt = first;
	Event* prv = 0;
	
	while (nxt!=0 && time >= nxt->getTime()) {
		time -= nxt->getTime();
		prv = nxt;
		nxt = nxt->getNext();
	}
	
	if (nxt) nxt->setTime(nxt->getTime() - time);
	ev->setTime(time);
	ev->setNext(nxt);
	if (prv!=0) prv->setNext(ev); else first = ev;    
}
bool Scheduler::processOneEvent (){
	Event* ev = first;
	if (ev==0) return false;
	first = first->getNext();
	curTime += ev->getTime();
	ITimedElement* el = ev->getTarget();
	if (el) el->notify(ev->getID());
	delete ev;
	return (first && first->getTime()==0);
}
bool Scheduler::processNow ()
{
	while (processOneEvent());
	return (first!=0);
}