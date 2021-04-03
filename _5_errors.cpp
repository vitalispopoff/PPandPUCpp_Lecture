#include "std_lib_facilities.h"

int area(int length, int width) { return length * width; };

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

//int x4 = area(10, -7);			// 	
//int x5 = area(10.7, 9.3);			//
//char x6 = area(100, 9999);		//

// Example 4 : Link-time errors ----------------

int f(int i1, int i2);
int f(double d1, double d2) { return 0; };
int f(int i1, int i2);

//int x = f(2, 3);					// err LNK2019, LNK1120

// Example 5 : Run-time errors -----------------

int framedArea(int x, int y) {
	return area(x - 2, y - 2);
}

void example05() {

	int
		x = -1,
		y = 2,
		z = 4,
		area1 = area(x, y),					// -2
		area2 = framedArea(1, z),			// -1 * 2 = -2
		area3 = framedArea(y, z);			// 0 * 2 = 0
	double
		ratio = double(area1) / area3;	// -2. / 0

	cout << "\n\t" << ratio << endl;
}

void example05_01() {
	int x, y;
	cin >> x >> y;	
	bool  trigger = rand() & 1;
	if (trigger) error("triggered.");	
	int area1 = area(x, y);
}

void becauseWeCan() {
	string s;
	while (cin >> s)
		throw runtime_error("because we can");
}



void errors() {

	becauseWeCan();
}