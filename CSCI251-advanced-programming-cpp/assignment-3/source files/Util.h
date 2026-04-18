// Util header file
//
// File name: Util.h


#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include "Point2D.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"

// Data structures


// Public functions
void readFile(std::vector<Point2D>& pt2DVctr, std::vector<Point3D>& pt3DVctr, 
				std::vector<Line2D>& ln2DVctr, std::vector<Line3D>& ln3DVctr, int& noOfRec);

// display Functions				
std::string displayPoint2D(std::vector<Point2D> pt2DVctr);
std::string displayPoint3D(std::vector<Point3D> pt3DVctr);
std::string displayLine2D(std::vector<Line2D> ln2DVctr);
std::string displayLine3D(std::vector<Line3D> ln3DVctr);

// Sorting and View function
void sortAndViewData(std::string& filter, std::string& attribute, std::string& order, 
					std::vector<Point2D>& pt2DVctr, std::vector<Point3D>& pt3DVctr, 
						std::vector<Line2D>& ln2DVctr, std::vector<Line3D>& ln3DVctr);

// File writing function
void writeFile(std::string& filter, std::vector<Point2D>& pt2DVctr, std::vector<Point3D>& pt3DVctr, 
				std::vector<Line2D>& ln2DVctr, std::vector<Line3D>& ln3DVctr, int& noOfRec);




#endif
