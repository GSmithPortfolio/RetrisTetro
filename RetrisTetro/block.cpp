#include "block.h"

// Constructor.
Block::Block()
{
	id = 0;
	cellSize = 30;
	rotationState = 0;
	colours = GetCellColours();
	rowOffset = 0;
	columnOffset = 0;
}

// Method to draw the block to the raylib window, allowing the player to see them.
void Block::Draw(int offsetX, int offsetY)
{
	std::vector<Position> tiles = GetCellPositions();
	for (Position item : tiles)
	{
		DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colours[id]);
	}
}

// Method to offset the block by the arguments being passed in, allowing the blocks to move around.
void Block::Move(int rows, int columns)
{
	rowOffset += rows;
	columnOffset += columns;
}

// Method for cycling through the different rotation states of each block.
void Block::Rotate()
{
	rotationState++;
	
	if (rotationState == (int)cells.size())
	{
		rotationState = 0;
	}
}

// Method to cancel a rotation, if it would result in an invalid block position.
void Block::UndoRotation()
{
	rotationState--;

	if (rotationState == -1)
	{
		rotationState = (int)cells.size() - 1;
	}
}

// Method to fill a vector of positions, to get the filled cells for game logic purposes.
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