#include "std_lib_facilities.h"

class Token {
public:
	char kind;
	double value;
	Token(char ch)
		: kind(ch), value(0) { }
	Token(char ch, double val)
		: kind(ch), value(val) {}
};

class Token_stream {
private:
	bool full{ false };
	Token buffer;
public:
	Token_stream();
	Token get();
	void putback(Token t);
};

Token_stream::Token_stream()
	:full(false), buffer(0) {}

void Token_stream::putback(Token t) {
	if (full)
		error("putback() into a full buffer");
	buffer = t;
	full = true;
}

Token Token_stream::get() {	// using cin in this implementation already falsifies main>while(cin) to true.
	if (full) {
		full = false;
		return buffer;
	}
	char ch;
	cin >> ch;
	switch (ch) {
	case 'x': case '=': case '!': case '{': case '}': case '(': case ')':
		return Token(ch);
	case '+': case '-':
		return Token(ch);
	case '*': case '/':
		return Token(ch);
	case '.': case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
		cin.putback(ch);
		double val;
		cin >> val;
		return Token('8', val);
	}
	default: error("Bad token");
	}
}

Token_stream ts;

double expression();

double primary() {
	Token
		t = ts.get();
	switch (t.kind) {
	case '{': {
		double
			d = expression();
		t = ts.get();
		if (t.kind != '}')
			error("'}' expected");
		return d;
	}
	case '(': {
		double
			d = expression();
		t = ts.get();
		if (t.kind != ')')
			error("')' expected");
		return d;
	}
	case '8':
		return t.value;
	default:
		error("primary expected");
	}
}

double term() {
	double
		left = primary();
	Token
		t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/': {
			double
				d = primary();
			if (d == 0)
				error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression() {
	double
		left = term();
	Token
		t = ts.get();
	while (true) {
		switch (t.kind) {
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left += term();
			t = ts.get();
			break;
		default:
			t.value = left;
			ts.putback(t);
			return left;
		}
	}
}

int calculatorMain() {
	try {

		/*cout
			<< "\n\tWelcome to our simple calculator"
			<< "\n\tPlease enter expressions using floating-point numbers."
			<< "\n\t----------------------------------------------------"
			<< "\n\t use signs for respective operations:\n"
			<< "\n\t\t+\taddition"
			<< "\n\t\t-\tsubtraction"
			<< "\n\t\t*\tmultiplication"
			<< "\n\t\t/\tdivision (remeber to avoid dividing by 0.0)"
			<< "\n\tand\t=\tfor a result."
			<< "\n\tUse\tx\t to exit."
			<< "\n\t----------------------------------------------------"
			<< "\n\tAfter each element of the expression hit enter."
			<< endl;*/

		while (cin) {
			Token
				t = ts.get();
			if (t.kind == 'x')
				return 0;
			if (t.kind == '=')
				cout << "=" << t.value << '\n';
			else
				ts.putback(t);
			t.value = expression();
		}
		keep_window_open();
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (...) {
		cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2;
	}
}