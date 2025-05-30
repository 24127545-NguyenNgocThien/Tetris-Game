#pragma once
#include "../include/position.h"
#include "../include/color.h"
#include <vector>
#include <map>

class Block
{
    public:
    int id;
    int state;
    std::map<int, std::vector<Position>> trang_thai;
    std::vector<Position> GetTilesPosition();
    Block();
    int offset_x;
    int offset_y;
    std::vector<Color> colors;
    int tiles_size;
    void DrawBlock(int x, int y);
    void Move(int x, int y);
    void Rotate();
    void UndoRotate();
};

class IBlock : public Block
{
public: 
    IBlock();
};

class JBlock : public Block
{
public: 
    JBlock();
};

class LBlock : public Block
{
public: 
    LBlock();
};

class OBlock : public Block
{
public: 
    OBlock();
};

class SBlock : public Block
{
public: 
    SBlock();
};

class TBlock : public Block
{
public: 
    TBlock();
};

class ZBlock : public Block
{
public: 
    ZBlock();
};

