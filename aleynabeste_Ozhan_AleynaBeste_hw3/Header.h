
#include <string>
using namespace std;


struct creditCardNode //node for store the credit card numbers
{ 
	string creditCardNo; //it will contain card number and another pointer to point next node
	creditCardNode * next; 

	creditCardNode::creditCardNode() //default constructor
	{}

	creditCardNode::creditCardNode(const string &s, creditCardNode * p) //constructor
		: creditCardNo(s), next(p)
	{}

};

struct expirationNode //node for store the expiration dates, associated with card numbers
{
	int month, year; //it will include month year, a next pointer, a prev pointer and another pointer for creditcardNode.
	creditCardNode * cHead; 
	expirationNode * next; 
	expirationNode * prev;//this structure provides double linked list

	expirationNode::expirationNode() //default constructor
	{}

	expirationNode::expirationNode(int i, int j, creditCardNode * p1, expirationNode * p2, expirationNode * p3)
		:month(i), year(j), cHead(p1), next(p2), prev(p3) //constructor
	{}

};

class CardList
{

public:
	CardList(); //constructor
	void insertCard (string creditCardNo, int month, int year); //inserts the given card number with its expiration date: earliest to latest
	void displayListChronological (); //display the list in the right order, starting from the head
	void displayListReverseChronological (); //display the list in the reverse order, starting from the tail
	void cardSearch (string creditCardNo); //it returns the expiration date for a given number, if such number exists in the list
	void bulkDelete (int month, int year); //delete the nodes with expiration date earlier than or equal to the given date
	void deleteAll (); //deletes the structure to prevent memory leak

private: 
	expirationNode * head; //starting pointer for the doubly linked list
	expirationNode * tail; //end point




};