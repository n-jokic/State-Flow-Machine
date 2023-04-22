//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#include <cmath>
#include "Visitor.h"
#include "UniRndGen.h"
#include "RndGen.h"
#include "ExpRndGen.h"

const unsigned long urndSeed = 2901970UL;
unsigned long RandomGenerator::urndNum = urndSeed;

// Class RandomGenerator methods
double RandomGenerator::getRandom (){
	double r = urnd();
	return convert(r);
}
double RandomGenerator::urnd (){
	urndNum = (314159261UL * urndNum + 907633385UL); // % 4294967296UL; provided that unsigned long is 32 bits
	return urndNum / 4294967296.0;
}

// Class UniformGenerator methods
void UniformGenerator::accept (Visitor* vis){
	if (vis) vis->visitUniformGenerator(this);
}
double UniformGenerator::convert (double x){
	return x*(upper-lower)+lower;
}

// Class ExpGenerator methods
void ExpGenerator::accept (Visitor* vis){
	if (vis) vis->visitExpGenerator(this);
}

double ExpGenerator::convert (double x){
	if (x>=1.0) x=0.0;
	return -mean*log(1.0-x);
}
