//	* Copyright (C) 2003 by Dragan Milicev *
//	* All rights reserved *

#ifndef Visitor_h
#define Visitor_h 

class Model;

class UniformGenerator;
class ExpGenerator;

class FlowSource;
class FlowSink;
class Pipe;
class QueuedServer;
class Switch1to3;
class CrossSemaphore;

class SignalGenerator;
class Probe;
class LogicCircuit;

//Abstract generalizations of all kinds of visitors (i.e. model traversal strategies). Visitor DP.

class Visitor{
  public:
      //Visits the specific kind of object. Visitor DP.
      virtual void visitModel (Model* e);
      virtual void visitUniformGenerator (UniformGenerator* e);
      virtual void visitExpGenerator (ExpGenerator* e);
	  virtual void visitFlowSource (FlowSource* e);
      virtual void visitFlowSink (FlowSink* e);
      virtual void visitPipe (Pipe* e);
      virtual void visitQueuedServer (QueuedServer* e);
      virtual void visitSwitch1to3 (Switch1to3* e);
      virtual void visitCrossSemaphore (CrossSemaphore* e);

	  // Digital circuit simulator specific methods.
	  virtual void visitSignalGenerator (SignalGenerator *e);
	  virtual void visitProbe (Probe *e);
	  virtual void visitLogicCircuit (LogicCircuit *e);
};

// Class Visitor inline methods (all are hook methods)
inline void Visitor::visitUniformGenerator (UniformGenerator* e) {}
inline void Visitor::visitExpGenerator (ExpGenerator* e) {}
inline void Visitor::visitFlowSource (FlowSource* e) {}
inline void Visitor::visitFlowSink (FlowSink* e) {}
inline void Visitor::visitPipe (Pipe* e) {}
inline void Visitor::visitQueuedServer (QueuedServer* e) {}
inline void Visitor::visitSwitch1to3 (Switch1to3* e) {}
inline void Visitor::visitCrossSemaphore (CrossSemaphore* e) {}

inline void Visitor::visitSignalGenerator (SignalGenerator *e) {}
inline void Visitor::visitProbe (Probe *e) {}
inline void Visitor::visitLogicCircuit (LogicCircuit *e) {}

#endif

