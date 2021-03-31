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

	// wrn C4390 : ';' : empty controlled statement found; is this the intent ?
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

void convertLengthIfElse() {

	constexpr double
		cmToInch = 2.54;
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
		cout << length << "in == " << length * cmToInch << "cm.\n";
	else
		if (unit == 'c')
			cout << length << "cm == " << length / cmToInch << "in.\n";
		else
			cout << "Unit must be either cm ('c') or in ('i'), and it's neither. Can't convert. Bye.\n";
}

void convertLengthSwitch() {

	constexpr double
		cmToInch{ 2.54 };
	double
		length{ 0 };
	char
		unit{ 'c' };
	cout
		<< "\n\n\tEnter a length followed by a unit:"
		<< "\n\t c\tcm"
		<< "\n\t i\tinch"
		<< "\n\t";
	cin
		>> length
		>> unit;
	cout
		<< "\n\t";
	switch (unit) {
	case 'c': {
		cout << length << "in == " << length * cmToInch << "cm.\n";
		break;
	};
	case 'i': {
		cout << length << "cm == " << length / cmToInch << "in.\n";
		break;
	};
	default: {
		cout << "Unit must be either cm ('c') or in ('i'), and it's neither. Can't convert.\n\tBye.\n";
		break;
	};
	}

}

void convertCashIfElse() {

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

void temporal() {

	char 
		currency{ ' ' };

	double
		eur2usd,
		jpy2usd,
		gbp2usd,
		chf2usd,
		value,
		result;
	string
		currencyCode;

	cout
		<< "\n\tenter currency:";


	auto attach = [&](double rate, string code) {

		result = value * rate;
		currencyCode = currency;
	};

	switch (currency) {

	case 'e' :break;
	case 'y' :break;
	case 'p' :break;
	case 'f' :break;
	default:break;

	}
}




void multipleSwitchCases() {

	/*
	Zbyszek
	Czesiek
	Rysiek
	Marzena
	Bo¿ena
	Gra¿yna
	*/

	char
		input{ ' ' };
	cin
		>> input;
	cout
		<< "\n\n\t";
	switch (input) {

		/*doesn't work - adding a filter variable to the case (e.g. 'c':) causes multiple errors
		err E0065 : expected a ';'
		err C2143 : syntax error: missing ';' ':'
		err C2059 : syntax error ':'
		*/
	case 'z':
		cout << "male in general";
		break;
	case 'c':
		cout << "c case";
		break;
	case 'm':
		break;
	default:
		cout << "moustache at will";
		break;
	}

	cout << endl;

}

void switchWithStringSelector1() {

	/*
	idea: implement switch using a hashcode of certain strings.

	the problem tho: is it possible to set the case filtering value to be not hardcoded... ?
	*/

	const unsigned int cases[3]{
		4126860097,
		261001112,
		2054715501,
	};

	string
		selectorIn{ " " };
	cin
		>> selectorIn;

	auto stringToUnInt = [](string s)-> unsigned int { return hash<string>()(s); };

	switch (stringToUnInt(selectorIn)) {

	case 4126860097: {
		cout << "\n\n\t this is Zbyszek.\n";
		break;
	}
	case 261001112: {
		cout << "\n\n\t this is Rysiek.\n";
		break;
	}
	case 2054715501: {
		cout << "\n\n\t this is Andrzej.\n";
		break;
	}
	default: {
		cout << "User not recognized. Access denied.\n";
	}
	}

	//cout << hash<string>()(selectorIn);
}

void computation() {

	//constants();	// constexpr
	//constants1();	// const

}