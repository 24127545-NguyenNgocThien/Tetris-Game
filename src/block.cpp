#include "block.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    Colors temp;
    colors = temp.GetCellColors();
    rowOffSet = 0;
    colOffSet = 0;
}

void Block::Draw(int offSetX, int offSetY)
{
    std::vector<Position> tiles = GetCellPositions();
    for (Position item : tiles)
    {
        DrawRectangle(item.col * cellSize + offSetX, item.row * cellSize + offSetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int cols)
{
    rowOffSet += rows;
    colOffSet += cols;
}

void Block::Rotation()
{
    rotationState++;
    if (rotationState >= (int)cells.size())
    {
        rotationState = 0;
    }
}

void Block::UndoRotation()
{
    rotationState--;
    if (rotationState < 0)
    {
        rotationState = (int)cells.size() - 1;
    }
}

std::vector<Position> Block::GetCellPositions()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> moveTiles;
    for (Position item : tiles)
    {
        Position newPos = Position(item.row + rowOffSet, item.col + colOffSet);
        moveTiles.push_back(newPos);
    }
    return moveTiles;
}