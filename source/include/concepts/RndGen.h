//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef RndGen_h
#define RndGen_h 

#include "Types.h"

class Visitor;

//Abstract generalization of random number generators.
class RandomGenerator {
  public:
      //Abstract. Accepts a Visitor. Visitor DP.
      virtual void accept (Visitor* vis) = 0;
      //Abstract. Returns the name of distribution of the generator.
      virtual String getDistributionName () = 0;
      //Abstract. Returns the mean value of the distribution.
      virtual double getMeanValue () = 0;
      //Returns a newly generated random number. Final. First calls urnd() to generate a random 
	  //number with the uniform distribution, and then calls the polymorphic operation convert()
	  //to convert the generated uniform number into a number with the desired distribution.
	  //Template Method DP.
      double getRandom ();
  protected:
      //Static, helper. Returns a new random number in [0..1] with the uniform distribution.
      static double urnd ();
      //Abstract. To be redefined in the derived classes. Converts the given random number x with 
	  //the uniform distribution in [0..1] into a random number with the desired distribution.
      virtual double convert (double x) = 0;
  private:
      //Static. The previously generated random number.
      static unsigned long urndNum;
};

// Class RandomGenerator inline methods

#endif
