//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef UniRndGen_h
#define UniRndGen_h 

#include "RndGen.h"

//Random number generator of a uniform distribution.

class UniformGenerator : public RandomGenerator{
  public:
      //Constructor. Accepts the lower and upper bounds of the 
	  //range of random numbers with the uniform distribution.
      UniformGenerator (double lowerBound = 0, double upperBound = 1);
      //Accepts a Visitor. Visitor DP.
      virtual void accept (Visitor* vis);
      //Redefined. Returns the name of distribution of the generator.
      virtual String getDistributionName ();
      //Redefined. Returns the mean value of the distribution.
      virtual double getMeanValue ();
  protected:
      //Redefined. Scales up the given random number x with the uniform distribution 
	  //in [0..1] into a random number with	the uniform distribution in [lower..upper].
      virtual double convert (double x);
  private:
      //The lower bound of the range of random numbers.
      double lower;
      //The upper bound of the range of random numbers.
      double upper;
};

// Class UniformGenerator inline methods
inline UniformGenerator::UniformGenerator (double lowerBound, double upperBound)
      : lower(lowerBound), upper(upperBound) {}
inline String UniformGenerator::getDistributionName (){
	return "Uniform";
}
inline double UniformGenerator::getMeanValue (){
	return (lower+upper)/2.0;
}

#endif
