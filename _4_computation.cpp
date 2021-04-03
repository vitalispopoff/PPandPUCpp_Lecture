#include "std_lib_facilities.h"

void constants() {

	constexpr double
		phi = 1.618039887,
		pi = 3.14159265359;

	//this results in
	//err E0137 : expressoin must be a modifiable lvalue
	//err C2105 : '++' needs l-value

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

	//this line results in
	//err E0137 : expression must be a modifiable lvalue
	//err C3892 : 'daysThisYear': you cannot assign to a variable that is const

	//daysThisYear++; // disabled due to the errors

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

	//neither of these will compile: as the conversion would risk in data loss
	//which is prevented by the {} conversion.
	//err C2397

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

void convertCashSwitch() {

	char
		currency{ ' ' };
	double
		eur2usd{ 1.17 },
		jpy2usd{ 0.00904 },
		gbp2usd{ 1.37 },
		chf2usd{ 1.06 },
		value{ 0. },
		result{ 0. };
	string
		currencyCode{ " " };
	cout
		<< "\n\tenter currency:"
		<< "\n\t 'e'\tEUR"
		<< "\n\t 'y'\tJPY"
		<< "\n\t 'p'\tGBP"
		<< "\n\t 'f'\tCHF"
		<< "\n\twhitespace and a value to convert into USD.\n\tConfirm with 'Enter'.\t";
	cin
		>> currency
		>> value;

	auto attach = [&](double rate, string code) {

		result = value * rate;
		currencyCode = code;
	};

	switch (currency) {

	case 'e':
	{
		attach(eur2usd, "EUR");
		break;
	}
	case 'y':
	{
		attach(jpy2usd, "JPY");
		break;
	}
	case 'p':
	{
		attach(gbp2usd, "GBP");
		break;
	}
	case 'f':
	{
		attach(chf2usd, "CHF");
		break;
	}
	default:
	{
		cout
			<< "\n\n\tNone of currencies available for a conversion were chosen."
			<< "\n\tBetter luck next time."
			<< "\n\tBye."
			<< endl;
		return;
	}

	}
	cout
		<< "\n\n\t" << fixed << setprecision(2) << currencyCode << ' ' << value << " equals to USD " << result
		<< endl;
}

void multipleSwitchCases() {

	//Zbyszek
	//Czesiek
	//Rysiek
	//Marzena
	//Bożena
	//Grażyna

	char
		input{ ' ' };
	cin
		>> input;
	cout
		<< "\n\n\t";
	switch (input) {

		//doesn't work - adding a filter variable to the case (e.g. 'c':) causes multiple errors
		//err E0065 : expected a ';'
		//err C2143 : syntax error: missing ';' ':'
		//err C2059 : syntax error ':'

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

	//idea: implement switch using a hashcode of certain strings.
	//the problem tho: is it possible to set the case filtering value to be not hardcoded... ?

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

void squaresWhile() {
	int
		i{ 0 },
		max{ 0 };
	cin
		>> max;
	while (i < max)
		cout
		<< "\n\t" << ++i
		<< "\t" << i * i;
	cout
		<< endl;
}

void randomizeWhile() {

	auto drawACoin = [] {
		int
			counter{ 0 };
		bool
			flag = true;
		while (flag) {
			counter++;
			flag = rand() & 1;
		}
		cout
			<< "\n\t" << counter;
	};
	char
		again{ 'y' };

	while (again == 'y') {

		drawACoin();
		cout
			<< "\n\tagain ?\t(y/n)\t";
		cin
			>> again;
	}
	cout
		<< endl;
}

void printableCharsWhile() {
	int
		c = 32;
	while (++c < 256)
		cout << "\n\t" << (char)c << "\t" << (unsigned int)c;
	cout
		<< endl;
}

void randomYayWhile() {
	//while loop w/ the counter increment inside the sustain statement


	int
		i{ 0 };
	while (i++ < 100) {
		cout
			<< "\n\t"
			<< (rand() & 1) ? "yay" : "";
	}
	cout
		<< endl;
}

void printableCharsFor() {

	for (int i = 32; i < 256; ++i) {
		cout
			<< "\n\t" << (char)i
			<< "\t" << i;
	}
	cout
		<< endl;
}

void squareByAdding() {

	int
		in{ 0 },
		result{ 0 };
	cin
		>> in;
	for (int i = 0; i < in; ++i)
		result += in;
	cout
		<< "\n\t" << result
		<< endl;
}

void vectors() {

	vector<int> v{ 0, 1, 2, 3 };
	cout << "\n\tvector v: ";
	for (int i : v)
		cout << i << " , ";
	//cout << endl;

	//cout << ' , '; // this produces something strange : 2108448210844821084482108448

	vector <int> w(4);
	cout << "\n\tvector w: ";
	for (int i : w)
		cout << i << " , ";

	vector<int> u(5);
	cout << "\n\tvector u: ";
	for (int i = 0; i < u.size(); ++i) {
		u[i] = i;
		cout << (i > 0 ? " , " : "") << u[i];
	}

	//to be correctly initialized vector needs at least a stated size, even 0 works.
	vector<int> t(0);
	cout
		<< "\n\tvector t:"
		<< "\n\t\tsize = " << t.size()
		<< "\n\t\tlocation = " << &t;
	t.push_back(0);
	cout
		<< "\n\t\tsize = " << t.size()
		<< "\n\t\tlocation = " << &t;
	cout
		<< endl;
}

void vectorPushBackWithRangeForLoop() {

	vector<char> txt(16);
	for (char& c : txt) cin >> c;

	cout << "\n\t";
	for (char c : txt) cout << c;
	cout << endl;
}

void fillingVectorWithForLoop() {
	//declaration is enough to make the vector work.

	vector<double>dd;
	for (double input; cin >> input; ) dd.push_back(input);

	cout << "\n\n\t";
	for (double d : dd) cout << d << " , ";
	cout << endl;
}

void wordBucket() {
	vector<string> words;
	for (string input; cin >> input;) {
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		words.push_back(input);
	}
	cout << "\n\twordcounter:\t" << words.size() << endl;
	sort(words);
	for (int i = 1; i < words.size(); ++i) if (words[i] != words[i - 1]) cout << words[i] << ",\n";
	cout << endl;
}

void bleep() {

	vector<string>
		blackList{ "broccoli" };
	string
		input;
	while (cin >> input) {
		bool
			approved{ true };
		for (string listed : blackList)
			if (input == listed)
				approved = false;
		if (approved)
			cout << "\n\n\t" << input << endl;
	}
}

void drill01() {
	//Write a program that consists of a while-loop
	//that (each time around the loop) reads in two ints
	//and then prints them.
	//Exit the program when a terminating '|' is entered.

	int input1, input2;
	cout << "\n\t";
	while (cin >> input1 >> input2)	cout << input1 << " , " << input2 << "\n\t";
}

void drill02() {
	//make 01 printout the smaller value

	int input1, input2;
	cout << "\n\t";
	while (cin >> input1 >> input2)
		cout
		<< "\n\tthe smaller value is: " << min(input1, input2)
		<< "\n\tthe larger value is: " << max(input1, input2);

	cout << endl;
}

void drill03() {
	//make it respond to an equal values

	int
		input1,
		input2;
	cout
		<< "\n\t";
	while (cin >> input1 >> input2)
		if (input1 == input2)
			cout
			<< "\n\tnumbers are equal"
			<< endl;
		else cout
			<< "\n\tthe smaller value is: " << min(input1, input2)
			<< "\n\tthe larger value is: " << max(input1, input2)
			<< endl;
}

void drill04() {
	//change it to doubles

	double
		input1,
		input2;
	cout
		<< "\n\t";
	while (cin >> input1 >> input2)
		if (input1 == input2)
			cout
			<< "\n\tnumbers are equal"
			<< endl;
		else cout
			<< "\n\tthe smaller value is: " << min(input1, input2)
			<< "\n\tthe larger value is: " << max(input1, input2)
			<< endl;
}

void drill05() {
	//add the "almost equal" printout  for the non-equal case with a diff < 0.01

	double
		input1,
		input2;
	cout
		<< "\n\t";
	while (cin >> input1 >> input2)
		if (input1 == input2)
			cout
			<< "\n\tnumbers are equal"
			<< endl;
		else {
			cout
				<< "\n\tthe smaller value is: " << min(input1, input2)
				<< "\n\tthe larger value is: " << max(input1, input2)
				<< endl;
			if (abs(input1 - input2) < 0.01)
				cout
				<< "\n\tthe numbers are almost equal"
				<< endl;
		}
}

void drill06() {
	// make while write just one int each iteration; add min and max. report upon reaching either of 'em

	double
		minimum{ std::numeric_limits<double>::max() },
		maximum{ std::numeric_limits<double>::min() },
		input[2];
	bool
		switcher{ false };
	cout
		<< "\n\t";

	while (cin >> input[switcher]) {
		if (input[switcher] > maximum) {
			cout
				<< "\tis the largest value so far" << endl;
			maximum = input[switcher];
		}

		if (input[switcher] < minimum) {
			cout
				<< "\tis the smallest value so far" << endl;
			minimum = input[switcher];
		}

		if (switcher) {
			if (input[0] == input[1])
				cout
				<< "\n\tnumbers are equal"
				<< endl;
			else {
				cout
					<< "\n\tthe smaller value is: " << min(input[0], input[1])
					<< "\n\tthe larger value is: " << max(input[0], input[1])
					<< endl;
				if (abs(input[0] - input[1]) < 0.01)
					cout
					<< "\n\tthe numbers are almost equal"
					<< endl;
			}
		}
		switcher = !switcher;
	}
}

void drill07() {

	double
		minimum = numeric_limits<double>::max(),
		maximum = numeric_limits<double>::min(),
		values[2];
	bool switcher{ false };
	vector<string> unitCodeBook{ "cm", "in", "ft","m" };
	vector<double> unitConversionBook{ 1, 2.54, (2.54 * 12), 100. };
	string input;
	int	inputParseIndex, unitIndex;

	auto allowedUnit = [&]() -> bool {
		for (unitIndex = 0; unitIndex < unitCodeBook.size(); ++unitIndex)
			if (input.find(unitCodeBook[unitIndex]) < input.size())
				return true;
		return false;
	};
	while (cin >> input && allowedUnit()) {

		values[switcher] = stod(input) * unitConversionBook[unitIndex];

		if (values[switcher] < minimum) {
			minimum = values[switcher];
			cout << "\n\t" << values[switcher] << " is the smallest so far.";
		}
		if (values[switcher] > maximum) {
			maximum = values[switcher];
			cout << "\n\t" << values[switcher] << " is the largest so far.";
		}
		if (switcher) {
			if (values[0] == values[1]) cout << "\n\tlengths are equal.\n";
			else {
				cout << "\n\tthe smaller value is " << min(values[0], values[1]) << "\n\tthe larger values is " << max(values[0], values[1]);
				if (abs(values[0] - values[1]) < 0.01) cout << "\n\tthe values are almost equal.\n";
			}
		}
		switcher = !switcher;
	}
}

void drill09() {

	double
		minimum = numeric_limits<double>::max(),
		maximum = numeric_limits<double>::min(),
		values[3];
	bool switcher{ false };
	vector<string> unitCodeBook{ "cm", "in", "ft","m" };
	vector<double> unitConversionBook{ 1, 2.54, 2.54 * 12., 100. };
	vector<double>allValues{};
	string input;
	int	inputParseIndex, unitIndex;

	auto allowedUnit = [&]() -> bool {
		for (unitIndex = 0; unitIndex < unitCodeBook.size(); ++unitIndex)
			if (input.find(unitCodeBook[unitIndex]) < input.size())
				return true;
		return false;
	};
	while (cin >> input && allowedUnit()) {

		values[switcher] = (stod(input) * unitConversionBook[unitIndex]) / 100.;
		values[2] += values[switcher];
		allValues.push_back(values[switcher]);

		if (values[switcher] < minimum) {
			minimum = values[switcher];
			cout << "\n\t" << values[switcher] << " is the smallest so far.";
		}
		if (values[switcher] > maximum) {
			maximum = values[switcher];
			cout << "\n\t" << values[switcher] << " is the largest so far.";
		}
		if (switcher) {
			if (values[0] == values[1]) cout << "\n\tlengths are equal.\n";
			else {
				cout << "\n\tthe smaller value is " << min(values[0], values[1]) << "\n\tthe larger values is " << max(values[0], values[1]);
				if (abs(values[0] - values[1]) < 0.01) cout << "\n\tthe values are almost equal.\n";
			}
		}
		switcher = !switcher;
	}
	sort(allValues);
	cout
		<< "\n\tthe smallest value : " << minimum
		<< "\n\tthe largest value : " << maximum
		<< "\n\tThe sum of all values : " << values[2]
		<< "\n\tall entered values (sorted, and converted to meters):\n";
	for (double d : allValues)
		cout << "\n\t" << d;
	cout << "\n\n\tBye.\n";

}

void exc02() {

	vector<double>temps;
	for (double temp; cin >> temp;)	temps.push_back(temp);
	int length = temps.size();
	if (length == 0) return;
	sort(temps);
	cout << "\n\n\t";
	for (double t : temps) cout << t << " , ";

	cout << endl
		<< "\n\tmedian = "
		<< ((length & 1) ? (temps[length / 2]) : (temps[(length >> 1) - 1] + temps[length >> 1]) / 2.)
		<< endl;
}

void exc03() {

	int numberOfCities = 11;
	vector<double> distances;
	double maxDist = 1000.;
	uniform_real_distribution<double> unif(0., maxDist);
	default_random_engine re;

	for (int i = 1; i < numberOfCities; ++i)
		distances.push_back(unif(re));

	cout << endl;
	for (double d : distances) cout << d << " , ";
	cout << endl;

	sort(distances);
	cout << "\n\tthe smallest distance is " << distances[0];
	cout << "\n\tthe largest distance is  " << distances[distances.size() - 1];

	double average{ 0 };
	for (double d : distances) average += d;

	cout << "\n\taverage distances is " << average / distances.size() << endl;
}

void exc04() {

	int
		guess{ 50 },
		margin{ guess / 2 };
	cout
		<< "\n\n\tThink of a number between 0 and " << guess * 2 << endl;
	char
		answer{ ' ' };

	while (answer != '=' && margin > 0) {
		cout
			<< "\n\t if it's less than " << guess << " - enter '<',"
			<< "\n\t if t's more than " << guess << " - enter '>',"
			<< "\n\t and if it is " << guess << " - enter '='.\n";
		cin
			>> answer;

		if (answer == '<')
			guess -= margin;

		else if (answer == '>')
			guess += margin;

		if (margin > 1) margin /= 2;
	}

	if (answer != '=')
		cout
		<< "\n\n\tc'mon! You've cheated...";

	else {
		cout
			<< "\n\n\tSo, it was " << guess << " all along... Nice. Wanna play again ?"
			<< "\n\t('n' is nah, anything else is yay... almost)"
			<< endl;

		if (cin >> answer && answer != 'n')
			exc04();

		else
			return;
	}
}

void exc05() {

	cout << "\n\n\tenter value1, operation (+ - * / ), and value2 - all separated with spaces.\t";
	double
		value1{ 0 },
		value2{ 0 },
		result{ 0 };
	char
		operation{ ' ' };
	string
		s{ "+-:/*" },
		names[]{ "sum", "subtraction", "multiplication", "division", "division" };

	while (cin >> value1 >> operation >> value2 && s.find(operation) < s.size()) {

		switch (operation) {
		case '+':
			result = value1 + value2;
			break;
		case'-':
			result = value1 - value2;
			break;
		case'*':
			result = value1 * value2;
			break;
		case'/':;
		case':':
			result = value2 == 0 ? NAN : value1 / value2;
			break;
		default:
			cout << "\n\n\tsomething went wrong with the operation sign, start all over again unles You've enough - then ctrl-z will is the solution./n";
		}
		cout << "\n\n\t the " << names[s.find(operation)] << " of " << value1 << " and " << value2 << " is " << result << " .\n";
	}

}

void exc06() {

	vector<string> names{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	string input;

	auto findDigit = [&]() -> int {
		for (int i = 0; i < input.size(); ++i)
			if (input[i] >= '0' && input[i] <= '9')
				return input[i] - '0';
		return -1;
	};

	auto findName = [&]() ->int {
		for (int i = 0; i < names.size(); ++i)
			if (input.find(names[i]) < input.size())
				return i;
		return -1;
	};

	while (cin >> input) {

		int foundDigit = findDigit();
		if (foundDigit >= 0) cout << "\n\n\t" << names[foundDigit];

		int foundName = findName();
		if (foundName >= 0) cout << "\n\n\t" << foundName;
		cout << endl;
	}
}

void exc07() {

	vector<string> digits{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	string input1, input2;

	auto findDigit = [&](string input) -> int {
		for (int i = 0; i < input.size(); ++i)
			if (input[i] >= '0' && input[i] <= '9')
				return input[i] - '0';
		return -1;
	};
	auto findName = [&](string input) ->int {
		for (int i = 0; i < digits.size(); ++i)
			if (input.find(digits[i]) < input.size())
				return i;
		return -1;
	};
	auto decipher = [&](string input) -> int {

		int foundDigit = findDigit(input);
		if (foundDigit >= 0)
			return foundDigit;
		else {
			int foundName = findName(input);
			if (foundName >= 0)
				return foundName;
		}
		return 0;
	};

	int
		value1{ 0 },
		value2{ 0 },
		result{ 0 };
	char
		operation{ ' ' };
	string
		s{ "+-:/*" },
		names[]{ "sum", "subtraction", "multiplication", "division", "division" };

	while (cin >> input1 >> operation >> input2 && s.find(operation) < s.size()) {

		value1 = decipher(input1);
		value2 = decipher(input2);

		switch (operation) {
		case '+':
			result = value1 + value2;
			break;
		case'-':
			result = value1 - value2;
			break;
		case'*':
			result = value1 * value2;
			break;
		case'/':;
		case':':
			result = value2 == 0 ? NAN : value1 / value2;
			break;
		default:
			cout << "\n\n\tsomething went wrong with the operation sign, start all over again unles You've enough - then ctrl-z will is the solution./n";
		}
		cout << "\n\n\t the " << names[s.find(operation)] << " of " << value1 << " and " << value2 << " is " << result << " .\n";
	}
}

void exc08() {

	int
		aimValue{ 0 };
	cin >> aimValue;
	int i = 0;
	for (; (1 << i) < aimValue / 2.; ++i) cout << "\n\t" << (1 << i);
	cout << "\n\n\t" << i;
}

void exc09() {

	//	The amount of all grains from the chessboard would be: (2^65) - 1;
	//double would lack a single bit to represent the number;


	float
		grains = (ULLONG_MAX * 2.) - 1.;

	cout
		<< fixed << "\n\t" << grains
		<< scientific << "\n\t" << grains
		<< endl;

	// -------------------------------------

	//What  is  the  largest  number  of  squares  for  which  you can calculate the approximate number of grains(using a double)

	//start with a signed floating-point;
	//MSb = sign
	//7bits = base;
	//24LSBs = significand

	//significand is a proper part of a fraction (stuff after the '.')
	//so a significand is 1 + (1 - (2^-24)) = 2 - (1 / 16 ,777, 216)

	//base is a (2^7)-1 = 127
	//assuming that unsigned floating point adds sign bit to the base we'get

	//(2-(1/16777216))^255,
	//which is almost 2^255;
}

void exc10() {

	cout
		<< "\n\t~\tpaper"
		<< "\n\tx\tscissors"
		<< "\n\to\trock"
		<< "\n\t";
	char
		input;
	int
		player1{ 0 },
		player2{ 0 };
	vector<string> betNames{
		"rock",			// 0 : 0b00
		"paper",		// 1 : 0b01
		"scissors"		// 2 : 0b10
	};
	while (cin >> input) {

		player2 = (rand() % 3);

		//converting player input to int
		switch (input)
		{
		case 'o': player1 = 0; break;
		case '~': player1 = 1; break;
		case 'x': player1 = 2; break;
		case '8': cout << "Whoah! A shotgun! You win all the games!\n"; return;
		default:;
		}

		if (player1 == player2)
			cout << "\n\tIt's a draw.\n";

		else {
			bool
				whosBigger = (player1 > player2),
				result = abs(player1 - player2) & 1;	//the bigger bid wins with LSb = 1; the smaller bid otherwise
			cout
				<< ((whosBigger == result) ? "\n\tWow. You won against the " : "\n\tUgh. You lost against the ")
				<< betNames[player2] << "\n\t";
		}
	}
}

void exc11() {

	vector<int> primes{ 2 };

	auto isPrime = [&](int input) -> bool {

		for (int i = 0; i < primes.size() && primes[i] <= 1 + (input >> 1); ++i)
			if (input % primes[i] == 0)
				return false;
		return true;
	};

	int max;
	vector<string> wtf{ "\t", "\n\t" };

	while (cin >> max) {

		for (int i = 3; i <= max; ++i)
			if (isPrime(i)) primes.push_back(i);

		cout << "\n\t";
		for (int i = 0; i < primes.size(); ++i) cout << primes[i] << wtf[i % 10 == 9];
		cout << endl;
	}
}

void exc13() {

	int max{ 0 };

	while (cin >> max) {

		vector<int>primes{};								// list of results
		vector<char>candidates{ 0, 0 };						// list of candidates

		for (int i = 2; i < max; ++i)						// populate candidate list
			candidates.push_back(1);

		for (int i = 2; i < max; ++i) {						// traverse the candidates

			if (candidates[i]) {							// qualify candidate
				primes.push_back(i);						//add candidate to prime list

				for (int j = 2 * i; j <= max - i; j += i)
					candidates[j] = 0;						//disqualify all multiplications of a qualified candidate
			}
		}

		for (int prime : primes) cout << prime << " , ";
		cout << endl;
	}
}

void exc15() {

	int population, max;

	while (cin >> population) {
		if (population == 1) cout << "2 , \n";
		else {
			//computing the search range.
			{
				double temporal{ 1. + double(population) };
				max = int(ceil(1.2 * temporal * log(temporal)));
			}

			vector<int>primes{};								// list of results
			vector<char>candidates{ 0, 0 };						// list of candidates
			for (int i = 2; i < max; ++i)						// populate candidate list
				candidates.push_back(1);

			for (int i = 2; i < max && primes.size() < population; ++i) {						// traverse the candidates
				if (candidates[i]) {							// qualify candidate
					primes.push_back(i);						//add candidate to prime list

					for (int j = 2 * i; j <= max - i; j += i)
						candidates[j] = 0;						//disqualify all multiplications of a qualified candidate
				}
			}

			for (int prime : primes) cout << prime << " , ";
			cout << endl;
		}
	}
}

void exc16() {

	vector<int> series;
	int
		size{ 20 },
		range{ 10 };
	for (int i = 0; i < size; ++i)
		series.push_back(rand() % (range - 1));
	sort(series);

	struct mode {
		int element, appearances;
		mode(int element) {
			this->element = element;
			appearances = element < 0 ? -1 : 1;
		}
		mode& operator++(int) {
			appearances++;
			return *this;
		}
	};

	vector<mode> modes{ mode(-1) };

	for (int i : series) {
		int index = modes.size() - 1;
		mode& thisMode = (modes[index]);

		if (i == thisMode.element)
			thisMode++;
		else
			modes.push_back(mode(i));
	}

	mode& theMode{ modes[0] };
	for (mode m : modes) {
		if (m.appearances > theMode.appearances)
			theMode = m;
	}

	for (int i : series) cout << "\n\t" << i;
	cout << "\n\t";

	cout << "\n\t" << theMode.element << "/" << theMode.appearances;
	cout << endl;
}

void exc17() {

	int length{ 8 }, population{ 16 };
	//length = rand()% (length - 1);
	//population = (rand() % (population / 2)) + population / 2;

	vector<string> strings;

	// populating the strings vector
	for (int i = 0; (i < population); ++i) {
		string s{ "" };
		for (int j = 0; j < length; ++j) {
			char c = (rand() % ('z' - 'a')) + 'a';
			s += c;
		}
		cout << "\n\t" << s;
	}
	sort(strings);	
	cout << "\n\tmin " << strings[0] << "\t\tmax" << strings[strings.size() - 1] << endl;

	//...
}

void exc18() {

	double a, b, c;

	while (cin >> a >> b >> c) {

		double discriminant = (b * b) - 4 * a * c;

		cout << endl;
		switch ((discriminant > 0) - (discriminant < 0)) {

		case 1: {
			double root = sqrt(discriminant), denominator = a * 2;
			cout << "\n\t" << ((-b + root) / denominator);
			cout << "\t" << ((-b - root) / denominator) << endl;
			break;
		}
		case 0: {
			cout << "\n\t" << (-b / (a * 2)) << endl;
			break;
		}
		case -1:
			cout << "\n\t" << "no solutions in a real number domain" << endl;
		}
		cout << "\n\tagain ?\n";
	}

}

void exc19() {

	string name{ "" };
	int score;
	vector<string> names;
	vector<int> scores;

	auto nameIndex = [&]()-> int {
		for (int i = 0; i < names.size(); ++i)
			if (names[i] == name) return i;
		return -1;
	};
	auto breakPoint = [&]()->bool {	// has to pass the reference in order to stay up-to-date
		return (name == "NoName") && (score == 0);
	};

	//fill the vectors
	while (cin >> name >> score && !breakPoint()) {
		if (nameIndex() < 0) {
			names.push_back(name);
			scores.push_back(score);
		}
		else break;
	}

	//query
	string input{ "" };

	auto inputIsInt = [&] {
		for (char c : input)
			if (c < '0' || c > '9')
				return false;
		return true;
	};
	auto scoreIndex = [&]()-> int {
		for (int i = 0; i < scores.size(); ++i)
			if (scores[i] == score) return i;
		return -1;
	};

	while (cin >> input) {

		if (inputIsInt()) {
			score = stoi(input);
			int index = scoreIndex();

			//report a single score (prints the first on the list only), inform whether n/a 
			switch (index) {
			case -1:
				cout << "\n\tScore not found.\n";
				break;
			default:
				cout << "\t: " << names[index]<< endl;
			}

		}
		else {
			cout << "\n\t";
			name = input;
			int index = nameIndex();

			// report everybody and exit
			if (name == "get_all") {
				cout << endl;
				for (int i = 0; i < names.size(); ++i)
					cout << "\n\t" << names[i] << "\t: " << scores[i];
				cout << endl;
				return;
			}

			//report a single person, inform whether n/a 
			switch (index) {
			case -1:
				cout << "\n\tName not found.\n";
				break;
			default:
				cout << "\t: " << scores[index] << endl;
			}
		}





	}


	//query
	while (cin >> name) {

	}
}

void computation() {

	exc19();

}