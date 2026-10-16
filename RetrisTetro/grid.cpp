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

bool Grid::IsCellOutside(int row, int column)
{
	if (row >= 0 && row < numOfRows && column >= 0 && column < numOfCols)
	{
		return false;
	}
	return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
	if (grid[row][column] == 0)
	{
		return true;
	}
	return false;
}

int Grid::ClearFullRows()
{
	int completed = 0;
	for (int row = numOfRows - 1; row >= 0; row--)
	{
		if (IsRowFull(row))
		{
			ClearRow(row);
			completed++;
		}
		else if (completed > 0)
		{
			MoveRowDown(row, completed);
		}
	}
	return completed;
}

bool Grid::IsRowFull(int row)
{
	for (int column = 0; column < numOfCols; column++)
	{
		if (grid[row][column] == 0)
		{
			return false;
		}
	}
	return true;
}

void Grid::ClearRow(int row)
{
	for (int column = 0; column < numOfCols; column++)
	{
		grid[row][column] = 0;
	}
}

void Grid::MoveRowDown(int row, int numRows)
{
	for (int column = 0; column < numOfCols; column++)
	{
		grid[row + numRows][column] = grid[row][column];
		grid[row][column] = 0;
	}
}
