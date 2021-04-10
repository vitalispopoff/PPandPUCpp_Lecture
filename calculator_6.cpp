#include "std_lib_facilities.h"

const char 
	number{'8'}, 
	quit{'q'}, 
	print{'='},
	name{'a'},
	let{'L'};
const string 
	prompt{"> "}, 
	result{"= "},
	declKey{"let"};

// Token ---------------------------------------

class Token
{
	public:

		char kind;
		double value;
		string name;

		//Token(char ch) : kind(ch), value(0) {}
		Token(char ch) : kind{ch} {}			// yet another way to implement a constructor, innit?
		//Token(char ch,double val) : kind(ch), value(val) {}
		Token(char ch, double val) : kind{ch}, value{val} {}
		Token(char ch, string n) : kind{ch}, name{n} {}
};

// Tokenstream ---------------------------------

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

Token_stream::Token_stream() : full(false), buffer(0) {}

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
			if(isalpha(ch))		// is ch a letter?
			{
				string s;
				s += ch;
				while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) //cin.get() - read the istream input into the get() input; doesn't skip ' ';
					s += ch;

				cin.putback(ch);
				//string s;
				//cin >> s;
				if(s == declKey)
					return Token{let};
				return Token{name, s};
			}
			error("Bad token");
	}
}

// Variable ------------------------------------

class Variable
{
	public:
		string name;
		double value;

		Variable(string n, double v)
		: name(n), value(v) {}
};

// global variables ----------------------------

Token_stream ts;
vector<Variable> var_table;

bool is_declared(string var)
{
	for(const Variable& v : var_table)
		if (v.name == var) return true;
	return false;
}

double define_name(string name, double value)
{
	if (is_declared(name)) 
		error(name, " declared twice");
	
	var_table.push_back(Variable(name, value));
}



double get_value(string s)
{
	for(const Variable& v : var_table)
		if(v.name == s)
			return v.value;
	error("get: undefined variable ",s);
}

void set_value(string s,double d)
{
	for(Variable& v : var_table)
		if(v.name == s)
		{
			v.value = d;
			return;
		}
	error("set: undefined variable ",s);
}

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

double declaration()
{
	Token 
		t = ts.get();
	if(t.kind != name)
		error("name expected in declaration");

	Token 
		t2 = ts.get();
	if(t2.kind != '=') 
		//error("= missing in declaration of ", var_name);
		error("= missing in declaration of ",name); // is it to be like this?

	double
		d = expression();
	define_name(var_name, d);

	return d;
}

double statement()
{
	Token
		t = ts.get();
	switch(t.kind)
	{
	case let:
		return declaration();
	default:
		ts.putback(t);
		return expression();

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
				//<< statement()
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
		define_name("pi", 3.1415926535);
		define_name("e", 2.7182818284);

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