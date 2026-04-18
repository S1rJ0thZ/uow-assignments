// Point3D class declaration
//
// File name: Point3D.h

#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
#include "Point2D.h"


class Point3D : public Point2D {
	protected:
		int z;
		
		// protected functions
		virtual void setDistFrOrigin() override;
		
	public:
		// Constructor
		Point3D(int x = 0, int y = 0, int z = 0);
		
		// Accessor
		int getZ();
		
		// Mutator
		void setZ(int z);
		
		// Operator overloading		(Find out how to call the base class overloaded operator)
		bool operator==(const Point3D& other) const;
		bool operator!=(const Point3D& other) const;
		bool operator<(const Point3D& other) const;
		
		// Overloaded friend functions
		friend std::ostream& operator<<(std::ostream& out, const Point3D& pt);
};


#endif
