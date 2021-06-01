#include "GameBoard.h"
#include <ctime>
#include <windows.h>
void GameBoard::createBoard(int value)
{
	size = value;
	srand((int)time(0));
	gameOver = false;
	win = false;
	numMines = ceil((size * size) / 6.4);
	tilesLeft = (size * size) - numMines;
	tileArr.resize(size + 2, std::vector<Tile>(size + 2, Tile()));
	do
	{
		c1 = rand() % size + 1;
		if (c1 == 0)
			c1++;
		c2 = rand() % size + 1;
		if (c2 == 0)
			c2++;
		if (tileArr[c1][c2].CheckMine() == false)
		{
			tileArr[c1][c2].IsMine();
			numMines--;
		}
	} while (numMines > 0);
	for (int col = 1; col < size + 1; col++)
	{
		for (int row = 1; row < size + 1; row++)
		{
			if (tileArr[col][row].CheckMine() == false)
			{
				int count = 0;
				int C_left = col - 1;
				int C_right = col + 1;
				int R_down = row + 1;
				int R_up = row - 1;
				if (tileArr[C_left][row].CheckMine())
					++count;
				if (tileArr[C_right][row].CheckMine())
					++count;
				if (tileArr[col][R_down].CheckMine())
					++count;
				if (tileArr[col][R_up].CheckMine())
					++count;
				if (tileArr[C_left][R_up].CheckMine())
					++count;
				if (tileArr[C_left][R_down].CheckMine())
					++count;
				if (tileArr[C_right][R_up].CheckMine())
					++count;
				if (tileArr[C_right][R_down].CheckMine())
					++count;
				tileArr[col][row].SetProx(count);
			}
		}
	}
}

GameBoard::GameBoard()
{
	score = 0;
	size = 20;
	createBoard(size);
}

GameBoard::GameBoard(int size)
{
	score = 0;
	this->size = size;
	createBoard(size);
}

GameBoard::~GameBoard()
{

}

void GameBoard::TileCreate()
{
	std::string letterArr[]{"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
	int counterNum = 1;
	int counterLet = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("CLS");
	std::cout << "VICTOR BESSON'S MINESWEEPER" << std::endl;
	for (int row = 0; row < size + 4; row++)
	{
		for (int col = 0; col < size + 4; col++)
		{
			SetConsoleTextAttribute(hConsole, 15); //Reset Color Back to White
			if((row == size + 3 & col < 1) || (row == size + 3 & col > size + 2))
				std::cout << "   ";
			if ((row == size + 3 & col > 1) && (row == size + 3 & col < size + 2))
			{
				std::cout << " " << letterArr[counterLet] << " ";
				counterLet++;
			}
			if ((row > 1 && col == size + 3) && (row < size + 2 && col == size + 3))
			{
				std::cout << counterNum;
				counterNum++;
			}
			if(((row == 1 && col > 1) && (row == 1 && col < size + 2)) || ((row == size + 2 && col > 1) && (row == size + 2 && col < size + 2)))
				std::cout << "---";
			if (((col == 1 && row > 0) && (col == 1 && row < size + 3)) || ((col == size + 2 && row > 0) && (col == size + 2 && row < size + 3)))
				std::cout << " | ";
			if (col > 1 && row > 1 && row < size + 2 && col < size + 2)
			{
				if (gameOver == true)
					tileArr[row-1][col-1].Click();
				//Set Colors
				if(tileArr[row - 1][col - 1].ShowClickedValue() == " ")
					SetConsoleTextAttribute(hConsole, 15);
				if (tileArr[row - 1][col - 1].ShowClickedValue() == "0")
					SetConsoleTextAttribute(hConsole, 15);
				if (tileArr[row - 1][col - 1].ShowClickedValue() == "1")
					SetConsoleTextAttribute(hConsole, 9);
				if (tileArr[row - 1][col - 1].ShowClickedValue() == "2")
					SetConsoleTextAttribute(hConsole, 10);
				if (tileArr[row - 1][col - 1].ShowClickedValue() == "3")
					SetConsoleTextAttribute(hConsole, 11);
				if (tileArr[row - 1][col - 1].ShowClickedValue() == "4")
					SetConsoleTextAttribute(hConsole, 12);
				if (tileArr[row - 1][col - 1].ShowClickedValue() == "5")
					SetConsoleTextAttribute(hConsole, 13);
				if (tileArr[row - 1][col - 1].ShowClickedValue() == "6")
					SetConsoleTextAttribute(hConsole, 14);
				if (tileArr[row - 1][col - 1].ShowClickedValue() == "7")
					SetConsoleTextAttribute(hConsole, 3);
				if (tileArr[row - 1][col - 1].ShowClickedValue() == "8")
					SetConsoleTextAttribute(hConsole, 8);
				if (tileArr[row - 1][col - 1].ShowClickedValue() == "*")
					SetConsoleTextAttribute(hConsole, 64);
				std::cout << "[" << tileArr[row-1][col-1].ShowClickedValue() << "]";
			}
			if (col == size + 3)
				std::cout << std::endl;
		}
	}
	if (gameOver == true)
	{
		std::cout << "GAMEOVER" << "   " << std::endl;
		std::cout << "Your Score Was " << score << std::endl;
		return;
	}
	else if (win == true)
	{
		std::cout << "WINNER" << "   " << std::endl;
		std::cout << "Your Score is " << score << std::endl;
		return;
	}
	else
		std::cout << "Score: " << score << std::endl;
}

void GameBoard::TileClicked(int x, int y)
{
	if (tileArr[x][y].CheckMine())
	{
		tileArr[x][y].Click();
		gameOver = true;
		TileCreate();
		return;
	}
	if (tileArr[x][y].CheckClicked() == false)
		score++;
	tileArr[x][y].Click();
	if(tileArr[x][y].ShowClickedValue() != "0")
	tilesLeft--;
	if (tileArr[x][y].ShowClickedValue() == "0")
		searchEmptyTilesLoop(x, y);
	if (tilesLeft == 0)
		win = true;
	TileCreate();
}

bool GameBoard::GameoverBool()
{
	return gameOver;
}
bool GameBoard::WinnerBool()
{
	return win;
}
int GameBoard::GetSize()
{
	return size;
}
int GameBoard::GetScore()
{
	return score;
}
void GameBoard::searchEmptyTiles(int x, int y)
{
	if (tileArr[x][y].ShowClickedValue() == "0")
	{
		int C_left = x - 1;
		int C_right = x + 1;
		int R_down = y + 1;
		int R_up = y - 1;
		if (tileArr[C_left][y].CheckClicked() == false)
			searchEmptyTilesLoop(C_left, y);
		if (tileArr[C_right][y].CheckClicked() == false)
			searchEmptyTilesLoop(C_right, y);
		if (tileArr[x][R_down].CheckClicked() == false)
			searchEmptyTilesLoop(x, R_down);
		if (tileArr[x][R_up].CheckClicked() == false)
			searchEmptyTilesLoop(x, R_up);
		if (tileArr[C_left][R_up].CheckClicked() == false)
			searchEmptyTilesLoop(C_left, R_up);
		if (tileArr[C_left][R_down].CheckClicked() == false)
			searchEmptyTilesLoop(C_left, R_down);
		if (tileArr[C_right][R_up].CheckClicked() == false)
			searchEmptyTilesLoop(C_right, R_up);
		if (tileArr[C_right][R_down].CheckClicked() == false)
			searchEmptyTilesLoop(C_right, R_down);
	}
}

void GameBoard::searchEmptyTilesLoop(int x, int y)
{
	tileArr[x][y].Click();
	if(x > 0 && y > 0 && y < size + 1 && x < size + 1)
	tilesLeft--;
	searchEmptyTiles(x, y);
}


