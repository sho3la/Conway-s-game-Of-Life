#pragma once
#include "Igame of Life.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class SerialGame : public GameOfLife
{
public:
	SerialGame(std::string fileName);
	~SerialGame();

	void iterate();
	void Init();
	void SaveFile();
private:
	int countNeighbors(int,int);
	void LoadFile(std::string fileName);
	
	void StrToVec(std::string Str);

	std::vector<std::string> fileOutput;
	std::vector<int> Grid_indices;

};