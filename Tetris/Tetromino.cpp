#include <vector>
#include <iostream>
#include "Point.h"
#include "Tetromino.h"

TetShape Tetromino::getRandomShape() {
	return static_cast<TetShape>(rand() % static_cast<int>(TetShape::TetShapeCount));
}

// set the shape
//  - clear any blockLocs set previously
//  - set the blockLocs for the shape
//  - set the color for the shape
void Tetromino::setShape(TetShape shape)
{
	blockLocs = {};
	this->shape = shape;
	switch (shape)
	{
		case TetShape::SHAPE_S:
			color = TetColor::RED;
			blockLocs.push_back(Point(0, 0));
			blockLocs.push_back(Point(-1, 0));
			blockLocs.push_back(Point(0, 1));
			blockLocs.push_back(Point(1, 1));
			break;
		case TetShape::SHAPE_Z:
			color = TetColor::ORANGE;
			blockLocs.push_back(Point(0, 0));
			blockLocs.push_back(Point(0, 1));
			blockLocs.push_back(Point(1, 0));
			blockLocs.push_back(Point(-1, 1));
			break;
		case TetShape::SHAPE_L:
			color = TetColor::YELLOW;
			blockLocs.push_back(Point(0, 0));
			blockLocs.push_back(Point(0, 1));
			blockLocs.push_back(Point(0, -1));
			blockLocs.push_back(Point(1, -1));
			break;
		case TetShape::SHAPE_J:
			color = TetColor::GREEN;
			blockLocs.push_back(Point(0, 0));
			blockLocs.push_back(Point(0, -1));
			blockLocs.push_back(Point(0, 1));
			blockLocs.push_back(Point(-1, -1));
			break;
		case TetShape::SHAPE_O:
			color = TetColor::BLUE_LIGHT;
			blockLocs.push_back(Point(0, 0));
			blockLocs.push_back(Point(1, 0));
			blockLocs.push_back(Point(0, 1));
			blockLocs.push_back(Point(1, 1));
			break;
		case TetShape::SHAPE_I:
			color = TetColor::BLUE_DARK;
			blockLocs.push_back(Point(0, 0));
			blockLocs.push_back(Point(0, -1));
			blockLocs.push_back(Point(0, 1));
			blockLocs.push_back(Point(0, 2));
			break;
		case TetShape::SHAPE_T:
			color = TetColor::PURPLE;
			blockLocs.push_back(Point(0, 0));
			blockLocs.push_back(Point(-1, 0));
			blockLocs.push_back(Point(0, -1));
			blockLocs.push_back(Point(1, 0));
			break;
	}
}

// rotate the shape 90 degrees around [0,0] (clockwise)
// to do this:
//  - iterate through blockLocs
//  - rotate each Point 90 degrees around [0,0]
// hint: rotate the point [1,2] clockwise around [0,0] and note
// how the x,y values change. There are 2 functions in the Point
// class that can be used to accomplish a rotation.	
void Tetromino::rotateCW()
{
	for (int i = 0; i < int(blockLocs.size()); i++)
	{
		blockLocs[i].swapXY();
		blockLocs[i].multiplyY(-1);
	}
}

// print a grid to display the current shape
// to do this:
// print out a “grid” of text to represent a co-ordinate
// system.  Start at top left [-3,3] go to bottom right [3,-3]
// (use nested for loops)
//  for each [x,y] point, loop through the blockLocs and if
//  the point exists in the list, print an 'x' instead of a '.'
// You should end up with something like this:
// (results will vary depending on shape and rotation, eg: this
//  one shows a T shape rotated clockwise once)
//  .......
//  .......
//  ...x...
//  ..xx...
//  ...x...
//  .......
void Tetromino::printToConsole() const
{
	bool set = false;
	const int MAX_SIZE{ 4 };
	for (int y{ -3 }; y < MAX_SIZE; y++)
	{
		for (int x{ -3 }; x < MAX_SIZE; x++)
		{
			for (int i{ 0 }; i < NUM_POINTS; i++)
			{
				if (!set && blockLocs[i].getX() == x && blockLocs[i].getY() == y * -1) {
					std::cout << "X";
					set = true;
				}
			}
			if (!set)
			{
				std::cout << ".";
			}
			set = false;
		}
		std::cout << '\n';
	}
}