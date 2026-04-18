// Square implementation
//
// File name: Square.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include "Square.h"
#include "util.h"

using namespace std;




// Constructor
Square::Square(string name, bool containsWarpSpace, Point* vertices) :
ShapeTwoD(name, containsWarpSpace)
{
	for (int i = 0; i < 4; ++i) {
		this->vertices[i] = vertices[i];
	}
	
	// load max and min values
	loadMaxMin();
	
	// Load points in and on shape
	loadPointsOnPerimeter();
	loadPointsInShape();
}	




// Display method
string Square::toString()
{
	ostringstream oss;
	
	oss << ShapeTwoD::toString();
	
	// formatting
	oss << fixed << setprecision(2);
	
	// display rectangle info
	oss << "Area : " << area << " units sqaure" << endl;
	oss << "Vertices : " << endl;
	
	for (int i = 0; i < 4; ++i) {
		oss << "Point[" << i << "] : (";
		oss << vertices[i].x << ", " << vertices[i].y << ")" << endl;
	}
	oss << endl;
	
	// Points on shape
	oss << "Points on perimeter : ";
	
	for (const Point& pt : pointsOnPerimeter) {
		oss << "(" << pt.x << ", " << pt.y << ") ";
	}
	oss << endl;
	
	// Points in shape
	oss << "\nPoints within shape : ";
	for (const Point& pt : pointsInShape) {
		oss << "(" << pt.x << ", " << pt.y << ") ";
	}
	oss << endl;
	
	return oss.str();
}




// Mutator
void Square::setArea()
{
	area = computeArea();
	areaComputed = true;
}




// Find and load points
void Square::loadMaxMin()
{
	minX = vertices[0].x;
	minY = vertices[0].y;
	maxX = vertices[0].x;
	maxY = vertices[0].y;
	
	// Find bounds
	//for (const Point& vertex : vertices) 
	for (int i = 1; i < 4; ++i) {
		if (vertices[i].x < minX)
			minX = vertices[i].x;
			
		if (vertices[i].x > maxX)
			maxX = vertices[i].x;
			
		if (vertices[i].y < minY)
			minY = vertices[i].y;
			
		if (vertices[i].y > maxY)
			maxY = vertices[i].y;
	}
}


void Square::loadPointsOnPerimeter()
{
	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			Point currentPt = {x, y};
			
			if (isPointOnShape(currentPt))
				pointsOnPerimeter.push_back(currentPt);
		}
	}
}


void Square::loadPointsInShape()
{
	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			Point currentPt = {x, y};
			
			if (isPointInShape(currentPt))
				pointsInShape.push_back(currentPt);
		}
	}
}
		



// Calculation methods
double Square::computeArea()
{
	int length = maxY - minY;
	return length * length;
}


bool Square::isPointInShape(const Point& vertex)
{
	bool within_x_range = vertex.x > minX && vertex.x < maxX;
	bool within_y_range = vertex.y > minY && vertex.y < maxY;
	
	if (within_x_range && within_y_range)
		return true;
	
	return false;
}


bool Square::isPointOnShape(const Point& vertex)
{
	bool within_x_range = vertex.x > minX && vertex.x < maxX;
	bool within_y_range = vertex.y > minY && vertex.y < maxY;
	
	if ( ((vertex.y == maxY || vertex.y == minY) && within_x_range) ||
		((vertex.x == minX || vertex.x == maxX) && within_y_range) ) {
		return true;
	}
	
	return false;
}






