#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
	Grid();
	void Initialize();
	void Print();
	void Draw();
	int grid[20][10];

private:
	int numOfRows;
	int numOfCols;
	int cellSize;
	std::vector<Color> colours;
};