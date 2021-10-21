#include <iostream>
#include <sstream>
#include "IntegerSet.h"
using namespace std;

IntegerSet::IntegerSet()
{
	size=0; //default constructor will create a null set 
	ptr=NULL;
}
IntegerSet::IntegerSet(int s)
{
	if(s>0) //when size is specified
	{
		size=s;
		ptr=new int[s]; //pointer will point an array with size many  integer elements
		int i=0;
		for(int j=0; j<s; j++)
		{
			ptr[j]=i; // initially it is giving values from 0 to size-1
			i++;
		}
	}
	else //is size is 0 or negative, null set is created 
	{
		size=0;
		ptr=NULL;
	}
}

IntegerSet::IntegerSet(const IntegerSet & copy)
{
	
	size=copy.getsize(); //since it is copy, size is same
	ptr=new int[size];
    for (int i = 0; i < size; ++i) 
	{
        ptr[i] = copy.getptr()[i]; //and the elements in it also same
    }
	
}


IntegerSet::~IntegerSet()
{
	delete[] ptr; //delete the dynamic memory
	ptr=NULL;
}

void IntegerSet::deletearray()
{
	delete[] ptr;
	ptr=NULL;
}

const IntegerSet & IntegerSet::operator =(const IntegerSet & set_rhs) //since it is assignment it returns const integerset with &
{
	if (&set_rhs != this) //if two sets are not the same set
    {
		deletearray(); //firs we should delete the lhf because we are gonna create another lhs 
		size=set_rhs.getsize(); //for the new lhs, size is the size of rhs
		ptr=new int [size];
		for (int i=0; i<set_rhs.getsize(); i++)
		{
			ptr[i]=set_rhs.getptr()[i]; //elements of new lhs are equal to rhs
		}
    }

    return *this; //we are returning lhf, the set on which the function is applied

}

 const IntegerSet & IntegerSet::operator +(const int & rhs) 
{
	if(!(rhs<=*this)) // if the element the function is trying to add is not already in the set
	{
		if(size==0) //if initially we have a null set
		{
			this-> deletearray();
			size=1; //size will be 1 with newly added element
			ptr=new int[1];
			ptr[0]=rhs;
		}
		else
		{
			
			IntegerSet temp (*this); //first we should make a copy because we need the element information but we are gonna delete the array
			this->deletearray();
			size=temp.getsize()+1; //create another lhf with increased size
			ptr=new int [size];
			for(int i=0; i<temp.getsize(); i++)
			{
				ptr[i]=temp.getptr()[i]; //fill the set with same elements of temp until the last element

			}
			ptr[size-1]=rhs; //last element is the newly added integer


		}
		return *this; //return updated
	}
	return *this; //if the element is already in the set, return unchanged set

}

IntegerSet IntegerSet::operator+(const IntegerSet & set) const //member function that does not change the private data members needs to be const member function
{
	if(size==0) //is rhs is null set, union will be lhs directly
	{
		IntegerSet temp (set);
		return temp;
	}
	else if(set.getsize()==0) //is lhs is null set, union will be rhs directly
	{
		IntegerSet temp (*this); //create copy because of the return type
		return temp;
	
	}
	else 
	{
		int common_count=0; //num of elements in common
		for (int j=0; j<size; j++)
		{
			for (int i=0; i<set.getsize();i++)
			{
				if(ptr[j]==set.getptr()[i]) //check equality
				{
					common_count++;
				}
			}
		}
		IntegerSet temp1(*this);
		int new_size=(size+set.getsize())-common_count;
		IntegerSet unionSet(new_size); //union set is created with new element 
		for(int i=0; i<size;i++)
		{
			unionSet.getptr()[i]=ptr[i]; //first put all elements of lhs
		}
		int s=size;
		for(int j=0; j<set.getsize();j++)
		{

			if(!(set.getptr()[j]<=temp1))
			{
				unionSet.getptr()[s]=set.getptr()[j]; //then put elements of rhs that are not in the rhs
				s++;
			}
		}
		return unionSet; 
	}
}

bool IntegerSet::operator !=( const IntegerSet & set_rhs)
{
	if(size !=set_rhs.size) //if their size are different they are different for sure
	{
		return true;
	}
	else //if their size are equal
	{
		if(size>0)
		{
			int count=0;
			for (int j=0; j<size; j++)
			{
				for (int i=0; i<size;i++)
				{
					if(ptr[j]==set_rhs.ptr[i]) //check for equality of elements
					{
						count++;
					}

		
				}
			}
			if(count!=size) //if size many elements are notequal then two sets are not equal
			{
				return true; //inequality is true
			}
			else 
			{
				return false;
			}
		}
		else if(size==0) //rhs is null, and they have diff sizes, they are different
			return false;
	}
}

bool IntegerSet::operator<= (const IntegerSet & set_rhs)
{
	int count=0;
	for (int j=0; j<size; j++)
	{
		for (int i=0; i<set_rhs.getsize();i++)
		{
			if(ptr[j]==set_rhs.getptr()[i]) //check the element equality
			{
				count++;
			}
		}
	}
	if(count!=size) //if all elements of rhs is in the lhf, count will be the same
	{
		return false;
	}
	else 
	{
		return true;
	}
}
int* IntegerSet::getptr() const
{
	return ptr;
}

int IntegerSet::getsize() const
{
	return size;
}

ostream &  operator << (ostream & os, IntegerSet & mySet)
{
	if(mySet.getsize()==0)
	{
		os << "{}"; //if null set
	}
	else 
	{
		os << "{";
		for (int i=0; i<mySet.getsize()-1; i++)
		{
			os << mySet.getptr()[i] << "," ;
		}
		os << mySet.getptr()[mySet.getsize()-1] <<"}"; //closing paranthesis is after the last element
	}
	return os;
}

bool operator <= (const int & lhs, IntegerSet & rhs)
{
	
	int count=0;
	for(int i=0; i < rhs.getsize() ; i++)
	{
		if(lhs==rhs.getptr()[i])
		{
			count++; //if there is same element in the lhs, count increases
		}
	}
	if(count!=0) //if count is different than 0, it means given int exist in the list
	{
		return true;
	}
	else
		return false;
}
const IntegerSet &IntegerSet:: operator +=(const IntegerSet & set_rhs)
{
	int common_count=0;
	for (int j=0; j<size; j++)
	{
		for (int i=0; i<set_rhs.getsize();i++)
		{
			if(ptr[j]==set_rhs.getptr()[i])
			{
				common_count++; //we need num of common elements
			}
		}
	}
	IntegerSet temp(*this); //we create a copy in order to keep element information
	this->deletearray(); //delete lhs because we re gonna create a new lhs

	int new_size=(size+set_rhs.getsize())-common_count;
	size=new_size; //here also update the private data
	ptr=new int [size]; //new lhs with new size
	for(int i=0; i<temp.getsize();i++)
	{
		ptr[i]=temp.getptr()[i]; //copy the elements of old lhs
	}
	int s=temp.getsize();
	for(int j=0; j<set_rhs.getsize();j++)
	{
		
		if(!(set_rhs.getptr()[j]<=temp))
		{
			ptr[s]=set_rhs.getptr()[j]; //add also the elements of rhs which are not also in lhs
			s++;
		}
	}
	return *this;


}

IntegerSet IntegerSet:: operator *( IntegerSet & set1)
{
	int common_count=0;
	for (int j=0; j<size; j++)
	{
		for (int i=0; i<set1.getsize();i++)
		{
			if(ptr[j]==set1.getptr()[i])
			{
				common_count++;
			}
		}
	}
	int new_size=common_count; //same logic for the new size, common many elements must be creates
	IntegerSet intersectionSet(new_size); //new set is created
	int s=0;
	for(int i=0; i<size;i++)
	{
		if(ptr[i] <= set1) //if the elements of lhs are also in the rhs, add
		{
			intersectionSet.getptr()[s]=ptr[i];
			s++;
		}
	}
	return intersectionSet;


}