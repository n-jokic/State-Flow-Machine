#ifndef _PORT_H_
#define _PORT_H_
#include "AbstractClasses.h"
#include "PRExceptions.h"
#include <iostream>

class IPort : public Port {
public:
	IPort(Expression result):Port(result) {};
private:
protected:
};
class OPort : public Port {
public:
	OPort(Expression result, Port* target = nullptr);
	virtual void send();
	void setTarget(Port* t);
protected:
private:
	Port* target;
};

//Output port inline methods
inline void OPort::send() {
	if (target) target->acceptFlow(getResult());

}
inline void OPort::setTarget(Port * t)
{
	if(t) target = t;
	(t->getExpression()).setStatus(ExspressionStatus::constant);
}


inline OPort::OPort(Expression result, Port * target) : Port(result), target(target)
{
}

#endif // !_PORT_H_

