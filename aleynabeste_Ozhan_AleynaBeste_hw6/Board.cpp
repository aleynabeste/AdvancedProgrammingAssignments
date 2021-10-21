#include "Board.h"
#include <iostream>

using namespace std; 

/* Begin: code taken but modified from Board.cpp from tictactoe exercise */
Board::Board() //costructor, initially all cells are -
{
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			theBoard[i][j] = '-';
		}
	}
}

void Board::displayBoard()const 
{
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			cout << theBoard[i][j] << " ";
		}
		cout << endl<< endl ; //space between rows
	}
	cout << endl;
}
/* end: code taken but modified from Board.cpp from tictactoe exercise */

char Board::getOwner(int row, int column)
{
	return theBoard[row][column]; //it returns the char existing in this cell, - means no owner
}
void Board::setOwner (int row, int column, char owner)
{
	if(theBoard[row][column]=='-') //if there is no owner yet
	{
		theBoard[row][column]=owner; //cell is filled with the name of player
	}
}

/* Begin: code taken but modified from Board.cpp from tictactoe exercise */
bool Board::isFull()const
{
	
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			if(theBoard[i][j]=='-')
			{
				return false; //once I find a - character, board is not ful
			}
		}
	}
	return true;
}
/* end: code taken but modified from  Board.cpp from tictactoe exercise */

int Board::countOwnedCells (char owner)
{
	int countCells = 0;
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<6; j++)
		{
			if(theBoard[i][j]==owner) //iterating over all cells and checking if cell is occupied by this player
			{
				countCells++; 
			}
		}
	}
	return countCells;
}