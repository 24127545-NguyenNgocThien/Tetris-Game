#pragma once
#include <raylib.h>
#include <vector>

class Grid
{
private:
    int numRows;
    int numCols;
    int cellSize;
    double flashStartTime = 0;
    std::vector<Color> colors;
    std::vector<int> rowsToClear;
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numCompleted);
public:
    bool isFlashing = false;
    int grid[20][10];
    Grid();
    void Initialize();
    void Print();
    void Draw();
    bool FlashFinished();
    bool IsRowMarked(int row);
    bool IsCellEmpty(int row, int col);
    bool IsCellOutSide(int row, int col);
    int ClearFullRows();
};