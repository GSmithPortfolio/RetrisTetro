#include <iostream>
#include <raylib.h>
#include "grid.h"

int main()
{
	InitWindow(300, 600, "Tetro Minos");
	SetTargetFPS(60);

	Color backgroundColour = { 44, 44, 127, 255 };

	Grid grid = Grid();
	grid.Print();

	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(backgroundColour);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}