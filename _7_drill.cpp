#include "std_lib_facilities.h"

const char let = 'L';
const char name = 'a';
const char number = '8';
const char print = ';';
const char quit = 'Q';
const char squareRoot = 'R';
const char power = 'P';

struct Token
{
	char kind;
	double value{0.};
	string tokenName;

	Token(char ch): kind(ch) {}
	Token(char ch,double val): kind(ch),value(val) {}
	Token(char ch,string s): kind(ch),value{0},tokenName(s) {}
};

class Token_stream
{
	private:
	bool full;

	public:
	Token buffer;
	Token_stream(): full{false},buffer(0) {}	// what does buffer(0) actually do? how does it initialize?

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
	switch(c)
	{
		case '(': case ')':
		case '+': case '-':
		case '*': case '/': case '%':
		case ';': case '=':
		{
			return Token(c);
		};

		//case '.': case '0':
		//case '1': case '2': case '3':
		//case '4': case '5': case '6':
		//case '7': case '8': case '9':
		//{
			//cin.unget();
			//double d;
			//cin >> d;
			//return Token(number,d);
		//};

		case '#':
			return Token(let);
		
		default:
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
				while(cin.get(c) && (isalpha(c) || isdigit(c) || c == '_'))
					s += c;
				
				cin.unget();
				if(s == "let")
					return Token(let);

				if(s == "quit" || s == "exit")
					return Token(quit);

				if(s == "sqrt")
					return Token(squareRoot);

				if(s == "pow")
					return Token(power);

				return Token(name,s);
			};

			error("Bad token");
		}
	}
}

void Token_stream::ignore(char c)
{
	if(full && c == buffer.kind)	// why c == buffer.kind ?
	{
		full = false;
		return;
	}
	full = false;
	char ch;
	while(cin >> ch)
		if(ch == c)		// what happens when ch != c ?
			return;
}

struct Variable
{
	string name;
	double value;
	Variable(string n,double v): name(n),value(v) {}
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
			double prim_d =
				expression();		// wy d is not used anywhere?
			t =
				ts.get();
			if(t.kind != ')')
				error("'(' expected");
			else
				return prim_d;
		}
		case squareRoot:
		{
			double prim_d =
				primary();
			if(prim_d < 0)
				error("positive number for the root expected (imaginary numbers are not supported).");
			return sqrt(prim_d);
		}
		case '-':
			return -primary();
		case number:
			return t.value;
		case name:
			return get_value(t.tokenName);
		case power:
		{
			char c;
			if(cin >> c && c == '(')
			{
				double prim_d;
				cin >> prim_d;
				if(cin >> c && c == ',')
				{
					int i;
					cin >> i;
					if(cin >> c && c == ')')
						return performPower(prim_d,i);
				}
				error("something's wrong with your power");
			}
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
		Token t =
			ts.get();
		switch(t.kind)
		{
			case '*':
			{
				d *= primary(); break;
			}			

			case '/':
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
	Token token = ts.get();
	if(token.kind != 'a')
		error("name expected in declaration");

	string name = token.tokenName;
	if(is_declared(name))
		error(name," declared twice");

	Token token2 = ts.get();
	if(token2.kind != '=')
		error("= missing in declaration of ",name);

	double d = expression();
	names.push_back(
		Variable(name,d));
	return d;
}


double statement()
{
	Token stat_t = ts.get();
	switch(stat_t.kind)
	{
		case let:
			return declaration();
		case name:
		{
			char c;
			if(cin >> c && c == '=' && is_declared(stat_t.tokenName))
			{
				double d = expression();
				set_value(stat_t.tokenName,d);
				return get_value(stat_t.tokenName);
			}
			cin.unget();
		}
		default:
		{
			ts.unget(stat_t);
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
		Token calc_t = ts.get();

		while(calc_t.kind == print)
			calc_t = ts.get();

		if(calc_t.kind == quit)
			return;

		ts.unget(calc_t);
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