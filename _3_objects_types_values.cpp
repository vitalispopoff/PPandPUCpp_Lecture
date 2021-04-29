#include "std_lib_facilities.h"

namespace p01_03
{
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

	/*bool truth = true;
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
	};*/
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


	cout << "\n\n\tEnter the names of the recipient and sender separated with whitespace.\t";
	string recipient, sender;
	cin >> recipient >> sender;

	cout << "\n\tEnter 'f' for female or other character for male and age separated with whitespace.\t";
	char fem;
	int age;
	cin >> fem >> age;


	cout
		<< "\n\n\t\tDear " << recipient
		<< ",\n\n\tIn these first words of sympathy I'd like You to ask You to stop writing your code at once."
		<< "\n\t Your recent software development activities have already shown as a damaging factor to a emotional health to all the "
		<< (fem == 'f' ? "fe" : "") << "males in our office, and the authorities were already adviced to intervene with no hesistation."
		<< "\n\tBeing " << age << (abs(age) == 1 ? " year" : " years") << " of age is certainly not a proper moment in life to dedicate oneself to become a Dev."
		<< "\n\n\t\tSincerely, \n\n\t\t" << sender << "\n\n";
}

void truncateIt() {

	double input;
	//int i;

	while (cin >> input) {

		//if (input == NAN) i = 0; // actually this should return kinda NaN or out of range exception.
		//else if (input < INT_MIN) i = INT_MIN;
		//else if (input > INT_MAX) i = INT_MAX;
		//else i = input;

		//cout << "\n\n\t" << i << endl;
	}
}

void excercise02() {

	double miles{ 0 };
	double types[]{
		1.609344, //imperial
		1.85166, //nautic
	};
	int type;

	cout << "\n\n\t enter distance (in miles) and mile type (0: imperial, 1 : nautical).\t";

	cin >> miles >> type;

	//if (type != 0 || type != 1) type = type > 1;

	cout << "\n\n\t" << miles << ((bool)type ? " nautical" : " imperial") << " is about " << miles * types[type] << " kilometers in distance.\n";

}

void excercise03() {

	/*
	err E0084
	err C2632
	wrn C4901
	*/
	//int double;

	/*
	* err E0040
	* err C2059
	*/
	//double 3three;

	/*
	wrn C4101
	*/
	//bool _main;

	/*
	err E0065
	err C2143
	err C2059
	*/
	//char H4><0R;
}


void excercise04() {

	int
		val1{ 0 },
		val2{ 0 };

	cout << "\n\n\tEnter to integrals.\t";
	cin >> val1 >> val2;

	if (val1 == val2)
		cout << "\n\n\t the integrals provided are equal.\n";
	else {
		int
			smaller = min(val1, val2),
			bigger = max(val1, val2),
			sum = val1 + val2;

		cout << "\n\n\t" << smaller << " is smaller than " << bigger << " by " << bigger - smaller;
		cout << "\n\t which is " << 100. * ((double)bigger - smaller) / bigger << "% of the bigger of them.";

		cout << "\n\n\t Together they are equal " << sum << " , and on average " << sum / 2.;
	}
}

void excercise05() {

	double
		val1{ 0. },
		val2{ 0. };

	cout << "\n\n\tEnter to numbers.\t";
	cin >> val1 >> val2;

	if (val1 == val2)
		cout << "\n\n\t the integrals provided are equal.\n";
	else {
		double
			smaller = min(val1, val2),
			bigger = max(val1, val2),
			sum = val1 + val2;

		cout << "\n\n\t" << smaller << " is smaller than " << bigger << " by " << bigger - smaller;
		cout << "\n\t which is " << 100. * (bigger - smaller) / bigger << "% of the bigger of them.";

		cout << "\n\n\t Together they are equal " << sum << " , and on average " << sum / 2.;
	}
}

void excercise06() {

	int i[3]{ 0 };

	cin >> i[0] >> i[1] >> i[2];

	auto swap = [&](int i1, int i2) {

		if (i[i1] > i[i2] && i1 < i2) {

			int temp = i[i1];
			i[i1] = i[i2];
			i[i2] = temp;
		}
	};

	swap(0, 1);
	swap(1, 2);
	swap(0, 1);

	cout << "\n\n\t" << i[0] << " , " << i[1] << " , " << i[2] << endl;
}

void excercise07() {

	string s[3]{ " " };

	cin >> s[0] >> s[1] >> s[2];

	auto swap = [&](int i1, int i2) {

		if (s[i1] > s[i2] && i1 < i2) {

			string temp = s[i1];
			s[i1] = s[i2];
			s[i2] = temp;
		}
	};

	swap(0, 1);
	swap(1, 2);
	swap(0, 1);

	cout << "\n\n\t" << s[0] << " , " << s[1] << " , " << s[2] << endl;

}

void excercise08() {

	int i;
	string answer[]{ "odd", "even" };

	cin >> i;

	/*
	bit masking in assembly: mov, and, mov
	*/
	//bool result1 = i & 1;

	/*
	modulo with equation in assembly: mov, and, jns, dec, or, inc, test, jne, mov, jmp, mov, mov, mov
	*/
	//bool result2 = i % 2 == 0;

	/*
	in assemly: push, mov, and, imul, lea, push, push, mov, mov, push, push, mov, push, call, add, mov, call, cmp, call, push, call, add, push, call, add, push, call, add
	*/

	cout << "\n\n\t" << i << " is " << answer[i & 1] << ".\n";

	/*
	in assembly: mov, and, je, mov, jmp, mov, mov, push, push, mov, mov, push, push, mov, push, call, add, mov, call, cmp, call, push, call, add, push, call, add
	*/
	//cout << "\n\n\t" << i << " is " << ((i & 1) ? "odd.\n" : "even.\n");
}

void excercise09() {

	string
		s{ " " },
		answers[]{ "zero", "one", "two", "three", "four" };
	bool
		unanswered{ true };
	cin >> s;

	for (int i = 0; i < 5 && unanswered; ++i) {

		if (s == answers[i]) {

			unanswered = false;
			cout << "\n\n\t" << s << " is equal to " << i << endl;
		}
	}

	if (unanswered) cout << "\n\n\tDon't ask me, what You know - is true...\n";
}

void excercise10() {

	char type{ 0 };
	double val1{ 0 }, val2{ 0 };

	cin >> type >> val1 >> val2;

	double& result{ val1 };

	switch (type) {

		case '+': {
			result += val2;
			break;
		};
		case '-': {

			result -= val2;
			break;
		};
		case '*': {
			result *= val2;
			break;
		};
		case '/':;
		case ':': {
			if(val2 == 0) 
				return;
			else result /= val2;
			break;
		}
	}

	cout << "\n\n\t result: " << result << endl;	
}

void excercise1a() {

	double v1{ 0 }, v2{ 0 }, res{ 0 };
	string operation{ " " };

	cin >> operation >> v1 >> v2;

	if (operation == "+" || operation == "plus") res = v1 + v2;
	else if (operation == "-" || operation == "minus") res = v1 - v2;
	else if (operation == "*" || operation == "mul") res = v1 * v2;
	else if (operation == "/" || operation == ":" || operation == "div") res = v1 / v2;
	else cout << "\n\n\t we don't do that here\n";

	cout << "\n\n\t" << res << endl;
}

void excercise11() {

	unsigned int
		pennies{ 0 },
		nickles{ 0 },
		dimes{ 0 },
		quarters{ 0 },
		halves{ 0 },
		dollars{ 0 };

	cout << "write us about your pennies, nicklez, dimes, quartaz, havz and bucks...\t";
	cin >> pennies >> nickles >> dimes >> quarters >> halves >> dollars;

	string
		p = pennies == 1 ? "penny" : "penny",
		n = nickles == 1 ? "nickle" : "nickles",
		d = dimes == 1 ? "dime" : "dimes",
		q = quarters == 1 ? "quarter" : "quarters",
		h = halves == 1 ? "50-cent" : "505-cents",
		b = dollars == 1 ? "dollar" : "dollars";
	auto bulletCoins = [](unsigned int val, string name) {
		if (val > 0) cout << "\n\t" << val << "\t" << name;
	};

	cout << "\n\n\tYou've said to have on you:\n";
	
	bulletCoins(pennies, p);
	bulletCoins(nickles, n); 
	bulletCoins(dimes, d);
	bulletCoins(quarters, q);
	bulletCoins(halves, h);
	bulletCoins(dollars, b);
	cout << "\n\n\t which gives a neatly round sum of " << (pennies + 5. * nickles + 10. * dimes + 25. * quarters + 50. * halves + dollars) / 100. << " dollaz.\n";
}

}

void objectsTypesValues() {

	using namespace p01_03;
	//hiYetAgain();
	//avoidingSpace();
	//operationsOperators();
	//integralArithmetics();
	//stringArithmetics();
	//stringArithmetics02();
	//repetitions();
	//conversions0();
	//conversions1();
	//drill();
	//truncateIt();

	//excercise02();
	//excercise04();
	//excercise05();
	//excercise06();
	//excercise07();
	//excercise08();
	//excercise09();
	//excercise10();
	//excercise1a();
	excercise11();


}