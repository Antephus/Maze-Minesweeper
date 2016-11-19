#include <iostream>
#include <time.h>

using namespace std;


// Class definitions
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
	void setBomb(bool bombStatus);
	void setHint(int bombCount);
	int getHint();
	bool getVisibility();
	void setVisibility(bool visibility);
	void setOccupancy(bool occupancy);
	bool getOccupancy();
	int calculateHint(int, int, Board);
};

class Board
{
private:
	const int rows;
	int cols;
	Square board[rows][cols];
public:
	Board();
	Board(int rows, int cols);
	int getRows();
	int getCols();
	void generateBoard();
	void drawBoard();
	int** getBoard();
};


class player
{
private:

public:

};

// Constructors
Square::Square()
{
	isBomb = false;
	isHidden = false;
	isOccupied = false;
	adjacentBombs = 0;
}

Board::Board()
{
	rows = 8;
	cols = 8;
	board[rows][cols] = { 0 };
}

Board::Board(int givenRows, int givenCols)
{
	rows = givenRows;
	cols = givenCols;
	board[rows][cols] = { 0 };
}


// Square class function definitions
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

void Square::setVisibility(bool newVisibility)
{
	isHidden = newVisbility;
}

void Square::setOccupancy(bool newOccupancy)
{
	isOccupied = newOccupancy;
}

bool Square::getOccupancy()
{
	return isOccupied;
}

int Square::calculateHint(int chosenRow, int chosenCol, Board currentBoard)
{
	int bombCount = 0;
	int scanRow = chosenRow - 1;
	int scanCol = chosenCol - 1;
	Square squares[currentBoard.getRows()][currentBoard.getCols()] = currentBoard.getBoard();

	for (int i = 0; i < 3; i++)
	{
		if (scanRow + i < 0) i++; //Skip row if out of bounds
		if (scanRow + i < currentBoard.getRows())
		{
			for (int j = 0; j < 3; j++)
			{
				if (scanCol + j < 0) j++; //Skip cell if out of bounds
				if (i == 1 && j == 1) j++; //Skip cell if same as given cell
				if (scanRow + j < currentBoard.getCols())
				{
					if (currentBoard.getBoard()[scanRow + i][scanCol + j].getBombStatus())
						bombCount++;
				}
			}
		}
	}
	return bombCount;
}


// Board class method definitions
int Board::getRows()
{
	return rows;
}

int Board::getCols()
{
	return cols;
}

int** Board::getBoard()
{
	return board;
}

void Board::generateBoard()
{
	int totalBombs = rows * cols / 2;
	int rowBombs = rows - 1;
	int columnBombs[cols];
	for (int column = 0; column < cols; column++)
		columnBombs[column] = cols - 1;

	for (int i = 0; i < rows; i++)
	{
		if (totalBombs > 0)
			rowBombs = rows - 1;

		for (int j = 0; j < cols; j++)
		{
			bool setTo = false;
			int willBeBomb = rand() % 2;
			if (willBeBomb == 0) setTo = true;

			if (rowBombs > 0 && columnBombs[j] > 0 && totalBombs > 0 && setTo == true)
			{
				board[i][j].setBomb(setTo);
				rowBombs--; columnBombs[j]--; totalBombs--;
			}
		}
	}
}

void Board::drawBoard()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
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



int main()
{
	Board Level1 = Board();
	srand(time(NULL));
	generateBoard(Level1);
	drawBoard(Level1);
	return 0;
}