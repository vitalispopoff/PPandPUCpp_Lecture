#include "std_lib_facilities.h"

void hiYetAgain() {

	cout << "\n\tPlease enter your first name and hit 'Enter'.\n\t";

	string firstName;

	cin >> firstName;

	cout << "\n\n\tHello, " << firstName << ". Please to meet You.\n";
}

void avoidingSpace() {

	cout << "\n\tPlease enter your first name (and age).";

	string firstName;
	int age = 0;

	cin >> firstName;
	cin >> age;

	cout << "\n\n\tHey, " << firstName << ".\n\tWow. You definitely don't look like " << age << ".\n\n\tYou look like " << (int)(age * 1.4) << ".\n";
}

void operationsOperators() {

	int i;
	cin >> i;
	string s;
	cin >> s;

	int i2 = i + 2;
	string s2 = s + " Jr. ";	// concatenation

	int i3 = i - 2;
	//string s3 = s2 - " Jr. "; //disabled due to the error : E0349
}

void integralArithmetics() {

	int i = 500;
	auto gen = [=] {return i + (rand() % (i << 1)); };
	int a = gen(), b = gen();

	auto result = [=]()-> int {return a / b * b + a % b; };

	cout << "\n\n\t" << (result() == a);
}

void stringArithmetics() {

	string first, second;

	cin >> first >> second;

	cout << "\n\n\t";
	if (first == second) cout << "these are the same";
	else cout << first << ((first < second) ? " is before " : " is after ") << second;
	cout << ".\n";
}

void stringArithmetics02() {

	auto letters = [](string& s) {

		int counter = (rand() % 9) + 3;
		cout << "\ndbg: " << counter;

		for (int i = 0; i < counter; ++i) {
			int x = (rand() % 25) + 65 + 32 * (i != 0);
			s.append(1, (char)x);
		}
	};

	string s1, s2;

	letters(s1);
	letters(s2);

	cout << "\n\n\t";
	if (s1 == s2) cout << s1 << " and " << s2 << " are the same";
	else cout << s1 << ((s1 < s2) ? " is before " : " is after ") << s2;
	cout << ".\n";
}

void repetitions() {

	string previous = " ", current;
	int repeated = 0;

	while (cin >> current) {
		if (previous == current)
			cout << "\n\t\'" << current << "\' repeated " << repeated << (++repeated == 1 ? " time\n" : " times\n");
		//else repeated -= repeated;	// assemlby mov, sub, mov
		else repeated = 0;				// assembly : mov

		previous = current;
	}
}

void typeSafety() {

	//int x, y = x, z = y + 2;
}

void conversions0() {

	bool truth = true;
	char c = truth;
	int i = c;
	float f = i;
	double d = f;

	double phi = 1.6180339887498948482;
	float fi = phi;
	long lie = fi;

	int big = 0x80000001;
	char small = big;

	auto check = [](auto v1, auto v2) {

		string
			type1 = typeid(v1).name(),
			type2 = typeid(v2).name(),
			result[]{ "changed.", "remained." };
		bool
			comparison = v1 == v2;

		cout
			<< "\n\tcast " << type1
			<< " to " << type2
			<< " - value has " << result[comparison]
			<< endl;
	};
}

void conversions1() {

	int i = 0;
	char c = 0;

	while (cin >> i) {
		c = i;
		int result = i - c;
		cout
			<< "\n\tint " << i
			<< " cast to char (" << (int)c
			<< "), difference in value is " << result
			<< endl;
	}
}

void conversions2() {

	/*using c++11 universal & uniform initialization syntax prevents narrowing conversion:
		C2397 : conversion from 'int' to 'char' requires a narrowing conversion.
	using pre-C++11 notation convention would result in 
		C4244 : 'initializing': conversion from 'int' to 'char', possible loss of data
	but the compilator would proceed anyways.
	*/

	int i{ 0 };

	/*
	while (cin >> i) {

		char c{ i };
		int result{ i - c };

		cout
			<< "\n\tint " << i
			<< " cast to char (" << (int)c
			<< "), difference in value is " << result
			<< endl;
	}
	*/
}

void drill() {

	string recipient, sender;

	cout << "\n\n\tEnter the names of the recipient and sender separated with whitespace.\t";	
	cin >> recipient >> sender;
	cout << "\n\n\tDear " << recipient <<",\n\n\tIn these first words of sympathy I'd like You to ask You to stop writing your code at once.\n\n\tSincerely,\n\t"<<sender<<endl;
}

void objectsTypesValues() {

	//hiYetAgain();
	//avoidingSpace();
	//operationsOperators();
	//integralArithmetics();
	//stringArithmetics();
	//stringArithmetics02();
	//repetitions();
	//conversions0();
	//conversions1();
	drill();


}