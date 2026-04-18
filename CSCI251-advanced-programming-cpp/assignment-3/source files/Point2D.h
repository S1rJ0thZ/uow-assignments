// Point2D class declaration
//
// File name: Point2D.h

#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>


class Point2D {
	protected:
		int x;
		int y;
		double distFrOrigin;
		
		// protected functions
		virtual void setDistFrOrigin();
		
	public:
		// Constructor
		Point2D(int x = 0, int y = 0);
		
		// Accessors
		int getX();
		int getY();
		double getScalarValue();
		
		// Mutators
		void setX(int x);
		void setY(int y);
		
		// Operator overloading
		bool operator==(const Point2D& other) const;
		bool operator!=(const Point2D& other) const;
		bool operator<(const Point2D& other) const;
		
		// Overloaded friend functions
		friend std::ostream& operator<<(std::ostream& out, const Point2D& pt);
};




#endif
