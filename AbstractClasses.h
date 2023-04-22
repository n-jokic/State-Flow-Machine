#ifndef _ABSTRACT_CLASSES_H_
#define _ABSTRACT_CLASSES_H_

#include "concepts/AbstractConcepts.h"
#include "concepts/Interfaces.h"
#include "PrTypes.h"

#include <list>
#include <string>

class TreeNode;

//Operation can be left or right associative or both
enum association { left, right, both };

//Expression status
enum ExspressionStatus { constant = 0, variable };


class Expression {
public:
	Expression(std::string variable = std::string());

	OP getValue();

	std::string& getName();

	ExspressionStatus getStatus();
protected:
	friend class Port;
	friend class OPort;
	void setStatus(ExspressionStatus stat);
private:
	friend class Memory;

	void setValue(OP val);

	ExspressionStatus status;
	std::string variable;
	OP value = 0;
};

//Recives/sends data from/to  operation
class Port : public IFlowSource {
public:
	virtual void switchOff();
	//Swithes port on-> ready for reading
	virtual void switchOn();
	//Return true if port is ready to send data
	virtual bool isOn();
	//Hook
	virtual void accept(Visitor* vis) {};

	virtual void acceptFlow(OP result);

	virtual OP getResult();

	virtual void send() {};

	virtual bool isVariable();

	virtual std::string getVarName();

	Expression&  getExpression();

protected:
	friend class ArithmeticOperation;

	virtual void setTarget(Port* t) {};

	Port(Expression result) : onOff(true), result(result) {};

private:
	bool onOff;

	Expression result;
};

//Abstract operation, has n inputs and n outputs
class Operation : public ControlElement, public ITimedElement {
public:
	~Operation();

	virtual association getAssoc();

	//Hook, operation processing
	virtual void process() = 0;

	Time getDelay();

	virtual void notify(ID) = 0;

	virtual bool isReady();

	virtual bool isDone();

	virtual bool canProcess();

protected:
	friend class TreeNode;
	friend class SyntaxTree;

	virtual void setTarget(Port* input) = 0;

	Operation(Time T);

	virtual void setAssoc(association assoc);

	std::list<Port*> inputPorts;

	std::list<Port*> outputPorts;

	Time delay;

	void setStatus( bool b);
	void setPrStatus(bool b);
private:
	bool processStauts;

	bool operationStatus;

	association assoc = both;
};


class ArithmeticOperation : public Operation {
public:
	ArithmeticOperation(std::list<Port*> inputPorts, std::list<Port*> outputPorts, Time T);

	virtual void process();

	virtual void notify(ID);
protected:
	virtual OP init() = 0;


	virtual void setTarget(Port* setInput);

	virtual OP operation(OP, OP) { return 0; };
private:
	virtual void setValueNotify() {};
};


inline void Port::switchOff()
{
	onOff = false;
}

//Class Port inline methods
inline void Port::switchOn() {
	onOff = true;
}
inline void Port::acceptFlow(OP result)
{
	this->result.value = result;
	onOff = true;
}
inline OP Port::getResult() {
	return result.getValue();
}

inline bool Port::isVariable() {
	return result.getStatus() == ExspressionStatus::variable;
}

inline std::string Port::getVarName()
{
	return result.getName();
}


//Class Operation iline methods
inline void Operation::setAssoc(association assoc)
{
	this->assoc = assoc;
}
inline void Operation::setStatus(bool b)
{
	Operation::operationStatus = b;
}
inline void Operation::setPrStatus(bool b)
{
	this->processStauts = b;
}
inline association Operation::getAssoc()
{
	return assoc;
}
inline Time Operation::getDelay()
{
	return delay;
}
inline void Operation::notify(ID)
{
	process();
}

inline bool Operation::isReady()
{
	for (auto i : inputPorts) if (!i->isOn()) return false;
	return true;
}

inline bool Operation::isDone()
{
	return Operation::operationStatus;
}

inline bool Operation::canProcess()
{
	return processStauts;
}

//Class Expression inline methods
inline std::string& Expression::getName()
{
	return variable;
}

inline ExspressionStatus Expression::getStatus()
{
	return status;
}

inline void Expression::setStatus(ExspressionStatus stat)
{
	status = stat;
}

inline void Expression::setValue(OP val) {
	value = val;
	status = ExspressionStatus::constant;
}

#endif // !_ABSTRACT_CLASSES_H_

