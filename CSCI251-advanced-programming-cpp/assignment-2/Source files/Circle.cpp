// Circle implementation
//
// File name: Circle.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include "Circle.h"
#include "util.h"

using namespace std;




// Constructor
Circle::Circle(string name, bool containsWarpSpace, Point center, int radius) : 
ShapeTwoD(name, containsWarpSpace)
{
	this->center = center;
	this->radius = radius;
	
	// Load points on and in shape
	loadPointsOnPerimeter();
	loadPointsInShape();
}




// Find points
void Circle::loadPointsOnPerimeter()
{
	Point top = {center.x, center.y + radius};
	Point bottom = {center.x, center.y - radius};
	Point right = {center.x + radius, center.y};
	Point left = {center.x - radius, center.y};
	
	pointsOnPerimeter = {top, bottom, right, left};
}


void Circle::loadPointsInShape()
{
	int topBound = center.y + radius;
	int bottomBound = center.y - radius;
	int leftBound = center.x - radius;
	int rightBound = center.x + radius;
	
	for (int y = bottomBound; y <= topBound; ++y) {
		for (int x = leftBound; x <= rightBound; ++x) {
			Point currentPt = {x, y};
			
			if (isPointInShape(currentPt) && currentPt != center)
				pointsInShape.push_back(currentPt);
		}
	}
}
		
	
	
		
// Display method
string Circle::toString()
{
	ostringstream oss;
	
	oss << ShapeTwoD::toString();
	
	// formatting
	oss << fixed << setprecision(2);
	
	// display circle info
	oss << "Area : " << area << " units square" << endl;
	oss << "Center : (" << center.x << ", " << center.y << ")" << endl;
	oss << "Radius : " << radius << " units" << endl;
	oss << endl;
	
	oss << "Points on perimeter : ";
	for (const Point& point : pointsOnPerimeter) {
		oss << "(" << point.x << ", " << point.y << ")";
	}
	oss << endl;
	
	oss << "\nPoints within shape : ";
	for (const Point& point : pointsInShape) {
		oss << "(" << point.x << ", " << point.y << ")"; 
	}
	oss << endl;
	
	return oss.str();
}




// Mutator
void Circle::setArea()
{
	area = computeArea();
	areaComputed = true;
}




// Calculation methods
double Circle::computeArea() 
{
	double pi = M_PI;
	return pi * pow(radius, 2);
}


bool Circle::isPointInShape(const Point& vertex)
{
	double distance = sqrt( pow(center.y - vertex.y, 2) + pow(center.x - vertex.x, 2) );
	if (distance < radius)
		return true;
	else
		return false;
}


bool Circle::isPointOnShape(const Point& vertex)
{
	double distance = sqrt( pow(center.x - vertex.x, 2) + pow(center.y - vertex.y, 2) );
	if (distance == radius)
		return true;
	else
		return false;
}


/*
// Destructor
Circle::~Circle() 
{
	delete pointsInShape[];
}
*/
