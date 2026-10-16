#include "game.h"
#include <random>

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
	bgm = LoadMusicStream("Sounds/Space Fighter Loop.mp3");
	PlayMusicStream(bgm);
	SetMusicVolume(bgm, 0.1);
	rotateSound = LoadSound("Sounds/rotate.wav");
	clearSound = LoadSound("Sounds/clear.wav");
	SetSoundVolume(rotateSound, 0.6);
	SetSoundVolume(clearSound, 0.3);
	intervalUpdatedRecently = false;
}
Game::~Game()
{
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	UnloadMusicStream(bgm);
	CloseAudioDevice();
}

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

std::vector<Block> Game::GetAllBlocks()
{
	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

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

void Game::Reset()
{
	grid.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{

	if (linesCleared > 0)
	{
		score += 100 + (linesCleared - 1) * 200;
	}

	score += moveDownPoints;

}

void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();
	if (gameOver && keyPressed != 0)
	{
		gameOver = false;
		SetMusicVolume(bgm, 0.2);
		Reset();
	}
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

int Game::UpdateInterval(int interIN)
{
	int oldScore = score;
	int newInterval = interIN;

	if (oldScore != score && score % 100 > oldScore % 100)
	{
		intervalUpdatedRecently = false;
		oldScore = score;
	}

	if (!intervalUpdatedRecently)
	{
		newInterval -= 0.05;
		intervalUpdatedRecently = true;
		return newInterval;
	}
	return newInterval;
}