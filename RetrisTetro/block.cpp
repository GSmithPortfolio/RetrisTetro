#include "block.h"

Block::Block()
{
	id = 0;
	cellSize = 30;
	rotationState = 0;
	colours = GetCellColours();
	rowOffset = 0;
	columnOffset = 0;
}

void Block::Draw()
{
	std::vector<Position> tiles = GetCellPositions();
	for (Position item : tiles)
	{
		DrawRectangle(item.column * cellSize + 1, item.row * cellSize + 1, cellSize - 1, cellSize - 1, colours[id]);
	}
}

void Block::Move(int rows, int columns)
{
	rowOffset += rows;
	columnOffset += columns;
}

void Block::Rotate()
{
	rotationState++;
	
	if (rotationState == cells.size());
	{
		rotationState = 0;
	}
}

void Block::UndoRotation()
{
	rotationState--;

	if (rotationState == -1)
	{
		rotationState = cells.size() - 1;
	}
}

std::vector<Position> Block::GetCellPositions()
{
	std::vector<Position> tiles = cells[rotationState];
	std::vector<Position> movedTiles;

	for (Position item : tiles)
	{
		Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
		movedTiles.push_back(newPos);
	}
	return movedTiles;
}