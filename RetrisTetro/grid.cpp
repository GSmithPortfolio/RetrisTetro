#include "grid.h"
#include <iostream>

Grid::Grid()
{
	numOfRows = 20;
	numOfCols = 10;
	cellSize = 30;
	Initialize();
}

void Grid::Initialize()
{
	for (int row = 0; row < numOfRows; row++)
	{
		for (int column = 0; column < numOfCols; column++)
		{
			grid[row][column] = 0;
		}
	}
}

void Grid::Print()
{
	for (int row = 0; row < numOfRows; row++)
	{
		for (int column = 0; column < numOfCols; column++)
		{
			std::cout << grid[row][column] << " ";
		}
		std::cout << std::endl;
	}
}