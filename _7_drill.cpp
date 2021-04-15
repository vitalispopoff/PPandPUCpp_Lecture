#include "std_lib_facilities.h"



struct Variable
{
	public:
		string name;
		double value;
		
		Variable(string n,double v) : name(n), value(v) {}
};

vector<Variable> names;

double get_value(string s)
{
	for(Variable var : names)
		if(var.name == s)
			return var.value;

	error("get: undefined name ",s);
}

void set_value(string s,double d)
{
	for(Variable &var : names)
		if(var.name == s)
		{
			var.value = d;
			return;
		}
	error("set: undefined name ",s);
}

bool is_declared(string s)
{
	for(Variable var : names)
		if(var.name == s)
			return true;
	return false;
}



const char let		{'L'};
const char name		{'a'};
const char number	{'8'};
const char print	{';'};
const char quit		{'Q'};
const char root		{'R'};
const char power	{'P'};

struct Token
{
	public:
		char kind;
		double value {0.};
		string tokenName;

		Token(char ch) : kind(ch) {}
		Token(char ch,double val) : kind(ch), value(val) {}
		Token(char ch,string s) : kind(ch), value{0}, tokenName(s) {}
};

class Token_stream
{
	private:
		bool full;
		Token buffer;

	public:
		Token_stream() : full{false}, buffer(0) {}

		void unget(Token);
		Token get();
		void ignore(char);
};

void Token_stream::unget(Token t)
{
	buffer = t;
	full = true;
}

Token Token_stream::get()
{
	if(full)
	{
		full = false;
		return buffer;
	}
	char c;
	cin >> c;
	switch (c)
	{
		case '('	:	case '+'	:	case '*'	:
		case ')'	:	case '-'	:	case '/'	:
		case '='	:	case ';'	:	case '%'	:
		{
			return Token(c);
		};

		case '#' :
			return Token(let);
		
		default	:
		{
			if (c == '.' || isdigit(c))
			{
				cin.unget();
				double d;
				cin >> d;

				return Token(number,d);
			};

			if (c == '_' || isalpha(c))
			{
				string s;
				s += c;
				while (cin.get(c) && (isalpha(c) || isdigit(c) || c == '_'))	// this needs serious refactoring
					s += c;
				
				
				cin.unget();
				if (s == "let")
					return Token(let);

				if (s == "quit" || s == "exit")
					return Token(quit);

				if (s == "sqrt")
					return Token(root);

				if (s == "pow")
					return Token(power);

				return Token(name,s);
			};

			error("Bad token: ");
		}
	}
}

void Token_stream::ignore(char c)
{
	full = false;

	if (c== buffer.kind)
		return;

	char input;

	while(cin >> input)
		if (input == c)		
			return;
}

Token_stream ts;



double expression();

double performPower(double d,int i)
{
	if(i == 0)
		return 1;

	double result = 1;
	
	for(; i > 0 ; --i)
		result *= d;
	
	return result;
}

double primary()
{
	Token t = ts.get();

	switch(t.kind)
	{
		case '(':
		{
			double d;
			cin>>d;
			t = ts.get();

			if(t.kind != ')')
				error("')' expected");
			else
				return d;
		}
		case root:
		{
			double d =
				primary();

			if(d < 0)
				error("positive number for the root expected (imaginary numbers are not supported).");

			return sqrt(d);
		}
		case '-':
			return -primary();

		case number:
			return t.value;

		case name:
			return get_value(t.tokenName);

		case power:
		{
			t = ts.get();
			if(t.kind != '(')
				error("'(' expected");
				
			double d1 = expression();
			t = ts.get();
			if(t.kind != ';')	// temporarily into ';'
				error("';' expected");

			double d2 = expression();
			t = ts.get();
			if(t.kind != ')')
				error("')' expected");
			
			return pow(d1, d2);
		}

		default:
			error("primary expected");
	}
}

double term()
{
	double d = primary();
	while(true)
	{
		Token t = ts.get();

		switch(t.kind)
		{
			case '*' :
			{
				d *= primary(); 
				break;
			}

			case '/' :
			{
				double denominator = primary();

				if(denominator == 0)
					error("divide by zero");

				d /= denominator;
				break;
			}

			default:
			{
				ts.unget(t);
				return d;
			}
		}
	}
}

double expression()
{
	double d = term();

	while(true)
	{
		Token t = ts.get();

		switch(t.kind)
		{
			case '+':
				d += term(); break;

			case '-':
				d -= term(); break;

			default:
			{
				ts.unget(t);
				return d;
			}
		}
	}
}

double declaration()
{
	vector<string>messages{
		"name expected in declaration",
		" declared twice",
		"= missing in declaration of ",
	};
	Token t1 = ts.get();

	if(t1.kind != 'a')
		error(messages[0]);

	string name = t1.tokenName;

	if(is_declared(name))
		error(name, messages[1]);

	Token t2 = ts.get();

	if(t2.kind != '=')
		error(messages[2], name);

	double d = expression();

	names.push_back(Variable(name, d));
	return d;
}


double statement()
{
	Token t = ts.get();
	switch(t.kind)
	{
		case let:
			return declaration();

		case name:
		{
			char c;
			if(cin >> c && c == '=' && is_declared(t.tokenName))
			{
				double d = expression();
				set_value(t.tokenName,d);
				return get_value(t.tokenName);
			}
			cin.unget();
		}
		default:
		{
			ts.unget(t);
			return expression();
		}
	}
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while(true)
		try
	{
		cout << prompt;
		Token t = ts.get();

		while(t.kind == print)
			t = ts.get();

		if(t.kind == quit)
			return;

		ts.unget(t);
		cout
			<< result << statement() << endl;
	}
	catch(runtime_error &e)
	{
		cerr
			<< e.what() << endl;
		ts.ignore(print);
	}
}

int calculatorMain()
{
	try
	{
		calculate();
		return 0;
	}
	catch(exception &e)
	{
		cerr
			<< "exception: " << e.what() << endl;
		char c;
		while(cin >> c && c != ';') {};

		return 1;
	}
	catch(...)
	{
		cerr
			<< "exception\n";
		char c;
		while(cin >> c && c != ';') {};

		return 2;
	}
}