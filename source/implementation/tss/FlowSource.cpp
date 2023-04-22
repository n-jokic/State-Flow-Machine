//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#include "ExpRndGen.h"
#include "Visitor.h"
#include "FlowSource.h"

//Class FlowSource methods
FlowSource::FlowSource (double meanValue): onOff(true), RandomTimedFlowElement(new ExpGenerator(meanValue)){
	raiseEvent();
}
void FlowSource::accept (Visitor* vis){
	if (vis) vis->visitFlowSource(this);
}
void FlowSource::notify (ID ){
	if (isOn()) {
		counter++;
		send();
	}
	raiseEvent();
}