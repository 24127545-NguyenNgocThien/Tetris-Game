#include "game.h"
#include <random>

Game::Game()
{
    level = 0;
    score = 0;
    grid = Grid();
    holdBlock = -1;
    canHold = true;
    gameOver = false;
    blocks = GetAllBlock();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();

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
    if (currBlock)
        delete currBlock;
    if (nextBlock)
        delete nextBlock;
    for (Block *block : blocks)
    {
        if (block)
            delete block;
    }

    UnloadSound(clearSound);
    UnloadSound(rotateSound);
    UnloadSound(lostSound);
    UnloadSound(placingSound);
    UnloadSound(resetSound);
    UnloadMusicStream(music);

    CloseAudioDevice();
}

Block *Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlock();
    }
    int randomIndex = rand() % blocks.size();
    Block *block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

Block *Game::CreateBlockByID(int id)
{
    switch (id)
    {
    case 1:
        return new LBlock();
    case 2:
        return new JBlock();
    case 3:
        return new IBlock();
        break;
    case 4:
        return new OBlock();
    case 5:
        return new SBlock();
    case 6:
        return new TBlock();
    case 7:
        return new ZBlock();
    }
    return nullptr;
}

std::vector<Block *> Game::GetAllBlock()
{
    return {new LBlock(), new JBlock(), new IBlock(), new OBlock(), new SBlock(), new TBlock(), new ZBlock()};
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
        currBlock->Draw(11, 11);
        switch (nextBlock->id)
        {
        case 3:
            nextBlock->Draw(255, 290);
            break;
        case 4:
            nextBlock->Draw(255, 280);
            break;
        default:
            nextBlock->Draw(270, 270);
            break;
        }

        if (holdBlock != -1)
        {
            Block *preview = CreateBlockByID(holdBlock);
            switch (holdBlock)
            {
            case 3:
                preview->Draw(255, 510);
                break;
            case 4:
                preview->Draw(255, 500);
                break;
            default:
                preview->Draw(270, 490);
                break;
            }
            delete preview;
        }
    }
}

void Game::SaveBlock()
{
    if (!canHold || gameOver)
        return;

    if (holdBlock == -1)
    {
        holdBlock = currBlock->id;
        delete currBlock;
        currBlock = nextBlock;
        nextBlock = GetRandomBlock();
    }
    else
    {
        int temp = currBlock->id;
        delete currBlock;
        currBlock = CreateBlockByID(holdBlock);
        holdBlock = temp;
    }

    canHold = false; // chỉ được hold 1 lần cho đến khi block lock xuống
}

void Game::LevelUp()
{
    if (score >= 8000)
        level = 5;
    else if (score >= 6000)
        level = 4;
    else if (score >= 3000)
        level = 3;
    else if (score >= 1500)
        level = 2;
    else if (score >= 500)
        level = 1;
}

void Game::Reset()
{
    PlaySound(resetSound);
    level = 0;
    score = 0;
    holdBlock = -1;
    grid.Initialize();
    blocks = GetAllBlock();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    ResumeMusicStream(music);
    gameOver = false;
}

void Game::DropBlock()
{
    if (!gameOver)
    {
        int numMoves = 0;
        while (true)
        {
            currBlock->Move(1, 0);
            if (IsBlockOutSide() || !BlockFits())
            {
                currBlock->Move(-1, 0);
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

    if (IsKeyPressed(KEY_R) && gameOver)
    {
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
    case KEY_Z:
        SaveBlock();
        break;
    default:
        break;
    }
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currBlock->Move(0, -1);
        if (IsBlockOutSide() || !BlockFits())
        {
            currBlock->Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currBlock->Move(0, 1);
        if (IsBlockOutSide() || !BlockFits())
        {
            currBlock->Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currBlock->Move(1, 0);
        if (IsBlockOutSide() || !BlockFits())
        {
            currBlock->Move(-1, 0);
            LockBlock();
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currBlock->GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.col] = currBlock->id;
    }

    currBlock = nextBlock;
    if (!BlockFits())
    {
        PlaySound(lostSound);
        PauseMusicStream(music);
        gameOver = true;
    }
    else
        PlaySound(placingSound);

    nextBlock = GetRandomBlock();

    int rowsToClear = grid.ClearFullRows();
    if (rowsToClear > 0)
    {
        pendingRows = rowsToClear;
        PlaySound(clearSound);
    }
    canHold = true;
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currBlock->Rotation();
        if (IsBlockOutSide() || !BlockFits())
        {
            currBlock->UndoRotation();
        }
        else
        {
            PlaySound(rotateSound);
        }
    }
}

bool Game::IsBlockOutSide()
{
    std::vector<Position> tiles = currBlock->GetCellPositions();
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
    std::vector<Position> tiles = currBlock->GetCellPositions();
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
        baseScore = 150;
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
