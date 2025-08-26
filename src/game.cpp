#include "game.h"
#include <random>

Game::Game()
{
    gameOver = false;
    blocks = GetAllBlock();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    level = 0;
    score = 0;
    grid = Grid();
    
    InitAudioDevice();
    music = LoadMusicStream("Sounds/TetrisTheme.mp3");
    PlayMusicStream(music);
    SetMusicVolume(music, 0.5f);

    clearSound = LoadSound("Sounds/clear.mp3");
    rotateSound = LoadSound("Sounds/vgmenuselect.wav");
    lostSound = LoadSound("Sounds/vgdeathsound.wav");
    placingSound = LoadSound("Sounds/placingSoundEffect.mp3");
    resetSound = LoadSound("Sounds/target.flac");
}

Game::~Game()
{
    UnloadSound(clearSound);
    UnloadSound(rotateSound);
    UnloadSound(lostSound);
    UnloadSound(placingSound);
    UnloadSound(resetSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlock();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlock()
{
    return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    if (pendingRows > 0 && !grid.isFlashing)
    {
        UpdateScore(pendingRows, 0);
        pendingRows = 0;
    }

    if (!gameOver)
    {
        currBlock.Draw(11, 11);
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
    }
}

void Game::LevelUp()
{
    if (score >= 5000)
        level = 5;
    else if (score >= 3000)
        level = 4;
    else if (score >= 2000)
        level = 3;
    else if (score >= 1000)
        level = 2;
    else if (score >= 500)
        level = 1;
}

void Game::Reset()
{   
    PlaySound(resetSound);
    level = 0;
    score = 0;
    grid.Initialize();
    blocks = GetAllBlock();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

void Game::DropBlock()
{
    if (!gameOver)
    {
        int numMoves = 0;
        while (true)
        {
            currBlock.Move(1, 0);
            if (IsBlockOutSide() || !BlockFits())
            {
                currBlock.Move(-1, 0);
                break;
            }
            numMoves++;
        }
        LockBlock();
        UpdateScore(0, numMoves);
    }
}

void Game::HandleInput()
{
    int key = GetKeyPressed();
    if (gameOver && key != 0)
    {
        gameOver = false;
        Reset();
    }

    if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_DOWN))
    {
        DropBlock();
    }

    switch (key)
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
    default:
        break;
    }
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currBlock.Move(0, -1);
        if (IsBlockOutSide() || !BlockFits())
        {
            currBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currBlock.Move(0, 1);
        if (IsBlockOutSide() || !BlockFits())
        {
            currBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currBlock.Move(1, 0);
        if (IsBlockOutSide() || !BlockFits())
        {
            currBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.col] = currBlock.id;
    }

    PlaySound(placingSound);

    currBlock = nextBlock;
    if (!BlockFits())
    {   
        PlaySound(lostSound);
        UnloadMusicStream(music);
        gameOver = true;
    }
    nextBlock = GetRandomBlock();

    int rowsToClear = grid.ClearFullRows();
    if (rowsToClear > 0)
    {
        pendingRows = rowsToClear;
        PlaySound(clearSound);
    }
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currBlock.Rotation();
        if (IsBlockOutSide() || !BlockFits())
        {
            currBlock.UndoRotation();
        }
        else
        {
            PlaySound(rotateSound);
        }
    }
}

bool Game::IsBlockOutSide()
{
    std::vector<Position> tiles = currBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutSide(item.row, item.col))
        {
            return true;
        }
    }
    return false;
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (!grid.IsCellEmpty(item.row, item.col))
        {
            return false;
        }
    }
    return true;
}

void Game::UpdateScore(int rowsCleared, int moveDownPoints)
{
    int baseScore = 0;
    switch (rowsCleared)
    {
    case 1:
        baseScore = 100;
        break;
    case 2:
        baseScore = 300;
        break;
    case 3:
        baseScore = 1000;
        break;
    case 4:
        baseScore = 2000;
        break;
    default:
        break;
    }

    double bonus = 1.0 + 0.1 * level;
    score += static_cast<int>(baseScore * bonus);
    score += moveDownPoints;

    LevelUp();
}
