#include <iostream>
#include <thread>

#include <random> 
#include <time.h>
#include <iomanip>  // for put_time       
#include <chrono> // for chrono::system_clock
#include <ctime>  // for time_t, tm, localtime, mktime
#include <mutex>  //to use mutex
#include "HW8DynIntQueue.h"

using namespace std;


int count_index = 1; //this global variable is to keep the track of customers

mutex myMutex,coutMutex; 

HW8DynIntQueue market_queue; //shared queue object

int random_range(const int & min, const int & max) //given function for the random number generation
{ 
	static mt19937 generator(time(0)); 
	uniform_int_distribution<int> distribution(min, max); 
	return distribution(generator); 
}

void arrival(int num_of_customers, int min, int max) //arrival thread uses this function. It takes parameters for customer amount and min max for arrival range in sec
{
	for(int i = 0; i <num_of_customers; i++) //until the final customer arrives
	{
		int arrival_time=random_range(min,max); //random arrival ranges for each customer, doesnt need to be in locked mutex since its local variable
		myMutex.lock();
	
		market_queue.enqueue(i); //while mutex is locked, enqueue the i'th customer
		int size=market_queue.getCurrentSize(); //current size while mutex is locked is necessary for printing out the info message. store it in a local variable
		myMutex.unlock();

		coutMutex.lock(); //for output purpose only
		time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
		struct tm *ptm = new struct tm; 
		localtime_s(ptm, &tt); 
		cout <<"New customer with ID "<<i+1<<" has arrived (queue size is " << size<< "): "<< put_time(ptm,"%X") <<endl;
		coutMutex.unlock();
		this_thread::sleep_for(chrono::seconds(arrival_time)); //sleep the thread before another customer comes, this is inter arrival time. 
	}
}
void cashier1 (const int min, const int max, int num_of_customers) //function for cashier1. Takes min max for transaction range and num of customers
{
	int transaction_time=random_range(min,max);//another random time for transaction duration within min max range 
	this_thread::sleep_for(chrono::seconds(transaction_time)); //there is a sleeping process right after simulation starts
	int item;
	while(count_index <= num_of_customers) //until final customer arrival
	{
		myMutex.lock();
		if (!market_queue.isEmpty()) //check if queue is empty after locking
		{  
			transaction_time=random_range(min,max); //generate another random transaction time for each customer differently
			int temp_count= count_index; //for output operation, store the current customer id before unlocking 
			count_index++; //increment the count for customers since this one is gone
			
			market_queue.dequeue(item); 
			int size=market_queue.getCurrentSize(); //store the size at that point after dequeueing, for output operation
			myMutex.unlock();

			coutMutex.lock(); //for output
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout <<"Cashier 1 started transaction with customer "<< temp_count <<" (queue size is " << size<< "): "<< put_time(ptm,"%X") <<endl;
			coutMutex.unlock();	
			this_thread::sleep_for(chrono::seconds(transaction_time)); // simulation for transaction duration

			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			//ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<< "Cashier 1 finished transaction with customer "<< temp_count <<": " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
		}
		else
			myMutex.unlock();
	}
}

void cashier2 (const int min, const int  max, int num_of_customers, int threshold)
{
	int transaction_time=random_range(min,max);
	int item;
	this_thread::sleep_for(chrono::seconds(transaction_time));
	while(count_index <= num_of_customers) //all of the operations are same as cashier 1 but this time another condition
	{
		transaction_time=random_range(min,max);
		myMutex.lock();
		if (market_queue.getCurrentSize()>=threshold && !market_queue.isEmpty() ) //we need queue size to be greater than or equal to threshold, in order to let cashier2 start
		{  
			int temp_count=count_index;
			count_index++;
			market_queue.dequeue(item);
			int size=market_queue.getCurrentSize();
			myMutex.unlock();

			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout <<"Cashier 2 started transaction with customer "<< temp_count <<" (queue size is " << size<< "): "<< put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
			
			this_thread::sleep_for(chrono::seconds(transaction_time)); // simulation for consume

			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			//ptm = new struct tm; 
			localtime_s(ptm, &tt); 
			cout<< "Cashier 2 finished transaction with customer "<< temp_count <<": " << put_time(ptm,"%X") <<endl;
			coutMutex.unlock();
			
		}
		else
		{
			myMutex.unlock();
		}
	}
}


int main() 
{

	int total_customer_count, cashier2_threshold, min_arrival,
		min_checkout_time, max_arrival, max_checkout_time;

	//required parameters are asked to user. We assume that all inputs are correct. 
	cout << "Please enter the total number of customers: ";
	cin >> total_customer_count;

	cout << "Please enter the number of customers waiting in the queue to open the second cashier: "; 
	cin >> cashier2_threshold;

	cout << "Please enter the inter-arrival time range between two customers:" 
		<< endl << "Min: ";
	cin >> min_arrival;

	cout << "Max ";
	cin >> max_arrival;
	

	cout << "Please enter the checkout time range of cashiers:"
		<< endl << "Min: " ;
	cin >> min_checkout_time;

	cout <<"Max: ";
	cin >> max_checkout_time;

	//lines provided by professor to gets the current time
	time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  
	struct tm *ptm = new struct tm;  
	localtime_s(ptm, &tt);  
	cout << "Simulation starts " << put_time(ptm,"%X") << endl;  
	
	//start the threads
	thread customer(&arrival,total_customer_count,min_arrival,max_arrival);
	thread cashier(&cashier1, min_checkout_time,max_checkout_time, total_customer_count);
	thread backup_cashier(&cashier2, min_checkout_time,max_checkout_time, total_customer_count,cashier2_threshold);
	//join all of them to do not crash
	customer.join();
	cashier.join();
	backup_cashier.join();
	
	tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
	//ptm = new struct tm; 
	localtime_s(ptm, &tt); 
	cout << "End of the simulation ends: " << put_time(ptm,"%X")<< endl;
	
	cin.get();
	cin.ignore();
	return 0;
}