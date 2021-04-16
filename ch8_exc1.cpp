#include "std_lib_facilities.h"

/*
make the input stream an explicit paremeter
give the Token_stram constructor an istream& parameter

*/

struct Variable
{
	public:
	string name;
	double value;
	bool readOnly;

	Variable(string n,double v): name(n),value(v),readOnly(false) {}
	Variable(string n,double v,bool b): name(n),value(v),readOnly(b) {}
};



class SymbolTable
{
	private:
	vector<Variable> varTable;

	public:
	double get(string);
	void set(string,double,bool);
	bool isDeclared(string);
	void declare(Variable);
};

double SymbolTable::get(string s)
{
	for(const Variable &var : varTable)
		if(var.name == s)
			return var.value;
	error("undefined name for a variable: ",s);
}

void SymbolTable::set(string s,double d,bool b)
{
	for(Variable &var : varTable)
	{
		if(var.readOnly)
		{
			cout << "\n\tThis variable is read-only.\n";
			return;
		}
		var.value = d;
		var.readOnly = b;
		return;
	}
	error("Undefined name for a variable to set: ",s);
}

bool SymbolTable::isDeclared(string s)
{
	for(const Variable &var : varTable)
		if(var.name == s)
			return true;
	return false;
}

void SymbolTable::declare(Variable v)
{
	varTable.push_back(v);
}



const char let		{'L'};
const char name		{'a'};
const char number	{'8'};
const char print	{';'};
const char power	{'P'};
const char quit		{'Q'};
const char remember	{'#'};
const char root		{'R'};

struct Token
{
	public:
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
		Token buffer;
		istream& inputStream;

	public:
		Token_stream(): full{false}, buffer(0), inputStream(cin) {}

		istream& getInputStream();
		void unget(Token);
		Token get();
		void ignore(char);
};

istream& Token_stream::getInputStream()
{
	return inputStream;
}

void Token_stream::unget(Token t)
{
	this->buffer = t;
	this->full = true;
}

Token Token_stream::get()
{
	if(full)
	{
		this->full = false;
		return buffer;
	}
	char c;
	inputStream >> c;
	switch(c)
	{
		case '(':	case '+':	case '*':
		case ')':	case '-':	case '/':
		case '=':	case ';':	case '%':
		case '#':
			return Token(c);

		default:
		{
			if(c == '.' || isdigit(c))
			{
				inputStream.unget();
				double d;
				inputStream >> d;
				return Token(number,d);
			};

			if(c == '_' || isalpha(c))
			{
				string s;
				s += c;
				while(inputStream.get(c) && (isalpha(c) || isdigit(c) || c == '_'))					// this needs serious refactoring
					s += c;

				inputStream.unget();
				if(s == "let")
					return Token(let);

				if(s == "quit" || s == "exit")
					return Token(quit);

				if(s == "sqrt")
					return Token(root);

				if(s == "pow")
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

	if(c == buffer.kind)
		return;

	char input;
	while(inputStream >> input)
		if(input == c)
			return;
}



double expression(Token_stream &, SymbolTable &);

double primary(Token_stream &ts, SymbolTable &table)
{
	Token t = ts.get();

	switch(t.kind)
	{
		case '(':
		{
		double d //;
				= expression(ts, table);	//innit fix?
			//ts.getInputStream() >> d;
			t = ts.get();

			if(t.kind != ')')
				error("')' expected");
			else
				return d;
		}

		case '-':
			return -primary(ts, table);

		case number:
			return t.value;

		case root:
		{
			double d = primary(ts, table);

			if(d < 0)
				error("positive number for the root expected (imaginary numbers are not supported).");
			return sqrt(d);
		}

		case power:
		{
			t = ts.get();
			if(t.kind != '(')
				error("'(' expected");

			double d1 = expression(ts, table);
			t = ts.get();
			if(t.kind != ';')	// temporarily into ';'
				error("';' expected");

			double d2 = expression(ts, table);
			t = ts.get();
			if(t.kind != ')')
				error("')' expected");

			return pow(d1,d2);
		}

		case name:
			return table.get(t.tokenName);

		default:
			error("primary expected");
	}
}

double term(Token_stream &ts,SymbolTable &table)
{
	double d = primary(ts, table);
	while(true)
	{
		Token t = ts.get();
		switch(t.kind)
		{
			case '*':
				d *= primary(ts, table); break;

			case '/':
			{
				double denominator = primary(ts, table);
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

double expression(Token_stream &ts,SymbolTable &table)
{
	double d = term(ts, table);
	while(true)
	{
		Token t = ts.get();
		switch(t.kind)
		{
			case '+':
				d += term(ts, table); break;

			case '-':
				d -= term(ts, table); break;

			default:
			{
				ts.unget(t);
				return d;
			}
		}
	}
}

double declaration(Token_stream &ts,SymbolTable &table)
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
	if(table.isDeclared(name))
		error(name,messages[1]);

	Token t2 = ts.get();
	if(t2.kind != '=')
		error(messages[2],name);

	double d = expression(ts, table);
	Variable v = Variable(name,d);
	table.declare(v);
	return d;
}

double statement(Token_stream &ts,SymbolTable &table)
{
	Token t = ts.get();
	bool b{false};
	while(true)
		switch(t.kind)
		{
			case let:
				return declaration(ts,table);

			case remember:
			{
				t = ts.get();
				b = true;
			}

			case name:
			{
				char c;
				if(cin >> c && c == '=' && table.isDeclared(t.tokenName))
				{
					double d = expression(ts, table);
					table.set(t.tokenName,d,b);
					return table.get(t.tokenName);
				}
				ts.getInputStream().unget();
			}

			default:
			{
				ts.unget(t);
				return expression(ts, table);
			}
		};
}

const string prompt = "> ";
const string result = "= ";

void setConstants(SymbolTable &table)
{
	table.declare(Variable("pi",3.141592628,true));
}




void calculate(Token_stream ts,SymbolTable &table)
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
			<< result << statement(ts, table) << endl;
		ts.get();
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
		Token_stream ts;
		SymbolTable table;
		setConstants(table);
		calculate(ts, table);
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