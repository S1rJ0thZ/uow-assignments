// Cross header file
//
// File name: Cross.h

#ifndef CROSS_H
#define CROSS_H

#include <string>
#include <vector>
#include "ShapeTwoD.h"
#include "util.h"

class Cross : public ShapeTwoD {
	private:
		Point vertices[12];
		int minX;
		int maxX;
		int minY;
		int maxY;
		
		// Squares X bounds
		int topLeftSqX;
		int topRightSqX;
		int bottomLeftSqX;
		int bottomRightSqX;
		
		// Squares Y bounds
		int topLeftSqY;
		int bottomLeftSqY;
		int topRightSqY;
		int bottomRightSqY;
		
		// include area ?
		
		// Vectors
		std::vector<Point> pointsOnPerimeter;
		std::vector<Point> pointsInShape;
		
		// Find and load points
		void loadMaxMin();
		void loadBounds();
		void loadPointsOnPerimeter();
		void loadPointsInShape();
	
	public:
		// Constructor 
		Cross(std::string name, bool containsWarpSpace, Point* vertices);	
		
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

