#include "colours.h"
// Declaring all the colours that will be used during the game.
const Color darkGreyEmpty = { 26, 31, 40, 255 };
const Color green = { 47, 230, 23, 255 };
const Color red = { 232, 18, 18, 255 };
const Color orange = { 226, 116, 17, 255 };
const Color yellow = { 237, 234, 4, 255 };
const Color purple = { 166, 0, 247, 255 };
const Color cyan = { 21, 204, 209, 255 };
const Color blue = { 13, 64, 216, 255 };
const Color backgroundColour = { 44, 44, 127, 255 };
const Color uiColour = { 59, 85, 162, 255 };

// Method to return a vector full of the possible valid colours for the grid cells to be.
std::vector<Color> GetCellColours()
{
	return { darkGreyEmpty, green, red, orange, yellow, purple, cyan, blue };
}