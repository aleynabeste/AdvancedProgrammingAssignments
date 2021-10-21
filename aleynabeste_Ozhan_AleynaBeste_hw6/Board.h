#ifndef BOARD_H
#define BOARD_H

#include<string>
using namespace std;
class Board
{
	public:
		Board();
		
		char getOwner (int row, int column); //returns the current owner of a cell
		void setOwner (int row, int column, char owner); //player gets the cell by writing its name
		bool isFull()const; //checks if board is completely occupied by players
		int countOwnedCells (char owner); //return num of cells occupied by a player
		void displayBoard()const; //printing the board


	private:
		char theBoard[2][6]; //it a not dynamic

};
#endif