#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

//I create a struct because I wanna keep the matrix character name like x or o and plus, if this character is visited or not. 
struct elements {
  char XorO;
  bool Visited;
} ;


//print function for a vector in the type of struct defined above
void Print(const vector<vector<elements>> & mat)
{
	for (int j=0; j < mat.size(); j++){   

		for (int k=0; k < mat[0].size(); k++){  

			cout << setw(3) << mat[j][k].XorO; //I use setw to adjust spacing
		}
		cout << endl;
	}
}
//print function of an integer matrix

void Print(const vector<vector<int>> & mat)
{
	if(mat[0][0]==mat[mat.size()-1][0] && mat[0][1]==mat[mat.size()-1][1])
	{
		for (int j=0; j < mat.size()-1; j++){   

			for (int k=0; k < mat[0].size(); k++){  

				cout << setw(3) << mat[j][k]; //I use setw function to adjust spacing
			}
			cout << endl;
		}
	}
	else
	{
		for (int j=0; j < mat.size(); j++){   

			for (int k=0; k < mat[0].size(); k++){  

				cout << setw(3) << mat[j][k];
			}
			cout << endl;
		}
	}
	
}
//function that checks if the user given coordinates are valid
int startingCoordinateCheck(vector<vector<elements>> matrix, int x, int y)
{
	if( x == -1 && y == -1 ) //if termination order is given
	{
		return 1;

	}
	else if( (x < 0 ) || (x >= matrix.size()) || (y < 0 ) || (y >= matrix[0].size())) //to check if coordinates are not out of boundaries. 
	{
		return 2;
	}
	else if ( matrix[x][y].XorO=='o') //to check if given coordinate is empty
	{
		return 4;
	}
	else //if everything is ok
	{
		return 3;
	}

}


int main()
{
	string file_name;
	cout << "Please enter file name: " ;
	cin >> file_name;
	ifstream inputFile;
	inputFile.open(file_name);
	while(inputFile.fail()) //I want my user to enter file name until its correct 
	{
		cout << "Cannot find a file named" << " " << file_name << endl;
		cout << "Please enter file name: " ;
		cin >> file_name;
		inputFile.open(file_name);
	}
	vector<vector<elements>> matrix;
	int count=0;
	string line;
	int check_invalid=0;
	while(!inputFile.eof()) //I read my file until the end of it
	{
		getline(inputFile, line);
		istringstream ss(line);
		
		char element;
		vector<elements> temp;
		
		while(ss >> element)
		{
			
			if((element == 'x') || (element== 'o')) //my element must be x or o, other chars are invalid
			{
				elements e;
				e.Visited=false;//firs, when creating my matrix, I want all of my elements to be not visited yet
				e.XorO=element;
				temp.push_back(e);//I create a temporary matrix to store the info
			}
			else {
				check_invalid++; //I dont want to print invalid char error each time so I create an integer any everytime my character is wrong, I increase it
			
				count++;//This one is also to check if something is wrong		
			}
		}
	
		matrix.push_back(temp);//I add my temp vectors to matrix.
	}
	if( check_invalid!=0)//if something is wrong, then invalid check must have been increased. 0 means everything is ok.
	{
		cout << file_name << " " << "includes invalid char(s)" <<  endl; //First, I check for invalid chars
	}
	int rows = matrix.size();
	int cols = matrix[0].size();
	for (int j=0; j<rows-1; j++)
	{
		if(matrix[j].size()!=matrix[j+1].size() && count==0) //second, I check for row size
		{  
			cout << file_name << " is invalid matrix, does not contain same amount of char each row!"<< endl; 
			count++; //Again, if I have a problem here, my check integer will be increased
			
		}
	}
	if (count==0)//If my check integer is not increased, this means everything is ok. Now I can take input for coordinates
	{
		cout << "Input Matrix: "<< endl;
		Print(matrix);
	

		int Cordx, Cordy;
		cout << "Please enter starting coordinates, first row X then column Y: ";
		cin >> Cordx >> Cordy;

		int check=startingCoordinateCheck(matrix, Cordx, Cordy);
		while(check!=1)//meaning that if user has not entered -1 -1 yet, I am continuing to check
		{
			while (!cin || check==2) //if input is string or out of boundary integer, my check function will return 2
			{
				cin.clear(); //to clear strings etc if entered. 
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
	

				cout << "Invalid Coordinates" << endl;
				cout << "\n" ;
				cout << "Please enter starting coordinates, first row X then column Y: ";
				cin >> Cordx;
				cin >> Cordy;
				check= startingCoordinateCheck(matrix, Cordx, Cordy);
			}

			while( check==4) //4 means user has entered a start coordinate which points "o"
			{
				cout << "This cell is not occupied!" << endl;
				cout << "\n" ;
				cout << "Please enter starting coordinates, first row X then column Y: ";
				cin >> Cordx;
				cin >> Cordy;
				check= startingCoordinateCheck(matrix, Cordx, Cordy);
			
			}
	

			if (check==3)// 3 means coordinate is valid and I am ready to seek for a path
			{
				int initialx=Cordx;//I want to keep my initials because I will update my coordinate x and y everytime. 
				int initialy=Cordy;
				vector<int> temporary;//I create a temporary vector and matrix because I want to keep my visited coordinates in a matrix
				vector <vector<int>> temporaryM;
				temporary.push_back(Cordx);//my firs visited cell will be my start coordinate. 
				temporary.push_back(Cordy);
				temporaryM.push_back(temporary);
				
				
				bool while_check=true;
				while (while_check)
				{
					if( (Cordy+1) < matrix[0].size() && matrix[Cordx][Cordy].XorO==matrix[Cordx][Cordy+1].XorO && matrix[Cordx][Cordy+1].Visited==false && !(initialx==Cordx && initialy==Cordy+1))
					{//RIGHT CELL CHECK. I shpuldnt go out of boundary when I step right and it needs to be x also, and it cant be my starting coordinate. 
						temporary.clear();//Eeach time I clear my temporary vector 
						temporary.push_back(Cordx); //I add my new coordinates
						temporary.push_back(Cordy+1);
						temporaryM.push_back(temporary);//I add my coordinates to matrix
						matrix[Cordx][Cordy+1].Visited=true;//I make the visited cell as visited
						
						Cordy=Cordy+1;//I update coordinate
					}
					else if ( (Cordx+1) < matrix.size() && matrix[Cordx][Cordy].XorO==matrix[Cordx+1][Cordy].XorO && matrix[Cordx+1][Cordy].Visited==false && !(initialx==Cordx+1 && initialy==Cordy))
					{//DOWN CELL CHECK
						temporary.clear();
						temporary.push_back(Cordx+1);
						temporary.push_back(Cordy);
						temporaryM.push_back(temporary);
						matrix[Cordx+1][Cordy].Visited=true;
						
						Cordx=Cordx+1;
					}
					else if (Cordy-1 >= 0 && matrix[Cordx][Cordy].XorO==matrix[Cordx][Cordy-1].XorO && matrix[Cordx][Cordy-1].Visited==false && !(initialx==Cordx && initialy==Cordy-1))
					{//LEFT CELL CHECK
						temporary.clear();
						temporary.push_back(Cordx);
						temporary.push_back(Cordy-1);
						temporaryM.push_back(temporary);
						matrix[Cordx][Cordy-1].Visited=true;
						
						Cordy=Cordy-1;
					}
					else if (Cordx-1 >= 0 && matrix[Cordx][Cordy].XorO==matrix[Cordx-1][Cordy].XorO && matrix[Cordx-1][Cordy].Visited==false && !(initialx==Cordx-1 && initialy==Cordy))
					{//UP CELL CHECK
						temporary.clear();
						temporary.push_back(Cordx-1);
						temporary.push_back(Cordy);
						temporaryM.push_back(temporary);
						matrix[Cordx-1][Cordy].Visited=true;
						
						Cordx=Cordx-1;
					}

					else //if there is no way right down left up, it means it is end of the way.
					{
						while_check=false;//I exit loop
						if( (Cordx+1==initialx && Cordy==initialy) || (Cordx-1==initialx && Cordy==initialy) || (Cordx==initialx && Cordy-1==initialy) || (Cordx==initialx && Cordy+1==initialy))
						//If any neighbor of my end cell is my starting point, it means it s a closed path
						{
							if(temporaryM.size()==2) //if I have visited only two cells, it means my neighbor is my starting point but I dont have a closed path like 
								cout << "Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path: " << endl;
							else
								cout << "Found an enclosed area. The coordinates of the followed path: " << endl;
								
							
						
						}
						else if (Cordx==initialx && Cordy==initialy) //If I didnt move at all, its not a closed path
						{
							cout << "Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path: " << endl;
							cout << Cordx << setw(3) << Cordy << endl;

						
						}
						else 
						{
							cout << "Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path: "<< endl;
							
						}
					}
				}
				Print(temporaryM); 
				for (int j=0; j < matrix.size(); j++)
				{   
					for (int k=0; k < matrix[0].size(); k++)
					{  
						matrix[j][k].Visited=false; //I make my matrix elements as unvisited because I will find a path with new given starting coordinate
					}
					
				}
				cout << "\n";
				cout << "Please enter starting coordinates, first row X then column Y: ";
				cin >> Cordx;
				cin >> Cordy;
				check= startingCoordinateCheck(matrix, Cordx, Cordy);	//as long as user enters -1 -1, I keep asking

			}
		}

		if(check==1)//check 1 means user enters -1 -1
		{
			cout << "Terminating..." << endl;
		}
	}
	
	cin.get();
	cin.ignore();//end
	//ALEYNA BESTE OZHAN, 24921, ALEYNABESTE@SABANCIUNIV.EDU

	return 0;
}



