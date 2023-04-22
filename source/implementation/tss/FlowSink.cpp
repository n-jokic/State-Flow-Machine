//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#include "Visitor.h"
#include "FlowSink.h"

// Class FlowSink methods
void FlowSink::accept (Visitor* vis){
	if (vis) vis->visitFlowSink(this);
}

// Additional Declarations
