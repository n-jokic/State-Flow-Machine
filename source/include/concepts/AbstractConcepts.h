//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef AbstractConcepts_h
#define AbstractConcepts_h 

#include "Types.h"
#include "Interfaces.h"

class Visitor;
class RandomGenerator;

//	Abstract generalization of all elements in the model.
class ModelElement{
  public:
      //Destructor. Removes this Model Element from the Model.
      virtual ~ModelElement ();
      //Abstract. Accepts a Visitor. Visitor DP.
      virtual void accept (Visitor* vis) = 0;
      //Returns the internally generated and unique ID of the Model Element.
      virtual MEID getID ();
      //Returns the name of the Model Element.
      virtual String getName ();
      //Sets the name of the Model Element.
      virtual void setName (String newVal);
      //Returns the description of the Model Element.
      virtual String getDescr ();
      //Sets the description of the Model Element.
      virtual void setDescr (String newVal);
  protected:
      //Constructor. Adds this Model Element to the Model.
      ModelElement ();
  private:
      // Data Members for Class Attributes
      //Internal Model Element ID generator. Static.
       static MEID idCounter;
      //Internally generated ID of a Model Element.
      MEID id;
      //The name of the element.
      String name;
      //The description of the element.
      String descr; 
};

//	Abstract generalization of Model Elements that generate, transport, or accept traffic flow.

class FlowElement : public ModelElement {
  public:
      //Accepts one flow item (a vehicle occurrence). Increments
      //the counter and invokes process(). Template Method DP.
      virtual void acceptFlow ();
      //Returns the total number of transported occurrences.
      virtual unsigned long getNumOfOccurrences ();
      //Resets the counter of transported occurrences.
      virtual void resetCounter ();
      //Data Members for Associations
      FlowElement *target;
  protected:
      //Constructor.
      FlowElement ();
      //Processes an occurrence. To be redefined in derived classes.
      virtual void process ();
      //Sends a vehicle occurrence to the target Flow Element.
      virtual void send ();
	  //Data Members for Class Attributes
	  //The counter of transported occurrences.
      unsigned long counter;
};

//Abstract generalization og Model Elements that control traffic flow (e.g. a traffic light).
class ControlElement : public ModelElement {
  public:
    // Additional Public Declarations
  protected:
    // Additional Protected Declarations
  private:
    // Additional Private Declarations     
};

//Abstract generalization of Flow Elements that have a random timed flow service, generation, or delay.
class RandomTimedFlowElement : public FlowElement, public ITimedElement {
  public:
      //Returns the associated random generator.
      virtual RandomGenerator* getRndGen ();
      //Notifies the receiver of the Event that the requested time delay has elapsed,
	  //or the time-scheduled Event has occurred.
      virtual void notify (ID id) = 0;	// Auxiliary identification of the Event.
  protected:
      //Constructor. Accepts a Random Generator.
      RandomTimedFlowElement (RandomGenerator* rg);
      //Destructor. Destroys the owned Random Generator.
      virtual ~RandomTimedFlowElement ();
      //Raises a new timed Event with the time generated randomly by the associated Random Generator.
      virtual void raiseEvent (ID id = 0);
  private:
    // Data Members for Associations
    RandomGenerator *rndGen;
};

// Class ModelElement Other Operations (inline)
inline MEID ModelElement::getID (){  
	return id;
}
inline String ModelElement::getName (){
	return name;
}
inline String ModelElement::getDescr (){
  	return descr;  
}

// Class FlowElement inline methods 
inline FlowElement::FlowElement (): counter(0), ModelElement(), target(0) {}
inline void FlowElement::acceptFlow (){
  	counter++;
	process();
}
inline void FlowElement::process () {}
inline void FlowElement::send () {
	if (target) target->acceptFlow();
}
inline unsigned long FlowElement::getNumOfOccurrences (){
  	return counter;
}
inline void FlowElement::resetCounter (){
  	counter = 0;
}

// Class ControlElement inline methods 

// Class RandomTimedFlowElement inline methods 
inline RandomTimedFlowElement::RandomTimedFlowElement (RandomGenerator* rg): rndGen(rg) {}
inline RandomGenerator* RandomTimedFlowElement::getRndGen (){
  	return rndGen;
}

#endif
