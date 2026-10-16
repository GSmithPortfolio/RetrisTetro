#include <raylib.h>
#include "game.h"

double lastUpdateTime = 0;
double currentInterval = 0.2;

bool EventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}

	return false;
}

int main()
{
	InitWindow(500, 620, "Tetro Minos");
	SetTargetFPS(60);

	Color backgroundColour = { 44, 44, 127, 255 };

	Game tetGame = Game();

	while (WindowShouldClose() == false)
	{
		tetGame.HandleInput();
		if (EventTriggered(currentInterval))
		{
			tetGame.MoveBlockDown();
		}

		BeginDrawing();
		ClearBackground(backgroundColour);
		tetGame.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}