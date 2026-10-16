#include "game.h"
#include <random>

// Constructor, initialising all the default values of the variables required by the game's logic.
// Includes grid objects, vector containing the blocks available, the score, the font, music and sound effects.
Game::Game()
{
	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	score = 0;
	font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
	InitAudioDevice();
	// Music from Kevin MacLeod on incompetech.com
	bgm = LoadMusicStream("Sounds/Space Fighter Loop.mp3");
	PlayMusicStream(bgm);
	SetMusicVolume(bgm, 0.1);
	// Sound effects created using free tool jsfxr on sfxr.me
	rotateSound = LoadSound("Sounds/rotate.wav");
	clearSound = LoadSound("Sounds/clear.wav");
	SetSoundVolume(rotateSound, 0.6);
	SetSoundVolume(clearSound, 0.3);

	currentInterval = 0.6;
	previousScoreUpdated = 0;
}
// Destructor, unloading sounds, music and audio device to play them.
Game::~Game()
{
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	UnloadMusicStream(bgm);
	CloseAudioDevice();
}

// Method to pull a random block from the list of available blocks, refilling the list if it is empty.
// This allows the game to cycle through each type of block at least once before repeating.
Block Game::GetRandomBlock()
{
	if (blocks.empty())
	{
		blocks = GetAllBlocks();
	}

	srand(time(NULL));
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}

// Method to return a vector filled with one of each type of block available in the game.
std::vector<Block> Game::GetAllBlocks()
{
	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

// Method to draw the various game objects on the raylib window.
// Includes the method to draw the UI elements, the grid, as well as drawing the next available block centered in the next box.
// Also stops drawing the current block if the game is over, preventing overlaying a non-controllable block on the stack that lost the game.
void Game::Draw()
{
	DrawUI();
	grid.Draw();
	switch (nextBlock.id)
	{
	case 3:
		nextBlock.Draw(255, 290);
		break;
	case 4:
		nextBlock.Draw(255, 280);
		break;
	default:
		nextBlock.Draw(270, 270);
		break;
	}
	if (!gameOver)
	{
		currentBlock.Draw(11, 11);
	}
}

// Method to draw the game's UI elements.
// Draws text labelling and displaying the score, as well as the Next Block box.
// Also draws the game over text and instructions to restart if the game is over.
void Game::DrawUI()
{
	DrawTextEx(font, "Score", { 365, 15 }, 38, 2, WHITE);
	DrawTextEx(font, "Next", { 370, 175 }, 38, 2, WHITE);
	DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, uiColour);

	char scoreText[10];
	sprintf_s(scoreText, "%d", score);
	Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

	DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, WHITE);
	DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, uiColour);
	if (gameOver)
	{
		DrawTextEx(font, "GAME OVER", { 320, 450 }, 38, 2, WHITE);
		DrawTextEx(font, "ANY KEY TO RESTART", { 323, 490 }, 16, 2, WHITE);
	}
}

// Method to check if a block is outside of the bounds of the grid, for game logic purposes.
bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();

	for (Position item: tiles)
	{
		if (grid.IsCellOutside(item.row, item.column))
		{
			return true;
		}
	}
	return false;
}

// Method to rotate the current controllable block.
// If the block would rotate to an invalid position, the rotation is reversed.
// Also plays the rotation sound.
void Game::RotateBlock()
{
	if (!gameOver)
	{
		currentBlock.Rotate();
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.UndoRotation();
		}
		else
		{
			PlaySound(rotateSound);
		}
	}
}

// Method to lock a block in place, once it has reached the bottom of the play field or any already-locked blocks.
// Also contains the logic to trigger the game over state, as well as clearing full rows and updating the game's score if they are.
void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles)
	{
		grid.grid[item.row][item.column] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (BlockFits() == false)
	{
		gameOver = true;
		SetMusicVolume(bgm, 0.05);
	}
	nextBlock = GetRandomBlock();
	int rowsCleared = grid.ClearFullRows();
	if (rowsCleared > 0)
	{
		PlaySound(clearSound);
		UpdateScore(rowsCleared, 0);
	}
}

// Method to check whether or not a block will fit in its next position, for use in various pieces of game logic.
bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles)
	{
		if (grid.IsCellEmpty(item.row, item.column) == false)
		{
			return false;
		}
	}
	return true;
}

// Method to reset all relevant game elements to their starting functions, used once the game over state is aborted.
// Resets score, grid, available blocks, current and next blocks, as well as game speed.
void Game::Reset()
{
	grid.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	score = 0;
	currentInterval = 0.6;
	previousScoreUpdated = 0;
}

// Method to update the score, using arguments passed in.
// Used when clearing rows, and when using the down arrow key to move the block faster.
void Game::UpdateScore(int linesCleared, int moveDownPoints)
{

	if (linesCleared > 0)
	{
		score += 100 + (linesCleared - 1) * 200;
	}

	score += moveDownPoints;

}

// Method to handle the keyboard inputs.
void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();
	// Resets the game, when the game is in the game over state and any key is pressed.
	// Sets music to normal volume and calls the method to reset game objects.
	if (gameOver && keyPressed != 0)
	{
		gameOver = false;
		SetMusicVolume(bgm, 0.2);
		Reset();
	}
	// Switch statement detects which key has been pressed, calling the relevant methods.
	switch (keyPressed)
	{
	case KEY_LEFT:
		MoveBlockLeft();
		break;
	case KEY_RIGHT:
		MoveBlockRight();
		break;
	case KEY_DOWN:
		MoveBlockDown();
		UpdateScore(0, 1);
		break;
	case KEY_UP:
		RotateBlock();
		break;
	}
}

// Method to move the block left, checking for collisions with the edge of the grid and any frozen blocks.
void Game::MoveBlockLeft()
{
	if (!gameOver)
	{
		currentBlock.Move(0, -1);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(0, 1);
		}
	}
}

// Method to move the block right, checking for collisions with the edge of the grid and any frozen blocks.
void Game::MoveBlockRight()
{
	if (!gameOver)
	{
		currentBlock.Move(0, 1);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(0, -1);
		}
	}
}

// Method to move the block down, checking for collisions with the edge of the grid and any frozen blocks.
void Game::MoveBlockDown()
{
	if (!gameOver)
	{
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
}