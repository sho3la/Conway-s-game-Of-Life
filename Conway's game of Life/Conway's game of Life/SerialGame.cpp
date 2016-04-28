#include "SerialGame.h"

SerialGame::SerialGame(std::string fileName)
{

	LoadFile(fileName);

	Num_of_generations = std::stoi( fileOutput[0] );

	width =  std::stoi( fileOutput[1] );
	height =  std::stoi( fileOutput[1] );

	StrToVec(fileOutput[2]);

	grid = new bool*[width];
	tempGrid = new bool*[width];

	for (size_t i = 0; i < width; ++i) 
	{
		grid[i] = new bool[height];
		tempGrid[i] = new bool[height];
	}

	xdomain = new int [3];
	ydomain = new int [3];

	srand((unsigned)time(NULL));

}

SerialGame::~SerialGame()
{
	for (size_t i = 0; i < width; ++i) 
	{
		delete [] grid[i];
		delete [] tempGrid[i];
	}

	delete [] grid;
	delete [] tempGrid;

	delete [] xdomain;
	delete [] ydomain;
}

void SerialGame::Init()
{
	for(size_t i = 0; i < width; ++i) 
	{
		for(size_t j = 0; j < height; ++j) 
		{
			grid[i][j] = false;
		}
	}

	for(int i=0; i < Grid_indices.size(); ++i)
	{
		int x = Grid_indices[i] / width;
		int y = Grid_indices[i] % height;

		grid[y][x] = true;
	}
}


void SerialGame::iterate()
{
	for (size_t i = 0; i < width; ++i) 
	{
		for(size_t j = 0; j < height; ++j) 
		{
			int neighbors = countNeighbors(i, j);

			if (grid[i][j] == true) 
			{
				if (neighbors == 2 || neighbors == 3)
				{
					// organism survives 
					tempGrid[i][j] = true;
				}
				else
				{
					// organism dies
					tempGrid[i][j] = false;
				}
			} 
			else 
			{
				if (neighbors == 3) 
				{
					// organism is born
					tempGrid[i][j] = true;
				} 
				else 
				{
					// continues empty
					tempGrid[i][j] = false;
				}
			}
		}
	}

	bool** t = grid;
	grid = tempGrid;
	tempGrid = t;
}


int SerialGame::countNeighbors(int x,int y)
{
	int neighbors = 0;

	xdomain[0] = (x == 0 ? width - 1: x - 1);
	xdomain[1] = x;
	xdomain[2] = (x == width - 1 ? 0 : x + 1);

	ydomain[0] = (y == 0 ? height - 1: y - 1);
	ydomain[1] = y;
	ydomain[2] = (y == height - 1 ? 0 : y + 1);

	for(size_t i = 0; i < 3; ++i) 
	{
		for(size_t j = 0; j < 3; ++j) 
		{
			if (!(xdomain[i] == x && ydomain[j] == y)) 
			{
				if (grid[xdomain[i]][ydomain[j]]) 
				{
					++neighbors;
				}
			}
		}
	}

	return neighbors;
}

void SerialGame::LoadFile(std::string fileName)
{
	std::ifstream myReadFile;
	myReadFile.open(fileName);



	if (myReadFile.is_open())
	{
		while (!myReadFile.eof()) 
		{
			std::string out;
			getline(myReadFile,out);
			fileOutput.push_back(out);
		}
	}
	myReadFile.close();
}

void SerialGame::StrToVec(std::string Str)
{
	std::stringstream ss(Str);

	int i;

	while (ss >> i)
	{
		Grid_indices.push_back(i);

		if (ss.peek() == ',')
			ss.ignore();
	}
}

void SerialGame::SaveFile()
{
	std::ofstream outFile;
	outFile.open("Data/output.txt");

	outFile<<Num_of_generations<<std::endl;

	int num_Cell_alive = 0;
	for(int i=0 ; i < width; ++i)
	{
		for(int j=0; j < height ; ++j)
		{
			if(grid[i][j])
			{
				++num_Cell_alive;
			}
		}
	}
	outFile<<num_Cell_alive<<std::endl;



	for(int i=0 ; i < width; ++i)
	{
		for(int j=0; j < height ; ++j)
		{
			outFile<<grid[j][i]<<" ";
		}
		outFile<<std::endl;
	}

	outFile.close();
}