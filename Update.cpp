#include <iostream>
#include <time.h>

using namespace std;

const int boardX = 4;
const int boardY = 4;

class Square
{
private:
	bool isBomb;
	bool isHidden;
	bool isOccupied;
	int adjacentBombs;
public:
	Square();
	char getSquareType();
	void setBomb(bool);
	void setHint(int);
	bool getVisibility();
	int getHint();
};

Square :: Square()
{
	isBomb = false;
	isHidden = false;
	isOccupied = false;
	adjacentBombs = 0;
}

char Square :: getSquareType()
{
	if(isBomb)
		return 'X'; //B for Bomb
	else if (isOccupied)
		return 'o'; //O for Occupied
	else if (adjacentBombs > 0)
		return adjacentBombs;	//A for adjacent
	else return ' '; //E for empty
}

void Square :: setBomb(bool givenSet)
{
	isBomb = givenSet;
}

void Square :: setHint(int calculatedHint)
{
	adjacentBombs = calculatedHint;
}

int Square :: getHint()
{
	return adjacentBombs;
}

class player
{
private:

public:

};

void generateBoard(Square board[boardX][boardY]);
void drawBoard(Square board[boardX][boardY]);
void setHint(Square board[boardX][boardY], int, int);

int main()
{
	 srand(time(NULL));
	Square board[boardX][boardY];
	generateBoard(board);
	drawBoard(board);
	return 0;
}

void generateBoard(Square board[boardX][boardY])
{
	for(int i = 0; i < boardX; i++)
	{
		for(int j = 0; j < boardY; j++)
		{
			bool setTo = rand()%2;
			board[i][j].setBomb(setTo);
		}
	}
}

void drawBoard(Square board[boardX][boardY])
{
	for(int i = 0; i < boardX; i++)
	{
		for(int j = 0; j < boardY; j++)
		{
			cout << "|" 
			     << board[i][j].getSquareType()
				 << "|";
		}
		cout << endl;
	}
}
