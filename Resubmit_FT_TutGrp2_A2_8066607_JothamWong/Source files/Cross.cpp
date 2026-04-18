// Cross implementation
//
// File name: Cross.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include "Cross.h"
#include "util.h"

using namespace std;



// Constructor 
Cross::Cross(string name, bool containsWarpSpace, Point* vertices) :
ShapeTwoD(name, containsWarpSpace)
{
	for (int i = 0; i < 12; ++i) {
		this->vertices[i] = vertices[i];
	}
	
	// Load max min and bounds
	loadMaxMin();
	loadBounds();
	
	// Load points on and in shape
	loadPointsOnPerimeter();
	loadPointsInShape();
	
}




// Display method
string Cross::toString()
{
	ostringstream oss;
	
	oss << ShapeTwoD::toString();
	
	//formatting
	oss << fixed << setprecision(2);
	
	// display Cross info
	oss << "Area : " << area << " units square" << endl;
	oss << "Vertices : " << endl;
	
	for (int i = 0; i < 12; ++i) {
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
void Cross::setArea()
{
	area = computeArea();
	areaComputed = true;
}




// Find and load points
void Cross::loadMaxMin()
{	
	minX = vertices[0].x;
	minY = vertices[0].y;
	maxX = vertices[0].x;
	maxY = vertices[0].y;
	
	// Find bounds
	//for (const Point& vertex : vertices) 
	for (int i = 1; i < 12; ++i) {
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


void Cross::loadBounds()
{
	// Squares X bounds
	topLeftSqX = maxX;
	topRightSqX = minX;
	bottomLeftSqX = maxX;
	bottomRightSqX = minX;
	
	// Squares Y bounds
	topLeftSqY = minY;
	bottomLeftSqY = maxY;
	topRightSqY = minY;
	bottomRightSqY = maxY;
	
	// find Sqare lengths
	for (const Point& vertex : vertices) {
		// Find X lengths
		if (vertex.y == minY) {
			if (vertex.x < bottomLeftSqX)
				bottomLeftSqX = vertex.x;
				
			if (vertex.x > bottomRightSqX)
				bottomRightSqX = vertex.x;
		}
		
		if (vertex.y == maxY) {
			if (vertex.x < topLeftSqX)
				topLeftSqX = vertex.x;
			
			if (vertex.x > topRightSqX)
				topRightSqX = vertex.x;
		}
		
		// Find Y lengths
		if (vertex.x == minX) {
			if (vertex.y < bottomLeftSqY)
				bottomLeftSqY = vertex.y;
			
			if (vertex.y > topLeftSqY)
				topLeftSqY = vertex.y;
		}
		
		if (vertex.x == maxX) {
			if (vertex.y < bottomRightSqY)
				bottomRightSqY = vertex.y;
				
			if (vertex.y > topRightSqY)
				topRightSqY = vertex.y;
		}
	}
}


void Cross::loadPointsOnPerimeter()
{
	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			Point currentPt = {x, y};
			
			if (isPointOnShape(currentPt))
				pointsOnPerimeter.push_back(currentPt);
		}
	}
}


void Cross::loadPointsInShape()
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
double Cross::computeArea()
{
	int length = maxX - minX;
	int breadth = maxY - minY;
	
	double total = length * breadth;
	
	// Compute Square areas
	double topLeftSq = (topLeftSqX - minX) * (maxY - topLeftSqY);
	double topRightSq = (maxX - topRightSqX) * (maxY - topRightSqY);
	double bottomLeftSq = (bottomLeftSqX - minX) * (bottomLeftSqY - minY);
	double bottomRightSq = (maxX - bottomRightSqX) * (bottomRightSqY - minY);
	
	// Find Area
	double area = total - (topLeftSq + topRightSq + bottomLeftSq + bottomRightSq);
	
	return area;
}


bool Cross::isPointInShape(const Point& vertex)
{
	if (vertex.x > minX && vertex.x < maxX && vertex.y > minY && vertex.y < maxY) {
		if ( (vertex.x <= bottomLeftSqX && vertex.y <= bottomLeftSqY) ||
			 (vertex.x >= bottomRightSqX && vertex.y <= bottomRightSqY) ||
			 (vertex.x <=  topLeftSqX && vertex.y >= topLeftSqY) ||
			 (vertex.x >= topRightSqX && vertex.y >= topRightSqY) ) {
			
			return false;	 
		}
		
		return true; 
		
	} else {
		return false;
	}
}


bool Cross::isPointOnShape(const Point& vertex)
{
	// Checks for max and min edges
	bool onBottomBound = (vertex.y == minY && 
						  vertex.x > bottomLeftSqX && 
						  vertex.x < bottomRightSqX);
						
	bool onTopBound = (vertex.y == maxY &&
					   vertex.x > topLeftSqX &&
					   vertex.x < topRightSqX);
					 
	bool onLeftBound = (vertex.x == minX && 
						vertex.y > bottomLeftSqY &&
						vertex.y < topLeftSqY);
						
	bool onRightBound = (vertex.x == maxX &&
						 vertex.y > bottomRightSqY &&
						 vertex.y < topRightSqY);
						 
	// Checks for point lying on square
	bool onBottomLeftSq = ( (vertex.x == bottomLeftSqX &&
							 vertex.y > minY &&
							 vertex.y < bottomLeftSqY) ||
							(vertex.y == bottomLeftSqY &&
							 vertex.x > minX &&
							 vertex.x < bottomLeftSqX) );
							  
	bool onBottomRightSq = ( (vertex.x == bottomRightSqX &&
							  vertex.y > minY &&
							  vertex.y < bottomRightSqY) ||
							 (vertex.y == bottomRightSqY &&
							  vertex.x > bottomRightSqX &&
							  vertex.x < maxX) );
							   
	bool onTopLeftSq = ( (vertex.x == topLeftSqX &&
						  vertex.y > topLeftSqY &&
						  vertex.y < maxY) ||
						 (vertex.y == topLeftSqY &&
						  vertex.x > minX &&
						  vertex.x < topLeftSqX) );
						   
	bool onTopRightSq = ( (vertex.x == topRightSqX &&
						   vertex.y > topRightSqY &&
						   vertex.y < maxY) ||
						  (vertex.y == topRightSqY &&
						   vertex.x > topRightSqX &&
						   vertex.x < maxX) );
						   
	if (onBottomBound || onTopBound || onLeftBound || onRightBound || 
		onBottomLeftSq || onBottomRightSq || onTopLeftSq || onTopRightSq) {
		return true;
	} else{
		return false;
	}
}




