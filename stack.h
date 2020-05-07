#ifndef _STACK_H
#define _STACK_H
using namespace std;

struct StackNode
{
	int rws;
	int columns;
	StackNode *next;
};

class DynIntStack
{
private:
	StackNode *top;

public:
	DynIntStack(void);
	~DynIntStack(); //destructor
	void push(int rows, int cols);
	void pop(int & rows, int & cols);
	bool isEmpty(void);
};

#endif