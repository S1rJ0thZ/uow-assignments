// Point3D implementation
//
// Compile object: g++ -std=c++11 -c Point3D.cpp -o Point3D.o
//
// File name: Point3D.cpp

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Point3D.h"

using namespace std;


/* Protected */
void Point3D::setDistFrOrigin()
{
	distFrOrigin = sqrt( pow(x - 0, 2) + pow(y - 0, 2) + pow(z - 0, 2) );
}



/* Public */
// Constructor
Point3D::Point3D(int x, int y, int z)
{
	setX(x);
	setY(y);
	setZ(z);
	setDistFrOrigin();
}


// Accessor
int Point3D::getZ()
{
	return z;
}


// Mutator
void Point3D::setZ(int z)
{
	if (z <= 999 && z >= -999)
		this->z = z;
}


// Operator overloading
bool Point3D::operator==(const Point3D& other) const
{
	return ( this->x == other.x && 
			 this->y == other.y && 
			 this->z == other.z );
}
				
bool Point3D::operator!=(const Point3D& other) const
{
	return !(*this == other);
}

bool Point3D::operator<(const Point3D& other) const
{
	return (this->distFrOrigin < other.distFrOrigin);
}


// Friend function overloading
ostream& operator<<(ostream& out, const Point3D& pt)
{
	// formatting 
	out << right << fixed << setprecision(3);
	
	// Coordinate values
	out << "[";
	out << setw(4) << pt.x << ", ";
	out << setw(4) << pt.y << ", ";
	out << setw(4) << pt.z;
	out << "]";
	
	/*
	// Distance values
	out << setw(3) << " ";
	out << pt.distFrOrigin << endl;
	*/
	
	return out;	
}


		
