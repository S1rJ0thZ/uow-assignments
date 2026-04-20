// Assignment 1 wips header file
//
// To include in all assignment files
//
// File name: wips.h

#pragma once
#include <string>
#include <map>
#include <functional>



/* Data structures */
// Grid
struct GridCell {
	int x, y;	// Coordinates
	int cityID;	// 0 if no city
	std::string cityName; 
	int cloudCover;
	int pressure;
};



/* Variables */
// Map variables (2D array dynamic array)
extern GridCell** weatherMap;	// declaration, no memory allocated
extern int gridXMin, gridXMax, gridYMin, gridYMax;

// City variables (map)
extern std::map<int, std::string, std::greater<int>> cities;	



/* User Callable Functions */
// load files and data
void loadFile(int& gridXMin, int& gridXMax, int& gridYMin, int& gridYMax, 
				std::map<int, std::string, std::greater<int>>& cities);

// Display functions
void displayMap(GridCell** weatherMap, int& minX, int& maxX, int& minY, int& maxY, 
					void (*mapType)(GridCell**, int&, int&, int&));

void city(GridCell** weatherMap, int& x_length, int& y_length, int& maxY);

void cloudIndex(GridCell** weatherMap, int& x_length, int& y_length, int& maxY);

void cloudLMH(GridCell** weatherMap, int& x_length, int& y_length, int& maxY);

void pressureIndex(GridCell** weatherMap, int& x_length, int& y_length, int& maxY);

void pressureLMH(GridCell** weatherMap, int& x_length, int& y_length, int& maxY);

void displayWeatherSummary(std::map<int, std::string, std::greater<int>>& cities, GridCell** weatherMap,  
							int minX, int maxX, int minY, int maxY);

// Clear memory
void deleteMap(GridCell**& map2D, int yMin, int yMax);





/* Old Cities method */
// CityInfo
/* 
struct CityInfo {
	std::string cityName;
	int cityID;
	float avgCloudCover;
	float avgPressure;
	float rainProb;
};

// Variables
extern CityInfo* arrayCities;	
extern int numOfCities;
*/







