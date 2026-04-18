// Util header file
// 
// Compile: g++ -std=c++11 -c Util.cpp -o Util.o
//
// File name: Util.cpp


#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"
#include "Util.h"


using namespace std;



/* Public functions */
/*
// Read file function
void readFile(vector<Point2D>& pt2DVctr, vector<Point3D>& pt3DVctr, 
				vector<Line2D>& ln2DVctr, vector<Line3D>& ln3DVctr, int& noOfRec);

// display Functions				
string displayPoint2D(vector<Point2D> pt2DVctr);
string displayPoint3D(vector<Point3D> pt3DVctr);
string displayLine2D(vector<Line2D> ln2DVctr);
string displayLine3D(vector<Line3D> ln3DVctr);

// Sorting and View function
void sortAndViewData(string& filter, string& attribute, string& order, 
					vector<Point2D>& pt2DVctr, vector<Point3D>& pt3DVctr, 
						vector<Line2D>& ln2DVctr, vector<Line3D>& ln3DVctr);

// File writing function
void writeFile(string& filter, vector<Point2D>& pt2DVctr, vector<Point3D>& pt3DVctr, 
				vector<Line2D>& ln2DVctr, vector<Line3D>& ln3DVctr, int& noOfRec);
*/



/* Prototypes */
// Extract data + Construct objects
static vector<int> extractPointValues(const string& line, int& startPos);

static Point2D makePoint2D(const string& line, int& startPos);
static Point3D makePoint3D(const string& line, int& startPos);
static Line2D makeLine2D(const string& line, int& startPos);
static Line3D makeLine3D(const string& line, int& startPos); // Cannot default argument for int&

template<typename T>
static void moveSetToVector(set<T>& objSet, vector<T>& vctr);

		
// Sorting Comparators
template<typename Point>
static bool compareXValueAsc(Point val1, Point val2);
template<typename Point>
static bool compareXValueDsc(Point val1, Point val2);

template<typename Point>
static bool compareYValueAsc(Point val1, Point val2);
template<typename Point>
static bool compareYValueDsc(Point val1, Point val2);

static bool compareZValueAsc(Point3D val1, Point3D val2);
static bool compareZValueDsc(Point3D val1, Point3D val2);

template<typename T>
static bool compareScalarValueAsc(T val1, T val2);
template<typename T>
static bool compareScalarValueDsc(T val1, T val2);

template<typename Point>
static bool compareXYValues(Point val1, Point val2, bool ascending = true);

template<typename Line>
static bool comparePt1Asc(Line val1, Line val2);
template<typename Line>
static bool comparePt1Dsc(Line val1, Line val2);

template<typename Line>
static bool comparePt2Asc(Line val1, Line val2);
template<typename Line>
static bool comparePt2Dsc(Line val1, Line val2);


// Display functions
template<typename T> static string showObjects(vector<T> vctr);





/* Functions */
// Read in Data
void readFile(vector<Point2D>& pt2DVctr, vector<Point3D>& pt3DVctr, 
				vector<Line2D>& ln2DVctr, vector<Line3D>& ln3DVctr, int& noOfRec)
{
	set<Point2D> unqPt2D;
	set<Point3D> unqPt3D;
	set<Line2D> unqLn2D;
	set<Line3D> unqLn3D;
	
	string fileName;
	
	cout << "Please enter filename : ";
	cin >> fileName;
	cout << endl;
	
	ifstream InData(fileName);
	string line;
	
	if (!InData.is_open()) {
		cerr << "Error opening File" << endl;
		return;
	}
	
	while (getline(InData, line)) {
		int startPos = 0;
		
		if (line.empty()) {
			break;
		}else {
			// See object type and place Constructed object into unordered set
			if (line.find("Point2D") != string::npos) {
				// Make Point2D and place in unordered set
				unqPt2D.insert(makePoint2D(line, startPos));
		
			}else if (line.find("Point3D") != string::npos) {
				// Make Point3D and place in unordered set
				unqPt3D.insert(makePoint3D(line, startPos));
			
			}else if (line.find("Line2D") != string::npos) {
				// Make Line2D and place in unordered set
				unqLn2D.insert(makeLine2D(line, startPos));
				
			}else if (line.find("Line3D") != string::npos) {
				// Make Line3D and place in unordered set
				unqLn3D.insert(makeLine3D(line, startPos));
			
			}	
		}
	}
	
	// close file
	InData.close();
	
	// Copy objects from set into vector
	moveSetToVector(unqPt2D, pt2DVctr);
	moveSetToVector(unqPt3D, pt3DVctr);
	moveSetToVector(unqLn2D, ln2DVctr);
	moveSetToVector(unqLn3D, ln3DVctr);
	
	int size = pt2DVctr.size() + pt3DVctr.size() + ln2DVctr.size() + ln3DVctr.size();
	
	cout << size - noOfRec << " records read in successfully! " << endl;
	cout << endl;
	
	noOfRec = size;
} 


// Extract values
static vector<int> extractPointValues(const string& line, int& startPos)
{
	vector<int> values;
	
	// Find square bracket positions
	int start = line.find('[', startPos);
	int end = line.find(']', start);
	
	// Create substring for the values
	string content = line.substr(start + 1, end - start - 1);
	
	// Remove whitespaces
	content.erase( remove(content.begin(), content.end(), ' '), content.end() );
	
	stringstream ss(content);
	string token;
	
	while (getline(ss, token, ',')) {
		if (!token.empty()) {
			values.push_back(stoi(token));
		}
	}
	
	startPos = end + 1;
	
	return values;
}


// Read and construct objects
static Point2D makePoint2D(const string& line, int& startPos)
{
	vector<int> values = extractPointValues(line, startPos);
	Point2D pt(values[0], values[1]);
	
	return pt;
}


static Point3D makePoint3D(const string& line, int& startPos)
{
	vector<int> values = extractPointValues(line, startPos);
	Point3D pt(values[0], values[1], values[2]);
	
	return pt;
}


static Line2D makeLine2D(const string& line, int& startPos)
{
	vector<Point2D> points;
	int pos = startPos;
	
	while ((pos = line.find('[', pos)) != string::npos) {
		//string currentSearch = line.substr(pos);
		points.push_back( makePoint2D(line, pos) );
		
		//int end = line.find(']', pos);
		//pos = end + 1;
	}
	
	Line2D ln(points[0], points[1]);
	
	return ln;
}


static Line3D makeLine3D(const string& line, int& startPos)
{
	vector<Point3D> points;
	int pos = startPos;
	
	while ((pos = line.find('[', pos)) != string::npos) {
		points.push_back( makePoint3D(line, pos) );
		
		//int end = line.find(']', pos);
		//pos = end + 1;
	}
	
	Line3D ln(points[0], points[1]);
	
	return ln;
}


// Convert set to vector
template<typename T>
static void moveSetToVector(set<T>& objSet, vector<T>& vctr)
{
	for (T object : objSet) {
		vctr.push_back(object);	
	}
}




// Sorting function
void sortAndViewData(string& filter, string& attribute, string& order, 
					vector<Point2D>& pt2DVctr, vector<Point3D>& pt3DVctr, 
						vector<Line2D>& ln2DVctr, vector<Line3D>& ln3DVctr)
{
	cout << "[ View data ... ]" << endl;
	cout << " filtering criteria : " << filter << endl;
	cout << " sorting criteria : " << attribute << endl;
	cout << " sorting order : " << order << endl;
	cout << endl;
	
	bool ascending = (order == "ASC");
	
	if (filter == "Point2D") {
		// sort Point2D vector
		if (attribute == "x-ordinate") {
			sort(pt2DVctr.begin(), pt2DVctr.end(), 
				ascending ? compareXValueAsc<Point2D> : compareXValueDsc<Point2D>);
		
		}else if (attribute == "y-ordinate") {
			sort(pt2DVctr.begin(), pt2DVctr.end(), 
				ascending ? compareYValueAsc<Point2D> : compareYValueDsc<Point2D>);
				
		}else {
			sort(pt2DVctr.begin(), pt2DVctr.end(), 
				ascending ? compareScalarValueAsc<Point2D> : compareScalarValueDsc<Point2D>);
		}
		
		// display the 
		cout << displayPoint2D(pt2DVctr);
		
		
	}else if (filter == "Point3D") {
		// sort Point3D
		if (attribute == "x-ordinate") {
			sort(pt3DVctr.begin(), pt3DVctr.end(), 
				ascending ? compareXValueAsc<Point3D> : compareXValueDsc<Point3D>);
		
		}else if (attribute == "y-ordinate") {
			sort(pt3DVctr.begin(), pt3DVctr.end(), 
				ascending ? compareYValueAsc<Point3D> : compareYValueDsc<Point3D>);
				
		}else if (attribute == "z-ordinate") {
			sort(pt3DVctr.begin(), pt3DVctr.end(), 
				ascending ? compareZValueAsc : compareZValueDsc);
				
		}else {
			sort(pt3DVctr.begin(), pt3DVctr.end(), 
				ascending ? compareScalarValueAsc<Point3D> : compareScalarValueDsc<Point3D>);
		}
		
		// display
		cout << displayPoint3D(pt3DVctr);
		
		
	}else if (filter == "Line2D") {
		// sort Line2D
		if (attribute == "Pt. 1") {
			sort(ln2DVctr.begin(), ln2DVctr.end(), 
				ascending ? comparePt1Asc<Line2D> : comparePt1Dsc<Line2D>);
		
		}else if (attribute == "Pt. 2") {
			sort(ln2DVctr.begin(), ln2DVctr.end(), 
				ascending ? comparePt2Asc<Line2D> : comparePt2Dsc<Line2D>);
				
		}else {
			sort(ln2DVctr.begin(), ln2DVctr.end(), 
				ascending ? compareScalarValueAsc<Line2D> : compareScalarValueDsc<Line2D>);
		}
		
		// display
		cout << displayLine2D(ln2DVctr);
		
	
	}else {
		// sort Line3D
		if (attribute == "Pt. 1") {
			sort(ln3DVctr.begin(), ln3DVctr.end(), 
				ascending ? comparePt1Asc<Line3D> : comparePt1Dsc<Line3D>);
		
		}else if (attribute == "Pt. 2") {
			sort(ln3DVctr.begin(), ln3DVctr.end(), 
				ascending ? comparePt2Asc<Line3D> : comparePt2Dsc<Line3D>);
				
		}else {
			sort(ln3DVctr.begin(), ln3DVctr.end(), 
				ascending ? compareScalarValueAsc<Line3D> : compareScalarValueDsc<Line3D>);
		}
		
		// display
		cout << displayLine3D(ln3DVctr);
		
	}
}



// Comparator functions
// Sort by x-ordinate
template<typename Point>
static bool compareXValueAsc(Point val1, Point val2)
{
	return val1.getX() < val2.getX();
}

template<typename Point>
static bool compareXValueDsc(Point val1, Point val2)
{
	return val1.getX() > val2.getX();
}


// Sort by y-ordinate
template<typename Point>
static bool compareYValueAsc(Point val1, Point val2)
{
	return val1.getY() < val2.getY();
}

template<typename Point>
static bool compareYValueDsc(Point val1, Point val2)
{
	return val1.getY() > val2.getY();
}


// Sort by Z
static bool compareZValueAsc(Point3D val1, Point3D val2)
{
	return val1.getZ() < val2.getZ();
}

static bool compareZValueDsc(Point3D val1, Point3D val2)
{
	return val1.getZ() > val2.getZ();
}


// Sort By Length
template<typename T>
static bool compareScalarValueAsc(T val1, T val2)
{
		return val1.getScalarValue() < val2.getScalarValue();
}

template<typename T>
static bool compareScalarValueDsc(T val1, T val2)
{
		return val1.getScalarValue() > val2.getScalarValue();
}


// Sort By X and Y
template<typename Point>
static bool compareXYValues(Point val1, Point val2, bool ascending)
{
	if (val1.getX() == val2.getX()) {
		return ascending ? compareYValueAsc(val1, val2) : compareYValueDsc(val1, val2);
	}
	
	return ascending ? compareXValueAsc(val1, val2) : compareXValueDsc(val1, val2);
}


// Compare Point1
template<typename Line>
static bool comparePt1Asc(Line val1, Line val2)
{
	return compareXYValues(val1.getPt1(), val2.getPt1());
}

template<typename Line>
static bool comparePt1Dsc(Line val1, Line val2)
{
	return compareXYValues(val1.getPt1(), val2.getPt1(), false);
}


// Compare Point2
template<typename Line>
static bool comparePt2Asc(Line val1, Line val2)
{
	return compareXYValues(val1.getPt2(), val2.getPt2());
}

template<typename Line>
static bool comparePt2Dsc(Line val1, Line val2)
{
	return compareXYValues(val1.getPt2(), val2.getPt2(), false);
}




// Display Functions
template<typename T>
static string showObjects(vector<T> vctr)
{
	stringstream os;
	
	for (T point : vctr) {
		os << point;
		os << setw(3) << " ";
		os << point.getScalarValue() << endl;
	}
	
	return os.str();
}


string displayPoint2D(vector<Point2D> pt2DVctr)
{
	stringstream os;
	
	// Formatting 
	os << right << fixed << setprecision(3);
	
	// Header
	os << setw(5) << "X" << setw(6) << "Y";
	os << setw(4) << " ";
	os << "Dist. Fr Origin" << endl;
	
	for (int i = 0; i < 19; i++) {
		os << "- ";
	}
	os << endl;
	
	// show objects
	os << showObjects(pt2DVctr);
	os << endl;
	
	return os.str();
} 


string displayPoint3D(vector<Point3D> pt3DVctr)
{
	stringstream os;
	
	// Formatting 
	os << right << fixed << setprecision(3);
	
	// Header
	os << setw(5) << "X";
	os << setw(6) << "Y";
	os << setw(6) << "Z";
	os << setw(4) << " ";
	os << "Dist. Fr Origin" << endl;
	
	for (int i = 0; i < 19; i++) {
		os << "- ";
	}
	os << endl;
	
	// Show objects
	os << showObjects(pt3DVctr);
	os << endl;
	
	return os.str();
} 


string displayLine2D(vector<Line2D> ln2DVctr)
{
	stringstream os;
	
	// Formatting 
	os << right << fixed << setprecision(3);
	
	// Header
	os << setw(5) << "P1-X";
	os << setw(6) << "P1-Y";
	os << setw(5) << " ";
	os << setw(4) << "P2-X";
	os << setw(6) << "P2-Y";
	os << setw(4) << " ";
	os << "Length" << endl;
	
	for (int i = 0; i < 27; i++) {
		os << "- ";
	}
	os << endl;
	
	// Show objects
	os << showObjects(ln2DVctr);
	os << endl;
	
	return os.str();
} 


string displayLine3D(vector<Line3D> ln3DVctr)
{
	stringstream os;
	
	// Formatting 
	os << right << fixed << setprecision(3);
	
	// Header
	os << setw(5) << "P1-X";
	os << setw(6) << "P1-Y";
	os << setw(6) << "P1-Z";
	os << setw(5) << " ";
	os << setw(4) << "P2-X";
	os << setw(6) << "P2-Y";
	os << setw(6) << "P2-Z";
	os << setw(4) << " ";
	os << "Length" << endl;
	
	for (int i = 0; i < 27; i++) {
		os << "- ";
	}
	os << endl;
	
	// Show objects
	os << showObjects(ln3DVctr);
	os << endl;
	
	return os.str();
} 




void writeFile(string& filter, vector<Point2D>& pt2DVctr, vector<Point3D>& pt3DVctr, 
				vector<Line2D>& ln2DVctr, vector<Line3D>& ln3DVctr, int& noOfRec)
{
	string fileName;
	
	cout << "Please enter filename : ";
	cin >> fileName;
	
	ofstream writeData(fileName, ios::app);
	
	// Check if stream is open
	if (!writeData.is_open()) {
		cerr << "Error opening File" << endl;
		return;
	}
	
	// write file
	if (filter == "Point2D") {
		writeData << displayPoint2D(pt2DVctr) << endl;
		
	}else if (filter == "Point3D") {
		writeData << displayPoint3D(pt3DVctr) << endl;

	}else if (filter == "Line2D") {
		writeData << displayLine2D(ln2DVctr) << endl;
	
	}else {
		writeData << displayLine3D(ln3DVctr) << endl;
	}
	
	// close file
	writeData.close();
	cout << endl;
	
	cout << noOfRec << " records output successfully!" << endl;
	cout << endl;
}




