#include <iostream>
#include <string>
using namespace std;

bool index_is_1_at_i (unsigned char plain, int i) //this function returns true if an unsigned char's bit value equals to 1 at index i. 
{
	if ((plain & (1 << i )) !=0) 
		//if given index's value is 1, then plain AND all 0s except the bit value(0000 0001 for index 0) at index=1 must
		// have bit 1 at that index which makes it different than zero (1 and 1 = 1)
		return true;
	else
		return false;
}

unsigned char  function_P (unsigned char plain) // This function makes the required encryption described in hw as function p. 
{
	unsigned char cipher ='a'; //the initial value doesnt matter, the function is going to change it anyways and return it as final version. 
	//Here cipher char is what function will return. 

	if (index_is_1_at_i(plain, 0)) 
		//firt we have to know what bit value we have at index 0 because function must set bit value at index 2(index of the output char) to value at index 0
	{
		cipher= cipher | (1 << 2); 
		//If we have bit value 1 at index 0: cipher char OR 0000 0100 will make 2nd index of cipher char 1 because 1 OR anything is 1. 
		//Other indices wont change because 0 or 1 = 1 no change for the original bit value, 0 or 0= 0 no change for the original bit value.  
	}
	else
	{
		cipher = cipher & ~ (1 << 2); 
		//Else if we have bit value 0 at index 0, cipher char AND 1111 1011 make 2nd index 0, because 0 and anything is 0. 
		//Other indices wont change because 1 and 0 is 0=no change for the original bit value, 1 and 1=1, no change for the original bit value. 
	}
	

	if (index_is_1_at_i(plain, 1)) //bit value at index 1 will move to to index 0
	{
		cipher= cipher | (1 << 0); //cipher or 0000 0001
	}
	else
	{
		cipher = cipher & ~ (1 << 0); //cipher and 1111 1110
	}

	//same logic for the other cases

	if (index_is_1_at_i(plain, 2)) //bit value at index 2 will move to to index 3
	{
		cipher= cipher | (1 << 3);
	}
	else
	{
		cipher = cipher & ~ (1 << 3);
	}

		
	if (index_is_1_at_i(plain, 3)) //bit value at index 3 will move to to index 1
	{
		cipher= cipher | (1 << 1);
	}
	else
	{
		cipher = cipher & ~ (1 << 1);
	}

	
	if (index_is_1_at_i(plain, 4)) //bit value at index 4 will move to to index 6
	{
		cipher= cipher | (1 << 6);
	}
	else
	{
		cipher = cipher & ~ (1 << 6);
	}

	

	if (index_is_1_at_i(plain, 5)) //bit value at index 5 will move to to index 4
	{
		cipher= cipher | (1 << 4);
	}
	else
	{
		cipher = cipher & ~ (1 << 4);
	}
	
	if (index_is_1_at_i(plain, 6)) //bit value at index 6 will move to to index 7
	{
		cipher= cipher | (1 << 7);
	}
	else
	{
		cipher = cipher & ~ (1 << 7);
	}

	
	if (index_is_1_at_i(plain, 7)) //bit value at index 7 will move to to index 5
	{
		cipher= cipher | (1 << 5);
	}
	else
	{
		cipher = cipher & ~ (1 << 5);
	}

	return cipher; //resulting char 
}

int main ()
{
	cout << "*** Welcome to the Simple Data Encryption Application ***" << endl;
	cout << "Please enter the encryption key: ";
	string key;
	getline (cin, key);
	
	cout << "Please enter the plaintext to be encrypted: ";
	string line;
	unsigned char a;
	while (getline (cin, line)) // loop until user enters ^Z. Here, we are taking as line because we want to keep spaces as well
	{
		cout << "Ciphertext: " ;
		int count=0;
		for (int k=0; k < line.length(); k++ ) //for each character in the string, the function P will be applied
		{
			a=line[k];
			unsigned char after_f= function_P(a);
			int index= count % key.length(); 
			// every time we are using next character of key, if key length is smaller than the plain text then we will return to the beginning of key. 
			//Thats why here we used modulus.
			after_f= after_f ^ key[index]; //XOR operation between char returned from function P and corresponding char of key. 
			count ++; 
			cout << hex << int (after_f); //printing out the hex equivalent
		
		}
		cout <<  '\n' << '\n' << "Please enter the plaintext to be encrypted: ";
	}
	
	cin.get();
	cin.ignore(); 
	return 0;
}