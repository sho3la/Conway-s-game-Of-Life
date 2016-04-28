#include "Igame of Life.h"

GameOfLife::GameOfLife()
{
}

GameOfLife::~GameOfLife()
{
}


bool GameOfLife::organismAt(int x, int y)
{
	return grid[x][y];
}

void GameOfLife::RandomInit(double probability)
{
	for(size_t i = 0; i < width; ++i) 
	{
		for(size_t j = 0; j < height; ++j) 
		{
			double r = (double)rand() / RAND_MAX;
			grid[i][j] = (r < probability);
		}
	}
}