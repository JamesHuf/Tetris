// Author: James Hufnagel

#include "GridTetromino.h"
#include "Point.h"
#include <vector>

// constructor, initialize gridLoc to 0,0
GridTetromino::GridTetromino() : gridLoc{ 0,0 }
{
	Tetromino();
}

// return the tetromino's grid/gameboard loc (x,y)
Point GridTetromino::getGridLoc() const
{
	return gridLoc;
}

// sets the tetromino's grid/gameboard loc using x,y
void GridTetromino::setGridLoc(int x, int y)
{
	gridLoc.setXY(x, y);
}

// sets the tetromino's grid/gameboard loc using a Point
void GridTetromino::setGridLoc(const Point& pt)
{
	gridLoc = pt;
}

// transpose the gridLoc of this shape
//	(1,0) represents a move to the right (x+1)
//	(-1,0) represents a move to the left (x-1)
//	(0,1) represents a move down (y+1)
void GridTetromino::move(int xOffset, int yOffset)
{
	gridLoc.setXY(gridLoc.getX() + xOffset, gridLoc.getY() + yOffset);
}

// build and return a vector of Points to represent our inherited
// blockLocs vector mapped to the gridLoc of this object instance.
// eg: if we have a Point [x,y] in our vector,
// and our gridLoc is [5,6] the mapped Point would be [5+x,6+y].
std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const
{
	std::vector<Point> LocsOnGrid{};
	int x{ gridLoc.getX() };
	int y{ gridLoc.getY() };
	for (int i{ 0 }; i < int(blockLocs.size()); i++) {
		LocsOnGrid.push_back(Point(blockLocs[i].getX() + x, blockLocs[i].getY() + y));
	}
	return LocsOnGrid;
}