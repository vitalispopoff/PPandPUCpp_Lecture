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

	while (cin >> current) {

		if (previous == current) cout << "repeated word: " << current << endl;
		previous = current;
	}
}

void objectsTypesValues() {

	//hiYetAgain();
	//avoidingSpace();
	//operationsOperators();
	//integralArithmetics();
	//stringArithmetics();
	//stringArithmetics02();
	repetitions();
}