// A2 Main driver file
//
// Test Compile: g++ -std=c++11 Assn2.cpp -o Assn2.app
//
// File name: Assn2.cpp

#include <iostream>
#include <iomanip>
#include <string>
#include "ShapeTwoD.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Cross.h"
#include "util.h"

// include header file

using namespace std;

// Prototypes
int displayMenu();
void userSelect(const int& input, ShapeTwoD** Shape2D, int& size);


// Main
int main()
{
	// Declare array
	ShapeTwoD* Shape2D[100];
	int size = 0;
	
	// Init pointers to nullptr?
	
	int choice;
	do {
		choice = displayMenu();
		userSelect(choice, Shape2D, size);
		
	} while (choice != 5);
	
	return 0;	
}



// Display menu
int displayMenu()
{
	int userInput;
	
	// left align
	cout << left;
	
	// Display header
	cout << setw(13) << "Student ID" << ": 8066607" << endl;
	cout << setw(13) << "Student Name" << ": Jotham Wong Hsien Ee" << endl;
	for (int i = 0; i < 34; ++i) {
		cout << '-';
	}
	cout << endl;
	cout << "Welcome to Assn2 program!\n" << endl;
	
	// Show options
	cout << setw(6) << "1)" << "Input sensor data" << endl;
	cout << setw(6) << "2)" << "Compute area (for all records)" << endl;
	cout << setw(6) << "3)" << "Print shapes report" << endl;
	cout << setw(6) << "4)" << "Sort shape data" << endl;
	cout << setw(6) << "5)" << "Quit" << endl;
	cout << endl;
	
	cout << "Please enter your choice : ";
	cin >> userInput;
	cout << endl;
	
	return userInput;
}



void userSelect(const int& input, ShapeTwoD** Shape2D, int& size)
{
	if (input < 1 || input > 5) {
		cout << "\n\nInvalid choice! Press <Enter> to return" << endl;
		cin.ignore().get();
		return;
		
	} else {
		switch (input) {
			case 1:
				// input data function (util file)
				readInput(Shape2D, size);
				return;
			
			case 2:
				// Compute area function (object implementation)
				computeShapeAreas(Shape2D, size);
				return;
		
			case 3:
				// display shapes report function (Object implementation)
				displayShapesReport(Shape2D, size);
				return;
				
			case 4:
				// Sort shapes function (util and object implementation , operator overloading?)
				sortShapesMenu(Shape2D, size);
				return;
				
			case 5:
				// Delete memory function (util function)
				deallocateMemory(Shape2D, size);
				return;
		}
	}
}



