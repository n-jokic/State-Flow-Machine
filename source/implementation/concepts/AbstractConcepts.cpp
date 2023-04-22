//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#include <cstring>
#include "AbstractConcepts.h" // AbstractConcepts
#include "Model.h" // Model
#include "RndGen.h" // RndGen
#include "Event.h" // Event
#include "Visitor.h" // Visitor

// Class ModelElement 
MEID ModelElement::idCounter = 0;

ModelElement::ModelElement () : id(++idCounter), name(0), descr(0){
	Model::Instance()->add(this);
}

ModelElement::~ModelElement (){
	Model::Instance()->remove(this);
	delete name;
	delete descr;
}
void ModelElement::setName (String newVal){
	delete name;
	name = new char[strlen(newVal)+1];
	if (name) strcpy(name,newVal);
}
void ModelElement::setDescr (String newVal){
	delete descr;
	descr = new char[strlen(newVal)+1];
	if (descr) strcpy(descr,newVal);
}

// Class FlowElement 

// Class ControlElement 

// Class RandomTimedFlowElement 
RandomTimedFlowElement::~RandomTimedFlowElement (){
  	delete rndGen;
}
void RandomTimedFlowElement::raiseEvent (ID id){
  	Time tm = 0;
	if (rndGen) tm = rndGen->getRandom();
	else return;
	Event::create(this,tm,id);
}

// Class Model 
Model* Model::Instance (){
  	static Model instance;
	return &instance;
}
void Model::accept (Visitor* vis){
	if (vis) vis->visitModel(this);
}
void Model::clear (){
  	while (!elements.isEmpty()) {
		ModelElement* me = elements.itemAt(0);
		delete me;
		elements.remove(0);
	}
}