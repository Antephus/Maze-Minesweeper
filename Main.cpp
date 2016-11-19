#include <iostream>
#include <time.h>

using namespace std;

const int ROWS = 8;
const int COLS = 8;

class Square
{
private:
	bool isBomb;
	bool isHidden;
	bool isOccupied;
	int adjacentBombs;
public:
	Square();
	bool getBombStatus();
	void setBomb(bool);
	void setHint(int);
	bool getVisibility();
	int getHint();
};

Square::Square()
{
	isBomb = false;
	isHidden = false;
	isOccupied = false;
	adjacentBombs = 0;
}

bool Square::getBombStatus()
{
	return isBomb;
}

void Square::setBomb(bool givenSet)
{
	isBomb = givenSet;
}

void Square::setHint(int calculatedHint)
{
	adjacentBombs = calculatedHint;
}

int Square::getHint()
{
	return adjacentBombs;
}

bool Square::getVisibility()
{
	return isHidden;
}

class player
{
private:

public:

};

void generateBoard(Square board[ROWS][COLS]);
void drawBoard(Square board[ROWS][COLS]);
void setHint(Square board[ROWS][COLS], int, int);

int main()
{
	srand(time(NULL));
	Square board[ROWS][COLS];
	generateBoard(board);
	drawBoard(board);
	return 0;
}

void generateBoard(Square board[ROWS][COLS])
{
	int totalBombs = ROWS * COLS / 2;
	int rowBombs = ROWS - 1;
	int columnBombs[COLS];
	for (int column = 0; column < COLS; column++)
		columnBombs[column] = COLS - 1;

	for (int i = 0; i < ROWS; i++)
	{
		if (totalBombs > 0)
			rowBombs = ROWS - 1;

		for (int j = 0; j < COLS; j++)
		{
			bool setTo = false;
			int willBeBomb = rand() % 2;
			if (willBeBomb == 0 ) setTo = true;

			if (rowBombs > 0 && columnBombs[j] > 0 && totalBombs > 0 && setTo == true)
			{
				board[i][j].setBomb(setTo);
				rowBombs--; columnBombs[j]--; totalBombs--;
			}
		}
	}
}

void drawBoard(Square board[ROWS][COLS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			cout << "|";
			
			if (!board[i][j].getVisibility())
			{
				if (board[i][j].getBombStatus() == 1)
					cout << "*";
				else cout << " ";
			}
			else
				cout << " ";

			cout << "|";
		}
		cout << endl;
	}
}


int calculateAdjacentBombs(int chosenRow, int chosenCol, Square board[ROWS][COLS])
{
	int bombCount = 0;
	int scanRow = chosenRow - 1;
	int scanCol = chosenCol - 1;

	for(int i = 0; i < 3; i++)
	{
		if (scanRow + i < 0) i++; //Skip row if out of bounds
		if (scanRow + i < ROWS)
		{
			for(int j = 0; j < 3; j++)
			{	
				if (scanCol + j < 0) j++; //Skip cell if out of bounds
				if (i == 1 && j == 1) j++; //Skip cell if same as given cell
				if (scanRow + j < COLS)
				{			
					if(board[scanRow + i][ scanCol + j].getBombStatus())
						bombCount++;
				}
			}
		}
	}
	return bombCount;
}