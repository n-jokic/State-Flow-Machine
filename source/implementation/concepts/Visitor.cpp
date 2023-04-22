//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *
#include "Model.h"
#include "AbstractConcepts.h"
#include "Visitor.h"

// Class Visitor methods definitions
void Visitor::visitModel (Model* e){
	if (e==0) return;
	CollectionME* c = e->getElements();
	if (c==0) return;
	CollectionMEIt* it=c->getIterator();
	for (it->reset(); !it->isDone(); it->next())
		(*it->currentItem())->accept(this);
}