// Assignment 3 main
//
// Test compile: g++ -std=c++11 Assn3.cpp -o Assn3.run
// Full compile: g++ -std=c++11 Point2D.o Point3D.o Line2D.o Line3D.o Util.o Assn3.cpp -o csci251_3.app
// 
// File name: Assn3.cpp


#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"
#include "Util.h"

using namespace std;


// prototypes
int displayMenu(const string& filter, const string& attribute, const string& order);
void userSelection(int choice, string& filter, string& attribute, string& order, 
					vector<Point2D>& pt2DVctr, vector<Point3D>& pt3DVctr, 
					vector<Line2D>& ln2DVctr, vector<Line3D>& ln3DVctr, int& noOfRec);

// Filter menu
void filterMenu(string& filter, string& attribute);

// Attributes menus
void attributeMenu(string& filter, string& attribute);
void menuPoint3D(string& attribute);
void menuPoint2D(string& attribute);
void menuLine(string& attribute);

// Order menue
void orderMenu(string& order);




// Main function
int main ()
{
	string filter = "Point2D";
	string attribute = "x-ordinate";
	string order = "ASC";
	int noOfRec = 0;
	
	// vectors
	vector<Point2D> pt2DVctr;
	vector<Point3D> pt3DVctr;
	vector<Line2D> ln2DVctr;
	vector<Line3D> ln3DVctr;
	
	int choice;
	
	do {
		choice = displayMenu(filter, attribute, order);
		userSelection(choice, filter, attribute, order, pt2DVctr, 
						pt3DVctr, ln2DVctr, ln3DVctr, noOfRec);
		cout << endl;
		
	} while (choice != 7);
	
	return 0;
}



// Display menu function
int displayMenu(const string& filter, const string& attribute, const string& order) 
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
	cout << "Welcome to Assn3 program!\n" << endl;
	
	// Show options
	cout << setw(6) << "1)" << "Read in data" << endl;
	cout << setw(6) << "2)" << "Specify filtering criteria (current : " << filter << ")" << endl;
	cout << setw(6) << "3)" << "Specify sorting criteria (current : " << attribute << ")" << endl;
	cout << setw(6) << "4)" << "Specify sorting order (current : " << order << ")" << endl;
	cout << setw(6) << "5)" << "View data" << endl;
	cout << setw(6) << "6)" << "Store data" << endl;
	cout << setw(6) << "7)" << "Quit" << endl;
	cout << endl;
	
	cout << "Please enter your choice : ";
	cin >> userInput;
	cout << endl;
	
	return userInput;
}


// Process main selection
void userSelection(int choice, string& filter, string& attribute, string& order, 
					vector<Point2D>& pt2DVctr, vector<Point3D>& pt3DVctr, 
					vector<Line2D>& ln2DVctr, vector<Line3D>& ln3DVctr, int& noOfRec)
{
	if (choice < 1 || choice > 7) {
		cout << "\nInvalid selection, press <enter> to try again" << endl;
		cin.ignore().get();
		return;
		
	}else if (choice == 1 || choice == 6) {
		if (choice == 1) {
			// Read data function
			readFile(pt2DVctr, pt3DVctr, ln2DVctr, ln3DVctr, noOfRec);
			
		}else {
			// Write data to file function
			writeFile(filter, pt2DVctr, pt3DVctr, ln2DVctr, ln3DVctr, noOfRec);
		} 
		
		cout << "Going back to main menu..." << endl;
		cout << endl;
		
	} else {
		switch (choice) {
			case 2:
				// filter menu function
				filterMenu(filter, attribute);
				break;
				
			case 3:
				// Show attribute menu function
				attributeMenu(filter, attribute);
				break;
			
			case 4:
				// Show order menu function
				orderMenu(order);
				break;
				
			case 5:
				// View data function
				sortAndViewData(filter, attribute, order, pt2DVctr, 
										pt3DVctr, ln2DVctr, ln3DVctr);
				/*
				// Test display
				displayPoint2D(pt2DVctr); displayPoint3D(pt3DVctr);
				displayLine2D(ln2DVctr); displayLine3D(ln3DVctr);
				*/
				
				cout << "Press any key to go back to main menu..." << endl;
				cin.ignore().get();
				
				return;	
				
			case 7:
				// Deallocate any dynamic memory (but no arrays used)
				return;
		}		
	}
}




// Swapping between object types (Menu, Container, string variable)
// One function dedicated to conduct sorting according to requirements after each exit
// Filter menu
void filterMenu(string& filter, string& attribute)
{
	char choice;
	
	// Formatting
	cout << left;
	
	// Menu display 
	cout << "[ Specifying filter criteria (current : " << filter << ") ]" << endl;
	cout << endl;
	
	cout << "\t" << setw(7) << "a)" << "Point2D records" << endl;
	cout << "\t" << setw(7) << "b)" << "Point3D records" << endl;
	cout << "\t" << setw(7) << "c)" << "Line2D records" << endl;
	cout << "\t" << setw(7) << "d)" << "Line3D records" << endl;
	cout << endl;
	
	// User Selection
	do {
		cout << "\tPlease enter your criteria (a - d) : ";
		cin >> choice;
		cout << endl;

	} while (choice < 'a' || choice > 'd');
	
	if (choice == 'a' || choice == 'b') {
		if (choice == 'a')
			filter = "Point2D";
		else
			filter = "Point3D";
			
		attribute = "x-ordinate";
		
	} else {
		if (choice == 'c')
			filter = "Line2D";	
		else
			filter = "Line3D";
		
		attribute = "Pt. 1";
	}
	
	// Message
	cout << "\tFilter criteria successfully set to '" << filter << "'!" << endl;
	cout << endl;
}



// Attribute menu
void attributeMenu(string& filter, string& attribute)
{
	if (filter == "Point2D") {
		menuPoint2D(attribute);
		
	}else if (filter == "Point3D") {
		menuPoint3D(attribute);
	
	}else {
		menuLine(attribute);
		
	}
	
	// Message
	cout << "\tSorting criteria successfully set to '" << attribute << "'!" << endl;
	cout << endl;
}


void menuPoint2D(string& attribute)
{
	char choice;
	
	// Formatting
	cout << left;
	
	// Menu display
	cout << "[ Specifying sorting criteria (current : " << attribute << ") ]" << endl;
	cout << endl;
	
	cout << "\t" << setw(7) << "a)" << "X ordinate value" << endl;
	cout << "\t" << setw(7) << "b)" << "Y ordinate value" << endl;
	cout << "\t" << setw(7) << "c)" << "Dist. Fr Origin value" << endl;
	cout << endl;
	
	// User Selection
	do {
		cout << "\tPlease enter your criteria (a - c) : ";
		cin >> choice;
		cout << endl;

	} while (choice < 'a' || choice > 'c');
	
	if (choice == 'a') {
		attribute = "x-ordinate";
		
	}else if (choice == 'b') {
		attribute = "y-ordinate";
		
	}else {
		attribute = "Dist. Fr Origin";
	}
}


void menuPoint3D(string& attribute)
{
	char choice;
	
	// Formatting
	cout << left;
	
	// Menu display
	cout << "[ Specifying sorting criteria (current : " << attribute << ") ]" << endl;
	cout << endl;
	
	cout << "\t" << setw(7) << "a)" << "X ordinate value" << endl;
	cout << "\t" << setw(7) << "b)" << "Y ordinate value" << endl;
	cout << "\t" << setw(7) << "c)" << "Z ordinate value" << endl;
	cout << "\t" << setw(7) << "d)" << "Dist. Fr Origin value" << endl;
	cout << endl;
	
	// User Selection
	do {
		cout << "\tPlease enter your criteria (a - d) : ";
		cin >> choice;
		cout << endl;

	} while (choice <'a' || choice > 'd');
	
	if (choice == 'a') {
		attribute = "x-ordinate";
		
	}else if (choice == 'b') {
		attribute = "y-ordinate";
		
	}else if (choice == 'c') {
		attribute = "z-ordinate";
		
	}else {
		attribute = "Dist. Fr Origin";
	}
}


void menuLine(string& attribute)
{
	char choice;
	
	// Formatting
	cout << left;
	
	// Menu display
	cout << "[ Specifying sorting criteria (current : " <<  attribute << ") ]" << endl;
	cout << endl;

	cout << "\t" << setw(7) << "a)" << "X and Y ordinate values of Pt. 1" << endl;
	cout << "\t" << setw(7) << "b)" << "X and Y ordinate values of Pt. 2" << endl;
	cout << "\t" << setw(7) << "c)" << "Length value" << endl;
	cout << endl;
	
	// User Selection
	do {
		cout << "\tPlease enter your criteria (a - c) : ";
		cin >> choice;
		cout << endl;

	} while (choice != 'a' && choice != 'b' && choice != 'c');
	
	if (choice == 'a') {
		attribute = "Pt. 1";
		
	}else if (choice == 'b') {
		attribute = "Pt. 2";
		
	}else {
		attribute = "Length";
	}
}



// Sorting Order Menu
void orderMenu(string& order)
{
	 char choice;
	
	// Formatting
	cout << left;
	
	// Menu display
	cout << "[ Specifying sorting order (current : " << order << ") ]" << endl;
	cout << endl;
	cout << "\t" << setw(7) << "a)" << "ASC (Ascending order)" << endl;
	cout << "\t" << setw(7) << "b)" << "DSC (Descending order)" << endl;
	cout << endl;
	
	// User input
	do {
		cout << "\tPlease enter your criteria (a - b) : ";
		cin >> choice;
		cout << endl;

	} while (choice != 'a' && choice != 'b');
	
	if (choice == 'a')
		order = "ASC";
	else
		order = "DSC";
		
	// Message
	cout << "\tSorting order successfully set to '" << order << "'!" << endl;
	cout << endl;
}
















