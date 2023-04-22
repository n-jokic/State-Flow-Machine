//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef Switch1to3_h
#define Switch1to3_h 

#include "AbstractConcepts.h"

class UniformGenerator;

//Switch with one input and three outputs: straight, left, and right. Randomly passes the input flow 
//to the three directions, according to the defined probabilities of turns with a uniform distribution.

class Switch1to3 : public FlowElement{
  public:
      //Constructor. Accepts the probabilities of left and right turns (they must be 
	  //in [0..1] and their sum must be in [0..1]). Creates a Uniform Random Generator.
      Switch1to3 (double leftTurnProb = 0.0, double rightTurnProb = 0.0);
      //Accepts a Visitor. Visitor DP.
      virtual void accept (Visitor* vis);
      //Returns the left-turn probability.
      virtual double getLTProb ();
      //Returns the right-turn probability.
      virtual double getRTProb ();
      //Sets the left-turn and right-turn probabilities. Accepts the probabilities of
	  //left and right turns. They must be in [0..1] and their sum must be in [0..1].
      virtual void setProbabilities (double leftTurnProb = 0.0, double rightTurnProb = 0.0);
      // Data Members for Associations
	  FlowElement *leftTarget;
      FlowElement *rightTarget;
  protected:
      //Destructor. Destroys its Uniform Random Generator.
      virtual ~Switch1to3 ();
      //Redefined. Passes the occurrence to the straight, left, or right target 
	  //randomly, according to the given probabilities of turns.
      virtual void process ();
  private:
      //Data Members for Class Attributes - left and right turn probability
      double ltProb;
      double rtProb;
      //Data Members for Associations
      UniformGenerator *rndGen;
};

// Class Switch1to3 inline methods
inline double Switch1to3::getLTProb (){
	return ltProb;
}
inline double Switch1to3::getRTProb (){
	return rtProb;
}

#endif
