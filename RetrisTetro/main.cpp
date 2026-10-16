#include <raylib.h>
#include "game.h"

int main()
{
	InitWindow(300, 600, "Tetro Minos");
	SetTargetFPS(60);

	Color backgroundColour = { 44, 44, 127, 255 };

	Game tetGame = Game();

	while (WindowShouldClose() == false)
	{
		tetGame.HandleInput();

		BeginDrawing();
		ClearBackground(backgroundColour);
		tetGame.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}