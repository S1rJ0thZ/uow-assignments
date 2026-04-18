// Square header file
//
// File name: Square.h

#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <vector>
#include "ShapeTwoD.h"
#include "util.h"

class Square : public ShapeTwoD {
	private:
		Point vertices[4];
		int minX;
		int maxX;
		int minY;
		int maxY;
		// include area?
		std::vector<Point> pointsOnPerimeter;
		std::vector<Point> pointsInShape;
		
		// Find and load points
		void loadMaxMin();
		void loadPointsOnPerimeter();
		void loadPointsInShape();
	
	public:
		// Constructor 
		Square(std::string name, bool containsWarpSpace, Point* vertices);	
		
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
