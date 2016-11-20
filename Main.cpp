#include <iostream>
#include <time.h>
#include <string>
#include <windows.h>

using namespace std;

int playerPositionX = 0;
int playerPositionY = 0;

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
};

class Board
{
private:
	int rows;
	int cols;
	Square** board;
public:
	Board();
	Board(int rows, int cols);
	int getRows();
	int getCols();
	void generateBoard();
	void drawBoard();
	void calculateHints();
};


class player
{
private:

public:

};




// Square class definitions
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

void Square::setVisibility(bool newVisibility)
{
	isHidden = newVisibility;
}

void Square::setOccupancy(bool newOccupancy)
{
	isOccupied = newOccupancy;
}

bool Square::getOccupancy()
{
	return isOccupied;
}

int getPlayerPositionX()
{
	return playerPositionX;
}

int getPlayerPositionY()
{
	return playerPositionY;
}

void setPlayerPositionX(int newX)
{
	playerPositionX = newX;
}

void setPlayerPositionY(int newY)
{
	playerPositionY = newY;
}


// Board class definitions
Board::Board()
{
	rows = 8;
	cols = 8;
	board = new Square*[rows];
	for (int i = 0; i < rows; ++i)
		board[i] = new Square[cols];
}

Board::Board(int givenRows, int givenCols)
{
	rows = givenRows;
	cols = givenCols;
	board = new Square*[rows];
	for (int i = 0; i < rows; ++i)
		board[i] = new Square[cols];
}

int Board::getRows()
{
	return rows;
}

int Board::getCols()
{
	return cols;
}

void Board::generateBoard()
{
	int totalBombs = rows * cols / 2;
	int rowBombs = rows - 1;
	int * columnBombs = new int[cols];
	for (int column = 0; column < cols; column++)
		columnBombs[column] = cols - 1;

	for (int i = 0; i < rows; i++)
	{
		if (totalBombs > 0)
		{
			rowBombs = rows - 1;
		}

		for (int j = 0; j < cols; j++)
		{
			bool isBomb = false;
			int willBeBomb = rand() % 2;
			if (willBeBomb == 0)
				isBomb = true;

			if (rowBombs > 0 && columnBombs[j] > 0 && totalBombs > 0 && isBomb == true)
			{
				board[i][j].setBomb(isBomb);
				rowBombs--;
				columnBombs[j]--;
				totalBombs--;
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
	/*cout << "hint:" << board[0][0].getHint() << "  --  hint:" << board[0][1].getHint() << " -- hint:" << board[0][2].getHint() << " -- hint:" << board[0][3].getHint();
	cout << " -- hint:" << board[0][4].getHint() << " -- hint:" << board[0][5].getHint();*/
}

void Board::calculateHints()
{
	int bombCount = 0;
	int currentRow = 0;
	int currentCol = 0;

	// For every square in the array...
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			// Check all surrounding squares for bombs and add to counter when one found
			bombCount = 0;
			for (int i = -1; i < 2; i++)
			{
				if (currentRow + i < 0)
				{
					continue; //Skip row if out of bounds
				}
				if (currentRow + i < rows)
				{
					//
					for (int j = -1; j < 2; j++)
					{
						if (currentCol + j < 0)
						{
							continue; //Skip cell if out of bounds
						}
						if (i == 0 && j == 0)
						{
							continue; //Skip cell if same as given cell
						}
						if (currentRow + j < cols)
						{
							if (board[currentRow + i][currentCol + j].getBombStatus())
							{
								bombCount++;
							}
						}
					}
				}
			}
			// One the bomb count is found, set the hint for the current square and move on to the next square
			board[currentRow][currentCol].setHint(bombCount);
			currentCol++;
		}
		currentRow++;
	}
}


bool checkMovementValidity(int mockPositionX, int mockPositionY)
{
	Board board;
	enum Blocked { Left, Right, Up, Down, None };
	Blocked blockedMove = None;
	if (mockPositionX > board.getRows())
		blockedMove = Right;
	else if (mockPositionY > board.getCols())
		blockedMove = Down;
	else if (mockPositionX < 0)
		blockedMove = Left;
	else if (mockPositionY < 0)
		blockedMove = Up;
	if (blockedMove == None)
		return 1;
	else
		return 0;
}

void playerMovement()
{
	int mockPositionX;
	int mockPositionY;
	string playerMove;
	cout << "Player position is: " << getPlayerPositionX() << ", " << getPlayerPositionY() << endl;
	cout << "Where do you want to move? ";
	getline(cin, playerMove);
	mockPositionX = getPlayerPositionX();
	mockPositionY = getPlayerPositionY();
	if (playerMove == "Down")
	{
		mockPositionY = mockPositionY + 1;
	}
	else if (playerMove == "Up")
	{
		mockPositionY = mockPositionY - 1;
	}
	else if (playerMove == "Right")
	{
		mockPositionX = mockPositionX + 1;
	}
	else if (playerMove == "Left")
	{
		mockPositionX = mockPositionX - 1;
	}

	else if (playerMove == "UpLeft")
	{
		mockPositionY = mockPositionY - 1;
		mockPositionX = mockPositionX - 1;
	}
	else if (playerMove == "UpRight")
	{
		mockPositionY = mockPositionY - 1;
		mockPositionX = mockPositionX + 1;
	}
	else if (playerMove == "DownRight")
	{
		mockPositionY = mockPositionY + 1;
		mockPositionX = mockPositionX + 1;
	}
	else if (playerMove == "DownLeft")
	{
		mockPositionY = mockPositionY + 1;
		mockPositionX = mockPositionX - 1;
	}
	else
		cout << "Invalid move!";
	if (checkMovementValidity(mockPositionX, mockPositionY))
	{
		setPlayerPositionX(mockPositionX);
		setPlayerPositionY(mockPositionY);
	}
	else
		cout << "Invalid move!";
}

void runGame()
{
	bool stop = false;
	Board Level1 = Board();
	srand(time(NULL));
	Level1.generateBoard();
	Level1.calculateHints();
	Level1.drawBoard();
	while (true)
	{
		playerMovement();
	}
}

void clearScreen()
{
	cout << "\033[2J\033[1;1H";
}

void mainMenu()
{
	string menuChoices[4] = { "Single Player", "Multi-Player", "About", "Exit" };
	int pointer = 0;

	while (true)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "Maze-Minesweeper\n\n";
		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				cout << menuChoices[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << menuChoices[i] << endl;
			}
		}
		while (true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer--;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer++;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{
				case 0:
				{
					cout << "\n\n\nStarting new game...";
					Sleep(1000);
					clearScreen();
					cin.ignore();
					runGame();
				} break;
				case 1:
				{
					cout << "\n\n\nThis is the mutli-player...";
					Sleep(1000);
				} break;
				case 2:
				{
					cout << "\n\n\nThis is the about page...";
					Sleep(1000);
				} break;
				case 3:
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //Reset Colours
					cout << "\n\n\nGood bye :)\n";
					Sleep(1000);
					exit(0);
				} break;
				}
				break;
			}
		}

		Sleep(150);
	}
}

int main()
{


	mainMenu();
	return 0;
}