//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#include "Visitor.h"
#include "UniRndGen.h"
#include "Switch1to3.h"

// Class Switch1to3 methods
Switch1to3::Switch1to3 (double leftTurnProb, double rightTurnProb)
      : ltProb(0.0), rtProb(0.0), leftTarget(0), rightTarget(0), rndGen(new UniformGenerator()){
		  setProbabilities(leftTurnProb,rightTurnProb);
}
Switch1to3::~Switch1to3 (){
	delete rndGen;
}
void Switch1to3::accept (Visitor* vis){
	if (vis) vis->visitSwitch1to3(this);
}
void Switch1to3::process (){
	if (rndGen==0) {
		send();
		return;
	}
	double rnd = rndGen->getRandom();
	if (rnd<ltProb) {
		if (leftTarget) leftTarget->acceptFlow();
		return;
	}
	if (rnd<ltProb+rtProb) {
		if (rightTarget) rightTarget->acceptFlow();
		return;
	}
	send();
}
void Switch1to3::setProbabilities (double leftTurnProb, double rightTurnProb){
	if (leftTurnProb>=0.0 && leftTurnProb<=1.0 &&
		rightTurnProb>=0.0 && rightTurnProb<=1.0 &&
		leftTurnProb+rightTurnProb<=1.0) {
		ltProb = leftTurnProb;
		rtProb = rightTurnProb;
	}
}
