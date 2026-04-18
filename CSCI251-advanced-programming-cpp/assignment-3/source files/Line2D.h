// Line2D class declaration
//
// File name: Line2D.h

#ifndef LINE2D_H
#define LINE2D_H

#include <iostream>
#include "Point2D.h"


class Line2D {
	private:
		Point2D pt1;
		Point2D pt2;
	
	protected:
		double length;
		
		// protected functions
		virtual void setLength();
	
	public:
		// Constructor
		Line2D(Point2D pt1, Point2D pt2);
		
		// Accessor
		Point2D getPt1();
		Point2D getPt2();
		double getScalarValue();
		
		// Mutator
		void setPt1(Point2D pt1);
		void setPt2(Point2D pt2);
		
		// Operator overloading
		bool operator==(const Line2D& other) const;
		bool operator!=(const Line2D& other) const;
		bool operator<(const Line2D& other) const;
		
		// Friend function overloading
		friend std::ostream& operator<<(std::ostream& out, const Line2D& line);
		
		/* Template version
		template <typename Line>
		friend std::ostream& operator<<(std::ostream& out, const Line& line);
		*/
};



#endif


