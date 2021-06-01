#pragma once
#include <iostream>
#include <string>
class Tile
{
private:
	int proximinity;
	std::string value;
	bool mine;
	bool clicked;
	std::string clickedValue;
public:
	Tile();
	~Tile();
	void SetProx(int amount);
	void IsMine();
	bool CheckMine();
	void Click();
	bool CheckClicked();
	std::string ShowClickedValue();
};

