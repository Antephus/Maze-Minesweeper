#include <iostream>
#include <time.h>

using namespace std;

const int ROWS = 4;
const int COLS = 4;

class Square
{
private:
	bool isBomb;
	bool isHidden;
	bool isOccupied;
	int adjacentBombs;
public:
	Square();
	char getBombStatus();
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

bool Square :: getSquareType()
{
	return isBomb;
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

void generateBoard(Square board[ROWS][COLS])
{
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			bool setTo = rand()%2;
			board[i][j].setBomb(setTo);
		}
	}
}

void drawBoard(Square board[ROWS][COLS])
{
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
			cout << "|" 
			     << board[i][j].getSquareType()
				 << "|";
		}
		cout << endl;
	}
}


int calculateAdjacentBombs(int chosenRow, int chosenCol, Square board[ROWS][COLS])
{
	int bombCount;
	int currentRow = chosenRow - 1;
	int currentCol = chosenCol - 1;

	// For every row
	for (int r = 0; r <= 3; r++)
	{
		// If the current row exists (isn't outwith the bounds of the board)
		if (currentRow >= 0 && currentRow <= boardRows)
		{
			//For every column
			for (int c = 0; col <= 3; c++)
			{

				// If the current column exists (isn't outwith the bounds of the board)
				if (col >= 0 && col <= boardCols)
				{

					// As long as the current square isn't the one originally selected and it has a bomb, add 1 to the bomb counter
					if (!(currentRow == chosenRow && currentCol == chosenCol) && board[currentRow][currentCol].getBombStatus())
						bombCount++;

					// Move on to next col
					col++;
				}

				// Move on to next row
				row++;
			}
		}
	}
}
