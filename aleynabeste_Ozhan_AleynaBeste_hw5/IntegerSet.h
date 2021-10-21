#include <iostream>
#include <string>
using namespace std;
class IntegerSet
{
	public:
		IntegerSet(); //default constructor
		IntegerSet(int s); //constructor with param
		IntegerSet(const IntegerSet&); //deep copy
		~IntegerSet (); //destructor
		const IntegerSet & operator +(const int & rhs); //adding an int to the set
		IntegerSet  operator +(const IntegerSet & set1) const; //adding two sets
		IntegerSet operator *( IntegerSet & set1); //intersection of two sets
		const IntegerSet & operator =(const IntegerSet & set_rhs);  //assignment
		const IntegerSet & operator +=(const IntegerSet & set_rhs); //plus assignment
		bool operator <= (const IntegerSet & set_rhs); //subset check
		void deletearray(); //helper function to delete the array
		bool operator !=(const IntegerSet & set_rhs); //inequality check
		int* getptr () const; //accessor
		int getsize() const; //accessor
		
	private:
		int size; //size of the array
		int *ptr ; //pointer to the head of dynamic array
		



};

ostream &  operator << (ostream & os,IntegerSet & mySet); //output
bool operator <= (const int & lhs,IntegerSet & rhs); //element check
