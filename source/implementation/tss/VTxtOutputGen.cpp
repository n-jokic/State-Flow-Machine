//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#include <iostream>
using namespace std;
#include "AbstractConcepts.h"
#include "VTxtOutputGen.h"

// Class VisTxtOutputGenerator methods 
VisTxtOutputGenerator::VisTxtOutputGenerator (ostream* outputStream): out(outputStream) {}
void VisTxtOutputGenerator::output (char* str){
	if (out && str) (*out)<<str;
}

void VisTxtOutputGenerator::writeNameType (ModelElement* me, char* typeName){
	if (me && out) {
		(*out)<<"[ID="<<me->getID()<<"] ";
		output(me->getName());
		output(" : ");
		output(typeName);
	}
}
void VisTxtOutputGenerator::writeDescrLn (ModelElement* me){
	if (me) {
		output("Description: ");
		output(me->getDescr());
		output("\n");
	}
}