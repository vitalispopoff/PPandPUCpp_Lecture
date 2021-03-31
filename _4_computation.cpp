#include "std_lib_facilities.h"

void constants() {

	constexpr double
		phi = 1.618039887,
		pi = 3.14159265359;

	/*
	this results in
	err E0137 : expressoin must be a modifiable lvalue
	err C2105 : '++' needs l-value
	*/
	//++phi; // disabled due to the errors
}

void constants1() {

	int input{ 0 };

	cout << "\n\n\twhat is current year ?\t";
	cin >> input;

	bool
		every4Years = input & 4,
		everyCentury = input & 100,
		every4Centuries = input & 400,
		leapYear = every4Years && (!everyCentury || every4Centuries);

	const int
		daysThisYear = 365 + leapYear;

	cout << "\n\n\thow many day current year has? " << daysThisYear << endl;

	/*
	this line results in
	err E0137 : expression must be a modifiable lvalue
	err C3892 : 'daysThisYear': you cannot assign to a variable that is const

	//daysThisYear++; // disabled due to the errors
	*/
}

void operators() {

	int i = -1;
	float f = 0;
	cout << "\n\n\t" << -i << endl;

	//narrowing conversion (casting >_>)
	cout << "\n\tcast: type(variable)\t" << typeid(double(i)).name();
	cout << "\n\tcast: (type)variable\t" << typeid((double)i).name();

	//non narrowing conversion (available since C++11 ?)

	cout << "\n\n\tcast: type{variable}\t" << typeid(long{ i }).name();
	cout << "\n\tcast: type{varialbe}\t" << typeid(double{ f }).name() << endl;

	/*neither of these will compile: as the conversion would risk in data loss
	which is prevented by the {} conversion.
	err C2397
	*/
	//cout << double{ i }; 
	//cout << long{ f };

}

void emptyStatements() {

	[]() {};

	if (true);

	//assembly: xor, je, jmp, jmp
	while (false)break;

	return;
}

void ifElse() {

	int i{ 0 };
	cin >> i;
	if (i) cout << "\n\n\tTRUE\n\n";
	else cout << "\n\n\tnot so true as it could have been if it was TRUE, just like intended in first place...\n";
}

void ifElse1() {

	constexpr double
		cmPerInch = 2.54;
	double
		length{ 0 };
	char
		unit{ 'c' };
	cout
		<< "\n\n\tEnter a length followed by a unit: cm:('c'), in:('i').\t";
	cin
		>> length
		>> unit;
	cout
		<< "\n\t";
	if (unit == 'i')
		cout << length << "in == " << length * cmPerInch << "cm.\n";
	else
		if (unit == 'c')
			cout << length << "cm == " << length / cmPerInch << "in.\n";
		else
			cout << "Unit must be either cm ('c') or in ('i'), and it's not either. Can't convert. Bye.\n";
}

void cashConvert() {

	const double
		eur2usd{ 1.17 },
		jpy2usd{ 0.00904 },
		gbp2usd{ 1.37 },
		chf2uds{ 1.06 };
	cout
		<< "\n\tenter currency:"
		<< "\n\t 'e'\tEUR"
		<< "\n\t 'y'\tJPY"
		<< "\n\t 'p'\tGBP"
		<< "\n\t 'f'\tCHF"
		<< "\n\twhitespace and a value to convert into USD.\n\tConfirm with 'Enter'.\t";
	char
		currency{ ' ' };
	string
		currencyCode = " ";
	double
		value{ 0 },
		result;
	cin
		>> currency
		>> value;

	auto attach = [&](double rate, string code) {
		result = value * rate;
		currencyCode = code;
	};

	if (currency == 'e')
		attach(eur2usd, "EUR");
	else
		if (currency == 'y')
			attach(jpy2usd, "JPY");
		else
			if (currency == 'p')
				attach(gbp2usd, "GPB");
			else
				if (currency == 'f')
					attach(chf2uds, "CHF");
				else {
					cout
						<< "\n\n\tNone of currencies available for a conversion were chosen."
						<< "\n\tBetter luck next time."
						<< "\n\tBye."
						<< endl;
					return;
				}
	cout
		<< "\n\n\t" << fixed << setprecision(2) << currencyCode << ' ' << value << " equals to USD " << result
		<< endl;
}







void computation() {

	//constants();	// constexpr
	//constants1();	// const
	//operators();
	//emptyStatements();
	//ifElse();
	//ifElse1();
	cashConvert();

}