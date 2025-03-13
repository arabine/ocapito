#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "Tile.h"
#include "Point.h"
#include "IBoard.h"
#include "IBoardVisitor.h"

class Board : public IBoard
{

public:
	Board();
	virtual ~Board() {}

	bool AddBoat(Boat &b);
    int GetSize() const { return m_gridSize; }
	void Print();
    void Fire(const Point &p);

	// From IBoard
	virtual void Accept(IBoardVisitor &v);

private:
    int m_gridSize = 10;
	Tile m_tiles[10][10];
};

#endif // BOARD_H
