#pragma once
#include "grid.h"
#include "blocks.cpp"
#include <iostream>

class Game
{
public:
	Game();
	~Game();
	void HandleInput();
	void MoveBlockDown();
	void Draw();
	
	int score;
	double currentInterval;
	int previousScoreUpdated;
	bool gameOver;
	Music bgm;

private:
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	bool IsBlockOutside();
	void RotateBlock();
	void LockBlock();
	bool BlockFits();
	void Reset();
	void UpdateScore(int linesCleared, int moveDownPoints);
	void MoveBlockLeft();
	void MoveBlockRight();
	void DrawUI();

	Grid grid;
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
	Font font;
	Sound rotateSound;
	Sound clearSound;
};


