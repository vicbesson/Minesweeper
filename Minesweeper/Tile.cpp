#include "Tile.h"
Tile::Tile()
{
	value = "";
	mine = false;
	proximinity = 0;
	clickedValue = " ";
	clicked = false;
}
Tile::~Tile()
{
	
}
void Tile::SetProx(int amount)
{
	if (mine == false)
	{
		proximinity = amount;
		value = std::to_string(amount);
	}
}
void Tile::IsMine()
{
	mine = true;
	value = "*";
}
bool Tile::CheckMine()
{
	return mine;
}
void Tile::Click() 
{
	clicked = true;
	clickedValue = value;
}
std::string Tile::ShowClickedValue()
{
	return clickedValue;
}
bool Tile::CheckClicked()
{
	return clicked;
}

