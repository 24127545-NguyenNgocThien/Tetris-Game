#include "blocks.h"
#include <raylib.h>

LBlock::LBlock()
{
    id = 1;
    cells[0] = {Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2)};
    cells[1] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2)};
    cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0)};
    cells[3] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1)};
    Move(0, 3);
}
void LBlock::Draw(int offSetX, int offSetY)
{
    auto tiles = GetCellPositions();
    for (auto item : tiles)
    {
        DrawRectangle(item.col * cellSize + offSetX, item.row * cellSize + offSetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}
std::vector<Position> LBlock::GetCellPositions()
{
    return Block::GetCellPositions();
}

JBlock::JBlock()
{
    id = 2;
    cells[0] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2)};
    cells[1] = {Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1)};
    cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2)};
    cells[3] = {Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1)};
    Move(0, 3);
}
void JBlock::Draw(int offSetX, int offSetY)
{
    auto tiles = GetCellPositions();
    for (auto item : tiles)
    {
        DrawRectangle(item.col * cellSize + offSetX, item.row * cellSize + offSetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}
std::vector<Position> JBlock::GetCellPositions()
{
    return Block::GetCellPositions();
}

IBlock::IBlock()
{
    id = 3;
    cells[0] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)};
    cells[1] = {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)};
    cells[2] = {Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)};
    cells[3] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1)};
    Move(-1, 3);
}
void IBlock::Draw(int offSetX, int offSetY)
{
    auto tiles = GetCellPositions();
    for (auto item : tiles)
    {
        DrawRectangle(item.col * cellSize + offSetX, item.row * cellSize + offSetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}
std::vector<Position> IBlock::GetCellPositions()
{
    return Block::GetCellPositions();
}

OBlock::OBlock()
{
    id = 4;
    cells[0] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)};
    cells[1] = cells[2] = cells[3] = cells[0];
    Move(0, 4);
}
void OBlock::Draw(int offSetX, int offSetY)
{
    auto tiles = GetCellPositions();
    for (auto item : tiles)
    {
        DrawRectangle(item.col * cellSize + offSetX, item.row * cellSize + offSetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}
std::vector<Position> OBlock::GetCellPositions()
{
    return Block::GetCellPositions();
}

SBlock::SBlock()
{
    id = 5;
    cells[0] = {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1)};
    cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2)};
    cells[2] = {Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1)};
    cells[3] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1)};
    Move(0, 3);
}
void SBlock::Draw(int offSetX, int offSetY)
{
    auto tiles = GetCellPositions();
    for (auto item : tiles)
    {
        DrawRectangle(item.col * cellSize + offSetX, item.row * cellSize + offSetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}
std::vector<Position> SBlock::GetCellPositions()
{
    return Block::GetCellPositions();
}

TBlock::TBlock()
{
    id = 6;
    cells[0] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)};
    cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1)};
    cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)};
    cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)};
    Move(0, 3);
}
void TBlock::Draw(int offSetX, int offSetY)
{
    auto tiles = GetCellPositions();
    for (auto item : tiles)
    {
        DrawRectangle(item.col * cellSize + offSetX, item.row * cellSize + offSetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}
std::vector<Position> TBlock::GetCellPositions()
{
    return Block::GetCellPositions();
}

ZBlock::ZBlock()
{
    id = 7;
    cells[0] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2)};
    cells[1] = {Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1)};
    cells[2] = {Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2)};
    cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0)};
    Move(0, 3);
}
void ZBlock::Draw(int offSetX, int offSetY)
{
    auto tiles = GetCellPositions();
    for (auto item : tiles)
    {
        DrawRectangle(item.col * cellSize + offSetX, item.row * cellSize + offSetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}
std::vector<Position> ZBlock::GetCellPositions()
{
    return Block::GetCellPositions();
}