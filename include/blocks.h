#include "position.h"
#include "block.h"

class LBlock : public Block
{
public:
    LBlock();
    void Draw(int offSetX, int offSetY) override;
    std::vector<Position> GetCellPositions() override;
};

class JBlock : public Block
{
public:
    JBlock();
    void Draw(int offSetX, int offSetY) override;
    std::vector<Position> GetCellPositions() override;
};

class IBlock : public Block
{
public:
    IBlock();
    void Draw(int offSetX, int offSetY) override;
    std::vector<Position> GetCellPositions() override;
};

class OBlock : public Block
{
public:
    OBlock();
    void Draw(int offSetX, int offSetY) override;
    std::vector<Position> GetCellPositions() override;
};

class SBlock : public Block
{
public:
    SBlock();
    void Draw(int offSetX, int offSetY) override;
    std::vector<Position> GetCellPositions() override;
};

class TBlock : public Block
{
public:
    TBlock();
    void Draw(int offSetX, int offSetY) override;
    std::vector<Position> GetCellPositions() override;
};

class ZBlock : public Block
{
public:
    ZBlock();
    void Draw(int offSetX, int offSetY) override;
    std::vector<Position> GetCellPositions() override;
};
