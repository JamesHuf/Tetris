#include <iostream>
#include "Point.h"

// swap x and y
void Point::swapXY()
{
	int temp = x;
	x = y;
	y = temp;
}

// multiply x by some factor
void Point::multiplyX(int factor)
{
	x *= factor;
}

// multiply y by some factor
void Point::multiplyY(int factor)
{
	y *= factor;
}

// return a string in the form "[x,y]" to represent
// the state of the Point instance (for debugging)
std::string Point::toString() const
{
	return "[" + x + ',' + y + ']';
}