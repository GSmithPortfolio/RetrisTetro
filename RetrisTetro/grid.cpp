#include "grid.h"
#include <iostream>

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

std::vector<Color> Grid::GetCellColours()
{
	Color darkGreyEmpty = { 26, 31, 40, 255 };
	Color green = { 47, 230, 23, 255 };
	Color red = { 232, 18, 18, 255 };
	Color orange = { 226, 116, 17, 255 };
	Color yellow = { 237, 234, 4, 255 };
	Color purple = { 166, 0, 247, 255 };
	Color cyan = { 21, 204, 209, 255 };
	Color blue = { 13, 64, 216, 255 };

	return { darkGreyEmpty, green, red, orange, yellow, purple, cyan, blue };
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