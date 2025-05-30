#include "../include/block.h"

Block::Block()
{
    offset_x = offset_y = 0;
    state = 0; 
    tiles_size = 50;
    colors = Bang_Mau();
}

std::vector<Position> Block::GetTilesPosition()
{
    std::vector<Position> cell = trang_thai[state];
    std::vector<Position> moved;
    for(Position xy : cell)
    {
        Position newPos = Position(xy.x + offset_x, xy.y + offset_y);
        moved.push_back(newPos);
    }
    return moved;
}

void Block::Move(int x, int y)
{
    offset_x += x;
    offset_y += y;
}

void Block::Rotate()
{
    state++;
    if(state == 4)
    {
        state = 0;
    }
}

void Block::UndoRotate()

{
    state--;
    if(state == -1)
    {
        state = 3;
    }
}

void Block::DrawBlock(int x, int y)
{
    std::vector<Position> tiles = GetTilesPosition();
    for(Position tile : tiles)
    {
        DrawRectangle(tile.x * tiles_size + x, tile.y * tiles_size + y, tiles_size - 1, tiles_size - 1, colors[id]);
    }
}

IBlock::IBlock()
{
    Move(2, -1);
    id = 1;
    trang_thai[0] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1)};
    trang_thai[1] = {Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)};
    trang_thai[2] = {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)};
    trang_thai[3] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)};
}

JBlock::JBlock()
{
    Move(3, -1);
    id = 2;
    trang_thai[0] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1)};
    trang_thai[1] = {Position(1, 0), Position(2, 0), Position(1, 1), Position(1, 2)};
    trang_thai[2] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2)};
    trang_thai[3] = {Position(1, 0), Position(1, 1), Position(0, 2), Position(1, 2)};
}

LBlock::LBlock()
{
    Move(3, -1);
    id = 3;
    trang_thai[0] = {Position(2, 0), Position(0, 1), Position(1, 1), Position(2, 1)};
    trang_thai[1] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2)};
    trang_thai[2] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(0, 2)};
    trang_thai[3] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2)};
}

OBlock::OBlock()
{
    Move(4, -1);
    id = 4;
    trang_thai[0] = {Position(0, 0), Position(1, 0), Position(0, 1), Position(1, 1)};
    trang_thai[1] = trang_thai[2] = trang_thai[3] = trang_thai[0];
}

SBlock::SBlock()
{
    Move(3, -1);
    id = 5;
    trang_thai[0] = {Position(1, 0), Position(2, 0), Position(0, 1), Position(1, 1)};
    trang_thai[1] = {Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2)};
    trang_thai[2] = {Position(1, 1), Position(2, 1), Position(0, 2), Position(1, 2)};
    trang_thai[3] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2)};
}

TBlock::TBlock()
{
    Move(3, -1);
    id = 6;
    trang_thai[0] = {Position(1, 0), Position(0, 1), Position(1, 1), Position(2, 1)};
    trang_thai[1] = {Position(1, 0), Position(1, 1), Position(2, 1), Position(1, 2)};
    trang_thai[2] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(1, 2)};
    trang_thai[3] = {Position(1, 0), Position(0, 1), Position(1, 1), Position(1, 2)};
}

ZBlock::ZBlock()
{
    Move(3, -1);
    id = 7;
    trang_thai[0] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1)};
    trang_thai[1] = {Position(2, 0), Position(1, 1), Position(2, 1), Position(1, 2)};
    trang_thai[2] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2)};
    trang_thai[3] = {Position(1, 0), Position(0, 1), Position(1, 1), Position(0, 2)};
}