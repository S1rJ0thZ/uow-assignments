// ShapeTwoD Implementation
//
// To Test Compile: g++ -std=c++11 ShapeTwoD.cpp -oShapeTwoD.app
// To compile object: g++ -std=c++11 -c ShapeTwoD.cpp -o ShapeTwoD.o
//
// File name: ShapeTwoD.cpp

#include <iostream>
#include <string>
#include <sstream>
#include "ShapeTwoD.h"

using namespace std;




// Constructor 
ShapeTwoD::ShapeTwoD(string name, bool containsWarpSpace) 
{
	this->name = name;
	this->containsWarpSpace = containsWarpSpace;
	this->area = 0;
	this->areaComputed = false;
}




// Accesor methods
string ShapeTwoD::getName()
{
	return name;
}


bool ShapeTwoD::getContainsWarpSpace()
{
	return containsWarpSpace;
}


string ShapeTwoD::specialType()
{
	return (containsWarpSpace ? "WS" : "NS");
}


double ShapeTwoD::getArea() const
{
	if (areaComputed)
		return area;
	return 0;
}


string ShapeTwoD::toString()	// Replace for circle + other subclasses also
{
	ostringstream oss;
	oss << "Name : " << name << endl;
	oss << "Special Type : " << specialType() << endl;
	return oss.str();
}




// Mutator
void ShapeTwoD::setName(string name)
{
	if (name != "Circle" || name != "Sqaure" || name != "Rectangle" || name != "Cross") {
		
	} else {
		// May need to implement copy to another subclass
		this->name = name;
	}
}


void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace)
{
	this->containsWarpSpace = containsWarpSpace;
}








