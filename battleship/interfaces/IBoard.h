#pragma once

class IBoardVisitor;

class IBoard
{
public:
    virtual ~IBoard() {}

    virtual void Accept(IBoardVisitor &v) = 0;
};
