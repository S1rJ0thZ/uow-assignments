// Point2D implementation
//
// Compile object: g++ -std=c++11 -c Point2D.cpp -o Point2D.o
//
// File name: Point2D.cpp

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Point2D.h"

using namespace std;


/* Protected */
void Point2D::setDistFrOrigin()
{
	distFrOrigin = sqrt( pow(x - 0, 2) + pow(y - 0, 2) );
}



/* Public */
// Constructor
Point2D::Point2D(int x, int y)
{
	setX(x);
	setY(y);
	setDistFrOrigin();
}


// Accessors
int Point2D::getX()
{
	return x;
}

int Point2D::getY()
{
	return y;
}

double Point2D::getScalarValue()
{
	return distFrOrigin;
}


// Mutators
void Point2D::setX(int x)
{
	if (x >= -999 && x <= 999)
		this->x = x;
}

void Point2D::setY(int y)
{
	if (y >= -999 && y <= 999)
		this->y = y;
}


// Operator overloading 
bool Point2D::operator==(const Point2D& other) const
{
	return ( this->x == other.x && this->y == other.y );
}

bool Point2D::operator!=(const Point2D& other) const
{
	return !(*this == other);
}

bool Point2D::operator<(const Point2D& other) const
{
	return (this->distFrOrigin < other.distFrOrigin);
}

// Friend function overload
ostream& operator<<(ostream& out, const Point2D& pt)
{
	// formatting 
	out << right << fixed << setprecision(3);
	
	// Coordinate values
	out << "[";
	out << setw(4) << pt.x << ", ";
	out << setw(4) << pt.y;
	out << "]";
	
	/*
	// Distance values
	out << setw(3) << " ";
	out << pt.distFrOrigin << endl;
	*/
	
	return out;	
}





