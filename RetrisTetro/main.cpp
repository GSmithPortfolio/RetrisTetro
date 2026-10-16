#include <raylib.h>
#include "game.h"
#include "colours.h"
#include <iostream>

double lastUpdateTime = 0;


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

	Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

	Game tetGame = Game();

	while (WindowShouldClose() == false)
	{
		UpdateMusicStream(tetGame.bgm);
		tetGame.HandleInput();
		if (EventTriggered(tetGame.currentInterval))
		{
			tetGame.MoveBlockDown();
		}
		if (tetGame.score != tetGame.previousScoreUpdated)
		{
			tetGame.currentInterval = 0.6 - (0.05 * floor(tetGame.score / 100));
			tetGame.previousScoreUpdated = tetGame.score;
		}

		BeginDrawing();
		ClearBackground(backgroundColour);
		
		tetGame.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}