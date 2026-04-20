// Assignment 1 WIPS main
//
// File name: A1_main.cpp


#include <iostream>
#include <iomanip>
#include "wips.h"

using namespace std;

// prototypes
int displayMenu();
void userSelection(int);


// Main function
int main ()
{
	int choice;
	
	do {
		choice = displayMenu();
		userSelection(choice);
		cout << endl;
		
	} while (choice != 8);
	
	return 0;
}




// Display menu function
int displayMenu () 
{
	int userInput;
	
	// left align
	cout << left;
	
	// menu
	cout << "Student ID   : 8066607" << endl;
	cout << "Student Name : Jotham Wong Hsien Ee" << endl;
	cout << "-------------------------------------" << endl;
	cout << "Welcome to Weather Information Processing System!\n" << endl;
	cout << setw(6) << "1)" << "Read in and process a configuration file" << endl;
	cout << setw(6) << "2)" << "Display city map" << endl;
	cout << setw(6) << "3)" << "Display cloud coverage map (cloudiness index)" << endl;
	cout << setw(6) << "4)" << "Display cloud coverage map (LMH symbols)" << endl;
	cout << setw(6) << "5)" << "Display atmospheric map (pressure index)" << endl;
	cout << setw(6) << "6)" << "Display atmospheric map (LMH symbols)" << endl;
	cout << setw(6) << "7)" << "Show weather forecast summary report" << endl;
	cout << setw(6) << "8)" << "Quit\n" << endl;
	cout << "Please enter your choice : ";
	cin >> userInput;
	cout << endl;
	
	return userInput;
}


// Process user input
void userSelection(int choice)
{
	if (choice < 1 || choice > 8) {
		cout << "\nInvalid selection, press <enter> to try again" << endl;
		cin.ignore().get();
		return;
		
	}else if (choice >= 2 && choice <= 7) {
		if(choice == 2) {
			// Display the city map
			displayMap(weatherMap, gridXMin, gridXMax, gridYMin, gridYMax, city);
			
		}else if(choice == 3) {
			// Display the cloud Index map
			displayMap(weatherMap, gridXMin, gridXMax, gridYMin, gridYMax, cloudIndex);
			
		}else if(choice == 4) {
			// Display the cloud coverage map (LMH)
			displayMap(weatherMap, gridXMin, gridXMax, gridYMin, gridYMax, cloudLMH);
			
		}else if(choice == 5) {
			// Display the Atmospheric Pressure Index map
			displayMap(weatherMap, gridXMin, gridXMax, gridYMin, gridYMax, pressureIndex);
			
		}else if(choice == 6) {
			// Display the Atmospheric Pressure map (LMH)
			displayMap(weatherMap, gridXMin, gridXMax, gridYMin, gridYMax, pressureLMH);
			
		}else {
			// Display the weather forecast summary report
			displayWeatherSummary(cities, weatherMap, gridXMin, gridXMax, gridYMin, gridYMax);
			
		}
		
		cout << "\n\nPress <enter> to go back to main menu..." << endl;
		cin.ignore().get();
		return;
		
	}else {
		if (choice == 1) {
			// Process config file and Load data structures
			loadFile(gridXMin, gridXMax, gridYMin, gridYMax, cities);
			
		} else {
			// If choice is 8, deallocate dynamic memory and quit
			deleteMap(weatherMap, gridYMin, gridYMax);
			
		}
	}
}








