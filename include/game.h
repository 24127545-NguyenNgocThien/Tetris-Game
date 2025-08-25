#pragma once
#include "grid.h"
#include "blocks.h"
#include <vector>

class Game
{
private:
    int lineCleared;
    Grid grid;
    Block currBlock;
    Block nextBlock;
    Block GetRandomBlock();
    std::vector<Block> blocks;
    std::vector<Block> GetAllBlock();

    bool BlockFits();
    bool IsBlockOutSide();

    void LevelUp();
    void Reset();
    void DropBlock();
    void RotationBlock();
    void MoveBlockLeft();
    void MoveBlockRight();
    void UpdateScore(int rowsCleared, int moveDownPoints);

    Sound clearSound;
    Sound rotateSound;
    Sound lostSound;
    Sound placingSound;
    Sound resetSound;
public:
    int pendingRows = 0;
    int level;
    int score;
    bool gameOver;
    Music music;
    Game();
    ~Game();
    void Draw();
    void LockBlock();
    void HandleInput();
    void MoveBlockDown();
};