#include <iostream>
#include <time.h>
// blahb lhs bjkgfe
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
	int totalBombs = ROWS * 2;
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
			bool setTo = rand() % 2;
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
			
			if (board[i][j].getBombStatus() == 1)
				cout << "*";
			
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
	int currentRow = chosenRow - 1;
	int currentCol = chosenCol - 1;

	// For every row around the chosen square, as long as we're not at the top/bottom edge of the board...
	for (int row = 0; row <= 3; row++)
	{
		if (currentRow >= 0 && currentRow <= ROWS)
		{
			// For every column around the chosen square, as long as we're not at the right/left edge of the board...
			for (int col = 0; col <= 3; col++)
			{
				if (currentCol >= 0 && currentCol <= COLS)
				{
					// If the current square isn't the one originally selected, and it has a bomb, add 1 to the bomb counter
					if (!(currentRow == chosenRow && currentCol == chosenCol) && board[currentRow][currentCol].getBombStatus())
						bombCount++;
				}
				col++;
			}
		}
		row++;
	}

	return bombCount;
}
