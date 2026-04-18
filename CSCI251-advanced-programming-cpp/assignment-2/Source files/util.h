// Utility functions
//
// File name: util.h

#ifndef UTIL_H
#define UTIL_H

class ShapeTwoD;

// Data structures
struct Point {
	int x;
	int y;
	
	// Operator overloads
	bool operator==(const Point& otherPt) const
	{
		return x == otherPt.x && y == otherPt.y;
	}
	
	bool operator!=(const Point& otherPt) const
	{
		return !(*this == otherPt);
	}
};


// Public Functions
void readInput(ShapeTwoD** Shape2D, int& size);
void computeShapeAreas(ShapeTwoD** Shape2D, const int& size);
void displayShapesReport(ShapeTwoD** Shape2D, const int& size);
void sortShapesMenu(ShapeTwoD** Shape2D, const int& size);
void deallocateMemory(ShapeTwoD** Shape2D, int& size);

#endif



