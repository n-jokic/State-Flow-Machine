#include "SyntaxTree.h"
#include "Memory.h"
#include "AbstractClasses.h"
#include "ArithmeticOperation.h"
#include "Port.h"
#include "PRExceptions.h"
#include "PrTypes.h"
#include <list>
#include <vector>
#include <stack>
#include <string>
#include <sstream>

TreeNode::TreeNode(Operation * op)
{
	operation = op;
	left = right = back = nullptr;
}

inline bool TreeNode::checkMem()
{
	std::string firstPortName = operation->inputPorts.front()->getVarName();
	std::string secondPortName= operation->inputPorts.back()->getVarName();
	bool firstPort = operation->inputPorts.front()->getExpression().getStatus();
	bool secondPort = operation->inputPorts.back()->getExpression().getStatus();

	if (!firstPort) {
		if (!secondPort) return true;
		return Memory::Instance()->isInMemory(secondPortName);
		}
	if (!secondPort) {
		if (!firstPort) return true;
		return Memory::Instance()->isInMemory(firstPortName);
	}

	return Memory::Instance()->isInMemory(secondPortName) && Memory::Instance()->isInMemory(firstPortName);
}

TreeNode::TreeNode(Operation & op)
{
	left = right = back = nullptr;
	operation = &op;
}

TreeNode::TreeNode(Operation && op)
{
	left = right = back = nullptr;
	operation = &op;
}

TreeNode::~TreeNode()
{
	if (back)
		if (back->left == this) back->left = nullptr;
		else
			if (back->right == this) back->right = nullptr;
	left = right = back = nullptr;
	delete operation;
}


void TreeNode::addLeft(Operation* child) {
	left = new TreeNode(child);
	left->setTarget(this->getOperationInfo()->inputPorts.front());
	left->back = this;
}

void TreeNode::addRight(Operation* child) {
	right = new TreeNode(child);
	right->setTarget(this->getOperationInfo()->inputPorts.back());
	right->back = this;
}



SyntaxTree::SyntaxTree(std::string imf)
{
	auto lst = std::list<Operation*>();

	lst = readFormat(imf);

	makeTree(lst);
}

SyntaxTree::~SyntaxTree()
{
	if (root != nullptr) {
		auto current = root;
		std::stack<TreeNode*> myStack;

		do {
			if (current != nullptr) {
				myStack.push(current);
				current = current->getLeft();
			}

			if (current == nullptr) {
				current = myStack.top()->getRight();
				if (myStack.top() == root) root = nullptr;
				delete myStack.top();
				myStack.pop();
			}
		} while (current != nullptr || myStack.size() > 0);
	}
	
}

bool SyntaxTree::checkMem()
{
	{
		if (root == nullptr) return true;
		auto current = root;
		std::stack<TreeNode*> myStack;

		do {
			if (current != nullptr) {
				myStack.push(current);
				current = current->getLeft();
			}

			if (current == nullptr) {
				current = myStack.top();

				if (!current->checkMem()) return false;

				current = current->getRight();
				myStack.pop();
			}
		} while (current != nullptr || myStack.size() > 0);

		return true;
	}
	
}

std::list<TreeNode*> SyntaxTree::findReady()
{
	auto outputLst = std::list<TreeNode*>();
	if (root == nullptr) return outputLst;
	auto current = root;
	std::stack<TreeNode*> myStack;

	do {
		if (current != nullptr) {
			myStack.push(current);
			current = current->getLeft();
		}

		if (current == nullptr) {
			current = myStack.top();

			if (current->isReady()) {
				outputLst.push_back(myStack.top());

				if (root == current) {
					root = nullptr;
				}
				
				current->remove();
			}

			current = current->getRight();
			myStack.pop();
		}
	} while (current != nullptr || myStack.size() > 0);

	return outputLst;
}

inline std::list<Operation*> SyntaxTree::readFormat(std::string imf)
{
	try {
		//(num) token1 token2/n
		auto token1 = std::string(), token2 = std::string(), operation = std::string(), name = std::string();
		if (imf.size() == 0) throw WrongFormatException("Bad format of imf file");
		auto ss = std::stringstream(imf);
		std::string op;
		int val, flag = 0;
		auto outputLst = std::list<Operation*>();

		do {
			switch (flag)
			{
				//left parenthesis num and right parenthesis
			case 0: ss >> op; name += op;  flag++; break;
				//reading operation
			case 1: ss >> op; operation += op; flag++; break;
				//reading first token
			case 2: ss >> op;  token1 += op; flag++; break;
				//reading second token
			case 3: ss >> op; token2 += op; flag++; break;
				//Prepearing for next reading
			case 4: flag = 0;
			}
			if (!flag) {
				Port* port1 = new IPort(Expression(token1)), *port2 = new IPort(Expression(token2)), *port3 = new OPort(Expression("0"));
				if (operation == std::string(1, '=')) outputLst.push_back(new SetValue({ port1, port2 }, { port3 }, name));
				if (operation == std::string(1, '^')) outputLst.push_back(new Power({ port1, port2 }, { port3 }, name));
				if (operation == std::string(1, '+')) outputLst.push_back(new Addition({ port1, port2 }, { port3 }, name));
				if (operation == std::string(1, '*')) outputLst.push_back(new Multiplication ({ port1, port2 }, { port3 }, name));
				name.clear();
				token1.clear();
				token2.clear();
				operation.clear();
			}
		} while (!ss.eof());
		return outputLst;
	}
	catch (WrongFormatException& e) {
		throw;
	}
}

void SyntaxTree::makeTree(std::list<Operation*> formatedImf)
{
	//opeartion = is at the end of formatedImf list
	root = new TreeNode(formatedImf.back());

	std::string varName = root->getOperationInfo()->inputPorts.front()->getVarName();
	if (Memory::Instance()->isInMemory(varName)) throw WrongFormatException("Multiple value assignment");
	Memory::Instance()->set(varName, 0);

	formatedImf.pop_back();
	if (formatedImf.empty()) return;

	auto current = root;
	std::stack<TreeNode*> myStack;
	std::string port1, port2;

	do {
		if (formatedImf.empty()) break;
		if (current != nullptr) {
			port1 = current->getOperationInfo()->inputPorts.front()->getVarName();
			port2 = current->getOperationInfo()->inputPorts.back()->getVarName();

			if (port1.c_str()[0] == '(') {
				auto i = formatedImf.end();
				do {
					i--;
					if ((*i)->getName() == port1) { current->addLeft((*i)); formatedImf.erase(i); break; }
				} while (i != formatedImf.begin());
			}
	
			if (port2.c_str()[0] == '(') {
				auto i = formatedImf.end();
				do {
					i--;
					if ((*i)->getName() == port2) { current->addRight((*i)); formatedImf.erase(i); break; }
				} while (i != formatedImf.begin());
			}
				
				
			myStack.push(current);
			current = current->getLeft();
		}

		if (current == nullptr) {
			current = myStack.top()->getRight();
			myStack.pop();
		}
	} while (current != nullptr || myStack.size() > 0);
	
}
