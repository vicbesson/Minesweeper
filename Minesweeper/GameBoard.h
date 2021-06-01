#pragma once
#include "Tile.h"
#include <vector>
class GameBoard
{
private:
	int numMines;
	int c1, c2;
	int size;
	int score;
	int tilesLeft;
	std::vector<std::vector<Tile>> tileArr;
	bool gameOver;
	bool win;
	void searchEmptyTiles(int x, int y);
	void searchEmptyTilesLoop(int x, int y);
	void createBoard(int value);
public:
	GameBoard();
	GameBoard(int size);
	~GameBoard();
	void TileCreate();
	void TileClicked(int x, int y);
	bool GameoverBool();
	bool WinnerBool();
	int GetSize();
	int GetScore();
};


