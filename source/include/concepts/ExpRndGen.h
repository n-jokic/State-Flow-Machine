//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef ExpRndGen_h
#define ExpRndGen_h 

#include "RndGen.h"

//Random number generator of an exponential distribution.
class ExpGenerator : public RandomGenerator{
  public:
      //Constructor. Accepts the mean value of the distribution.
      ExpGenerator (double meanValue = 1);
      //Accepts a Visitor. Visitor DP.
      virtual void accept (Visitor* vis);
      //Redefined. Returns the name of distribution of the generator.
      virtual String getDistributionName ();
      //Redefined. Returns the mean value of the distribution.
      virtual double getMeanValue ();
  protected:
      //Redefined. Converts the given random number x with the uniform distribution 
	  //in [0..1] into a random number with the exponential distribution.
      virtual double convert (double x);
  private:
      //The mean value of the distribution.
      double mean;
};

// Class ExpGenerator inline methods
inline ExpGenerator::ExpGenerator (double meanValue): mean(meanValue) {}
inline String ExpGenerator::getDistributionName (){
	return "Exponential";
}
inline double ExpGenerator::getMeanValue (){
	return mean;
}

#endif
