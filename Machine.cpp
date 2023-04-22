#include "Machine.h"
#include "Compailer.h"
#include "Memory.h"
#include "PrTypes.h"
#include "PRExceptions.h"
#include "SyntaxTree.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

Machine * Machine::Instance()
{
	static Machine machine = Machine();
	return  &machine;
}

void Machine::exec(std::string& file)
{
	fstream imf, log;


	imf.open(file.c_str(), ios_base::in);

	eraseSubStr(file, ".imf");
	file += ".log";
	log.open(file, ios_base::out);
	log.clear();

	try {
		std::list<SyntaxTree*> operationLst;
		std::list<TreeNode*> executionLst;
		std::list<std::string> formatedImf;

		if (!log || !imf) throw FileException("File reading error");
		formatedImf = splitImf(imf);
		if (formatedImf.empty()) throw WrongFormatException("Imf file is empty");

		for (auto&i : formatedImf) 
			operationLst.push_back(new SyntaxTree(i));
		
		for(auto&i : operationLst)
			if (!i->checkMem()) throw WrongFormatException("Variable must have assigned value");

		Memory::Instance()->MemClear();

		do {
			for (auto& i : operationLst) 
				for (auto&j : (i)->findReady()) executionLst.push_back(j);
			
			for (auto&i : executionLst) 
				i->process();

			scheduler->processNow();
			
			if (!operationLst.empty() && executionLst.empty()) throw WrongFormatException("Can not finish calculation");
			clearLists(operationLst, executionLst);
		} while (!operationLst.empty());

		
		log << getLog();

		clearLog();
		Memory::Instance()->MemClear();
	}
	catch (PRException& e) {
		std::cerr << e.what() << std::endl;
		clearLog();
		Memory::Instance()->MemClear();
		throw;
	}

	if (imf.is_open()) imf.close();
	if (log.is_open()) log.close();
}

Time Machine::getTime()
{
	return scheduler->getCurTime();
}

Machine::Machine()
{
	scheduler = Scheduler::Instance();
}

void Machine::clearLists(std::list<SyntaxTree*>& operationLst, std::list<TreeNode*>& executionLst)
{

	for (auto i = executionLst.begin(); i != executionLst.end(); i++)
		if ((*i)->isDone()) {
			delete *i;
			executionLst.erase(i);
			if(!executionLst.empty()) i = executionLst.begin();
			else break;
		}
	if (!executionLst.empty()) {
		auto i = executionLst.begin();
		if ((*i)->isDone()) {
			delete *i;
			executionLst.erase(i);
		}
	}

	for (auto i = operationLst.begin(); i != operationLst.end(); i++)
		if ((*i)->isOver()) {
			delete (*i);
			operationLst.erase(i);
			if (!operationLst.empty()) i = operationLst.begin();
			else break;
		};
	if (!operationLst.empty()) {
		auto i = operationLst.begin();
		if ((*i)->isOver()) {
			delete *i;
			operationLst.erase(i);
		}
	}
}

//Returns imf file split in setValue segments
std::list<std::string> Machine::splitImf(std::fstream& ss)
{
	bool flag = true, flag2 =true;
	std::size_t pos = 0;
	auto part = std::string(), op = std::string();
	auto outputLsr = std::list<std::string>();
	//(num)_operator_token_token/n _ is blank
	while (!ss.eof()) {
		std::string line;
		std::getline(ss, line);
		part += line + '\n';
		if(part.find('=', pos) != std::string::npos) {
			outputLsr.push_back(part);
			part.clear();
			pos = 0;
			continue;
		}
		pos += line.size();
	}

	return outputLsr;
}

void Machine::eraseSubStr(std::string & mainStr, const std::string & toErase)
{
	
		// Search for the substring in string
		size_t pos = mainStr.find(toErase);

		if (pos != std::string::npos)
		{
			// If found then erase it from string
			mainStr.erase(pos, toErase.length());
		}
	
}

void Machine::writeLog(std::string s, Time t1, Time t2)
{
	this->log.push_back(Log(s, t1, t2));
}

void Machine::clearLog()
{
	log.clear();
}

std::string Machine::getLog()
{
	auto outputStr = std::string();
	log.sort(LogComparator());
	
	for (auto&i : log)
		outputStr += '(' + std::to_string(i.num) + ')' + '\t' +
		std::to_string(i.t1) + 'n' + 's' + '/' + std::to_string(i.t2)
		+ 'n' + 's' + '\n';
	
	return outputStr;
}

Log::Log(std::string s, Time t1, Time t2): t1(t1), t2(t2)
{//format: (num)
	auto temp = std::string();
	const char* c = s.c_str();
	c++;
	while (*c != ')') {
		temp += c;
		c++;
	}
	num = std::stoi(temp);
}
