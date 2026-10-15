#include <iostream>
#include <raylib.h>
#include "grid.h"

int main()
{
	InitWindow(300, 600, "Tetro Minos");
	SetTargetFPS(60);

	Color backgroundColour = { 44, 44, 127, 255 };

	Grid grid = Grid();
	grid.grid[0][0] = 1;
	grid.grid[3][5] = 4;
	grid.grid[17][8] = 7;
	grid.Print();

	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(backgroundColour);
		grid.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}