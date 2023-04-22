//  * Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#include "Visitor.h"
#include "ExpRndGen.h"
#include "Pipe.h"

// Class Pipe methods
Pipe::Pipe (double meanValue): RandomTimedFlowElement(new ExpGenerator(meanValue)) {}
void Pipe::accept (Visitor* vis){
	if (vis) vis->visitPipe(this);
}

void Pipe::process (){
	raiseEvent();
}

void Pipe::notify (ID ){
	send();
}

// Additional Declarations