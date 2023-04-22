#ifndef _PR_EXCEPTIONS_H_
#define _PR_EXCEPTIONS_H_
#include <exception>
using namespace std;

class PRException : public exception {
public:
	PRException() : exception() {};
	PRException(const char* c) : exception(c) {};
};

//             PORT EXCEPTION                   //
class PortNumberException : public PRException {
public:
	PortNumberException() : PRException() {};
	PortNumberException(const char* c) : PRException(c) {};
};

//          COMPAILER EXCEPTION             //
class ConfigException : public PRException {
public:
	ConfigException() : PRException() {};
	ConfigException(const char* c) : PRException(c) {};
};

class FileException : public PRException {
public:
	FileException() : PRException() {};
	FileException(const char* c) : PRException(c) {};
};
class ParenthException : public PRException {
public:
	ParenthException() : PRException() {};
	ParenthException(const char* c) : PRException(c) {};
};
class ImfReadException : public PRException {
public:
	ImfReadException() : PRException() {};
	ImfReadException(const char* c) : PRException(c) {};

};

class WrongFormatException;


//            MEMORY EXCEPTION                   //
class VariableNotFoundException : public PRException {
public:
	VariableNotFoundException() : PRException() {};
	VariableNotFoundException(const char* c) : PRException(c) {};
};

class MemoryParallelWriteException : public PRException {
public:
	MemoryParallelWriteException() : PRException() {};
	MemoryParallelWriteException(const char* c) : PRException(c) {};
};


//        OPERATION EXCEPTION                   //
class SetValueException : public PRException {
public:
	SetValueException() : PRException() {};
	SetValueException(const char* c) : PRException(c) {};
};

//        MACHINE EXCEPTION                   //

class WrongFormatException : public PRException {
public:
	WrongFormatException() : PRException() {};
	WrongFormatException(const char* c) : PRException(c) {};
};


#endif // !_PR_EXCEPTIONS_

