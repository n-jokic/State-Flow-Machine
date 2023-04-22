//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef VTxtOutputGen_h
#define VTxtOutputGen_h 

#include <iostream>
using namespace std;

#include "Visitor.h"

class ModelElement;

//Abstract genralization of Visitors that generate a 
//textual (sequential) output into an output stream.
class VisTxtOutputGenerator : public Visitor{
  public:
      //Writes the given string to the output stream.
      virtual void output (char* str = (char*)"\n");
  protected:
      //Constructor. Accepts an output stream.
      VisTxtOutputGenerator (ostream* outputStream);
      //Writes the name and the type of the given Model Element.
      virtual void writeNameType (ModelElement* me, char* typeName);
      //Writes "Description:\n" and then the description of 
	  //the given Model Element. Puts a new line at the end.
      virtual void writeDescrLn (ModelElement* me);
      //The output stream.
      ostream* out;
};

// Class VisTxtOutputGenerator inline methods

#endif
