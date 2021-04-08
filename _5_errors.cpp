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

void error_drill01() {

	// 1.
	// err E0020
	// err C2065
	// wrn C4018 
	// wrn C4101
	//Cout << "Success!\n";

	cout << "Success!\n";
}

void error_drill02() {

	// err E0008
	// err E0065
	// err C2001
	// err C2143
	// wrn C4018
	// wrn C4101

	//cout << "Success!\n;

	cout << "Success!\n";
}

void error_drill03() {

	// err E0007
	// err E0008
	// err E0065
	// err C2017
	// err C2001
	// err C2065
	// err C2143
	// err C2142
	// wrn C4018
	// wrn C4101
	//cout << "Success" << !\n"

	cout << "Success" << "!\n";

}

void error_drill04() {

	// err E0020
	// err C2065
	// wrn C4018
	// wrn C4101
	//cout << success << '\n';

	cout << "success" << '\n';
}

void error_drill05() {

	// err E0415
	// err E0413
	// err C2440
	// err C2440
	// wrn C4018
	// wrn C4101
	//string res = 7; vector<int>v(10); v[5] = res; cout << "Success!\n";

	//string res = 7;	//mustn't be string.
	int res = 7;
	vector<int> v(10);
	v[5] = res;
	cout << "Success!\n";

}

void error_drill06() {

	// err E0980
	// err E0980
	// err C2064
	// err C2064
	// err C4018
	// err C4101
	//vector<int>v(10); v(5) = 7; if (v(5) != 7)cout << "Success!\n";

	vector<int>v(10);

	//v(5) = 7;	//wrong brackets
	v[5] = 7;

	//if (v(5) != 7) cout << "Success!\n";	// wrong brackets here as well
	//if (v[5] != 7) cout << "Success!\n";	// gotta switch != to == to get "Success!" 

	if (v[5] == 7) cout << "Success!\n";
}

void error_drill07() {

	// err E0020
	// err C2065
	// wrn C4018
	// wrn C4101

	//if (cond)cout << "Success!\n"; else cout << "Fail!\n"; // cond not declared, nor initialized.

	bool cond = true;
	if (cond) cout << "Success!\n";
	else cout << "Fail!\n";
}

void error_drill08() {

	//bool c = false; if(c)cout << "Success!\n"; else cout << "Fail!\n"; // c needs being true, or if assertion changed to !

	bool c = true;
	if (c) cout << "Success!\n";
	else cout << "Fail!\n";
}

void error_drill09() {

	// err E0020
	// err C2374
	// err C2065
	// err C2146
	// err C2065
	// err C2065
	// wrn C4018
	// wrn C4101
	//string s = "ape";boo c = "fool"<s;if(c)cout<<"Success!\n"; // no type 'boo'

	string s = "ape";
	bool c = "fool" < s;			// had to rename c to c1 because of line 408
	if (!c) cout << "Success!\n";	// to have it success gotta switch to !c1

}

void error_drill10() {

	//string s = "ape"; if (s == "fool")cout << "Success!\n";// this one needs != instead of ==

	string s = "ape";
	if (s != "fool") cout << "Success!\n";
}

void error_drill11() {

	// err E0349
	// err C2678
	// wrn C4018
	// wrn C4101
	//string s="ape";if(s=="fool")cout<"Success!\n"; // assert : == to != ; also cout << rather than <

	string s = "ape";
	if (s != "fool") cout << "Success!\n";
}

void error_drill12() {

	// err E0711
	// err E0349
	// err C2451
	// err C2678
	// wrn C4018
	// wrn C4101

	//string s="ape";if(s+"fool")cout<"Success!\n"; // assertion needs to be a proper expression, cout needs <<

	string s = "ape";
	s = "fool";		// was + a shift mistype?
	if (s == "fool") cout << "Success!\n";
}

void error_drill13() {

	//vector<char>v(5);for(int i=0;0<v.size();++i);cout<<"Success!\n";	// for loop sustain condition is always true, and its code block is empty

	vector<char> v(5);
	for (int i = 0; i < v.size(); ++i); // keeping it useless, but not infinite
	cout << "Success!\n";

}

void error_drill14() {

	//vector<char>v(5);for(int i=0;i<=v.size();++i);cout<<"Success!\n";//this works actually

	vector<char> v(5);
	for (int i = 0; i < v.size(); ++i); // we should change <= into < . just in case
	cout << "Success!\n";
}

void error_drill15() {

	//string s = "Success!\n"; for (int i = 0; i < 6; ++i) cout << s[i]; // prints "Success" only

	string s = "Success!\n";
	//for (int i = 0; i < s.size(); ++i) cout << s[i];

	for (char c : s) cout << c;	// even safer.
}

void error_drill16() {

	// err E0020
	// err E0065
	// err C2065
	// err C2146
	// err C2181
	// wrn C4018
	// wrn C4101
	// wrn C4018
	// wrn C4018

	//if (true)then cout << "Success!\n"; else cout << "Fail!\n"; // looks like Excel.

	if (true) cout << "Success!\n";
	else cout << "Fail!\n";

}

void error_drill17() {

	//int x = 2000; char c = x; if (c == 2000) cout << "Success!\n"; // 2000 exceeds char length

	int x = 2000;
	char c = (x % 256);

	if (c == char(2000)) cout << "Success!\n"; // not sure if char(2000 % 256) wasn't better

}

void error_drill18() {

	//string s = "Success!\n"; for (int i = 0 ; i < 10; ++i) cout << s[i]; works but is not safe.

	string s = "Success!\n";
	for (char c : s)cout << c;

}

void error_drill19() {

	// err E0441
	// err C2955
	// err C2514
	// err C2662
	// wrn C4018 
	// wrn C4101
	// wrn C4018 
	// wrn C4018


	//vector v(5); for (int i = 0; i <= v.size(); ++i); cout << "Success!\n"; // vector w/o type declaration, for loop sustaine condition not safe, for loop codeblock empty;

	int vectorLength = 5;					// vector length moved outside the declaration - vector cannot be defined properly
	//vector</*...*/> v(vectorLength);		// no info on the vector type provided
	for (int i = 0; i < vectorLength; ++i);	// sustain condition based on a external variable instead of vector member
	cout << "Success!\n";

}

void error_drill20() {

	//int i = 0; int j = 9; while (i < 10) ++j; if (j < i) cout << "Success!\n"; // will never happen

	//int i = 0, j = 9;
	//while (i < 10) ++j;	// will never stop
	//if (j < i) cout << "Success!\n";	// will never be true


	int i = 0, j = 9;
	while (i < 10) ++i;	// it's the i to be asserted
	if (j < i) cout << "Success!\n";

}

void error_drill21() {

	//int x = 2; double d = 5 / (x - 2); if (d == 2 * x + 0.5) cout << "Success!\n";

	int x = 2;
	double d = 5 / (double(x) - 2);					//this will yield 'inf.' but at least won't throw an exception
	if (d != 2 * x + 0.5) cout << "Success!\n";		//it's rude, but effective

}

void error_drill22() {

	//string<char>s = "Success!\n"; for (int i = 0; i <= 10; ++i) cout << s[i];	// string doesn't accept this kind of declaration


	string s = "Success!\n";						// removed the <char> thing
	for (char c : s) cout << c;						// switched from for to range for loop, dumped the magic constant, and got safer

}

void error_drill23() {

	//int i = 0; while (i < 10) ++j; if (j < i)cout << "Success!\n"; // j not defined

	int
		i = 0,
		j = 0;						// added definition of j
	while (i < 10)
		++i;						// changed to i increment to break the while condition, and make the if condition true
	if (j < i)
		cout << "Success!\n";
}

void error_drill24() {

	//int x = 4; double d = 5 / (x - 2); if (d = 2 * x + 0.5) cout << "Success!\n"; // d reinitialized in the if condition ?

	int
		x = 2;
	double
		d = x == 2 ? 0 : 5 / (double(x) - 2);
	if (d = 2 * x + 0.5)					// this is just true
		cout << "Success!\n";
}

void error_drill25() {

	//cin << "Success!\n"; cin requires >>, << requires cout

	cout << "Success!\n";

}

// Excercise 02 --------------------------------

//inspect and fix the code:

/*
	double ctok(double c)		//shortening the names not a good idea
	{

		int k = c + 273.15;		// int instead of double, 'k' is never referred to in the local scope
		return int				// no ';' , returned type instead of variable
	}

	int tempFunction01()
	{

		double c = 0;			// would be nice to have '0.0' rather than '0'
		cin >> d;				// 'd' was never declared
		double k = ctok("c");	//	ctok accepts doubles, this is string, declaring 'k; in the scope is confusing, as ctok already has the variable called 'k',
		Cout << k << '\n';		// cout should be written with small caps
	}

	*/


double CelsiusToKelvin02(double temperature) {

	return temperature + 273.15;
}

void error_exc02() {

	double
		input{ 0. };
	cin
		>> input;
	double
		tempInKelvin = CelsiusToKelvin02(input);
	cout
		<< tempInKelvin
		<< endl;

}

// Excercise 03 & 04 ---------------------------

// the exc02 program needs correction for input < -273.15.

double CelsiusToKelvin03(double temperature) {

	//branchless - if temperature is less then 0K, returns 0;
	return (temperature >= -273.15) * (temperature + 273.15);
}

void error_exc03() {

	double
		input{ 0. };
	cin
		>> input;
	double
		tempInKelvin = CelsiusToKelvin03(input);
	cout
		<< tempInKelvin
		<< endl;

}

// Excercise 05 --------------------------------

/*converts temperature value between different scales.
* @var temperature - value
* @var scale - scale to which temperature is to be converted
*/
double CelsiusToKelvin05(double temperature, char scale) {

	//branchless - if temperature is less then 0K, returns 0;

	switch (scale) {

	case 'k':; case 'K':
		return (temperature >= -273.15) * (temperature + 273.15);

	case 'c':; case 'C':
		return (temperature >= 0) * (temperature - 273.15);

	default:
		cout << "No accepted scale was chosen. Returning 0.";
		return 0.;
	}
}

void error_exc05() {

	double
		input{ 0. };
	char scale{ 'k' };
	cin
		>> input
		>> scale;
	double
		tempInKelvin = CelsiusToKelvin05(input, scale);
	cout
		<< tempInKelvin
		<< endl;

}

// Excercise 06 --------------------------------

double CelsiusToFahrenheit06(double temperature, char scale) {

	switch (scale) {

	case 'f':; case'F':
		return 32. + temperature * 1.8;
	case 'c':; case'C':
		return (temperature - 32) * 0.5555555555555;
	default:
		cout << "No accepted scale was chosen. Returning 0.";
		return 0;
	}
}

void error_exc06() {

	double
		input{ 0. };
	char
		scale{ 'f' };
	while (cin >> input >> scale) {
		double
			tempInFahrenheit = CelsiusToFahrenheit06(input, scale);
		cout
			<< tempInFahrenheit
			<< endl;
	}
}

// Excercise 07 --------------------------------

void error_exc07() {

	// a * x^2 + b * x + c == 0
	double
		a{ 0. },
		b{ 0. },
		c{ 0. };
	auto discriminant = [&]() -> double {
		return (b * b) - (4 * a * c);
	};

	while (cin >> a >> b >> c) {

		if (discriminant() < 0)
			cout << "\n\tNo solution available.";
		else if (discriminant() == 0)
			cout << "\n\tx: " << (0 - b) / (2 * a); // we don't want a '-0'
		else {
			cout
				<< "\n\tx1: " << (-b + sqrt(discriminant())) / (2 * a)
				<< "\tx2: " << -(b + sqrt(discriminant())) / (2 * a);
		}
		cout << endl;
	}
}

// Excercise 08 --------------------------------

void error_exc08() {

	for (int input; cin >> input;) {

		vector<int>
			numbers(input);
		cout
			<< "\n\tEnter "
			<< numbers.size()
			<< " integrals then.\t";
		for (int& i : numbers)
			cin >> i;
		int
			result = 0;
		for (int i : numbers)
			result += i;
		cout
			<< "\n\tSum of those "
			<< input
			<< " integrals of your choice is "
			<< result
			<< endl;
	}

}

// Excercise 09 --------------------------------

void error_exc09() {
	for (int input; cin >> input;) {

		vector<int>
			numbers(input);
		cout
			<< "\n\tEnter "
			<< numbers.size()
			<< " integrals then.\t";
		for (int& i : numbers)
			cin >> i;
		double
			result = 0;
		for (int i : numbers)
			result += i;

		if (result - floor(result) == 0.)
			cout
			<< "\n\tSum of those "
			<< input
			<< " integrals of your choice is "
			<< round(result)
			<< endl;
		else
			cout
			<< "\n\tResult is not a proper integral.\n";
	}
}

// Excercise 10 --------------------------------

void error_exc10() {

	for (int input; cin >> input;) {

		vector<double>
			numbers(input),
			differentials(input - 1);
		cout
			<< "\n\tEnter "
			<< numbers.size()
			<< " integrals then.\t";
		for (double& i : numbers)
			cin >> i;
		for (int i = 0; i < differentials.size(); ++i)
			differentials[i] = numbers[i + 1] - numbers[i];
		double
			result = 0;
		for (double i : numbers)
			result += i;
		cout
			<< "\n\tSum of those "
			<< input
			<< " values of your choice is "
			<< result
			<< "\n\n\tDifferentials of the provided numbers:\t";
		for (double d : differentials)
			cout << d << " , ";
		cout
			<< endl;
	}
}

// Excercise 11 --------------------------------

void error_exc11() {

	//nth of the fibonacci sequence. 
	//implemented with int - no concurrency

	vector<int> numbers{ 0, 1, };

	int nth{ 0 };
	while (cin >> nth && nth > 0 && nth < 47) // F47 exceeds int range.
	{

		if (nth >= numbers.size())
			for (int i = numbers.size(); i <= nth; ++i)
				numbers.push_back(numbers[i - 1] + numbers[i - 2]);

		cout << "\n\t Fibonacci's nth: " << numbers[nth] << endl;
	}
}

// Excercise 12 --------------------------------

struct num {

	int
		answer,
		guess;
	//bool
	//	status{ false };	// cow == true
	num(int answer) {
		this->answer = answer;
	}
	bool bull() {
		return answer == guess;
	}
};


void error_exc12() {

	// bulls and cows

	int
		sequenceLength = 4;
	vector<num>
		sequence;

	// generating sequence
	for (int i = 0; i < sequenceLength;) {
		int
			number = rand() % 10;
		auto
			compare = [&]()->bool {
			for (num s : sequence)
				if (number == s.answer)
					return false;
			return true;
		};
		if (compare()) {
			sequence.push_back(num(number));
			++i;
		}
	}

	int
		bulls{ 0 },
		cows{ 0 };

	// the round

	while (bulls < sequenceLength) {

		bulls = cows = 0;

		// player writing his guess
		for (num& i : sequence) {
			int
				tmp;
			if (cin >> tmp && tmp >= 0 && tmp < 10)
				i.guess = tmp;
		}

		// comparing guesses with anwswers

		for (int i = 0; i < sequenceLength; ++i) {
			bool
				temp = sequence[i].bull();
			if (temp)
				bulls++;
			else {
				for (int j = 0; j < sequenceLength; ++j) {
					if (i != j && sequence[i].guess == sequence[j].answer) {
						cows++;
						break;
					}
				}
			}
		}
		cout << "\n\tbulls: " << bulls << " , cows: " << cows << endl;
	}

}

// Excercise 14 --------------------------------

void error_exc14() {

	vector<int>
		rejected, monday, tuesday, wednesday, thursday, friday, saturday, sunday;
	string
		s{ "" };
	int
		value{ 0 };
	vector<string>
		glossary{ "monday", "tuesday", "wednesday","thursday", "friday", "saturday", "sunday", "mon", "tue", "wed", "thu", "fri", "sat", "sun"};
	auto
		searchGlossary = [&]()-> int {
		for (int i = 0; i < glossary.size(); ++i)
			if (s == glossary[i])
				return 1 + (i % 7);
		return -1;
	};
	while (cin >> s >> value) {
		auto
			toLower = [&] {
			for (char& c : s) {
				c = tolower(c);
			}
		};
		toLower();
		int
			switcher = searchGlossary();
		switch (switcher) {
		case 1: monday.push_back(value); break;
		case 2: tuesday.push_back(value); break;
		case 3: wednesday.push_back(value); break;
		case 4: thursday.push_back(value); break;
		case 5: friday.push_back(value); break;
		case 6: saturday.push_back(value); break;
		case 7: sunday.push_back(value); break;
		default: rejected.push_back(value);
		}
		if (s == "_end")
			break;
	}
	auto
		sumDay = [&](vector<int> day) -> int {
		int
			result{ 0 };
		for (int i : day)
			result += i;
		return result;
	};
	cout 
		<< "\n\tmonday:\t" << sumDay(monday)
		<< "\n\ttuesday:\t" << sumDay(tuesday)
		<< "\n\twednesday:\t" << sumDay(wednesday)
		<< "\n\tthursday:\t" << sumDay(thursday)
		<< "\n\tfriday:\t" << sumDay(friday)
		<< "\n\tsaturday:\t" << sumDay(saturday)
		<< "\n\tsunday:\t" << sumDay(sunday)
		<< "\n\n\trejected data entries:\t" << rejected.size()
		<< endl;
}


void errors() { error_exc14(); }