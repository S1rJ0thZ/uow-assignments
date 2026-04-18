// Line2D implementation
//
// Compile object: g++ -std=c++11 -c Line2D.cpp -o Line2D.o
//
// File name: Line2D.cpp

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Point2D.h"
#include "Line2D.h"

using namespace std;


/* Protected */
void Line2D::setLength()
{
	length = sqrt( pow(pt1.getX() - pt2.getX(), 2) + pow(pt1.getY() - pt2.getY(), 2) );
}
	


/* Public */
// Constructor
Line2D::Line2D(Point2D pt1, Point2D pt2)
{
	setPt1(pt1);
	setPt2(pt2);
	setLength();
}


// Accessor
Point2D Line2D::getPt1()
{
	return pt1;
}

Point2D Line2D::getPt2()
{
	return pt2;
}

double Line2D::getScalarValue()
{
	return length;
}


// Mutator
void Line2D::setPt1(Point2D pt1)
{
	this->pt1 = pt1;
}

void Line2D::setPt2(Point2D pt2)
{
	this->pt2 = pt2;
}
		

// Operator Overloading
bool Line2D::operator==(const Line2D& other) const
{
	return (this->pt1 == other.pt1 && this->pt2 == other.pt2);
}

bool Line2D::operator!=(const Line2D& other) const
{
	return !(*this == other);
}

bool Line2D::operator<(const Line2D& other) const
{
	return (this->length < other.length);
}


//freind function overloading
ostream& operator<<(ostream& out, const Line2D& line)
{
	// formatting 
	out << right << fixed << setprecision(3);
	
	// Show point values
	out << line.pt1;
	out << setw(3) << " ";
	out << line.pt2;
	
	return out;
}












