#pragma once
#include <string>

class GameOfLife
{
public:
	GameOfLife();
	~GameOfLife();

	bool** grid;
	bool** tempGrid;

	int *xdomain;
	int *ydomain;

	int width;
	int height;

	int Num_of_generations;


	void RandomInit(double probability = 0.1);
	bool organismAt(int x, int y);

	virtual void Init()=0;
	virtual void iterate()=0;
	virtual int countNeighbors(int,int)=0;
	virtual void LoadFile(std::string fileName)=0;
	virtual void SaveFile()=0;

};