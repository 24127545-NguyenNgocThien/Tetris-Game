#include "../include/grid.h"
#include "../include/color.h"

Grid::Grid()
{
    cell_size = 50;
    num_cols = 10;
    num_rows = 20;
    colors = Bang_Mau();
    Init();
}

void Grid::Init()
{
    for(int row = 0; row < num_rows; row++)
    {
        for(int col = 0; col < num_cols; col++)
        {
            grid[row][col] = 0;
        }
    }
}

void Grid::DrawGrid()
{
    for(int row = 0; row < num_rows; row++)
    {
        for(int col = 0; col < num_cols; col++)
        {
            // grid[][] = 0 => chưa đc lắp đầy còn = từ 1 -> 7 là đã đc lắp đầy
            int cell_color = grid[row][col];
            DrawRectangle(col * cell_size + 11, row * cell_size + 1, cell_size - 1, cell_size - 1, colors[cell_color]);
            DrawRectangleLines(col * cell_size + 11, row * cell_size + 1, cell_size - 1, cell_size - 1, colors[cell_color]);
        }
    }
}

bool Grid::IsOutGrid(Position xy)
{
    if(xy.x < 0 || xy.x >= num_cols || xy.y >= num_rows)
    {
        return true;
    }
    return false;
}

bool Grid::IsEmptyCell(Position xy)
{
    return grid[xy.y][xy.x] == 0;
}

bool Grid::IsFullRow(int row)
{
    for(int col = 0; col < num_cols; col++)
    {
        if(grid[row][col] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for(int col = 0; col < num_cols; col++)
    {
        grid[row][col] = 0;
    }
}

// còn xuất hiện lỗi chx fix được (tile sau khi rơi xuống có thể tạo fullrow nhưng lại ko xóa kịp trước khi block khác rơi xuốngxuống)
int Grid::ClearFullRow()
{
    int completed_row = 0;
    for(int row = num_rows - 1; row >= 0; row--)
    {
        if(IsFullRow(row))
        {
            ClearRow(row);
            completed_row++;
        }
    }
    if(completed_row > 0)
    {
        MoveRowDown();
    }
    return completed_row;
}

void Grid::MoveRowDown()
{
    for(int col = 0; col < num_cols; col++)
    {
        for(int row = num_rows - 2; row >= 0; row--)
        {
            if(grid[row][col] != 0 && grid[row + 1][col] == 0)
            {
                int curr_row = row;
                while(grid[curr_row + 1][col] == 0 && curr_row + 1 < num_rows)
                {
                    grid[curr_row + 1][col] = grid[curr_row][col];
                    grid[curr_row][col] = 0;
                    curr_row++;
                }
            }
        }
    }
}