#include "std_lib_facilities.h"

const char
number{'8'},
quit{'q'},
print{'='};

const string
prompt{"> "},
result{"= "};

class Token
{
public:

	char kind;
	double value;

	Token(char ch)
		: kind(ch),value(0) { }

	Token(char ch,double val)
		: kind(ch),value(val) {}
};

class Token_stream
{
private:
	bool
		full{false};
	Token
		buffer;
public:
	Token_stream();

	void putback(Token t);
	void ignore(char c);
	Token get();
};

Token_stream::Token_stream()
	:full(false),buffer(0) {}

void Token_stream::putback(Token t)
{
	if(full)
		error("putback() into a full buffer");

	buffer = t;
	full = true;
}

void Token_stream::ignore(char c)				// "c represents the kind of token"
{
	if(full && c == buffer.kind)				// "first look in buffer"
	{
		full = false;
		return;
	}

	full = false;
	char ch = 0;

	while(cin >> ch)
		if(ch == c)
			return;
}

Token Token_stream::get() 						// using cin in this implementation already falsifies main>while(cin) to true.
{
	if(full)
	{
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;

	switch(ch)
	{
	case quit:
	case print:

	case '{': case '}':
	case '(': case ')':

	case '+': case '-':
	case '*': case '/':
	case '%':
	{
		return Token(ch);
	}

	case '.': case '0':
	case '1': case '2': case '3':
	case '4': case '5': case '6':
	case '7': case '8': case '9':
	{
		cin.putback(ch);

		double val;

		cin >> val;
		return Token(number,val);
	}

	default:
		error("Bad token");
	}
}

Token_stream ts;

double expression();

double primary()
{
	Token
		t = ts.get();

	switch(t.kind)
	{

	case '{':
	{
		double
			d = expression();

		t = ts.get();

		if(t.kind != '}')
			error("'}' expected");

		return d;
	}

	case '(':
	{
		double
			d = expression();

		t = ts.get();

		if(t.kind != ')')
			error("')' expected");

		return d;
	}

	case number:
		return t.value;

	case'-':
		return -primary();

	case'+':
		return primary();

	default:
		error("primary expected");
	}
}

double term()
{
	double
		left = primary();
	Token
		t = ts.get();

	while(true)
	{
		switch(t.kind)
		{
		case '*':
		{
			left *= primary();
			t = ts.get();
			break;
		}

		case '/':
		{
			double
				d = primary();

			if(d == 0)
				error("divide by zero");

			left /= d;
			t = ts.get();
			break;
		}

		case '%':
		{
			double
				d = primary();

			if(d == 0)
				error("divide by zero");

			left = fmod(left,d);
			t = ts.get();
			break;
		}

		default:
		{
			ts.putback(t);
			return left;
		}
		}
	}
}

double expression()
{
	double
		left = term();
	Token
		t = ts.get();

	while(true)
	{
		switch(t.kind)
		{
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

void clean_up_mess()
{
	ts.ignore(print);
}

void calculate()
{
	while(cin){
		try
		{
			cout 
				<< prompt;
			Token
				t = ts.get();

			while(t.kind == print)
				t = ts.get();

			if(t.kind == quit)
				return;

			ts.putback(t);

			cout
				<< result
				<< expression()
				<< endl;
		}
		catch(exception& e)
		{
			cerr 
				<< e.what() 
				<< endl;

			clean_up_mess();
		}
	}
}

int calculatorMain() {
	try {
		calculate();
		keep_window_open();
		return 0;
	}
	catch(exception& e) 
	{
		cerr 
			<< "error: " 
			<< e.what() 
			<< endl;

		keep_window_open();
		return 1;
	}
	catch(...) 
	{
		cerr 
			<< "Oops: unknown exception!\n";

		keep_window_open();
		return 2;
	}
}