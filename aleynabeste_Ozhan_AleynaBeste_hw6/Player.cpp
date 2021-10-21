#include "Player.h"
#include "Board.h"
#include<iostream>
#include<string>

using namespace std;

void Player::move (int cell_num)
{
	for(int i=0; i < cell_num; i++) //I must take this many steps
	{
		if(rotation==1) //if its moving in clockwise direction
		{
			if(row==0) //if player is in the upper row, it should go to the right
			{
				if(0<=col && col<5)
				{
					col=col+1; //right=increase column
				}
				else if(col==5) //if it hits the boundary it should get down to the bottom row
				{
					row=1;
				}
			}
			else if(row==1) //if its in the bottom row, player should go to the left
			{
				if(0<col && col<6)
				{
					col=col-1; //left=decrease column
				}
				else if(col==0) //if hits the boundary
				{
					row=0; //jumps to upper row
				}
			}

		}
	
		else if(rotation==0) //same logic but here is vice versa because its counter cw
		{
			if(row==0)
			{
				if(0<col && col<6)
				{
					col=col-1;
				}
				else if(col==0)
				{
					row=1;
				}
			}	
			else if(row==1)
			{
				if(0<=col && col<5)
				{
					col=col+1;
				}
				else if(col==5)
				{
					row=0;
				}
			}
		}
	}
}
void Player::claimOwnership()
{
	if (board.getOwner(row,col)=='-') //if it is not occupied yet, board member function
	{
		board.setOwner(row,col,playerChar); //player get ownership of this cell by writing its char
	}
	
}

bool Player::wins()
{
	if (board.countOwnedCells(playerChar)==7) //board member function to get the count of occupied cell by a player
	{
		return true; // 7 means win
	}
	else
		return false;

}

int Player::getRow() const
{
	return row;
}

int Player::getCol() const
{
	return col;
}