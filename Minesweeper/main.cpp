#include "GameBoard.h"
#include <fstream>
#include <algorithm>
#include <windows.h>
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void Coords(GameBoard *GameboardX)
{
	bool value = true;
	std::string letterArrUpper[]{ "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };
	std::string letterArrLower[]{ "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };
	std::string x, y;
	std::cout << "Please Choose xCoords(Letter):";
	do
	{
		std::getline(std::cin, x);
		for (int i = 0; i < GameboardX->GetSize() ; i++)
		{
			if (x == letterArrUpper[i] || x == letterArrLower[i])
			{
				value = false;
				x = std::to_string(i + 1);
			}
		}
		if (value)
			std::cout << "Invalid Character(Letter):";
	} while (value);
	std::cout << "Please Choose yCoords(Number):";
	value = true;
	do
	{
		std::getline(std::cin, y);
		for (int i = 1; i < GameboardX->GetSize() + 1; i++)
		{
			if (y == std::to_string(i))
			{
				value = false;
			}
		}
		if (value)
			std::cout << "Invalid Character(Number):";
	} while (value);
	GameboardX->TileClicked(std::stoi(y), std::stoi(x));
}

void AddHighscore(std::string name, int score)
{
	std::vector<std::string> highscoreList;
	std::vector<std::string> highscoreListName;
	std::vector<int> highscoreListScore;
	std::string filename = "Highscores.txt";
	std::vector<std::pair<int, std::string>> pairs;
	std::ifstream infile(filename);
	std::string highscore;
	std::string token;
	bool newHighscore = false;
	int count = 0;
	std::string delimiter = "*|^|*";
	size_t pos = 0;
	if (infile.is_open())
	{
		while (std::getline(infile, highscore))
		{
			highscoreList.push_back(highscore.c_str());
		}
		infile.close();
	}
	do
	{
		if (highscoreList.size() < 10)
		{
			highscoreList.push_back("-1*|^|*V1ct0rsS3cr3tD3f4ultN4meF0rF1LLingLIst*|^|*");
		}
	} while(highscoreList.size() < 10);
	
	for (int i = 0; i < highscoreList.size(); i++)
	{
		while ((pos = highscoreList[i].find(delimiter)) != std::string::npos) {
			token = highscoreList[i].substr(0, pos);
			if (count == 1)
				highscoreListName.push_back(token);
			if (count == 0)
				highscoreListScore.push_back(std::stoi(token));
			highscoreList[i].erase(0, pos + delimiter.length());
			count++;
		}
		count = 0;
	}
	for (int i = 0; i < highscoreList.size(); i++)
	{
		pairs.push_back(std::make_pair(highscoreListScore[i], highscoreListName[i]));
	}
	std::sort(pairs.begin(), pairs.end());
	for (int i = 0; i < highscoreList.size(); i++)
	{
		highscoreListScore[i] = pairs[i].first;
		highscoreListName[i] = pairs[i].second;
	}
	std::reverse(highscoreListScore.begin(), highscoreListScore.end());
	std::reverse(highscoreListName.begin(), highscoreListName.end());
	do
	{
		if (score > highscoreListScore[count])
		{
			highscoreListScore.insert(highscoreListScore.begin() + count, score);
			highscoreListName.insert(highscoreListName.begin() + count, name);
			newHighscore = true;
		}
		if (count == 9)
			newHighscore = true;
		count++;
	} while (newHighscore == false);
	std::ofstream outfile;
	outfile.open("Highscores.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < highscoreList.size(); i++)
	{
		outfile << std::to_string(highscoreListScore[i]) + "*|^|*" + highscoreListName[i] + "*|^|*" << std::endl;
	}
	outfile.close();
}

void ReadHighscores()
{
	std::string filename = "Highscores.txt";
	std::ifstream infile(filename);
	std::string highscore;
	std::vector<std::string> highscoreList;
	std::vector<std::string> highscoreListName;
	std::vector<int> highscoreListScore;
	int count = 0;
	size_t pos = 0;
	std::string delimiter = "*|^|*";
	std::string token;
	if (infile.is_open())
	{
		while (std::getline(infile, highscore))
		{
			highscoreList.push_back(highscore.c_str());
		}
		infile.close();
	}
	for (int i = 0; i < highscoreList.size(); i++)
	{
		while ((pos = highscoreList[i].find(delimiter)) != std::string::npos) {
			token = highscoreList[i].substr(0, pos);
			if (count == 1)
				highscoreListName.push_back(token);
			if (count == 0)
				highscoreListScore.push_back(std::stoi(token));
			highscoreList[i].erase(0, pos + delimiter.length());
			count++;
		}
		count = 0;
	}
	SetConsoleTextAttribute(hConsole, 100);
	std::cout << "HighScores" << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	for (int i = 0; i < highscoreList.size(); i++)
	{
		if(i == 0)
			SetConsoleTextAttribute(hConsole, 11);
		if(i == 1)
			SetConsoleTextAttribute(hConsole, 10);
		if (i == 2)
			SetConsoleTextAttribute(hConsole, 13);
		if (highscoreListName[i] != "V1ct0rsS3cr3tD3f4ultN4meF0rF1LLingLIst")
		{
			std::cout << highscoreListName[i] << ": " << highscoreListScore[i] << std::endl;
		}
		SetConsoleTextAttribute(hConsole, 8);
	}
	SetConsoleTextAttribute(hConsole, 15);
}
void NewGame()
{
	std::string size;
	bool value = true;
	std::string name;
	SetConsoleTextAttribute(hConsole, 91);
	std::cout << "Welcome to Victor Besson's MINESWEEPER" << std::endl;
	ReadHighscores();
	std::cout << "Choose Game Size(3-26):";
	do
	{
		std::getline(std::cin, size);
		for (int i = 3; i < 27; i++)
		{
			if (size == std::to_string(i))
			{
				value = false;
			}
		}
		if(value)
			std::cout << "Invalid Size Retry(3-26):";
	} while(value);
	GameBoard *Game = new GameBoard(stoi(size));
	Game->TileCreate();
	do
	{
		Coords(Game);
	} while (Game->GameoverBool() == false && Game->WinnerBool() == false);
	std::cout << "Enter Name:";
	std::getline(std::cin, name);
	do
	{
		if (name.find("*|^|*") != std::string::npos)
		{
			std::cout << "Invalid Name Retry:";
			std::getline(std::cin, name);
		}
		else if (name.length() > 10)
		{
			std::cout << "Retry(MaxCharacters10):";
			std::getline(std::cin, name);
		}
	} while (name.find("*|^|*") != std::string::npos || name.length() > 10);
	AddHighscore(name, Game->GetScore());
}

int main() {
	std::string retry;
	bool done = false;

	NewGame();
	do
	{
		std::cout << "Retry Y/N:";
		do
		{
			std::getline(std::cin, retry);
			if (retry != "N" && retry != "Y" && retry != "n" && retry != "y")
			{
				std::cout << "Invalid Character (Choose either Y or N):";
			}
		} while(retry != "N" && retry != "Y" && retry != "n" && retry != "y");
		if (retry == "Y" || retry == "y")
		{
			system("CLS");
			NewGame();
		}
		else
		{
			done = true;
		}
	} while (done==false);
	system("CLS");
	std::cout << "THANK YOU FOR PLAYING" << std::endl;
	std::cout << "Click Enter to Exit";
	std::cin.get();
	return 0;
}
