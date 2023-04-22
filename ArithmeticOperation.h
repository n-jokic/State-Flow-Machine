#ifndef _ARITHMETIC_OPERATION_H_
#define _ARITHMETIC_OPERATION_H_
#include "AbstractClasses.h"
#include <list>
//Operation list is in PrTypes.h file

class Addition :public ArithmeticOperation {
public:
	Addition(std::list<Port*> inputPorts, std::list<Port*> outputPort, std::string name, Time T = Addition::opDelay);

	virtual void accept(Visitor* vis) {};

	static void setDelay(Time t);
protected:
	virtual OP init();
	virtual OP operation(OP first, OP second);
private:
	static Time opDelay;
};

class Multiplication : public ArithmeticOperation {
public:
	Multiplication(std::list<Port*> inputPorts, std::list<Port*> outputPort, std::string name, Time T = Multiplication::opDelay);

	virtual void accept(Visitor* vis) {};
	
	static void setDelay(Time t);
protected:
	virtual OP init();
	virtual OP operation(OP first, OP second);
private:
	static Time opDelay;
};

class Power : public ArithmeticOperation {
public:
	Power(std::list<Port*> inputPorts, std::list<Port*> outputPort, std::string name, Time T = Power::opDelay);

	virtual void accept(Visitor* vis) {};
	virtual void process();

	static void setDelay(Time t);
protected:
	virtual OP init() { return 0; };
private:
	static Time opDelay;
};
 
class SetValue : public ArithmeticOperation {
public:
	SetValue(std::list<Port*> inputPorts, std::list<Port*> outputPort,  std::string name, Time T = SetValue::opDelay);

	virtual void accept(Visitor* vis) {};

	virtual void process();

	virtual bool isReady();

protected:
	void setValueNotify();

	virtual OP init() { return 0; };
private:
	static Time opDelay;
};
#endif // !_ARITHMETIC_OPERATION_H_
