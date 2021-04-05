#include "std_lib_facilities.h"

int area(int, int);
int framedArea(int, int);

// Example 1 : syntax errors -------------------

//int s1 = area(7;					// err E0018, C2143, C2660
//int s2 = area()					// err E0165, E0065, C2660, C2144
//Int s3 = area(7);					// err E0020, E0165, C2660, C2144
//int s4 = area('7);				// err E0008, E0018, C2660, C2144

// Example 2 : type errors ---------------------

//int x0 = arena(7);				// err E0020, C3861
//int x1 = area(7);					// err E0165, C2660
//int x2 = area("seven", 2);		// err E0167, C2664

// Example 3 : non-errors ----------------------

//int area(int x, int y) { return x * y; }	// orginal implementation, non secure;
//int x4 = area(10, -7);			// 	
//int x5 = area(10.7, 9.3);			//
//char x6 = area(100, 9999);		//

// Example 4 : Link-time errors ----------------

//int f(int i1, int i2);
//int f(double d1, double d2) { return 0; };
//int f(int i1, int i2);
//int x = f(2, 3);					// err LNK2019, LNK1120

// Example 5 : Run-time errors -----------------

/*
void becauseWeCan() {
	string s;
	while (cin >> s) throw runtime_error("because we can");
}
*/

// area() non secure 
/*
int area(int length, int width) {
	return length * width;
}
*/

// framedArea() non secure
/*
int framedArea(int x, int y) {
	return area(x - 2, y - 2);
}
*/

// logic error
/*
void example05() {

	int
		x = -1,
		y = 2,
		z = 4,
		ar1 = area(x, y),			// -1 * 2 == -2
		ar2 = framedArea(1, z),		// -1 * (4-2) == -2
		ar3 = framedArea(y, z);		// (2-2) * (4-2) == 0
	double
		ratio = double(ar1) / ar3;	// -2 : 0 == -inf.
}
*/

// error handling by caller	------------
/*
void example05A() {

	int x, y, z;
	{
		x = -1; y = 2; z = 4;
	}

	if (x <= 0 || y <= 0) throw runtime_error("non-positive area() argument");
	int ar1 = area(x, y);

	if (z <= 2) throw runtime_error("non positive area() width called by framedArea()");
	int ar2 = framedArea(1, z);

	if (y <= 2 || z <= 2) throw runtime_error("non-positive area() argument called bye framedArea()");
	int ar3 = framedArea(y, z);
}
*/

//error handling on behalf of area()
/*
constexpr int frameWidth = 2;
int framedArea(int x, int y) {
	return area(x - frameWidth, y - frameWidth);
}
*/

//error handling on behafr of area() - a bit less messy
/*
int framedArea(int x, int y) {

	constexpr int frameWidth = 2;
	if (x <= frameWidth || y <= frameWidth)
		throw runtime_error("non-positive area() arguments intercepted by framedArea()");
	return area(x - frameWidth, y - frameWidth);
}
*/

//error handling by the area() itself --
/*
int area(int length, int width) {

	if (length <= 0 || width <= 0)
		throw runtime_error("non-positive area() arguments");
	return length * width;
}
*/

// Example 6 : exceptions ----------------------

//BadArea - exception type dedicated to area();
class BadArea {};

// area() handling by throwing an exception
int area(int length, int width) {
	if (length <= 0 || width <= 0) throw BadArea{};
	return length * width;
}

// framedArea() - non secure 
int framedArea(int x, int y) {
	return area(x - 2, y - 2);
}

//main scope secured with try-catch focused on BadArea type
void example06() {
	try {
		int x, y, z;
		{
			x = -1; y = 2; z = 4;
		}

		int ar1 = area(x, y);
		int ar2 = framedArea(1, z);
		int ar3 = framedArea(y, z);
		double ratio = ar1 / ar3;
	}
	catch (BadArea) { cout << "\n\tGotcha!\n"; }
}

// reange errors ---------------

vector<int> v;

void fillIntVector() {
	for (int i; cin >> i;)
		v.push_back(i);
}

// standard for loop - a non-secure solution
void vectorRange() {
	fillIntVector();
	for (int i = 0; i < v.size(); ++i) cout << "v[" << i << "]==" << v[i] << '\n';
}

//range for loop - secure but needs additional stuff to provide non obscured counter
void vectorRange1() {
	fillIntVector();
	int counter = 0;
	for (int i : v) cout << "v[" << counter++ << "]==" << i << '\n';
}

//intercepting out_of_range
void catchingOutOfRangeExc() {

	fillIntVector();

	try {
		for (int i = 0;; ++i)
			cout << "\n\tv[" << i << "] == " << v[i];
	}
	catch (out_of_range) {
		cerr << "\n\tWhooops.\n";
	}
	catch (...) {
		cerr << "\n\tSomething completely different.\n";
	}
}

// input errors ----------------

void inputErrors() {

	double d;
	while (true) {
		cin >> d;
		if (!cin) throw runtime_error("cin error - couldn't read a double");
	}

}

void theErrorToBeCaughtOuttaRange() {

	vector <int> v{ 0 };
	try {
		for (int i = 0; ; ++i)v[i];
	}
	catch (out_of_range& e) {
		cerr << "oops...\n";
	}
}

void theErrorToBeCaughtDivBy0() {

	//Exception thrown at 0x00085344 in PPandPUCpp_Lecture.exe: 0xC0000094 : Integer division by zero.
	//Unhandled exception at 0x00085344 in PPandPUCpp_Lecture.exe : 0xC0000094 : Integer division by zero.

	int i;
	cin >> i;
	try {
		i = 2 / i;
	}
	catch (runtime_error& e) {
		cerr << "runtime error: " << e.what() << '\n';
	}
	cout << "\n\twe good" << endl;
}

void notCaughtDivBy0() {

	//Exception thrown at 0x00983EC1 in PPandPUCpp_Lecture.exe: 0xC0000094 : Integer division by zero.
	//Unhandled exception at 0x00983EC1 in PPandPUCpp_Lecture.exe : 0xC0000094 : Integer division by zero.

	int i;
	cin >> i;
	i = 1 / i;
}

void narrowingErrors() {

	double d = 2.9;

	//Exception thrown at 0x76A2A8B2 in PPandPUCpp_Lecture.exe: Microsoft C++ exception : std::runtime_error at memory location 0x007AF874.
	//Unhandled exception at 0x76A2A8B2 in PPandPUCpp_Lecture.exe: Microsoft C++ exception : std::runtime_error at memory location 0x007AF874.
	//int x1 = narrow_cast<int>(d);

	int x2 = narrow_cast<int>(floor(d));

	int i = 1066;


	//Exception thrown at 0x76A2A8B2 in PPandPUCpp_Lecture.exe: Microsoft C++ exception : std::runtime_error at memory location 0x0079F508.
	//Unhandled exception at 0x76A2A8B2 in PPandPUCpp_Lecture.exe: Microsoft C++ exception : std::runtime_error at memory location 0x0079F508.
	//char c1 = narrow_cast<char>(i);

	char c2 = narrow_cast<char>(i % 256);
}

// Example 7 : logic errors --------------------

void lowHighAverage() {

	vector < double> temperatures;

	for (double temp; cin >> temp; temperatures.push_back(temp));

	//double sum = 0, highTemp = 0 , lowTemp= 0;	

	double sum{ 0 }, highTemp, lowTemp;
	highTemp = lowTemp = temperatures[0];

	//for (int x : temperatures)

	if (temperatures.size() > 0) {
		for (double x : temperatures)
		{
			highTemp = max(highTemp, x);
			lowTemp = min(lowTemp, x);
			sum += x;
		}

		cout
			<< "\n\tHigh temperature:\t" << highTemp
			<< "\n\tLow tempererature:\t" << lowTemp
			<< "\n\tAverage temperature:\t" << sum / temperatures.size()
			<< endl;
	}
	else cout << "no data provided.";

}

// Example11 : testing -------------------------



void errors() {



}