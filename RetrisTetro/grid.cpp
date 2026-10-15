#include "grid.h"
#include <iostream>
#include "colours.h"

Grid::Grid()
{
	numOfRows = 20;
	numOfCols = 10;
	cellSize = 30;
	Initialize();
	colours = GetCellColours();
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

void Grid::Draw()
{
	for (int row = 0; row < numOfRows; row++)
	{
		for (int column = 0; column < numOfCols; column++)
		{
			int cellValue = grid[row][column];
			DrawRectangle(column * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize - 1, colours[cellValue]);
		}
	}

}