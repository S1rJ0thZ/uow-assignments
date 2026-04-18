// Line2D class declaration
//
// File name: Line2D.h

#ifndef LINE3D_H
#define LINE3D_H

#include <iostream>
#include "Point3D.h"

class Line3D { 
	private:
		Point3D pt1;
		Point3D pt2;
	
	protected:		
		double length;
		
		// protected functions
		void setLength();
	
	public:
		// Constructor
		Line3D(Point3D pt1, Point3D pt2);
		
		// Accessor
		Point3D getPt1();
		Point3D getPt2();
		double getScalarValue();
		
		// Mutator
		void setPt1(Point3D pt1);
		void setPt2(Point3D pt2);
		
		// Operator overloading
		bool operator==(const Line3D& other) const;
		bool operator!=(const Line3D& other) const;
		bool operator<(const Line3D& other) const;
		
		// Friend function overloading
		friend std::ostream& operator<<(std::ostream& out, const Line3D& line);
};


#endif
