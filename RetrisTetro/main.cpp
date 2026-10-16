#include <raylib.h>
#include "game.h"
#include "colours.h"
#include <iostream>

// Function to check whether or not the time specified in the interval variable has passed.
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
	// Initialising the window with raylib, and setting the fps.
	InitWindow(500, 620, "Tetro Minos");
	SetTargetFPS(60);

	// Creating the Game object, that will hold all of the logic for the running of the game.
	Game tetGame = Game();

	// Game loop, will check if window has to close.
	while (WindowShouldClose() == false)
	{
		// Allowing the music to play.
		UpdateMusicStream(tetGame.bgm);
		// Calling the method to handle the inputs.
		tetGame.HandleInput();
		// Checking if the interval time has passed, and moving the piece down if it has.
		if (EventTriggered(tetGame.currentInterval))
		{
			tetGame.MoveBlockDown();
		}
		// Checking if the score is not the same as the last time the interval was updated, and then updating the interval to be faster for every 100 score.
		// Includes an extra check, so that the game has a maximum speed.
		if (tetGame.score != tetGame.previousScoreUpdated && tetGame.currentInterval > 0.05)
		{
			tetGame.currentInterval = 0.6 - (0.05 * floor(tetGame.score / 100));
			tetGame.previousScoreUpdated = tetGame.score;
		}

		// Methods to draw the background and game objects within the open raylib window.
		BeginDrawing();
		ClearBackground(backgroundColour);
		
		tetGame.Draw();

		EndDrawing();
	}

	// Closing the raylib window, and exiting the program.
	CloseWindow();
	return 0;
}