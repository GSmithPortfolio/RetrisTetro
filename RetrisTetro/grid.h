#pragma once

class Grid
{
public:
	Grid();
	void Initialize();
	void Print();
	int grid[20][10];

private:
	int numOfRows;
	int numOfCols;
	int cellSize;
};