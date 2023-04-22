//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#include "Visitor.h"
#include "ExpRndGen.h"

//QueServer header
#include "QueServer.h"

// Class QueuedServer 
QueuedServer::QueuedServer (double meanValue)
      : onOff(true), queSize(0), isServing(false), maxQueSize(0),
		RandomTimedFlowElement(new ExpGenerator(meanValue)) {}
void QueuedServer::accept (Visitor* vis){
	if (vis) vis->visitQueuedServer(this);
}
void QueuedServer::process (){
	if (isOn() && !isServing && queSize==0) {
		isServing = true;
		raiseEvent();
	} else {
		queSize++;
		if (queSize>maxQueSize) maxQueSize = queSize;
	}
}
void QueuedServer::notify (ID ){
	isServing = false;
	send();
	if (isOn() && !isServing && queSize>0) {
		queSize--;
		isServing = true;
		raiseEvent();
	}
}
void QueuedServer::switchOn ()
{
	onOff = true;
	if (isOn() && !isServing && queSize>0) {
		queSize--;
		isServing = true;
		raiseEvent();
	}
}