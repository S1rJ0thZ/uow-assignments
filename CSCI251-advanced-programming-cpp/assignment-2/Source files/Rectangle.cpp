// Rectangle implementation
//
// File name: Rectangle.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include "Rectangle.h"
#include "util.h"

using namespace std;




// Constructor
Rectangle::Rectangle(string name, bool containsWarpSpace, Point* vertices) : 
ShapeTwoD(name, containsWarpSpace)
{
	for (int i = 0; i < 4; ++i) {
		this->vertices[i] = vertices[i];
	}
	
	// get max and min
	loadMaxMin();
	
	// Load points on and in shape
	loadPointsOnPerimeter();
	loadPointsInShape();
}




// Display method
string Rectangle::toString()
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
void Rectangle::setArea()
{
	area = computeArea();
	areaComputed = true;
}




// Find and load points
void Rectangle::loadMaxMin()
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


void Rectangle::loadPointsOnPerimeter()
{
	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			Point currentPt = {x, y};
			
			if (isPointOnShape(currentPt))
				pointsOnPerimeter.push_back(currentPt);
		}
	}
}


void Rectangle::loadPointsInShape()
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
double Rectangle::computeArea()
{
	// get length and breadth
	int length = maxX - minX;
	int breadth = maxY - minY;
	
	return length * breadth;
}


bool Rectangle::isPointInShape(const Point& vertex)
{
	if (vertex.x > minX && vertex.x < maxX && vertex.y > minY && vertex.y < maxY)
		return true;
	else
		return false;
}


bool Rectangle::isPointOnShape(const Point& vertex)
{
	if ( ((vertex.y == maxY || vertex.y == minY) && vertex.x > minX && vertex.x < maxX) ||
		((vertex.x == minX || vertex.x == maxX) && vertex.y > minY && vertex.y < maxY) ) {
		return true;
	} else {
		return false;
	}
}







