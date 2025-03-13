#pragma once

class Tile;

class IBoardVisitor
{
public:
    virtual void Visit(const Tile &t) = 0;
};
