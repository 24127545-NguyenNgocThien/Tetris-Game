#include "grid.h"
#include "colors.h"
#include <iostream>
#include <algorithm>

void Grid::ClearRow(int row)
{
    for (int col = 0; col < numCols; col++)
    {
        grid[row][col] = 0;
    }
}

void Grid::MoveRowDown(int row, int rowsCleared)
{
    for (int col = 0; col < numCols; col++)
    {
        grid[row + rowsCleared][col] = grid[row][col];
        grid[row][col] = 0;
    }
}

bool Grid::IsRowFull(int row)
{
    for (int col = 0; col < numCols; col++)
    {
        if (grid[row][col] == 0)
        {
            return false;
        }
    }
    return true;
}

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            grid[row][col] = 0;
        }
    }
}

void Grid::Print()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            std::cout << grid[row][col] << " ";
        }
        std::cout << "\n";
    }
}

void Grid::Draw()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            int cellValue = grid[row][col];
            Color color = colors[cellValue];

            // Nếu đang flash và hàng này nằm trong rowsToClear
            if (isFlashing && IsRowMarked(row))
            {
                if (static_cast<int>((GetTime() - flashStartTime) / 0.2) % 2 == 0) // Nhấp nháy 0.2s
                {
                    color = LIGHTGRAY;
                }
            }

            DrawRectangle(col * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, color);
        }
    }

    // Sau khi flash xong sẽ xóa + dồn hàng
    if (FlashFinished())
    {
        // Quay ngược danh sách, xóa từ dưới lên trên theo bảng
        std::sort(rowsToClear.begin(), rowsToClear.end());

        int shift = 0;
        for (int row = numRows - 1; row >= 0; row--)
        {
            if (!rowsToClear.empty() && row == rowsToClear.back())
            {
                // Gặp hàng cần xóa sẽ tăng shift, xóa và bỏ khỏi list
                ClearRow(row);
                rowsToClear.pop_back();
                shift++;
            }
            else if (shift > 0)
            {
                // Dịch hàng hiện tại xuống
                MoveRowDown(row, shift);
            }
        }

        isFlashing = false;
    }
}


bool Grid::FlashFinished()
{
    return (isFlashing && GetTime() - flashStartTime > 0.5);
}

bool Grid::IsCellOutSide(int row, int col)
{
    if (row >= 0 && row < numRows && col >= 0 && col < numCols)
    {
        return false;
    }
    return true;
}

bool Grid::IsCellEmpty(int row, int col)
{
    if (grid[row][col] == 0)
    {
        return true;
    }
    return false;
}

bool Grid::IsRowMarked(int row) // Kiểm tra hàng có trong danh sách xóa không
{
    for (int r : rowsToClear)
    {
        if (r == row)
            return true;
    }
    return false;
}

int Grid::ClearFullRows() // Lưu danh sách các hàng cần xóa, việc xóa hàng sẽ do Draw() thực hiện
{
    rowsToClear.clear();
    for (int row = numRows - 1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            rowsToClear.push_back(row);
        }
    }

    if (!rowsToClear.empty())
    {
        isFlashing = true;
        flashStartTime = GetTime();
    }

    return rowsToClear.size();
}
