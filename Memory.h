#ifndef _MEMORY_H_
#define _MEMORY_H_
#include "AbstractClasses.h"
#include <string>
#include <list>

//Singleton DP
class Memory: public ModelElement, public ITimedElement {
public:
	static void setParallelW(unsigned int Nw);
	static void setMemWrite(Time t);

	static Memory* Instance();

	void set(std::string varName, double val);
	double get(std::string varName); //Throw if not found

	virtual void accept(Visitor* vis) {};

	virtual void notify(ID);
	
	static Time getDelay();

	virtual void MemClear();

	bool isReady(std::string& var);

	bool isInMemory(std::string& name);

	bool isReady();
protected:
private:
	Memory();

	static unsigned int Nw;

	static Time Mw;

	static unsigned int currentW;

	std::list<Expression> memory;

	std::list<Expression> memoryWrite;
};
#endif // !_MEMORY_H_
