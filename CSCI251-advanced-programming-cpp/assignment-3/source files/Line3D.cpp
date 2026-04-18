// Line3D implementation
//
// Compile object: g++ -std=c++11 -c Line3D.cpp -o Line3D.o
//
// File name: Line3D.cpp

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Point3D.h"
#include "Line3D.h"

using namespace std;


/* Protected */
void Line3D::setLength()
{
	length = sqrt( pow(pt1.getX()- pt2.getX(), 2) + pow(pt1.getY() - pt2.getY(), 2) + 
					pow(pt1.getZ() - pt2.getZ(), 2) );
}
	
	
	
/* Public */
// Constructor
Line3D::Line3D(Point3D pt1, Point3D pt2)
{
	setPt1(pt1);
	setPt2(pt2);
	setLength();
}


// Accessor
Point3D Line3D::getPt1()
{
	return pt1;
}

Point3D Line3D::getPt2()
{
	return pt2;
}

double Line3D::getScalarValue()
{
	return length;
}


// Mutator
void Line3D::setPt1(Point3D pt1)
{
	this->pt1 = pt1;
}

void Line3D::setPt2(Point3D pt2){
	this->pt2 = pt2;
}


// Operator Overloading
bool Line3D::operator==(const Line3D& other) const
{
	return (this->pt1 == other.pt1 && this->pt2 == other.pt2);
}

bool Line3D::operator!=(const Line3D& other) const
{
	return !(*this == other);
}

bool Line3D::operator<(const Line3D& other) const
{
	return (this->length < other.length);
}


//freind function overloading
ostream& operator<<(ostream& out, const Line3D& line)
{
	// formatting 
	out << right << fixed << setprecision(3);
	
	// Show point values
	out << line.pt1;
	out << setw(3) << " ";
	out << line.pt2;
	
	return out;
}

		
		
		

