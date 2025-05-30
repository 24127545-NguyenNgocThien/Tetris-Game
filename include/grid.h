#pragma once
#include "raylib.h"
#include "position.h"
#include <vector>

class Grid
{
public:
    int cell_size;
    int num_rows;
    int num_cols;
    std::vector<Color> colors;
    int grid[20][10];
    void Init();
    void DrawGrid();
    Grid();
    bool IsOutGrid(Position xy);
    bool IsEmptyCell(Position xy);
    bool IsFullRow(int row);
    void ClearRow(int row);
    int ClearFullRow();
    void MoveRowDown();
};