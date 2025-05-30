#pragma once
#include "grid.h"
#include "block.h"
#include "position.h"
#include <vector>

class Game
{
public:
    Grid grid;
    std::vector<Block> blocks;
    Block currBlock;
    Block nextBlock;
    std::vector<Block> KhoBlock();
    Block GetRandomBlock();
    Game();
    ~Game();
    void DrawGame();
    void XuLyBanPhim();
    void AutoMoveBlockDown();
    void MoveBlockLeft();
    void MoveBlockRight();
    void RotateBlock();
    void DropBlock();
    void ResetGame();
    void LockBlock();
    bool Conllision();
    int score;
    bool game_over;
    void UpdateScore(int row_completed);
    int level;
    int row_completed;
    void LevelUp();
    Music music;
    Sound clear;
    Sound rotate;
    Sound lost;
    Sound reset;
};