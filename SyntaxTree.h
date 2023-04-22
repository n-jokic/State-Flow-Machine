#ifndef _SYNTAX_TREE_H_
#define _SYNTAX_TREE_H_
#include "AbstractClasses.h"
#include <string>
#include <list>
//TODO:: Verovatno nema potrebe za stablom

class TreeNode {
public:
	TreeNode(Operation* op);
	TreeNode(Operation& op);
	TreeNode(Operation&& op);
	~TreeNode(); 

	Operation* getOperationInfo();

	void addLeft(Operation* child); 
	void addRight(Operation* child);

	TreeNode* getLeft();
	TreeNode* getRight();
	TreeNode* getBack();


	void process();
	bool isReady();

	bool isDone();

	void remove();

	bool checkMem();
private:
	void setTarget(Port* targ);

	Operation* operation;

	TreeNode *left , *right , *back ;
};


class SyntaxTree {
public:
	SyntaxTree(std::string imf);
	~SyntaxTree();
	
	bool checkMem();

	std::list<TreeNode*> findReady();
	bool isOver();
private:
	std::list<Operation*> readFormat(std::string imf);
	void makeTree(std::list<Operation*> formatedImf);
	TreeNode* root = nullptr;
};
//Class TreeNode inline methods

inline Operation* TreeNode::getOperationInfo(){
	return operation;
}

inline TreeNode * TreeNode::getLeft()
{
	return left;
}

inline TreeNode * TreeNode::getRight()
{
	return right;
}

inline TreeNode * TreeNode::getBack()
{
	return back;
}


inline void TreeNode::process()
{
	if(!operation->canProcess()) 
		operation->process();
}

inline bool TreeNode::isReady()
{
	return operation->isReady();
}

inline bool TreeNode::isDone()
{
	return operation->isDone();
}

inline void TreeNode::remove()
{
		if (back) {
			if (back->left == this)
				back->left = nullptr;
			if (back->right == this)
				back->right = nullptr;
		}
	
}

inline void TreeNode::setTarget(Port * targ)
{
	operation->setTarget(targ);
}

//Class Syntax Tree inline methods

inline bool SyntaxTree::isOver() {
	return root == nullptr;
}
#endif // !_SYNTAX_TREE_H_
