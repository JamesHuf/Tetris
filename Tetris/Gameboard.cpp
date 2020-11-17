// Author: James Hufnagel
#include "Gameboard.h"
#include <iomanip>
#include <assert.h>

// constructor - empty() the grid
Gameboard::Gameboard()
{
	empty();
}

// return the content at a given point
int Gameboard::getContent(Point pt) const
{
	assert(pt.getX() >= 0 && pt.getX() < MAX_X
		&& pt.getY() >= 0 && pt.getY() < MAX_Y);
	return grid[pt.getX()][pt.getY()];
}

// return the content at an x,y grid loc
int Gameboard::getContent(int x, int y) const
{
	assert(x >= 0 && x < MAX_X
		&& y >= 0 && y < MAX_Y);
	return grid[x][y];
}

// set the content at a given point
void Gameboard::setContent(Point pt, int content)
{
	assert(pt.getX() >= 0 && pt.getX() < MAX_X
		&& pt.getY() >= 0 && pt.getY() < MAX_Y);
	grid[pt.getX()][pt.getY()] = content;
}

// set the content at an x,y grid loc
void Gameboard::setContent(int x, int y, int content)
{
	assert(x >= 0 && x < MAX_X
		&& y >= 0 && y < MAX_Y);
	grid[x][y] = content;
}


// set the content for an array of grid locs
void Gameboard::setContent(std::vector<Point> locs, int content)
{
	for (int i{ 0 }; i < static_cast<int>(locs.size()); i++)
	{
		assert(locs[i].getX() >= 0 && locs[i].getX() < MAX_X
			&& locs[i].getY() >= 0 && locs[i].getY() < MAX_Y);
		grid[locs[i].getX()][locs[i].getY()] = content;
	}
}



// return true if the content at ALL (valid) points is empty
//   *** IMPORTANT NOTE: invalid x,y values can be passed to this method.
//   Invalid meaning: outside the bounds of the grid.
//   * ONLY TEST VALID POINTS (disregard the others - and ensure you
//   don't use them to index into the grid).  Testing invalid points
//   would likely result in an out of bounds error or segmentation fault!
//   If no points are valid, return true
bool Gameboard::areLocsEmpty(std::vector<Point> locs) const
{
	bool allValid = true;
	for (int i{ 0 }; i < static_cast<int>(locs.size()); i++)
	{
		// If point is valid
		if (locs[i].getX() >= 0 && locs[i].getX() < MAX_X &&
			locs[i].getY() >= 0 && locs[i].getY() < MAX_Y)
		{
			if (grid[locs[i].getX()][locs[i].getY()] != -1)
			{
				allValid = false;
			}
		}
	}
	return allValid;
}

// removes all completed rows from the board
//   use getCompletedRowIndices() and removeRows() 
//   return the # of completed rows removed
int Gameboard::removeCompletedRows()
{
	std::vector<int> fullRows { getCompletedRowIndices() };
	removeRows(fullRows);
	return fullRows.size();
}


// fill the board with EMPTY_BLOCK 
//   (iterate through each rowIndex and fillRow() with EMPTY_BLOCK))
void Gameboard::empty()
{
	for (int i{ 0 }; i < MAX_Y; i++)
	{
		fillRow(i, EMPTY_BLOCK);
	}
}


// getter for the spawnLoc for new blocks
Point Gameboard::getSpawnLoc() const
{
	return spawnLoc;
}


// print the grid contents to the console (for debugging purposes)
//   use std::setw(2) to space the contents out (#include <iomanip>).
void Gameboard::printToConsole() const
{
	for (int i{ 0 }; i < MAX_Y; i++)
	{
		for (int j{ 0 }; j < MAX_X; j++)
		{
			std::cout << std::setw(2) << grid[j][i];
		}
		std::cout << '\n';
	}
}


// return a bool indicating if a given row is full (no EMPTY_BLOCK in the row)
bool Gameboard::isRowCompleted(int rowIndex) const
{
	bool complete{ true };
	for (int x{ 0 }; x < MAX_X; x++)
	{
		if (grid[x][rowIndex] == EMPTY_BLOCK)
		{
			complete = false;
		}
	}
	return complete;
}


// scan the board for completed rows.
//   Iterate through grid rows and use isRowCompleted(rowIndex)
//   return a vector of completed row indices.
std::vector<int> Gameboard::getCompletedRowIndices() const
{
	std::vector<int> fullRows;
	for (int y{ 0 }; y < MAX_Y; y++)
	{
		if (isRowCompleted(y))
		{
			fullRows.push_back(y);
		}
	}
	return fullRows;
}


// In gameplay, when a full row is completed (filled with content)
// it gets "removed".  To be exact, the row itself is not removed
// but the content from the row above it is copied into it.
// This continues all the way up the grid until the first row
// is copied into the second row.  Finally, the first row is 
// filled with EMPTY_BLOCK
// given a row index:
//   1) Starting at rowIndex, copy each row above the removed
//     row "one-row-downwards" in the grid.
//     (loop from y=rowIndex down to 0, and copyRowIntoRow(y-1, y)).
//   2) call fillRow() on the first row (and place EMPTY_BLOCKs in it).
void Gameboard::removeRow(int rowIndex)
{
	for (int y{ rowIndex }; y > 0; y--)
	{
		copyRowIntoRow(y - 1, y);
	}
	fillRow(0, EMPTY_BLOCK);
}


// given a vector of row indices, remove them 
//   (iterate through the vector and and call removeRow()
//   on each row index). 
void Gameboard::removeRows(std::vector<int> rowIndices)
{
	for (int i{ 0 }; i < static_cast<int>(rowIndices.size()); i++)
	{
		removeRow(rowIndices[i]);
	}
}


// fill a given grid row with specified content
void Gameboard::fillRow(int rowIndex, int content)
{
	for (int i{ 0 }; i < MAX_X; i++)
	{
		grid[i][rowIndex] = content;
	}
}


// copy a source row's contents into a target row.
void Gameboard::copyRowIntoRow(int sourceRowIndex, int targetRowIndex)
{
	for (int i{ 0 }; i < MAX_X; i++)
	{
		grid[i][targetRowIndex] = grid[i][sourceRowIndex];
	}
}
