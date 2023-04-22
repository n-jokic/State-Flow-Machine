#include "Machine.h"
#include "Memory.h"
#include "Compailer.h"
#include "ArithmeticOperation.h"
#include "AbstractClasses.h"
#include "Port.h"
#include "PRExceptions.h"
#include "SyntaxTree.h"
#include "PrTypes.h"

#include <string>
#include <sstream>
#include <fstream>
#include "oop_pr.h"



int main(int argc, char *argv[]) {
	if (argc != 3) return 0;
	std::string configuration, program;
	configuration = argv[1];
	program = argv[2];

		try {
			configuration = argv[1];
			program = argv[2];
			if (configuration.empty() || program.empty()) return 0;

			Compailer::Instance()->readConfiguration(configuration)->processFile(program);

			Machine::Instance()->exec(program);
		}
		catch (PRException& e)
		{

			return 0;

		}
	
	return 1;
}