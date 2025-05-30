#include "../include/game.h"
#include <cstdlib>
#include <ctime>

Game::Game()
{
    grid = Grid();
    blocks = KhoBlock();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    level = row_completed = score = 0;
    game_over = false;
    InitAudioDevice();
    music = LoadMusicStream("../resource/outrage_live_9.wav");
    PlayMusicStream(music);
    clear = LoadSound("../resource/sound.wav");
    rotate = LoadSound("../resource/vgmenuselect.wav");
    lost = LoadSound("../resource/vgdeathsound.wav");
    reset = LoadSound("../resource/target.wav");
}

Game::~Game()
{
    UnloadMusicStream(music);
    UnloadSound(clear);
    UnloadSound(rotate);
    UnloadSound(lost);
    UnloadSound(reset);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if(blocks.empty())
    {
        blocks = KhoBlock();
    }
    srand(time(0));
    int idx = rand() % blocks.size();
    Block block_random = blocks[idx];
    blocks.erase(blocks.begin() + idx);
    return block_random;
}

std::vector<Block> Game::KhoBlock()
{
    return{
        IBlock(),
        JBlock(),
        LBlock(),
        OBlock(),
        SBlock(),
        TBlock(),
        ZBlock()
    };
}

void Game::DrawGame()
{
    grid.DrawGrid();
    currBlock.DrawBlock(11, 1);
    switch(nextBlock.id)
    {
        case 1:
            nextBlock.DrawBlock(430, 325);
            break;
        case 4:
            nextBlock.DrawBlock(380, 350);
            break;
        default:
            nextBlock.DrawBlock(410, 350);
            break;
    }
}

bool Game::Conllision()
{
    std::vector<Position> tiles = currBlock.GetTilesPosition();
    for (Position tile : tiles)
    {
        if (grid.IsOutGrid(tile) || tile.y >= 0 && !grid.IsEmptyCell(tile))
        {
            return true;
        }
    }
    return false;
}

void Game::XuLyBanPhim()
{
    int key = GetKeyPressed();
    switch(key)
    {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_UP:
            RotateBlock();
            break;
        case KEY_DOWN:
            DropBlock();
            break;
        case KEY_R:
            if(game_over)
            {
                ResetGame();
            }
            break;
    }
}

void Game::MoveBlockLeft()
{
    if(game_over)
    {
        return;
    }
    currBlock.Move(-1, 0);
    if(Conllision())
    {
        currBlock.Move(1, 0);
    }
}

void Game::MoveBlockRight()
{
    if(game_over)
    {
        return;
    }
    currBlock.Move(1, 0);
    if(Conllision())
    {
        currBlock.Move(-1, 0);
    }
}

void Game::RotateBlock()
{
    if(game_over)
    {
        return;
    }
    currBlock.Rotate();
    if(Conllision())
    {
        currBlock.UndoRotate();
        PlaySound(rotate);
    }
}

void Game::DropBlock()
{
    if(game_over)
    {
        return;
    }
    while(!Conllision())
    {
        currBlock.Move(0, 1);
    }
    currBlock.Move(0, -1);
    LockBlock();
}

void Game::AutoMoveBlockDown()
{
    if(game_over)
    {
        return;
    }
    currBlock.Move(0, 1);
    if(Conllision())
    {
        currBlock.Move(0, -1);
        LockBlock();
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currBlock.GetTilesPosition();
    for(Position tile : tiles)
    {
        if(tile.y >= 0)
        {
        grid.grid[tile.y][tile.x] = currBlock.id;
        }
    }
    currBlock = nextBlock;
    nextBlock = GetRandomBlock();

    int row_complete = grid.ClearFullRow();
    if(row_complete > 0)
    {
    row_completed += row_complete;
    LevelUp();
    UpdateScore(row_completed);
    PlaySound(clear);
    }

    if(Conllision())
    {
        game_over = true;
        PlaySound(lost);
    }
}

void Game::ResetGame()
{
    grid.Init();
    blocks = KhoBlock();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    game_over = false;
    level = row_completed = score = 0;
    PlaySound(reset);
}

void Game::UpdateScore(int row_complete)
{
    int scor_each_row[5] = {0, 40, 100, 300, 1200};
    score = scor_each_row[row_complete] * (level + 1);
    return;
}

void Game::LevelUp()
{
    if(row_completed >= 10)
    {
        row_completed -= 10;
        level++;
    }
}