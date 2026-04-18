// Rectangle header file
//
// File name: Rectangle.h

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <vector>
#include "ShapeTwoD.h"
#include "util.h"

class Rectangle : public ShapeTwoD {
	private:
		Point vertices[4];
		int minX;
		int maxX;
		int minY;
		int maxY;
		// include area
		std::vector<Point> pointsOnPerimeter;
		std::vector<Point> pointsInShape;
		
		// Find and load points
		void loadMaxMin();
		void loadPointsOnPerimeter();
		void loadPointsInShape();
		
	public:
		// Constructor 
		Rectangle(std::string name, bool containsWarpSpace, Point* vertices);	
		
		// Accessor
		virtual std::string toString() override;
		
		// Mutator
		virtual void setArea() override;
		
		// Calculation methods
		virtual double computeArea() override;
		virtual bool isPointInShape(const Point& vertex) override;
		virtual bool isPointOnShape(const Point& vertex) override;
		
};

#endif
