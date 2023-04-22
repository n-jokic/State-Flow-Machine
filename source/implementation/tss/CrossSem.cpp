//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#include "Visitor.h"
#include "Event.h"
#include "CrossSem.h"

// Class CrossSemaphore methods
CrossSemaphore::CrossSemaphore (Time timeVertical, Time timeHorizontal): curDir(horizontal), tVer(1), tHor(1){
	horSource[0]=horSource[1]=0;
	verSource[0]=verSource[1]=0;
	setTimes(timeVertical,timeHorizontal);
	notify(0);
}
void CrossSemaphore::accept (Visitor* vis){
	if (vis) vis->visitCrossSemaphore(this);
}
void CrossSemaphore::notify (ID ){
	if (curDir==horizontal) {
		if (horSource[0]) horSource[0]->switchOff();
		if (horSource[1]) horSource[1]->switchOff();
		curDir = vertical;
		if (verSource[0]) verSource[0]->switchOn();
		if (verSource[1]) verSource[1]->switchOn();
		Event::create(this,tVer);
	} else {
		if (verSource[0]) verSource[0]->switchOff();
		if (verSource[1]) verSource[1]->switchOff();
		curDir = horizontal;
		if (horSource[0]) horSource[0]->switchOn();
		if (horSource[1]) horSource[1]->switchOn();
		Event::create(this,tHor);
	}
}