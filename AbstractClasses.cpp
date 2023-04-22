#include "AbstractClasses.h"
#include "Memory.h"
#include "Machine.h"
#include "PRExceptions.h"
#include "concepts/Event.h"
#include <iostream>
#include <string>
#include <sstream>


Operation::~Operation()
{
	for (auto&i : inputPorts) delete i;
	for (auto&i : outputPorts) delete i;
}



Operation::Operation(Time T) : delay(T)
{
	operationStatus = false;
	processStauts = false;
}


ArithmeticOperation::ArithmeticOperation(std::list<Port*> inputPorts, std::list<Port*> outputPorts, Time T) : Operation(T)
{
	try {
		if (inputPorts.size() != 2 || outputPorts.size() != 1) throw PortNumberException("Arithmetic operation must have 2 input and 1 output port");
		this->inputPorts = inputPorts;
		this->outputPorts = outputPorts;
	}
	catch (PortNumberException&e) {
		std::cerr << e.what() << std::endl;
		throw;
	}
}

void ArithmeticOperation::process()
{
//initialisation
	OP result = init();

	for (auto& i : inputPorts) {
		result = operation(result, i->getResult());
	}

	Event::create(this, getDelay());
	
	outputPorts.front()->acceptFlow(result);

	setPrStatus(true);
}

void ArithmeticOperation::notify(ID)
{
	setValueNotify();

	outputPorts.front()->send();

	Time t = Machine::Instance()->getTime();

	Machine::Instance()->writeLog(getName(),t-getDelay(), t);

	setStatus(true);
}

void ArithmeticOperation::setTarget(Port* setInput)
{
	outputPorts.front()->setTarget(setInput);
	setInput->switchOff();
}


bool Port::isOn() {
	if (getExpression().getStatus() == ExspressionStatus::variable) return Memory::Instance()->isReady(getExpression().getName());
	return onOff;
}


Expression&  Port::getExpression()
{
	return result;
}

Expression::Expression(std::string variable) : variable(variable)
{
	if (variable.c_str()[0] <= '9' && variable.c_str()[0] >= '0') {
	
		this->value = std::stod(variable);
		status = ExspressionStatus::constant;
	}
	else
	{
		this->variable = variable;
		status = ExspressionStatus::variable;
	}
}

OP Expression::getValue()
{
	if (status == ExspressionStatus::constant) return value;
	if (status == ExspressionStatus::variable) return Memory::Instance()->get(variable);
}
