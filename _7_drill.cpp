#include "std_lib_facilities.h"

/*
	exc 6

	write help section available at 'H' and 'h'


namespace _7_drill
{

	void getHelp()
	{
		cout
			<< "\n\t help: \n\t-------\n"
			<< "\n\tbasic operations:\t+\t-\t*\t/\t%/"
			<< "\n\tadvanced operations:\tsqrt(VALUE)\tpow(VALUE; VALUE)"
			<< "\n\texecution of expressions:\t;"
			<< "\n\tvariables: saving:\tlet NAME = VALUE\t\treading:\tNAME\n"
			<< "\n\tsaving variables as constants:\t# NAME = VALUE\t (this is permanent)\n"
			<< "\n\tquit\tquit\n";
	}

	struct Variable
	{
		public:
			string name;
			double value;
			bool readOnly;
		
			Variable(string n, double v) : name(n), value(v), readOnly(false) {}
			Variable(string n, double v, bool b) : name(n), value(v), readOnly(b) {}
	};



	class SymbolTable
	{
		private:
			vector<Variable> varTable;

		public:
			double get(string);
			void set(string, double, bool);
			bool isDeclared(string);
			void declare(Variable);
	};

	SymbolTable table;

	double SymbolTable::get(string s)
	{
		for (Variable var : varTable)
			if (var.name == s)
				return var.value;
		error("undefined name for a variable: ", s);
	}

	void SymbolTable::set(string s, double d, bool b)
	{
		for (Variable &var : varTable)
		{
			if (var.readOnly)
				cout << "\n\tThis variable is read-only.\n";
			else
			{
				var.value = d;
				var.readOnly = b;
			}
			return;
		}
		error("Undefined name for a variable to set: ", s);
	}

	bool SymbolTable::isDeclared(string s)
	{
		for (Variable var : varTable)
			if (var.name == s)
				return true;
		return false;
	}

	void SymbolTable::declare(Variable v)
	{
		varTable.push_back(v);
	}



	//const char help		{'H'};
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

	Token_stream ts;

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
			case '#'	:
				return Token(c);

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

					if (s == "h" || s == "H" || "help")
					{
						getHelp();
						return ts.get();
					}

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




	double expression();

	double primary(Token_stream ts)
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
				
			case '-':
				return -primary(ts);

			case number:
				return t.value;

			case root:
			{
				double d = primary(ts);

				if(d < 0)
					error("positive number for the root expected (imaginary numbers are not supported).");
				return sqrt(d);
			}

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

			case name:
				return table.get(t.tokenName);

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
					d *= primary(); break;

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
		if (table.isDeclared(name))
			error(name, messages[1]);

		Token t2 = ts.get();
		if(t2.kind != '=')
			error(messages[2], name);

		double d = expression();
		Variable v = Variable(name, d);
		table.declare(v);
		return d;	 
	}

	double statement()
	{
		Token t = ts.get();
		bool b {false};
		while(true)
			switch(t.kind)
			{

				case let :		
					return declaration();

				case remember :
				{
					t = ts.get();
					b = true;
				}

				case name :
				{
					char c;
					if(cin >> c && c == '=' && table.isDeclared(t.tokenName))
					{
						double d = expression();
						table.set(t.tokenName, d, b);
						return table.get(t.tokenName);
					}
					cin.unget();
				}


				default:
				{
					ts.unget(t);
					return expression();
				}
			};
	}

	const string prompt = "> ";
	const string result = "= ";

	void setConstants()
	{
		table.declare(Variable("pi",3.141592628,true));
	}




	void calculate()
	{
		setConstants();	
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

}
*/