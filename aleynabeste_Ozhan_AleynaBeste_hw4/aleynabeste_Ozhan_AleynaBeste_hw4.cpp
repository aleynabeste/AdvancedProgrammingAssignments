
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DynIntStack.h"

using namespace std;

bool stringFullOfIntegers (string str) //it is to control if a given string is a number 
{
	int count=0;
	for(int i=0; i<str.size(); i++) 
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


/* Begin: code taken from matrix.cpp from lab week5 */
void PrintMatrix(char **matrix, int rsize, int csize ) 
{
	for(int i=0; i<rsize; i++)
	{
		 
		for(int j=0; j<csize; j++)
		{
			cout << matrix[i][j];
		}
		cout << endl;
	}
}


void DeleteMatrix(char ** matrix, int size)
{
	for(int i=0; i<size; i++)
	{
		delete [] matrix[i];
	}
	delete [] matrix;
}

/* end: code taken from matrix.cpp  */

int main()
{
	int rowsize;
	int columnsize;
	string mystr;
	string entered_value;
	cout << "Please enter the number of rows:" ; 
	getline (cin,mystr);
	stringstream(mystr) >> entered_value; //I keep the entered value in the form of string to be able to print it later in the error message
	bool check=true;
	
	while(check)
	{
		if(!stringFullOfIntegers(entered_value))//if given value is not a number then it is an invalid input
		{

			cout << entered_value << " is not valid!" << endl;
			cout << "Please enter the number of rows:" ; 
			getline (cin,mystr);
			stringstream(mystr) >> entered_value;
		
		}
		else if(stringFullOfIntegers(entered_value)&& stoi(entered_value)<3) //if given value is a number but is smaller than 3 
		{
			
			cout << stoi(entered_value)<< " is not valid!" << endl;
			cout << "Please enter the number of rows:" ; 
			getline (cin,mystr);
			stringstream(mystr) >> entered_value;
	
		}
		else if (stringFullOfIntegers(entered_value) && stoi(entered_value)>=3) //if given value is a number greater than or equal to 3
		{
			rowsize=stoi(entered_value); //stoi is to convert the string to its integer value
			check=false; //if true input is entered than no need to more check
		
		}
	}

	
	cout << "Please enter the number of columns:" ; 
	getline (cin,mystr);
	stringstream(mystr) >> entered_value;
	check=true;
	
	while(check) //check mechanism is same as before, like for the row value
	{
		if(!stringFullOfIntegers(entered_value))
		{

			cout << entered_value << " is not valid!" << endl;
			cout << "Please enter the number of columns:" ; 
			getline (cin,mystr);
			stringstream(mystr) >> entered_value;
		
		}
		else if(stringFullOfIntegers(entered_value)&& stoi(entered_value)<3)
		{
	
			cout << stoi(entered_value)<< " is not valid!" << endl;
			cout << "Please enter the number of columns:" ; 
			getline (cin,mystr);
			stringstream(mystr) >> entered_value;
			
		}
		else if (stringFullOfIntegers(entered_value) && stoi(entered_value)>=3)
		{
			columnsize=stoi(entered_value);
			check=false;
			
		}
	}

	string file_name, mystr2;
	cout << "Please enter file name: " ;
	getline (cin,mystr2);
	stringstream(mystr2) >> file_name;// again I stored the input line as string to be able to print later
	ifstream inputFile;
	inputFile.open(file_name);
	while(inputFile.fail()) //I want my user to enter file name until its correct 
	{

		cout << "Cannot find a file named" << " " << file_name << endl;
		cout << "Please enter file name: " ;
		cin >> file_name;
		inputFile.open(file_name);
	}
	/* Begin: code taken from matrix.cpp (but modified) */
	//Two dimensional dynamic array creation
	char** dmatrix = new char*[rowsize];
	for(int i =0; i<rowsize; i++)
	{
		dmatrix[i] = new char [columnsize];
	}
	/* end: code taken from matrix.cpp (but modified) */
	string line;
	int r=0;
	while(!inputFile.eof()) //I read my file until the end of it
	{
		getline(inputFile, line);
	
		//Process on dynamic matrix
	
		for(int j=0; j<columnsize; j++)
		{
			
			dmatrix[r][j] = line[j]; //since I know that the size of line in my given file is equal to columsize so I can assign the values like that
		}
		r++;
	}

	int row_coor, col_coor;
	cout << "Please enter the starting point: " ;
	cin >> row_coor >> col_coor;
	while(cin.fail() || row_coor<0 || row_coor>=rowsize || col_coor <0 || col_coor >= columnsize) //coordinate should be inside the boundary and be integer
	{
		cin.clear();
		cin.ignore(INT_MAX ,'\n'); //to clear the entered value if its wrong
		cout << "Invalid Coordinate!" << endl;
		cout << "Please enter the starting point: " ;
		cin >> row_coor >> col_coor;
	}

	DynIntStack mystack; //I create my stack, empty first

	if (dmatrix[row_coor][col_coor]=='X') //if the given coordinate by user is occupied program finishes
	{
		cout << "This cell is occupied." << endl << "Terminating..." << endl;
	}

	else 
	{
		char filler;
		cout << "Enter the filling char: ";
		cin >> filler;
		while(cin.fail() || filler == 'X' || filler == 'x' ) //given character to fill the matrix must be different from x or X
		{
			cin.clear();
			cin.ignore(INT_MAX ,'\n');
			cout << "Filling char is not valid!" << endl;
			cout << "Enter the filling char: ";
			cin>> filler;
		}
		mystack.push(row_coor, col_coor);//first I put the starting point in the stack
		dmatrix[row_coor][col_coor]=filler; //then I fill the matrix with filler char
		while(!mystack.isEmpty()) //I will try every neighbor direction if my stack is not empty
		{
			if(dmatrix[row_coor][col_coor+1]==' '&& col_coor+1 < columnsize) //right check
			{
				mystack.push(row_coor, col_coor+1);
				dmatrix[row_coor][col_coor+1]=filler;
				col_coor=col_coor+1;
			}
			else if(dmatrix[row_coor+1][col_coor]==' '&& row_coor+1<rowsize)//down check
			{
				mystack.push(row_coor+1, col_coor);
				dmatrix[row_coor+1][col_coor]=filler;
				row_coor=row_coor+1;		
			}
			else if(dmatrix[row_coor][col_coor-1]==' '&& col_coor-1>=0)//left check
			{
				mystack.push(row_coor, col_coor-1);
				dmatrix[row_coor][col_coor-1]=filler;
				col_coor=col_coor-1;	
			}
			else if(dmatrix[row_coor-1][col_coor]==' '&& row_coor-1>=0)//up check
			{
				mystack.push(row_coor-1, col_coor);
				dmatrix[row_coor-1][col_coor]=filler;
				row_coor=row_coor-1;
			}
			else
			{
				mystack.pop(row_coor,col_coor); //if all neighborhood directions are occupied, I take out last element on the stack and check again
			
			}
		}
		if(mystack.isEmpty())//If I reach empty stack it means I have filled the area completely
		{
			PrintMatrix(dmatrix, rowsize, columnsize);
		}
	}



	DeleteMatrix(dmatrix, rowsize);
	mystack.~DynIntStack();


	
	cin.get();
	cin.ignore();
	return 0;
}