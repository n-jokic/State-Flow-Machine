#ifndef _MACHINE_H_
#define _MACHINE_H_
#include "AbstractClasses.h"
#include "concepts/Sched.h"
#include <string>
#include <vector>
#include <list>

struct LogComparator;
class SyntaxTree;
class TreeNode;

struct Log {

private:
	friend struct LogComparator;
	friend class Machine;
	Log(std::string s, Time t1, Time t2);

	Time t1, t2;
	int num;
};

struct LogComparator
{
	// Compare 2  objects 
	bool operator ()(const Log & log1, const Log & log2)
	{
		if (log1.t1 == log2.t1)
			if (log1.t2 != log2.t2) return log1.t2 < log2.t2;
			else return log1.num < log2.num;
		
		return log1.t1 < log2.t1;
	}
};
//Singleton DP
class Machine {
public:
	static Machine* Instance();
	void exec(std::string& file);

	Time getTime();

	void writeLog(std::string s, Time,Time);

	void clearLog();

	std::string getLog();
private:
	Machine();

	std::list<Log> log;
	
	void clearLists(std::list<SyntaxTree*>& operationLst,
	std::list<TreeNode*>& executionLst);

	Scheduler* scheduler;

	std::list<std::string> splitImf(std::fstream& imf);

	void eraseSubStr(std::string & mainStr, const std::string & toErase);
};

#endif // !_MACHINE_H_

