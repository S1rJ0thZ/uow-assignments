// Circle header file
//
// File name: Circle.h

#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>
#include <vector>
#include "ShapeTwoD.h"
#include "util.h"

class Circle : public ShapeTwoD {
	private:
		Point center;
		int radius;
		// include area also
		std::vector<Point> pointsOnPerimeter;
		std::vector<Point> pointsInShape;
		
		// Find points and load
		void loadPointsOnPerimeter();
		void loadPointsInShape();
		
	public:
		// Constructor 
		Circle(std::string name, bool containsWarpSpace, Point center, int radius);
		
		// Accessor
		virtual std::string toString() override;
		
		// Mutator
		virtual void setArea() override;
		
		// Calculation methods
		virtual double computeArea() override;
		virtual bool isPointInShape(const Point& vertex) override;
		virtual bool isPointOnShape(const Point& vertex) override;
		
		// Destructor (may not require)
		/* virtual ~Circle() override; */ 
};

#endif
