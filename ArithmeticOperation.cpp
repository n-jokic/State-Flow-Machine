#include "ArithmeticOperation.h"
#include "Memory.h"
#include "PRExceptions.h"
#include "concepts/Event.h"
#include <math.h>
#include <string>
#include <iostream>

Time Addition::opDelay = 0;
Time Multiplication::opDelay = 0;
Time Power::opDelay = 0;
Time SetValue::opDelay = Memory::getDelay();

Addition::Addition(std::list<Port*> inputPorts, std::list<Port*> outputPort, std::string name, Time T) :ArithmeticOperation(inputPorts, outputPort, T)
{
	setName((char*)name.c_str());
	setDescr((char*)"+");
	//Addition is left associative
	setAssoc(association::left);
	delay = opDelay;

}

void Addition::setDelay(Time t)
{//Value delay can be changed only once
	static bool flag = true;
	if (flag) {
		Addition::opDelay = t;
		flag = false;
	}
}
void Multiplication::setDelay(Time t)
{//Value delay can be changed only once
	static bool flag = true;
	if (flag) {
		Multiplication::opDelay = t;
		flag = false;
	}
}

void Power::setDelay(Time t)
{//Value delay can be changed only once
	static bool flag = true;
	if (flag) {
		Power::opDelay = t;
		flag = false;
	}
}


OP Addition::init()
{
	return 0;
}

OP Addition::operation(OP first, OP second)
{
	return first+second;
}

Multiplication::Multiplication(std::list<Port*> inputPorts, std::list<Port*> outputPort, std::string name,Time T) :ArithmeticOperation(inputPorts, outputPort, T)
{
	setName((char*) name.c_str());
	setDescr((char*)"*");
	setAssoc(association::left);
	delay = opDelay;
}

OP Multiplication::init()
{
	return 1;
}

OP Multiplication::operation(OP first, OP second)
{
	return first*second;
}

Power::Power(std::list<Port*> inputPorts, std::list<Port*> outputPort, std::string name,Time T) : ArithmeticOperation(inputPorts, outputPort, T)
{
	setName((char*) name.c_str());
	setDescr((char*)"^");
	setAssoc(association::right);
	delay = opDelay;
}

void Power::process()
{
		outputPorts.front()->acceptFlow(pow(
			inputPorts.front()->getResult(),
			inputPorts.back()->getResult()
		));
		Event::create(this, getDelay());
		setPrStatus(true);
}

SetValue::SetValue(std::list<Port*> inputPorts, std::list<Port*> outputPort, std::string name, Time T) : ArithmeticOperation(inputPorts, outputPort, T)
{
	setName((char*) name.c_str());
	setDescr((char*)"=");
	setAssoc(association::right);
	delay = Memory::getDelay();
}

void SetValue::process()
{
	try {
		if (!inputPorts.front()->isVariable()) throw SetValueException("Can't assign value to constant");
		Event::create(this, getDelay());
		outputPorts.front()->acceptFlow(inputPorts.back()->getResult());
		setPrStatus(true);
	}
	catch (SetValueException& e) {
		std::cerr << e.what() << std::endl;
		throw;
	}
}

bool SetValue::isReady()
{
	if (inputPorts.back()->isOn())
		if (Memory::Instance()->isReady()) return true;
	return false;
}

void SetValue::setValueNotify()
{
	Memory::Instance()->set(inputPorts.front()->getVarName(), inputPorts.back()->getResult());
}
