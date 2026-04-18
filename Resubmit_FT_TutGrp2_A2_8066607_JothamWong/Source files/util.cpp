// Utility Implementation
//
// File Name: util.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include "util.h"
#include "ShapeTwoD.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Cross.h"

using namespace std;


/* Public Prototypes : Bring over to util.h & comment out later!*/
/* 
void readInput(ShapeTwoD** Shape2D, int& size);
void computeShapeAreas(ShapeTwoD** Shape2D, const int& size);
void displayShapesReport(ShapeTwoD** Shape2D, const int& size);
void sortShapesMenu(ShapeTwoD** Shape2D, const int& size);
void deallocateMemory(ShapeTwoD** Shape2D, int& size);
*/


/* Private Prototypes */
// Make shapes
static void makeCircle(const string& name, const bool& isWarpSpace, 
						ShapeTwoD** Shape2D, int& size);
static void makeRectangle(const string& name, const bool& isWarpSpace, 
							ShapeTwoD** Shape2D, int& size);
static void makeSquare(const string& name, const bool& isWarpSpace, 
						ShapeTwoD** Shape2D, int& size);
static void makeCross(const string& name, const bool& isWarpSpace, 
						ShapeTwoD** Shape2D, int& size);

// Decisions
static bool moreShapes(int choice);
static bool isWarpSpace();

// Sorting and Grouping
static void sortAsc(ShapeTwoD** Shape2D, const int& size, 
							const int startPos = 0, const int endPos = 0);
static void sortDesc(ShapeTwoD** Shape2D, const int& size, 
							const int startPos = 0, const int endPos = 0);

static int groupSpecialType(ShapeTwoD** Shape2D, const int& size);



// Function Implementation
/* Read Input Function */
void readInput(ShapeTwoD** Shape2D, int& size)
{
	string name;
	int choice;
	
	bool retry = false;
	
	cout << "[ Input sensor data ]" << endl;
	
	do {
		retry = false;
		cout << "Please enter name of shape : ";
		cin >> name;
		
		if ( name == "" || (name != "Circle" && name != "Rectangle" && 
							name != "Square" && name != "Cross") ) {
			retry = true;
			cout << "Invalid Shape! Press <enter> to try again";
			cin.ignore().get();
		} else {
		
			// Read in type
			bool warpSpace = isWarpSpace();
			cout << endl;
		
			// Choose, Create and Store shape
			if (name == "Circle") {
				makeCircle(name, warpSpace, Shape2D, size);
				
			} else if (name == "Rectangle") {
				makeRectangle(name, warpSpace, Shape2D, size);
				
			} else if (name == "Square") {
				makeSquare(name, warpSpace, Shape2D, size);
				
			} else if (name == "Cross") {
				makeCross(name, warpSpace, Shape2D, size);
				
			}
			
			cout << "Record stored successfully!" << endl;
			cout << endl;
			
			// Add more shapes?
			cout << "Add more shapes?" << endl;
			cout << "1) Yes" << endl;
			cout << "2) No" << endl; 
			cout << endl;
			cout << "Choice : ";
			cin >> choice;	
			cout << endl;
			retry = moreShapes(choice);
		}

	} while (retry);
	
	
}




/* Construct shape functions */
// Read in input for circle
static void makeCircle(const string& name, const bool& isWarpSpace, 
						ShapeTwoD** Shape2D, int& size)
{
	Point center;
	int radius;
		
	cout << "Please enter x-coordinate of center : ";
	cin >> center.x;
	cout << "Please enter y-coordinate of center : ";
	cin >> center.y;
	cout << "Please enter radius (units) : ";
	cin >> radius;
	cout << endl;
	
	// Construct Circle
	Shape2D[size++] = new Circle(name, isWarpSpace, center, radius);
}


// Read in input for rectangle
static void makeRectangle(const string& name, const bool& isWarpSpace, 
							ShapeTwoD** Shape2D, int& size)
{
	Point vertices[4];
	
	for (int i = 0; i < 4; ++i) {
		cout << "Please enter x-coordinate of pt." << i+1 << " : ";
		cin >> vertices[i].x;
		cout << "Please enter y-coordinate of pt." << i+1 << " : ";
		cin >> vertices[i].y;
		cout << endl;
	}
	
	// Construct Rectangle
	Shape2D[size++] = new Rectangle(name, isWarpSpace, vertices);
}


// Read in input for Square
static void makeSquare(const string& name, const bool& isWarpSpace, 
						ShapeTwoD** Shape2D, int& size)
{
	Point vertices[4];
	
	for (int i = 0; i < 4; ++i) {
		cout << "Please enter x-coordinate of pt." << i+1 << " : ";
		cin >> vertices[i].x;
		cout << "Please enter y-coordinate of pt." << i+1 << " : ";
		cin >> vertices[i].y;
		cout << endl;
	}
	
	// Construct Square
	Shape2D[size++] = new Square(name, isWarpSpace, vertices);
}


// Read in input for Cross
static void makeCross(const string& name, const bool& isWarpSpace, 
						ShapeTwoD** Shape2D, int& size)
{
	Point vertices[12];
	
	for (int i = 0; i < 12; ++i) {
		cout << "Please enter x-coordinate of pt." << i+1 << " : ";
		cin >> vertices[i].x;
		cout << "Please enter y-coordinate of pt." << i+1 << " : ";
		cin >> vertices[i].y;
		cout << endl;
	}
	
	// Construct Cross
	Shape2D[size++] = new Cross(name, isWarpSpace, vertices);
}




/* Decision functions */
static bool moreShapes(int choice)
{
	if (choice == 1) {
		return true;
	}
	
	cout << "Going back to main menu...\n" << endl;
	return false;
}


static bool isWarpSpace()
{
	string type;
	
	while (true) {
		cout << "Please enter special type : ";
		cin >> type;
		
		if (type == "WS") {
			return true;
			
		} else if (type == "NS") {
			return false;
		
		} else {
			cout << "\nTry again!\n" << endl;
		}
	} 
}




/* Compute all areas function */
void computeShapeAreas(ShapeTwoD** Shape2D, const int& size)
{
	for (int i = 0; i < size; ++i) {
		Shape2D[i]->setArea();
	}
	
	cout << "Computation completed! ( " << size << " records were updated )" << endl;
	cout << endl;
}




/* Display Shapes Report */
void displayShapesReport(ShapeTwoD** Shape2D, const int& size)
{
	cout << "Total no. of records available = " << size << endl;
	cout << endl;
	
	// show shapes
	for (int i = 0; i < size; ++i) {
		cout << "Shape[" << i << "]" << endl;
		cout << Shape2D[i]->toString() << endl;
		cout << endl;
	}
}




/* Sort Shapes Fucntions */
// Sort Shapes Menu
void sortShapesMenu(ShapeTwoD** Shape2D, const int& size)
{
	char choice;
	
	// formatting
	cout << left;
	
	do {	
		cout << "Sort your shape data" << endl;
		cout << "----------------------------------------" << endl;
		cout << "\t" << setw(9) << "a)" << "Sort by area (ascending)" << endl;
		cout << "\t" << setw(9) << "b)" << "Sort by area (descending)" << endl;
		cout << "\t" << setw(9) << "c)" << "Sort by special type and area" << endl;
		cout << endl;
		
		cout << "Please select sort option ('q' to go main menu) : ";
		cin >> choice;
		cout << endl;
		
		if (choice == 'a' || choice == 'b' || choice == 'c' || choice == 'q') {
			if (choice == 'a') {
				cout << "Sort by area (smallest to largest)..." << endl;
				cout << endl;
				
				// sort by ascending area
				sortAsc(Shape2D, size);
				displayShapesReport(Shape2D, size);
				
			} else if (choice == 'b') {
				cout << "Sort by area (largest to smallest)..." << endl;
				cout << endl;
				
				// sort by descending area
				sortDesc(Shape2D, size);
				displayShapesReport(Shape2D, size);
				
			} else if (choice == 'c') {
				cout << "Group by special type" << endl;
				cout << "Sort by area (largest to smallest)..." << endl;
				
				// sort by special type and area (WS first then NS, all descending)
				int lastWS = groupSpecialType(Shape2D, size);
				sortDesc(Shape2D, size, 0, lastWS);
				sortDesc(Shape2D, size, lastWS+1);
				displayShapesReport(Shape2D, size);
			}
			
		} else {
			cout << "Invalid option! Press <enter> to try again";
			cin.ignore().get();
			cout << endl;
		}
		
	} while (choice != 'q');
}


// Sort Ascending
static void sortAsc(ShapeTwoD** Shape2D, const int& size, 
							const int startPos, const int endPos)
{
	int last;
	
	if (endPos == 0)
		last = size - 1;
	else
		last = endPos;
	
	int n = last - startPos + 1;
	
	// loop over size of the array - 1 (first element no need swap)
	for (int i = 0; i < n - 1; ++i) {
		bool swapped = false;
		
		// loop over the position in the array (j is the current element)
		for (int j = startPos; j <= last - 1; ++j){
			int current = j;
			int next = j + 1;
			if (*Shape2D[current] > *Shape2D[next]) {
				ShapeTwoD* temp = Shape2D[next];
				Shape2D[next] = Shape2D[current];
				Shape2D[current] = temp;
				swapped = true;
			}
		}
		
		if (!swapped)
			break;
			
		// Last element sorted
		last--;
	}
}


// Sort Descending
static void sortDesc(ShapeTwoD** Shape2D, const int& size, 
							const int startPos, const int endPos)
{
	int last;
	
	if (endPos == 0)
		last = size - 1;
	else
		last = endPos;
	
	int n = last - startPos + 1;
	
	// loop over size of the array - 1 (first element no need swap
	for (int i = 0; i < n - 1; ++i) {
		bool swapped = false;
		
		// loop over the position in the array (j is the current element)
		for (int j = startPos; j <= last - 1 - i; ++j){
			int current = j;
			int next = j + 1;
			if (*Shape2D[current] < *Shape2D[next]) {
				ShapeTwoD* temp = Shape2D[next];
				Shape2D[next] = Shape2D[current];
				Shape2D[current] = temp;	
				swapped = true;
			}
		}
		
		if (!swapped)
			break;
	}
}


// Group by specialType (return end Position of list)
static int groupSpecialType(ShapeTwoD** Shape2D, const int& size)
{
	int lastWS = -1;
	
	for (int i = 0; i < size; ++i) {
		// Swap and increment
		if ( Shape2D[i]->getContainsWarpSpace() ) {
			ShapeTwoD* temp = Shape2D[i];
			Shape2D[i] = Shape2D[lastWS + 1];
			Shape2D[++lastWS] = temp;
		}
	}

	// Return position of Last WS
	return lastWS;
}




/* Quit functions */
// Deallocate Memory
void deallocateMemory(ShapeTwoD** Shape2D, int& size) 
{
	while (size > 0) {
		delete Shape2D[--size];
		Shape2D[size] = nullptr;
	}
}



