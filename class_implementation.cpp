#include <iostream>
#include "stack.h"
using namespace std;

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
DynIntStack::DynIntStack()
{
	top = NULL; 
}

//************************************************
// Deconstructor to delete a stack.       *
//************************************************
DynIntStack::~DynIntStack()
{
	StackNode * ptr = top;

	while (ptr != NULL) 
	{
		 ptr = top;
		 top = top -> next;
		 delete ptr;
	}
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void DynIntStack::push(int row, int cols)
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->rws = row;
	newNode->columns = cols;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void DynIntStack::pop(int &rows, int & cols)
{
	StackNode *temp;

	rows = top->rws;
	cols = top->columns;
	temp = top->next;
	delete top;
	top = temp;
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynIntStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}


