#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;



struct node
{
	int month, year;
	vector<string> cards;
	node* next; //those three properties are needed for our nodes in this hw

	node::node ()
		:cards(0), month(0), year(0), next(NULL) //default constructor
	{}

	//constructor
	node::node (vector<string> cardNumber,int month, int year, node *n)
		:cards(cardNumber), month(month), year(year) ,next(n)
	{}	



};

/* Begin: code taken from ptrfunc.cpp (but modified) */
node * AddInOrder(node * head, int Nmonth, int Nyear, vector <string> Ncardnum)
// pre: list is sorted
// post: add newkey to list, keep list sorted, return head of new list with newkey in it
{
    node *  ptr = head;   // loop variable

    // if new node should be first, handle this case and return  
    // in this case, we return the address of new node since it is new head  
    if (head == NULL || Nyear < head->year)        
    {   
		node * temp = new node (Ncardnum, Nmonth, Nyear, head);  //node to be inserted 
		
		cout << "New node is created with expiration date: " << Nmonth << " " << Nyear << endl;
		cout << "Credit card " << Ncardnum[0]<< " added to node " << Nmonth << " " << Nyear << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		return temp;
		
    }
	else if(head == NULL || Nyear == head->year)
	{
		if ( Nmonth<head->month) //this is the case when we want to insert a node that has a smaller month value but same year value.Inserting a bigger date is problematic which is gonna be handled in the next section
		{
			node * temp = new node (Ncardnum, Nmonth, Nyear, head);  //node to be inserted 
			cout << "New node is created with expiration date: " << Nmonth << " " << Nyear << endl;
			cout << "Credit card " << Ncardnum[0]<< " added to node " << Nmonth << " " << Nyear << endl;
			cout << "---------------------------------------------------------------------------" << endl;
			return temp;
		}
	}

    // check node one ahead so we don't pass!
	while (ptr->next != NULL && (ptr->next->year < Nyear || ( ptr->next->year == Nyear && ptr->next->month < Nmonth))) //we must check the month values also to preserve sorted list, here we are inserting bigger dates, we must check until we find a place.
    {   
		 
		ptr = ptr->next;
    } // postcondition: new node to be inserted just after the node that ptr points

    //now insert node with newkey after where ptr points to
	node * temp = new node (Ncardnum, Nmonth, Nyear, ptr->next);  //node to be inserted
	cout << "New node is created with expiration date: " << Nmonth << " " << Nyear << endl;
	cout << "Credit card " << Ncardnum[0]<< " added to node " << Nmonth << " " << Nyear << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	ptr->next = temp;
	return head;
    //ptr->next = new node(newkey,ptr->next);   //alternative to prev. 4 lines

    return head;
}
/* End: code taken from ptrfunc.cpp */

/* Begin: code taken from linkedlist.cpp */

void ClearList(node *head) //Deletes all of the elements in the list
{
	node *ptr;
	while(head!=NULL)
	{
		ptr=head;
		head=head->next;
		delete ptr;
	}
}
node * SearchList(node *head, int mont_Value, int year_Value)
{
	while (head != NULL)
	{
		if(head->month == mont_Value && head->year == year_Value ) //If the node with the given month and year value is found
			return head;
			
		head = head->next;
	}
	//If the code proceeds from here, it means that the whole list is traversed 
	//and a node with ID == searchValue could not be found. 
	return NULL;
}
/* End: code taken from linkedlist.cpp */

void DisplayList(node *nodePtr)
{
	node * temp=nodePtr;
	while (nodePtr != NULL)
	{

		cout << "Expiration Date: " << nodePtr->month << " " << nodePtr->year << endl;
		for( int i = 0 ; i < nodePtr->cards.size();i++)
		{
			cout << i+1 << ")"<< nodePtr->cards[i] << endl;

		}
		cout <<"-------------------"<< endl;
		nodePtr = nodePtr->next;	
	}
	if(temp==NULL)
	{
		cout << "List is empty! " << endl;
	
	}
}

bool stringFullOfIntegers (string str)
{
	int count=0;
	for(int i=0; i<16; i++) 
	{
		if(str[i]>'9' || str[i]<'0')
		{
			count++;
		}
	}
	if(count!=0)
		return false;
	else
		return true;
}

/* Begin: code taken from linkedlist.cpp */

node* SearchCardNum(node *head, string givenCardNumber)
{
	while (head != NULL)
	{
		for( int i = 0 ; i < head->cards.size();i++)
		{
			if(head->cards[i] == givenCardNumber)
			{//If the node with the given nummber is found
				return head;			
			}
		}
		head = head->next;		
	}
	//If the code proceeds from here, it means that the whole list is traversed 
	//and a node with ID == searchValue could not be found. 
	return NULL;
}
/* End: code taken from linkedlist.cpp */


/* Begin: code taken from ptrfunc.cpp */
void DeleteOneNode (node * toBeDeleted, node * & head)
/* pre: toBeDeleted points to the node to be deleted from the list
   post: deletes the node pointed by toBeDeleted, updates head if changes */
{
	node * ptr;
		
	if (toBeDeleted == head)  //if the node to be deleted is the first node
	{
		head = head->next;
		delete toBeDeleted;
	}
	else  //if the node to be deleted is in the middle or at the end
	{
		ptr = head;
		while (ptr->next != toBeDeleted)
			ptr = ptr->next;
		//after while ptr point to the node just before toBeDeleted

		//connect the previous node to the next node and delete
		ptr->next = toBeDeleted->next;
		delete toBeDeleted;
	}
}
/* End: code taken from ptrfunc.cpp */

int main()
{
	string file_name;
	cout << "Please enter file name: " ;
	cin >> file_name;
	ifstream inputFile;
	inputFile.open(file_name);


	while(inputFile.fail()) //I want my user to enter file name until its correct 
	{
		cin.clear(); //to clear strings etc if entered. 
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
		cout << "Cannot find a file named" << " " << file_name << endl;
		cout << "Please enter file name: " ;
		cin >> file_name;
		inputFile.open(file_name);
	}
	int month, year;
	string cardnum;
	string line = "";
	getline(inputFile,line);
	istringstream s (line);
	s>>cardnum >> month>> year;
	node * myList;
	if (cardnum=="")//if initially my text file is empty and my program doesnt get any value
	{
		cout << "List is empty!" << endl;
		myList=NULL;

	}
	else //if my list isnt empty, program takes line by line and shows information messages about the nodes it created.
	{
		vector <string> initial;
		initial.push_back(cardnum);
		myList= new node (initial, month, year, NULL);//this is the first element of the list
		cout << "New node is created with expiration date: " << month << " " << year << endl;
		cout << "Credit card " << initial[0]<< " added to node " << month << " " << year << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		node *p=myList;
	
		while(getline(inputFile,line))
		{
			istringstream s (line);
			s>>cardnum >> month>> year;
			vector <string> temp;
			node* p_check=SearchList(myList, month, year);//if there is a node with same date, p_check points this node

			if ( p_check==NULL) //if there is no pre-existed node with same date
			{
				temp.push_back(cardnum);
				myList=AddInOrder(myList, month, year, temp);
			
			}
			else
			{
				(*p_check).cards.push_back(cardnum);//the node with same date will be pushed by new card number
				cout << "Node with expiration date " <<  month << " " << year << " already exists " << endl;
				cout << "Credit card " << cardnum<< " added to node " << month << " " << year << endl;
				cout << "---------------------------------------------------------------------------" << endl;
			
			}
		
		
		}
	}
	
	int input_number; //even if list is empty, program keeps displaying options
	cout << "\n\n";
	cout << "1)Display List" << endl << "2)Card Search via Credit Number" << endl << "3)Delete Card with respect to Expiration Date"<< endl<< "4)Exit"<< endl;
	cout << "Please choose option from the menu: ";
	cin>>input_number;

	while(cin.fail() || input_number<1 || input_number>4) //option must be a valid entry
	{
		cin.clear(); //to clear strings etc if entered. 
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
		cout <<"Invalid option number, please choose option from the menu: " ;
		cin>>input_number;
	}

	while(input_number!=4)//as long as my user doesnt want to terminate the program, options will appear
	{
		if(input_number==1) //display option
		{

			DisplayList(myList);
			cout << "\n\n";
			cout << "1)Display List" << endl << "2)Card Search via Credit Number" << endl << "3)Delete Card with respect to Expiration Date"<< endl<< "4)Exit"<< endl;
			cout << "Please choose option from the menu: ";
			cin>>input_number;

			while(cin.fail()||input_number<1 || input_number>4)
			{
				cin.clear(); //to clear strings etc if entered. 
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				cout <<"Invalid option number, please choose option from the menu: " ;
				cin>>input_number;
			}
		}
		string number_to_be_searched;
		if(input_number==2) //search option
		{
			cout << "Please enter the credit card number: ";
			cin >> number_to_be_searched;
			while(cin.fail()||number_to_be_searched.length()!=16 || !stringFullOfIntegers(number_to_be_searched)) //card number must have valid format
			{
				cin.clear(); //to clear strings etc if entered. 
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				cout <<"Invalid format!"<<endl;
				cout << "Please enter the credit card number: ";
				cin >> number_to_be_searched;		
			}
			node * p=SearchCardNum(myList, number_to_be_searched); //ı search the given number throught the list and if there is any, p points that node
			if(p==NULL)
			{
				cout << "There is no credit card with given credit card number: " << number_to_be_searched << endl;
				

			}
			else
			{
				cout << "There exists a credit card given number " << number_to_be_searched << " with expiration date: " << p->month << " " << p->year << endl;
			
			}
			cout << "\n\n"; //program keeps displaying options
			cout << "1)Display List" << endl << "2)Card Search via Credit Number" << endl << "3)Delete Card with respect to Expiration Date"<< endl<< "4)Exit"<< endl;
			cout << "Please choose option from the menu: ";
			cin>>input_number;

			while(cin.fail()||input_number<1 || input_number>4)
			{
				cin.clear(); //to clear strings etc if entered. 
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				cout <<"Invalid option number, please choose option from the menu: " ;
				cin>>input_number;
			}

		}
		if(input_number==3)//delete option
		{
			int searchMonth, searchYear;
			cout << "Please enter month and year: " ;
			cin>> searchMonth >> searchYear;

			while (cin.fail() || (searchMonth>12 || searchMonth<1)) //valid date check
			{
				cin.clear(); //to clear strings etc if entered. 
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				cout << "Invalid Date!" << endl;
				cout << "Please enter month and year: " ;
				cin>> searchMonth >> searchYear;
			}	
			
			node* p2= SearchList(myList, searchMonth, searchYear);//if there is a node with given date, p2 points that node
			if (p2==NULL)
			{
				cout << "There is no node with expiration date " << searchMonth << " " << searchYear<< " nothing deleted!" << endl;
			}
			else
			{
				cout << "Node with expiration date " << searchMonth << " " << searchYear<< " and the following credit cards have been deleted!" << endl;
				for( int i=0; i< p2->cards.size(); i++)
				{
					cout << i+1 << ")" << p2->cards[i] << endl;
					
				}
				DeleteOneNode(p2,myList);

			}
			cout << "\n\n";
			cout << "1)Display List" << endl << "2)Card Search via Credit Number" << endl << "3)Delete Card with respect to Expiration Date"<< endl<< "4)Exit"<< endl;
			cout << "Please choose option from the menu: ";
			cin>>input_number;

			while(cin.fail()||input_number<1 || input_number>4)
			{
				cin.clear(); //to clear strings etc if entered. 
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				cout <<"Invalid option number, please choose option from the menu: " ;
				cin>>input_number;
			}
		}

	}

	if(input_number==4)//if user wants to end program
	{
		cout << "Terminating!!! " << endl;
	}
	ClearList(myList); //clear the list
	//These cin.get and cin.ignore for not closing program directly after. Otherwise you cannot see result on terminal
	cin.get();
	cin.ignore();
	return 0;

}





