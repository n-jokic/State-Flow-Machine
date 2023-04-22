#include "Compailer.h"
#include "ArithmeticOperation.h"
#include "Memory.h"
#include "PRExceptions.h"
#include "PrTypes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include <list>
#include <cctype>

constexpr auto OP_NUM = 4;

#define SEPARATOR '.'

//Operation priority
std::vector<string> OperatorList = { "=", "+" , "*" , "^" };
std::vector<string> RightAssociative = { "=", "^" };
std::vector<string> Paretnhesis = { "(", ")" };

bool Compailer::isOperator(std::string c)
{
	for (auto&i : OperatorList)
		if (i == c) return true;
	return false;
}

bool Compailer::isLeftParenth(std::string c)
{
	return c == Paretnhesis[0];
}
bool Compailer::isRightParenth(std::string c)
{
	return c == Paretnhesis[1];
}

Compailer * Compailer::Instance()
{
	static Compailer instance = Compailer();
	return &instance;
}

void Compailer::processFile(std::string& fileName)
{
	std::ifstream inputFile;
	inputFile.open(fileName);
	if(!inputFile.is_open()) throw FileException("Wrong file extension");
	if (fileName.find(".txt") == std::string::npos) throw FileException("Wrong file extension");
	//inputFile.clear();
	
	eraseSubStr(fileName, ".txt");
	fileName += ".imf";
	std::ofstream imfFile;
	imfFile.open(fileName);
	imfFile.clear();
	
	try {

		if (!inputFile ||!imfFile) throw FileException("File reading error"); //check imf

		std::list<std::string> rawImf = process(inputFile);

		imfFile << rawImfToImf(rawImf);

	}
	catch (FileException& e) {
		std::cerr << e.what() << std::endl;
		throw;
	}
	catch (ImfReadException& e) { 
		std::cerr << e.what() << std::endl; 
		throw; 
	}
	catch (ParenthException& e) { 
		std::cerr << e.what() << std::endl; 
		throw;
	}

	imfFile.close();
	inputFile.close();
}
Compailer* Compailer::readConfiguration(std::string& fileName)
{
	Time Ta= 0, Tm =0, Te =0, Tw =0, Nw =1;
	int count = 0;
	std::ifstream config;
	std::string line;
	config.open(fileName);

	try {
		if (!config) throw ConfigException("Config opening error");

		while (!config.eof()) {
			std::getline(config, line);

			if (line.find("Ta") != std::string::npos) { Ta = readNum(line); }
			if (line.find("Tm") != std::string::npos) { Tm = readNum(line); }
			if (line.find("Te") != std::string::npos) { Te = readNum(line); }
			if (line.find("Tw") != std::string::npos) { Tw = readNum(line); }
			if (line.find("Nw") != std::string::npos) { Nw = readNum(line); }
		}

	}
	catch (ConfigException& e) {
		std::cerr << e.what() << std::endl;
	}
	if (!Nw) Nw = 1;

	Addition::setDelay(Ta);
	Multiplication::setDelay(Tm);
	Power::setDelay(Te);
	Memory::setMemWrite(Tw);
	Memory::setParallelW(Nw);

	config.close();
	return this;
}
double Compailer::readNum(std::string s)
{
	const char* c = s.c_str();
	std::string temp;
	bool flag = true;
	bool flag2 = true;

	for (auto i = 0; i != s.size(); i++) 
		if (std::isdigit(c[i]) || c[i] == SEPARATOR)
		temp += c[i];
		
	return std::stod(temp);
}

std::list<std::string> Compailer::process(std::istream& in)
{
	try {
		std::list<std::string> Output = std::list<std::string>();
		std::stack<std::string>operatorStack = std::stack<std::string>();
		auto line = std::string();
		auto tokens = std::vector<std::string>();

		Token token;
		//Reads one line at the time from input file -> Shunt Yard Algorithm
		while (!in.eof()) {
			std::list<std::string> outputList = std::list<std::string>();
			//token reads one line from input file
			in >> token;

			tokens = token.splitToken();
			for (auto&i : tokens) {
				
				//If token is expresion (variable or int) then push it to output queue
				if (isExpression(i)) outputList.push_back(i);

				if (isOperator(i)) {
					//Checks serval conditions for pushing operators from operatorStack to outputList
					if (!operatorStack.empty()) {
						std::string other = operatorStack.top();
						while (isOperator(other) && isOperatorStackReady(i, other)) {
							outputList.push_back(other);
							operatorStack.pop();

							if (!operatorStack.empty())
								other = operatorStack.top();
							else
								break;
						}
					}
					operatorStack.push(i);
				}

				if (isLeftParenth(i)) operatorStack.push(i);

				//Looks for left parenthesis, parenthesis have highest priority
				if (isRightParenth(i)) {
					while (!isLeftParenth(operatorStack.top())) {
						if (operatorStack.empty()) throw ParenthException("One parenthesis is missing");
						outputList.push_back(operatorStack.top());
						operatorStack.pop();
					}
					//Pop left parenthesis
					if (operatorStack.empty()) throw ParenthException("One parenthesis is missing");
					operatorStack.pop();
				}
			}



			while (!operatorStack.empty()) {
				if (isLeftParenth(operatorStack.top())) throw ParenthException("One parenthesis is missing");
				outputList.push_back(operatorStack.top());
				operatorStack.pop();
			}

			Output.insert(Output.end(), outputList.begin(), outputList.end());
		}
		
		return Output;
	}
	catch (ParenthException &e) {
		std::cerr << e.what() << std::endl;
		throw;
	}
	catch (ImfReadException &e) {
		std::cerr << e.what() << std::endl;
		throw;
	}
}

void Compailer::eraseSubStr(std::string & mainStr, const std::string & toErase)
{
	// Search for the substring in string
	size_t pos = mainStr.find(toErase);

	if (pos != std::string::npos)
	{
		// If found then erase it from string
		mainStr.erase(pos, toErase.length());
	}
}


bool Compailer::isOperatorStackReady(std::string c, std::string top)
{
	if (top == Paretnhesis[0]) return false;
	int first = 0, second = 0;

	for (auto&i : OperatorList) {
		if (i ==top) break;
		first++;
	}


	for (auto&i : OperatorList) {
		if (i == c) break;
		second++;
	}

	//Operator on top of the OperatorStack has greater priority than new opeator
	if (first > second) return true;
	//If they have same priority then true is returned
	//if both are left associative, i.e. + and * 
	if (first == second) {

		for(auto& i : RightAssociative)
		if (top == i) return false;

		return true;
	}
	//Operator on top of the OperatorStack has lower priority than new opeator
	 return false;
}



std::string Compailer::rawImfToImf(std::list<std::string> rawImf)
{
	try {
		if (rawImf.empty()) return std::string();

		int counter = 1;
		std::string imf = std::string();

		for (auto iter = rawImf.begin(); iter != rawImf.end(); iter++) {
			std::string pos = std::string(), temp = std::string();
			auto prev = iter;
			int count = 0;

			if (isExpression(*iter) || isLeftParenth(*iter)) continue;
			//iterator is pointing at operator, all operators are binary
			//rawImf : 3x2^*2+z=
			//iter is pointing to ^ now

			pos += '(';
			pos += std::to_string(counter);
			pos += ')';
			iter--;
			if (iter == rawImf.begin()) throw ImfReadException("Operation has wrong number of arguments");
			iter--;
			//iter is pointing to x

			while (iter != rawImf.end() && count != 2) {
				count++;
				//temp is holding deleted stings, temp: x 2
				temp += *iter; temp += ' ';
				prev = iter++;
				rawImf.erase(prev);
			}

			//previous 2  are removed : 3^*2+z=
			//iter is poining at ^ again

			if (count != 2) throw ImfReadException("Operation has wrong number of arguments");
			
			// (num = 1), imf : (1) ^ x 2\n
			imf += pos; imf += ' '; imf += *iter; imf += ' '; imf += temp; imf += '\n';

			//Removes operator from rawImf, rawImf : 3*2+z=
			//and relaces it with (num), rawImf : 3(1)*2+z=
			iter->assign(pos);
			counter++;
		}
		return imf;
	}
	catch (ImfReadException&e) {
		std::cerr << e.what() << std::endl;
		throw;
	}
	catch (WrongFormatException&e) {
		std::cerr << e.what() << std::endl;
		throw;
	}

}

std::ostream & operator<<(std::ostream & str, Token const & t)
{
	return str << t.value;
}

std::istream & operator>>(std::istream &str, Token &t)
{
	if (!str) return str;
	t.value.clear();
	char c = ' ';
	while (!str.eof() && c != '\n') {
		if ((c = str.get()) != '\n' && !str.eof()) t.value += c;
	}
}

std::string Token::getToken()
{
	return value;
}

std::vector<std::string> Token::splitToken()
{
	std::vector<std::string> outputVctr;
	std::list<std::size_t> positions;
	int size;

	std::size_t pos;
	//Operator =
	if ((pos = value.find(OperatorList[0])) == std::string::npos) throw WrongFormatException("Operator = is missing");
	if((pos = value.find(OperatorList[0], pos+1)) != std::string::npos) throw WrongFormatException("Only single operator = is allowed");

	//find position of all operators in token
	for (auto&i : OperatorList) {
		pos = value.find(i, 0);
		do {
			while (pos != std::string::npos)
			{
				positions.push_back(pos);
				pos = value.find(i, pos + 1);
			}
		} while (pos != std::string::npos);
	}
	//Sorts positions
	positions.sort();
	if(positions.front() == 0)throw WrongFormatException("Can't assign value to nothing-> variable before operator = is missing");
	std::size_t j = 0;
	
	//Find all tokens between operators
	for (auto i = positions.begin(); i != positions.end(); i++) {
		auto num= std::string(), var = std::string();

		while (j < *i) {
			if (value[j] == ' ') { j++; continue; }
			//reads number : 231.412
			if (std::isdigit(value[j]) || value[j] == SEPARATOR) { num += value[j]; }

			//Reads variable
			if (std::isalpha(value[j])) { var += value[j]; }
			j++;
		}

		//Only one token can be between two operators, thus one and only one string is not empty
		if(var.empty() && num.empty()) throw WrongFormatException("Only one token can be between two operators");
		if(!var.empty() && !num.empty()) throw WrongFormatException("At least one token must be between two operators");

		if(!var.empty()) outputVctr.push_back(var);
		if (!num.empty()) outputVctr.push_back(num);

		for (auto&i : OperatorList) {
			if (value.find(i, j - 1) == j) {
				outputVctr.push_back(i); 
				size = i.size(); 
				break;
			}
		}
	}

	//Only last token is missing.
	auto temp = std::string();
	for (auto i = positions.back() + size; i != value.size(); i++) {
		if (value[i] == ' ') continue;
		temp += value[i];
	}
	if(temp.empty()) throw WrongFormatException("Last token is missing");
	
	outputVctr.push_back(temp);
	return outputVctr;
}
