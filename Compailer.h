#ifndef _COMPAILER_H_
#define _COMPAILER_H_
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "PrTypes.h"


class Compailer {
public:
	//Singleton DP
	static Compailer* Instance();
	void processFile(std::string& fileName);
	Compailer* readConfiguration(std::string& fileName);
protected:
private:

	double readNum(std::string s);
	std::list<std::string> process(std::istream& in);

	void eraseSubStr(std::string & mainStr, const std::string & toErase);

	bool isExpression(std::string c);
	bool isOperator(std::string c);
	bool isOperatorStackReady(std::string top,std::string c);
	bool isLeftParenth(std::string c);
	bool isRightParenth(std::string c);
	bool isNum(char c);

	std::string  rawImfToImf(std::list<std::string>);

};


class Token {
public:
	std::string getToken();

	std::vector<std::string> splitToken();

	friend std::ostream& operator<<(std::ostream&, Token const&);
	friend std::istream& operator>>(std::istream&, Token&);

private:
	std::string value;
};


//Inline compailer methods
inline bool Compailer::isNum(char c)
{
	switch (c) {
	case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.' : return true;
	default: return false;
	}
}

inline bool Compailer::isExpression(std::string c)
{
	return !isOperator(c);
}


#endif // !_COMPAILER_H_
