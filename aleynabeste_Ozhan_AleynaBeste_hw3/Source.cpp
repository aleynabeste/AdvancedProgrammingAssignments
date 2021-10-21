#include <iostream>
#include "Header.h"

using namespace std;

CardList::CardList()
{
	head=NULL; //when there isn't node in the list, head and tail points nowhere
	tail = NULL;
}

/* Begin: code taken from ptrfunc.cpp (but modified) */
void CardList::insertCard (string creditCardNo, int month, int year)
{
	expirationNode*ptr=head;
 
    if (head == NULL) //this is the case when program adds a expiration node to the list for the first time
	{
		creditCardNode *c;
		c=new creditCardNode(creditCardNo,NULL);//create a credit card node which is gonna be included in the expiration node as chead
		expirationNode * temp = new expirationNode(month, year, c, head, NULL);  //node to be inserted, with credit card node, head as next pointer which is null now, and null prev pointer
		tail=temp;//both tail and head are temp because it is the first node 
		head=temp;
		cout << creditCardNo<< " " << month << " " << year << ": added to a new expiration date node"<< endl;
		cout << "---------------------------------------------------------------------------" << endl;	
	}
	
	else if(year < head->year || (year == head->year && month<head->month))  //if node to be inserted is earlier than the head of the list      
    {   
		
		creditCardNode *c;
		c=new creditCardNode(creditCardNo,NULL);
		expirationNode * temp = new expirationNode(month, year, c, head, NULL);  //node to be inserted : next is head and prev is null
		temp->next->prev=temp; //previous of the old head will point new head because they must be connected
		head=temp; //new head is the node that program inserts in the beginning

		cout << creditCardNo<< " " << month << " " << year << ": added to a new expiration date node"<< endl;
		cout << "---------------------------------------------------------------------------" << endl;	
    }
	else 
	{
		// check node one ahead so we don't pass!
		while (ptr->next != NULL && (ptr->next->year < year || ( ptr->next->year == year && ptr->next->month < month) || (ptr->next->year == year && ptr->next->month == month))) //we must check the month values also to preserve sorted list, here we are inserting bigger dates, we must check until we find a place.
		{   //last condition in the while statement is for the case when program tries to insert an already existing node, ptr should point this node
		 
			ptr = ptr->next;
		} // postcondition: new node to be inserted just after the node that ptr points 
		if( ptr->month==month && ptr->year==year)//if ptr points the node with same date
		{
			creditCardNode* ptr2=ptr->cHead;
			if(ptr2->creditCardNo>creditCardNo)//if new number is smaller than head of single linked list
			{
				creditCardNode *tempc= new creditCardNode(creditCardNo, NULL);//in this case we re not trying to add new expiration node but a new card num to the credit card single linked list
				tempc->next=ptr2;
				ptr->cHead=tempc;//add to the beginning
				cout << creditCardNo<< " " << month << " " << year << ":inserted to an existing expiration date node"<< endl;
				cout << "---------------------------------------------------------------------------" << endl;	

			}
			else
			{
				//program tries to find out where to insert the new credit card number, with respect to order
				while(ptr2->next !=NULL && (ptr2->next->creditCardNo<creditCardNo || ptr2->next->creditCardNo==creditCardNo))
				{//last condition in the while statement is to make sure if there is a same card number, ptr points it
					ptr2=ptr2->next;
				}

				if(ptr2->creditCardNo==creditCardNo)//if same number is found
				{
					cout << creditCardNo<< " " << month << " " << year << ": this card was already inserted"<< endl;
					cout << "---------------------------------------------------------------------------" << endl;	
				}

				else
				{
					creditCardNode *tempc= new creditCardNode(creditCardNo, NULL);//credit card number is to be inserted after where ptr2 points
					tempc->next=ptr2->next;
					ptr2->next=tempc;
					cout << creditCardNo<< " " << month << " " << year << ": inserted to an existing expiration date node"<< endl;
					cout << "---------------------------------------------------------------------------" << endl;
				}
			}
		}
		else
		{
			//if expiration node is to be inserted after where ptr points
			creditCardNode *c;
			c=new creditCardNode(creditCardNo,NULL);
			expirationNode * temp = new expirationNode (month, year, c, ptr->next, ptr);  //node to be inserted
			cout << creditCardNo<< " " << month << " " << year << ": added to a new expiration date node"<< endl;
			cout << "---------------------------------------------------------------------------" << endl;	
			ptr->next = temp;
			if (temp->next != NULL)//if there is at least one node after the new added node, the prev of the next node should be the inserted node
			{
				temp->next->prev=temp;
			}
			else
			{
				tail=temp;//if the new inserted node is the last one, update the tail
			}
			
		}
	}

}
/* End: code taken from ptrfunc.cpp but modified*/

void CardList::displayListChronological()
{	
	
	expirationNode * ptr = head;
	//List is empty
	if(head == NULL)
	{
		cout << "List is empty" << endl;
	}
	else
	{
		cout << "Printing the linked list..." << endl;
		while(ptr != NULL)//while there are expiration nodes
		{
			cout << "Expiration Date: " << ptr->month << " " << ptr-> year << endl;
			creditCardNode * ptr2=ptr->cHead;
			int i=1;
			while (ptr2 != NULL)//while there is credit card node
			{
				cout << i << ")" << ptr2->creditCardNo << endl;
				ptr2=ptr2->next;//in case one expiration node may have multiple credit card nodes in it, iterate until ptr2 is null
				i++;
			}
			cout << "----------------------------------"<< endl;
			ptr = ptr->next;//go forward in the doubly linked list until you find an expiration node with next pointer null
		}
	}
}

void CardList::displayListReverseChronological() //same logic but we start from the tail and uptade prev node 
{	
	
	expirationNode * ptr = tail;
	//List is empty
	if(tail == NULL)
	{
		cout << "List is empty" << endl;
	}
	else
	{
		cout << "Printing the linked list..." << endl;
		while(ptr != NULL)
		{
			cout << "Expiration Date: " << ptr->month << " " << ptr-> year << endl;
			creditCardNode * ptr2=ptr->cHead;
			int i=1;
			while (ptr2 != NULL)
			{
				cout << i << ")" << ptr2->creditCardNo << endl;
				ptr2=ptr2->next;
				i++;
			}
			cout << "----------------------------------"<< endl;
			ptr = ptr->prev;
		}
	}
}

void CardList::cardSearch (string creditCardNo)
{
	
	//List is empty
	if(head == NULL)
	{
		cout << "There is no credit card with given credit card number: " << creditCardNo << endl;
	}
	else
	{
		expirationNode * ptr = head;
		bool isfound=false;
		while(ptr!=NULL)//check all expiration nodes in the list until you hit the end
		{
			creditCardNode*temp=ptr->cHead;
			while(temp!=NULL)//temp point the single linked list, card numbers
			{
				if(temp->creditCardNo==creditCardNo)//if you find a match
				{
					cout << "There exists a credit card given number " << creditCardNo << " with expiration date " << ptr->month << " " << ptr->year << endl;
					temp=NULL;//make temp null so you dont enter the loop again, because I know one card num can only exist once in one expiration node
					isfound=true;//ı need to keep a bool variable to detect if there is no match
				}
				else
				{
					temp=temp->next;
				}
			}
			ptr=ptr->next;//go to next expiration node
		}
		if(!isfound)
		{
			cout << "There is no credit card with given credit card number: " << creditCardNo << endl;
		}
	}

}

void CardList::bulkDelete (int month, int year)
{
	expirationNode*ptr;
	if(head==NULL)
	{
		cout << "List is empty" << endl;
	}
	else if(head!=NULL)
	{
		while(head!=NULL&&( head->year<year || (head->year==year && head->month<=month))) // I keep iterating in the list until the given date, including the date itself
		{//head shouldn't be null
	
			ptr=head;
			cout << "\n" << "Node with expiration date " << ptr->month << " " << ptr->year << " and the following credit cards have been deleted!" << endl;
			int i=1;
			while (ptr->cHead!=NULL)//ı have to clear creditcard nodes in one expiration node to delete it cmpletely
			{
				creditCardNode *ptr2=ptr->cHead;
				cout << i << ")" << ptr2->creditCardNo << endl;
				ptr->cHead=ptr2->next;
				delete ptr2;
				i++;
				
		
			}
			if(head->next!=NULL)//if there is at least one node after my expiration node to be deleted, I have to connect it
			{
				head->next->prev=head->prev; //prev of the nex head should be null
				head=head->next;//new head is the next node after old head
				delete ptr;//delete old head
			}
			else //if I am deleting the last node, I should make head and tail null otherwise they will cause problem, they will point the places like -231727
			{
				delete ptr;
				head=NULL;
				tail=NULL;
			}
		}
	}

	

}

void CardList::deleteAll ()//same logic like bulk delete but here my while condition is until I it the end
{
	expirationNode *ptr;
	while(head!=NULL)
	{
		ptr=head;
		
		while (ptr->cHead!=NULL) //until the end of list
		{
			creditCardNode *ptr2=ptr->cHead;
			ptr->cHead=ptr2->next;//delete card nums in each expiration node
			delete ptr2;
		
		}
		if(head->next!=NULL)//if the deleted one is not the last one
		{
			head->next->prev=head->prev;//connect properly
			head=head->next;
			delete ptr;
		}
		else//if the deleted one is the last one
		{
			delete ptr;
			head=NULL;
			tail=NULL;
		}
	}
}


