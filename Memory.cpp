#include "Memory.h"
#include "concepts/Event.h"
#include "PRExceptions.h"
#include <iostream>

Time Memory::Mw = 0;
unsigned int Memory::currentW = 0;
unsigned int Memory::Nw = 1;

void Memory::notify(ID)
{
	//All writes are finished, thus currentW is 0
	Memory::currentW = 0;

}

Time Memory::getDelay()
{
	return Memory::Mw;
}

void Memory::MemClear()
{
	memory.clear();
}

bool Memory::isReady(std::string& var)
{
	for (auto&i : memory) if (i.getName() == var) return true;
	return false;
}

bool Memory::isInMemory(std::string& name)
{
	for (auto& i : this->memory)
		if (i.getName() == name) return true;
	return false;
}

bool Memory::isReady()
{
	currentW++;
	return currentW - 1 < Nw;
}

Memory::Memory() {
}

void Memory::setParallelW(unsigned int Nw)
{ //Value Nw can be changed only once
	static bool flag = true;
	if (flag) {
		if(Nw) Memory::Nw = Nw;
		flag = false;
	}
}

void Memory::setMemWrite(Time t)
{//Value Mw can be changed only once
	static bool flag = true;
	if (flag) {
		Memory::Mw = t;
		flag = false;
	}
}

Memory * Memory::Instance()
{
	static Memory mem = Memory();
	return &mem;
}

void Memory::set(std::string varName, double val)
{
	bool flag = true;
	for (auto&i : memory) 
		if (i.getName() == varName) {
			i.setValue(val);
			flag = false;
		}

	if (flag) { 
		memory.push_back(Expression(varName));
		memory.back().setValue(val);
	}

	currentW = 0;

}

double Memory::get(std::string varName)
{	
	try {
		for (auto&i : memory)
			if (i.getName() == varName) {
				return i.getValue();
			}
		throw VariableNotFoundException("Variable not found in memory");
	}
	catch (VariableNotFoundException& e) {
		std::cerr << e.what() << std::endl;
		throw;
	}
}
