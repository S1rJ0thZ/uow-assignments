// ShapeTwoD Header file
//
// Inclusion: #include "ShapeTwoD.h"
//
// File name: ShapeTwoD.h

#ifndef SHAPETWOD_H
#define SHAPETWOD_H

#include <iostream>
#include <string>
#include "util.h"


// Declare ShapetwoD class
class ShapeTwoD {
	protected:
		std::string name;
		bool containsWarpSpace;
		double area;
		bool areaComputed;
		
	public:
		// Constructor
		ShapeTwoD(std::string name = "",bool containsWarpSpace = false);
		
		// Operator overloads
		bool operator>(const ShapeTwoD& other) const
		{
			return this->area > other.area;
		}
		
		bool operator<(const ShapeTwoD& other) const
		{
			return this->area < other.area;
		}
		
		bool operator==(const ShapeTwoD& other) const
		{
			return this->area == other.area;
		}
		
		bool operator!=(const ShapeTwoD& other) const
		{
			return !(*this == other);
		}
		
		
		// Accessor methods
		std::string getName();
		bool getContainsWarpSpace();
		std::string specialType();
		double getArea() const;
		virtual std::string toString() = 0;
		
		// Mutator methods
		void setName(std::string name);
		void setContainsWarpSpace(bool containsWarpSpace);
		virtual void setArea() = 0;
		
		// Calculation methods
		virtual double computeArea() = 0;
		virtual bool isPointInShape(const Point& vertex) = 0;
		virtual bool isPointOnShape(const Point& vertex) = 0;
		
		// Destructor (May not require)
		/* virtual ~ShapeTwoD() = 0; */ 
};


#endif




