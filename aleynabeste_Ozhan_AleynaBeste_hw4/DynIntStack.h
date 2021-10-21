
/* Begin: code taken from DynIntStack.h but modified*/

struct StackNode
{
	int row, column; //for the coordinates in the matrix
	StackNode *next;
};

class DynIntStack
{
private:
	StackNode *top;

public:
	DynIntStack();
	~DynIntStack();
	void push(int, int);
	void pop(int &, int&);
	bool isEmpty(void);
};

/* end: code taken from DynIntStack.h but modified*/