/* Begin: code taken from DynIntStack.cpp but modified*/
#include <iostream>
#include "dynintstack.h"
using namespace std;


//************************************************
// Constructor to generate an empty stack.       *
//************************************************
DynIntStack::DynIntStack()
{
	top = NULL; 
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void DynIntStack::push(int row_value, int column_value) //I have two value to push: rox and column
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->row = row_value;
	newNode->column=column_value;

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
void DynIntStack::pop(int &row_value, int &column_value)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		if (top->next!=NULL) //If there will be still some nodes after I pop the top, I want to keep the coord values of the new top to be. 
		{
			row_value = top->next->row;
			column_value=top->next->column;
			temp = top->next;
			delete top;
			top = temp;
		}
		else //But if I will pop the last value then values stays as the last nodes values
		{
			row_value = top->row;
			column_value=top->column;
			temp = top->next;
			delete top;
			top = temp;
		}
	}
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

DynIntStack::~DynIntStack() //destructor, delete everyhthing
{
   StackNode *nodePtr, *nextNode;

   // Position nodePtr at the top of the stack.
   nodePtr = top;

   // Traverse the list deleting each node.
   while (nodePtr != NULL)
   {
      nextNode = nodePtr->next;
      delete nodePtr;
      nodePtr = nextNode;
   }
}
/* end: code taken from DynIntStack.cpp but modified*/