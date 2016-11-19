#include <iostream>
#include <time.h>
#include <string>
#include <windows.h>

using namespace std;

const int ROWS = 4;
const int COLS = 4;

int playerPositionX = 0;
int playerPositionY = 0;

enum Blocked { Left, Right, Up, Down, None };

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
	playerPositionX=newX;
}

void setPlayerPositionY(int newY)
{
	playerPositionY=newY;
}


class player
{
private:

public:

};

void generateBoard(Square board[ROWS][COLS]);
void drawBoard(Square board[ROWS][COLS]);
void playerMovement();
void setHint(Square board[ROWS][COLS], int, int);

void runGame()
{
	srand(time(NULL));
	Square board[ROWS][COLS];
	generateBoard(board);
	drawBoard(board);
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
				pointer --;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer ++;
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
			cout << "|"
				<< board[i][j].getBombStatus()
				<< "|";
		}
		cout << endl;
	}
}

bool checkMovementValidity(int mockPositionX, int mockPositionY)
{
	enum Blocked { Left, Right, Up, Down, None };
	Blocked blockedMove=None;
	if (mockPositionX > ROWS)
		blockedMove = Right;
	else if (mockPositionY > COLS)
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
	cin.ignore(); //Flushes cin :)
	getline(cin, playerMove);
	mockPositionX = getPlayerPositionX();
	mockPositionY = getPlayerPositionY();
	if (playerMove == "Down")
	{
		mockPositionY= mockPositionY + 1;
	}
	if (playerMove == "Up")
	{
		mockPositionY = mockPositionY - 1;
	}
	if (playerMove == "Right")
	{
		mockPositionX = mockPositionX + 1;
	}
	if (playerMove == "Left")
	{
		mockPositionX = mockPositionX - 1;
	}

	if (playerMove == "UpLeft")
	{
		mockPositionY = mockPositionY - 1;
		mockPositionX = mockPositionX - 1;
	}
	if (playerMove == "UpRight")
	{
		mockPositionY = mockPositionY - 1;
		mockPositionX = mockPositionX + 1;
	}
	if (playerMove == "DownRight")
	{
		mockPositionY = mockPositionY + 1;
		mockPositionX = mockPositionX + 1;
	}
	if (playerMove == "Downleft")
	{
		mockPositionY = mockPositionY + 1;
		mockPositionX = mockPositionX - 1;
	}
	if (checkMovementValidity(mockPositionX, mockPositionY) == true)
	{
		setPlayerPositionX(mockPositionX);
		setPlayerPositionY(mockPositionY);
	}
	else
		cout << "Invalid move!";
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

int main()
{
	mainMenu();
	return 0;
}
