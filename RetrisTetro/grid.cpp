#include "grid.h"
#include <iostream>
#include "colours.h"

// Constructor
Grid::Grid()
{
	numOfRows = 20;
	numOfCols = 10;
	cellSize = 30;
	Initialize();
	colours = GetCellColours();
}

// Method to set each cell on the grid to a value of 0, creating an empty playing field.
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

// Method originally for testing the grid, which prints the current configuration to the console.
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

// Method to draw the elements on the grid to the raylib window, allowing the user to see it.
void Grid::Draw()
{
	for (int row = 0; row < numOfRows; row++)
	{
		for (int column = 0; column < numOfCols; column++)
		{
			int cellValue = grid[row][column];
			DrawRectangle(column * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colours[cellValue]);
		}
	}

}

// Method to check whether or not a cell is attempting to exist outside of the grid, for game logic purposes.
bool Grid::IsCellOutside(int row, int column)
{
	if (row >= 0 && row < numOfRows && column >= 0 && column < numOfCols)
	{
		return false;
	}
	return true;
}

// Method to check whether or not a cell is empty, for game logic purposes.
bool Grid::IsCellEmpty(int row, int column)
{
	if (grid[row][column] == 0)
	{
		return true;
	}
	return false;
}

// Method to clear rows on the grid that become full, incrementing a variable called completed and calling the method to move rows down.
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

// Method to check whether or not a row is full, for game logic purposes.
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
 
// Method to clear a row on the grid, replacing all cells with empty ones.
void Grid::ClearRow(int row)
{
	for (int column = 0; column < numOfCols; column++)
	{
		grid[row][column] = 0;
	}
}

// Method to move rows down according to the argument numRows, used when clearing full rows.
void Grid::MoveRowDown(int row, int numRows)
{
	for (int column = 0; column < numOfCols; column++)
	{
		grid[row + numRows][column] = grid[row][column];
		grid[row][column] = 0;
	}
}
