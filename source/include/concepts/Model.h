//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef Model_h
#define Model_h 

#include "Types.h"

class Visitor;
class ModelElement;

//The entire model, a collection of Model Elements. Singleton DP.
class Model {
  public:
	  //Destructor. Destroys its Model Elements.
      virtual ~Model ();
      //Returns the singleton instance of this class. Static. Singleton DP.
      static Model* Instance ();
      //Accepts a Visitor. Visitor DP.
      virtual void accept (Visitor* vis);
      //Adds a Model Element to the Model.
      virtual void add (ModelElement* me);
      //Removes a Model Element from the Model.
      virtual void remove (ModelElement* me);
      //Returns the owned Model Elements.
      virtual CollectionME* getElements ();
      //Clears the Model. Destroys all it's Model Elements.
      virtual void clear ();
	  // Additional Public Declarations
     
  protected:
      //Constructor. Singleton DP.
      Model ();
	  //Additional Protected Declarations
  private:
      //Data Members for Associations
      CollectionME elements;
      // Additional Private Declarations

};

// Class Model inline methods
inline Model::Model () {}
inline Model::~Model (){
  	clear();
}
inline void Model::add (ModelElement* me){
	if (me) elements.add(me);
}

inline void Model::remove (ModelElement* me){
	if (me) elements.remove(me);
}
inline CollectionME* Model::getElements (){
	return &elements;  
}

#endif
