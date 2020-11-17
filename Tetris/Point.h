#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
	// Allow TestSuite to access private vars
	friend class TestSuite;

private:
	int x;
	int y;

public:
	Point() { x = 0; y = 0; }
	Point(int newX, int newY) { x = newX; y = newY; }
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y){ this->y = y; }
	void setXY(int x, int y) { this->x = x;  this->y = y; }

	void swapXY();				// swap x and y
	void multiplyX(int factor);	// multiply x by some factor
	void multiplyY(int factor);	// multiply y by some factor

	std::string toString() const;	// return a string in the form "[x,y]" to represent
									// the state of the Point instance (for debugging)
};

#endif