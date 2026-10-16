#include "position.h"

// Constructor to initialise the position struct, using two arguments.
// Used in many parts of the game's logic, to choose where on the game grid things will be.
Position::Position(int row, int column)
{
	this->row = row;
	this->column = column;
}