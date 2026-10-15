#include <iostream>
#include <raylib.h>
#include "grid.h"
#include "blocks.cpp"

int main()
{
	InitWindow(300, 600, "Tetro Minos");
	SetTargetFPS(60);

	Color backgroundColour = { 44, 44, 127, 255 };

	Grid grid = Grid();
	grid.Print();

	LBlock block = LBlock();

	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(backgroundColour);
		grid.Draw();
		block.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}