// Assignment 1 wips file reading
//
// Compile Testing : g++ -std=c++11 wips.cpp -o wips.app
// Compile full integration : g++ 
//
// File name: wips.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <functional>
#include <utility>
#include "wips.h"

using namespace std;



/* Prototypes */
// File reading functions
static void readConfigFile(const string& fileName, int& gridXMin, int& gridXMax, int& gridYMin, 
							int& gridYMax, string& cityFile, string& cloudFile, string& pressureFile);			
static void readCityFile(const string& fileName, GridCell** weatherMap, int minX, int maxX, 
							int minY, int maxY, map<int, string, greater<int>>& cities);
static void readCloudFile(const string& fileName, GridCell** weatherMap, int minX, int maxX, 
							int minY, int maxY);
static void readPressureFile(const string& fileName, GridCell** weatherMap, int minX, int maxX, 
								int minY, int maxY);

// Map functions
static void initMap(GridCell**&, int, int, int, int);
static GridCell* getMapCell(GridCell** weatherMap, int x, int y, int maxY);

// City summary functions
static float getRainProb(char accLMH , char apLMH);
static void drawWeatherGraphic(float rainProb);

// Calculation functions
static int convertIndex(int value);
static char convertLMH(int value);
static float getCityAvg(GridCell** weatherMap, int minX, int maxX, int minY, int maxY, 
						int cityID, int GridCell::* memberPtr);



// Global variables
GridCell** weatherMap = nullptr;
int gridXMin, gridXMax, gridYMin, gridYMax;
map<int, string, greater<int>> cities;



/*
// For testing - Implementation must comment out!!!
int main() 
{
	int xMin, xMax, yMin, yMax;
	
	// Test load function + Allocate Memory
	loadFile(xMin, xMax, yMin, yMax, cities);
	cout << "Read file success!" << endl;

	// Test display city
	displayMap(weatherMap, xMin, xMax, yMin, yMax, city);
	cout << "display city map success!" << endl;

	// Test display cloudIndex
	displayMap(weatherMap, xMin, xMax, yMin, yMax, cloudIndex);
	cout << "display cloud cover map success!" << endl;
	
	// Test display cloud LMH map
	displayMap(weatherMap, xMin, xMax, yMin, yMax, cloudLMH);
	cout << "display cloudLMH map success!" << endl;
	
	// Test display pressureIndex
	displayMap(weatherMap, xMin, xMax, yMin, yMax, pressureIndex);
	cout << "display pressure index map success!" << endl;
	
	// Test display pressureLMH
	displayMap(weatherMap, xMin, xMax, yMin, yMax, pressureLMH);
	cout << "display pressure LMH map success!" << endl;
	cout << endl;
	
	// Test display weather summary
	displayWeatherSummary(cities, weatherMap, xMin, xMax, yMin, yMax);
	cout << endl;

	// Delete memory
	// clearMemory(weatherMap, yMin, yMax, arrayCities);
	deleteMap(weatherMap, yMin, yMax);
	
	return 0;
}
*/



/* PUBLIC FUNCTIONS */

// Load function
void loadFile(int& gridXMin, int& gridXMax, int& gridYMin, int& gridYMax, 
				map<int, string, greater<int>>& cities)
{
	string configFile, cityFile, cloudFile, pressureFile;
	
	cout << "[Read in and process a configuration file]" << endl;
	cout << "Please enter config filename : ";
	cin >> configFile; 
	cout << endl;
	
	// Read config file
	readConfigFile(configFile, gridXMin, gridXMax, gridYMin, gridYMax,
					cityFile, cloudFile, pressureFile);


	// Initialize Weather Map with respective coordinates
	initMap(weatherMap, gridXMin, gridXMax, gridYMin, gridYMax);
	
	
	cout << "Storing data from input file : " << endl;
	// Read city file
	readCityFile(cityFile, weatherMap, gridXMin, gridXMax, gridYMin, gridYMax, cities);
	
	// Read cloud cover file
	readCloudFile(cloudFile, weatherMap, gridXMin, gridXMax, gridYMin, gridYMax);
	
	// Read pressure file
	readPressureFile(pressureFile, weatherMap, gridXMin, gridXMax, gridYMin, gridYMax);
	
	// End message
	cout << "\nAll records successfully stored. Going back to main menu..." << endl;
}





/* Display Functions + Implementations */
// Display map
void displayMap(GridCell** weatherMap, int& minX, int& maxX, int& minY, int& maxY, 
					void (*mapType)(GridCell**, int&, int&, int&))
{	
	int x_length = maxX - minY + 1;
	int y_length = maxY - minY + 1;
	
	// right align 
	cout << right;
	
	// Display top border
	cout << setw(3) << " ";
	for (int i = 0; i < (x_length+2); i++) {
		cout << "# ";
	}
	cout << endl;
	
	// Display map
	mapType(weatherMap, x_length, y_length, maxY);
	
	// Display bottom border
	cout << setw(3) << " ";
	for (int i = 0; i < (x_length+2); i++) {
		cout << "# ";
	}
	cout << endl;
	
	// Display scale
	cout << setw(4) << " ";
	for (int i = minX; i < x_length; i++) {
		cout << setw(2) << i;
	}
	cout << endl;
}



// display city
void city(GridCell** weatherMap, int& x_length, int& y_length, int& maxY)
{
	for (int i = 0; i < y_length ; i++) {
		cout << setw(2) << maxY-i;
		cout << setw(2) << '#';
		for (int j = 0; j < x_length; j++) {
			if (weatherMap[i][j].cityID) {
				cout << setw(2) << weatherMap[i][j].cityID;
			} else {
				cout << setw(2) << " ";
			}
		}
		cout << setw(2) << "#" << endl;
	}
}


// display cloud index
void cloudIndex(GridCell** weatherMap, int& x_length, int& y_length, int& maxY)
{
	for (int i = 0; i < y_length ; i++) {
		cout << setw(2) << maxY-i;
		cout << setw(2) << '#';
		for (int j = 0; j < x_length; j++) {
			if (weatherMap[i][j].cloudCover) {
				cout << setw(2) << convertIndex(weatherMap[i][j].cloudCover);
			} else {
				cout << setw(2) << " ";
			}
		}
		cout << setw(2) << "#" << endl;
	}
}


// display cloud LMH
void cloudLMH(GridCell** weatherMap, int& x_length, int& y_length, int& maxY)
{
	for (int i = 0; i < y_length ; i++) {
		cout << setw(2) << maxY-i;
		cout << setw(2) << '#';
		for (int j = 0; j < x_length; j++) {
			if (weatherMap[i][j].cloudCover) {
				cout << setw(2) << convertLMH(weatherMap[i][j].cloudCover);
			} else {
				cout << setw(2) << " ";
			}
		}
		cout << setw(2) << "#" << endl;
	}
}


// display pressure index
void pressureIndex(GridCell** weatherMap, int& x_length, int& y_length, int& maxY)
{
	for (int i = 0; i < y_length ; i++) {
		cout << setw(2) << maxY-i;
		cout << setw(2) << '#';
		for (int j = 0; j < x_length; j++) {
			if (weatherMap[i][j].pressure) {
				cout << setw(2) << convertIndex(weatherMap[i][j].pressure);
			} else {
				cout << setw(2) << " ";
			}
		}
		cout << setw(2) << "#" << endl;
	}
}


// display pressure LMH
void pressureLMH(GridCell** weatherMap, int& x_length, int& y_length, int& maxY)
{
	for (int i = 0; i < y_length ; i++) {
		cout << setw(2) << maxY-i;
		cout << setw(2) << '#';
		for (int j = 0; j < x_length; j++) {
			if (weatherMap[i][j].pressure) {
				cout << setw(2) << convertLMH(weatherMap[i][j].pressure);
			} else {
				cout << setw(2) << " ";
			}
		}
		cout << setw(2) << "#" << endl;
	}
}



// Display Weather summary report
void displayWeatherSummary(map<int, string, greater<int>>& cities, GridCell** weatherMap,  
							int minX, int maxX, int minY, int maxY) 
{
	cout << "Weather Forecast Summary Report" << endl;
	cout << setfill('-') << setw(31) << '-' << endl;
	cout << setfill(' ');
	
	// Loop through arrayCities and display each city
	for (const auto& pair : cities) {	
		// Set left + 2 decimal place
		cout << left << fixed << setprecision(2);
		
		// initialize key and value
		int cityID = pair.first;
		string cityName = pair.second;
		
		// City name
		cout << setw(10) << "City Name" << ": " << cityName << endl;
		
		// City ID
		cout << setw(10) << "City ID" << ": " << cityID << endl;
		
		// average cloud cover
		float acc = getCityAvg(weatherMap, minX, maxX, minY, maxY, 
						cityID, &GridCell::cloudCover);
		cout << setw(17) << "Ave. Cloud Cover" << setw(8) << "(ACC)" << ": ";
		cout << acc << " (" << convertLMH(acc) << ")" << endl;
		
		// average pressure
		float ap = getCityAvg(weatherMap, minX, maxX, minY, maxY, 
						cityID, &GridCell::pressure);
		cout << setw(17) << "Ave. Pressure" << setw(8) << "(AP)" << ": ";
		cout << ap << " (" << convertLMH(ap) << ")" << endl;
		
		// Rain probability
		float rainProb = getRainProb(convertLMH(acc) , convertLMH(ap));
		cout << setw(25) << "Probability of Rain (%)" << ": " << rainProb << endl;
		
		// weather graphic
		drawWeatherGraphic(rainProb);
		cout << endl;
	}
}





/* Clear memory */

// Delete map memory (Public: to be called upon 'quit')
void deleteMap(GridCell**& map2D, int yMin, int yMax)
{
	int y_length = yMax - yMin + 1;
	for (int i = 0; i < y_length; i++) {
		delete [] map2D[i];
	}
	
	delete [] map2D;
	map2D = nullptr;
}





/* 
Consider for display summary the below solutions...
	* Use an ordered set to record the unique cities in a sorted order
	* Create an array of structs for each city and record down the timing 
	* 
*/



/* PRIVATE FUNCTIONS */

/* File Read Functions */
// Read config file
static void readConfigFile(const string& fileName, int& gridXMin, int& gridXMax, 
						int& gridYMin, int& gridYMax, string& cityFile, 
						string& cloudFile, string& pressureFile)
{		
	ifstream configFile;	
	string line;
	
	// Open file
	configFile.open(fileName);
	
	if (!configFile.is_open()) {
		cerr << "Error opening config file: " << fileName << endl;
		return;
	}
	
	// Retrieve x-range and y-range from file
	while (getline(configFile, line)) {
	// cout << "Inside config file while loop" << endl;		// debug confirm
		if (line.find("GridX_IdxRange=") != string::npos) {
			int eqPos = line.find('=');
			string range = line.substr(eqPos+1);
			int dashPos = range.find('-');		
			gridXMin = stoi(range.substr(0, dashPos));
			gridXMax = stoi(range.substr(dashPos+1));
			
		} else if (line.find("GridY_IdxRange=") != string::npos) {
			int eqPos = line.find('=');
			string range = line.substr(eqPos+1);
			int dashPos = range.find('-');
			gridYMin = stoi(range.substr(0, dashPos));
			gridYMax = stoi(range.substr(dashPos+1));
		
		} else if ((line.find("citylocation.txt")) != string::npos) {
			cityFile = "citylocation.txt";
		
		} else if ((line.find("cloudcover.txt")) != string::npos) {
			cloudFile = "cloudcover.txt";
			
		} else if ((line.find("pressure.txt")) != string::npos) {
			pressureFile = "pressure.txt";
			
		} 
	} 
	
	// Close file
	configFile.close();
	
	// Confirmation message
	cout << "Reading in GridX_IdxRange : " << gridXMin << "-" << gridXMax << "...done!" << endl;
	cout << "Reading in GridY_IdxRange : " << gridYMin << "-" << gridYMax << "...done!" << endl;
	cout << endl;
	
}



// Read city file
static void readCityFile(const string& fileName, GridCell** weatherMap, int minX, int maxX, 
							int minY, int maxY, map<int, string, greater<int>>& cities)
{
	int x, y, cityID;
	string cityName;
	
	// Open file
	ifstream cityFile(fileName);
	if (!cityFile.is_open()) {
		cerr << "Error opening city file: " << fileName << endl;
		return;
	}
	
	string line;
	
	while (getline(cityFile, line)) {
		// cout << "inside readcityfile() while loop" << endl;		// debug confirm
		if (line.empty()) {
			break;
		} else {
			// Find first range for x value
			int commaPos = line.find(',');
			x = stoi(line.substr(1, commaPos-1));
			
			// find second range for y value
			int lastbracket = line.find(']');
			y = stoi(line.substr(commaPos+2 , lastbracket-commaPos-2));
			
			// find the cityID and Name
			int dash1Pos = line.find('-', lastbracket);
			int dash2Pos = line.find('-', dash1Pos+1);
			cityID = stoi(line.substr(dash1Pos+1, dash2Pos-dash1Pos-1));
			cityName = line.substr(dash2Pos+1);
			
			// cout << "error below here" << endl;		--> Previous error stoi()
			
			// insert values
			if (x >= minX && x <= maxX && y >= minY && y <= maxY) {
				GridCell* cell = getMapCell(weatherMap, x, y, maxY);	// Problem with reference
				cell->cityID = cityID;
				cell->cityName = cityName;
				// If cityId does not exit in cities keys
				if (cities.count(cityID) == 0)
					cities[cityID] = cityName;
			}
		}
	}
	
	// close file
	cityFile.close();
	
	cout << "After reading in city file" << endl;
	// confirmation message
	cout << fileName << "...done!" << endl;
}



// Read cloud file
static void readCloudFile(const string& fileName, GridCell** weatherMap, int minX, int maxX, 
							int minY, int maxY)
{
	int x, y, cloudyValue;
	
	ifstream cloudFile(fileName);
	if (!cloudFile.is_open()) {
		cerr << "Error opening cloud file: " << fileName << endl;
		return;
	}
	
	string line;
	
	while (getline(cloudFile, line)) {
		if (line.empty()) {
			break;
		} else {
			// Find x value
			int commaPos = line.find(',');
			x = stoi(line.substr(1, commaPos-1));
			
			// Find y value
			int lastbracket = line.find(']');
			y = stoi(line.substr(commaPos+2, lastbracket-commaPos-2));
			
			// Find pressure value
			int dashPos = line.find('-');
			cloudyValue = stoi(line.substr(dashPos+1));
			
			// Insert values
			if (x >= minX && x <= maxX && y >= minY && y <=maxY) {
				GridCell* cell = getMapCell(weatherMap, x, y, maxY);
				cell->cloudCover = cloudyValue;
			}
		}
	}
	
	// close file
	cloudFile.close();
	
	// confirmation message
	cout << fileName << "...done!" << endl;
}



// Read pressure file
static void readPressureFile(const string& fileName, GridCell** weatherMap, int minX, int maxX, 
								int minY, int maxY)
{
	int x, y, pressureValue;
	
	ifstream pressureFile(fileName);
	if (!pressureFile.is_open()) {
		cerr << "Error opening pressure file: " << fileName << endl;
		return;
	}
	
	string line;
	
	while (getline(pressureFile, line)) {
		if (line.empty()) {
			break;
		} else {
			// Find x value
			int commaPos = line.find(',');
			x = stoi(line.substr(1, commaPos-1));
			
			// Find y value
			int lastbracket = line.find(']');
			y = stoi(line.substr(commaPos+2, lastbracket-commaPos-2));
			
			// Find pressure value
			int dashPos = line.find('-');
			pressureValue = stoi(line.substr(dashPos+1));
			
			// Insert values
			if (x >= minX && x <= maxX && y >= minY && y <=maxY) {
				GridCell* cell = getMapCell(weatherMap, x, y, maxY);
				cell->pressure = pressureValue;
			}
		}
	}
	
	// close file
	pressureFile.close();
	
	// confirmation message
	cout << fileName << "...done!" << endl;
}





/* Map Functions*/
// Allocate map memory
static void initMap(GridCell**& map2D, int minX, int maxX, int minY, int maxY)
{
	int row = maxY - minY + 1;
	int col = maxX - minX + 1;
	
	// Create first dimension array
	map2D = new GridCell*[row];
	
	// create 2nd dimension
	for (int i = 0; i < row; i++) {
		map2D[i] = new GridCell[col];
	}
	
	// Initialize Grid cell values
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			map2D[i][j].x = j;
			map2D[i][j].y = maxY - i;
			map2D[i][j].cityID = 0;
			map2D[i][j].cityName = "";
		}
	}
}



// Fix the return value to return a reference of the struct
// Retreive a cell to modify
static GridCell* getMapCell(GridCell** weatherMap, int x, int y, int maxY)
{
	// check if index is more than 0
	if ((maxY-y) < 0 || x < 0) {
		return nullptr;
	} else {
		return &weatherMap[maxY - y][x];
	}
}





/* City Summary Functions */

// Get Rain Probability
static float getRainProb(char accLMH , char apLMH)
{
	if (apLMH == 'L') {
		if (accLMH == 'H') {
			return 90;
			
		}else if (accLMH == 'M') {
			return 80;
			
		}else {
			return 70;
		}
	}else if (apLMH == 'M') {
		if (accLMH == 'H') {
			return 60;
			
		}else if (accLMH == 'M') {
			return 50;
			
		}else {
			return 40;
		}
	}else {
		if (accLMH == 'H') {
			return 30;
		
		}else if (accLMH == 'M') {
			return 20;
		
		}else {
			return 10;
		}
	}
}



// Draw weather graphic function
static void drawWeatherGraphic(float rainProb)
{
	int cloudCols = 4;
	int rainNo = 0;
	
	// Check cases
	if (rainProb >= 50 && rainProb <=90)
		rainNo = (rainProb / 10) - 4;
	
	if (rainProb >= 10 && rainProb < 40)
		cloudCols = rainProb / 10;
	
	// set right align
	cout << right;
	
	// Draw cloud
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < cloudCols; j++) {
			cout << '~';
		}
		cloudCols++;
		cout << endl;
	}
	
	// Draw rain
	stringstream rain;
	for (int i = 0; i < rainNo; i++) {
		rain << '\\';
	}
	
	cout << setw(5) << rain.str() << endl;
}





/* Calculation Functions */
// Index 
static int convertIndex(int value)
{
	return (value / 10);
}


// LMH
static char convertLMH(int value)
{
	if (value < 100 && value >= 0) {
		if (value < 35) {
			return 'L';
		} else if (value < 65) {
			return 'M';
		} else {
			return 'H';
		}
	} else {
		return ' ';
	}
}


// Calculate City Average (Cloud Cover, Pressure)
static float getCityAvg(GridCell** weatherMap, int minX, int maxX, int minY, int maxY, 
						int cityID, int GridCell::* memberPtr)
{
	int x_length = maxX - minX + 1;
	int y_length = maxY - minY + 1;

	int rightBound = 0;	// highestX
	int topBound = 0;	// highestY
	int leftBound = maxX;	// lowestX
	int bottomBound = maxY;	// lowestY
	
	// Loop through the map and find the bounds
	for (int i = 0; i < y_length; i++) {
		for (int j = 0; j < x_length; j++) {
			GridCell* cell = &weatherMap[i][j];
			
			// Check if  city ID matches
			if (cell->cityID == cityID) {
				// Find the bounds of the city
				if (cell->x < leftBound) 
					leftBound = cell->x;
					
				if (cell->y < bottomBound)
					bottomBound = cell->y;
					
				if (cell->x > rightBound)
					rightBound = cell->x;
					
				if (cell->y > topBound) 
					topBound = cell->y;
			}
		}
	}
	
	// Check if bound + 1 is within the map
	if (leftBound > minX) 
		leftBound--;
	
	if (bottomBound > minY) 
		bottomBound--;
	
	if (rightBound < maxX) 
		rightBound++;
		
	if (topBound < maxY)
		topBound++;
		
	// Loop through and sum of numbers
	int numOfCells = 0;
	float sum = 0.0;
	
	for (int y = bottomBound; y <= topBound; y++) {
		for (int x = leftBound; x <= rightBound; x++) {
			GridCell* cell = getMapCell(weatherMap, x, y, maxY);
			sum += cell->*memberPtr;
			numOfCells++;
		}
	}
	
	// if no zero division error, return Average 
	return (numOfCells == 0) ? 0.00 : (sum / numOfCells);
}





/* 
If not using array of cities, remove from...

read city File 

initCityArray()

global variables

wips.h file


*/











