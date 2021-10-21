#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include<string>
#include<iostream>
using namespace std;
class Player
{
	public:
		Player(); //constructor, passing myboard as reference since it must effect the board object, I dont want a copy of it.
		Player::Player(Board &myboard,char o, int m )
		: board(myboard), playerChar(o), rotation(m), row(0), col(0) //initially at 0,0. rotation and name are input
		{ }

		void move(int cell_num); //moving as many step as cell_num
		void claimOwnership(); //cell is getting occupied by this player
		bool wins(); //check if occupied cell number is 7, in this case it is win
		int getRow() const; //accessors
		int getCol() const;


	private:

		//Referenced variable (shared object between two players)
		Board &board;
		int row;
		int col;
		int rotation; //1 and 0, clockwise and counterclockwise
		char playerChar;
};

#endif