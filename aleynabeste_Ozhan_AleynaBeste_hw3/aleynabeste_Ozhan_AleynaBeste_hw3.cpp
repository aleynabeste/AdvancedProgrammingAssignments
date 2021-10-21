#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Header.h"
//ALEYNA BESTE OZHAN 24921

using namespace std;

bool stringFullOfIntegers (string str) //this function will be used in input check for the credit card number, before sending it to member function
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
		return true;//if input string is only consisted of integers, function returns true
}

int main()
{
	cout << "1) Upload Card(s) from a File" << endl 
		<< "2) Display List Chronological" << endl 
		<< "3) Display List Reverse Chronological" << endl 
		<< "4) Card Search" << endl
		<< "5) Bulk Delete" << endl 
		<<"6) Exit" << endl; //first display the menu and get an option from the user
	cout << "Please choose option from the menu: ";
	int input_number; 
	cin>>input_number;
	cout << "\n";
	while(cin.fail() || input_number<1 || input_number>6) //option must be a valid entry
	{
		cin.clear(); //to clear strings etc if entered. 
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
		cout <<"Invalid option number, please choose option from the menu: " ;
		cin>>input_number;
		cout << "\n" ;
	}
	CardList mylist; //construct the doubly linked list here
	
	while(input_number!=6) //if option is not for exitting the program
	{
		
		if(input_number==1)
		{
			string file_name; //if user enters 1, then program will ask for the filename
			cout << "Please enter file name: " ;
			cin >> file_name;
			ifstream inputFile;
			inputFile.open(file_name);


			if(inputFile.fail()) 
			{
				cin.clear(); //to clear strings etc if entered. 
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				cout << "Cannot find a file named" << " " << file_name << endl;
				
			}
			else
			{

				int month, year;
				string cardnum;
				string line = "";
				getline(inputFile,line);
				istringstream s (line);
				s>>cardnum >> month>> year;
				if (cardnum=="")//if initially my text file is empty and my program doesnt get any value
				{
					cout << "uploaded file is empty!" << endl;
				}
				else //if my list isnt empty, program takes line by line 
				{
					mylist.insertCard(cardnum,month,year);
					while(getline(inputFile,line))
					{
						istringstream s (line);
						s>>cardnum >> month>> year;
		
						mylist.insertCard(cardnum,month,year);//then card insertion function will be called
					}
				}
			}
		}
		else if(input_number==2) //option 2
		{
			mylist.displayListChronological();
		}
		else if(input_number==3)
		{
			mylist.displayListReverseChronological();
		}
		else if(input_number==4)
		{
			string cardnumber;
			cout <<"Please enter the credit card number: ";
			cin>>cardnumber;
			if(cin.fail()||cardnumber.length()!=16 || !stringFullOfIntegers(cardnumber)) //card number must have valid format
			{
				cin.clear(); //to clear strings etc if entered. 
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				cout <<"Invalid format!"<<endl;
		
			}
			else
			{
				mylist.cardSearch(cardnumber);
			}
		
		}
		else if(input_number==5)
		{
			int searchMonth, searchYear;
			cout << "Please enter month and year: " ;
			cin>> searchMonth >> searchYear;

			if(cin.fail() || (searchMonth>12 || searchMonth<1)) //valid date check
			{
				cin.clear(); //to clear strings etc if entered. 
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
				cout << "Invalid Format!" << endl;

			}
			else
			{
				mylist.bulkDelete(searchMonth, searchYear);	
			}
		}
		cout << "\n" ;
		cout << "1) Upload Card(s) from a File" << endl 
		<< "2) Display List Chronological" << endl 
		<< "3) Display List Reverse Chronological" << endl 
		<< "4) Card Search" << endl
		<< "5) Bulk Delete" << endl 
		<<"6) Exit" << endl;
		cout << "Please choose option from the menu: "; //menu should be displayed until user enters 6 
		
		cin>>input_number;
		cout << "\n";
		while(cin.fail() || input_number<1 || input_number>6) //option must be a valid entry
		{
			cin.clear(); //to clear strings etc if entered. 
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			cout <<"Invalid option number, please choose option from the menu: " ;
			cin>>input_number;
		}

	}
	if(input_number==6) //exit option
	{
		cout << "All the nodes have been deleted!" << endl <<"Terminating!!! " << endl;
	}
	mylist.deleteAll();
	cin.get();
	cin.ignore();
	return 0;


}