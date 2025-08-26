#pragma once
#include "colors.h"
#include "position.h"
#include <map>
#include <vector>

class Block
{
protected:
    int cellSize;
    int rotationState;
    int rowOffSet;
    int colOffSet;
    std::vector<Color> colors;
    std::map<int, std::vector<Position>> cells;
public:
    int id;
    Block();
    virtual ~Block() {}

    virtual void Draw(int offSetX, int offSetY) = 0;                 // abstract
    virtual std::vector<Position> GetCellPositions();            // abstract
    
    void Move(int row, int col);
    void Rotation();
    void UndoRotation();
};
