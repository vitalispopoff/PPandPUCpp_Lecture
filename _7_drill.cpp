/*	
	7 : Drills
		1. get the code to compile

		2. comment the code /skipped
			Token_stream > Token_stream()
			Token_stream :: get() > switch > default > while
			Token_stram :: ignore() >

		3. fix the found errors / skipped

		4. prepare a set of inputs for testing
			1+1;	.
			1+1*0;	.
			(1);	.
			(1*0.5)/-0.1;	.
*/

#include "std_lib_facilities.h"

const char let = 'l';
const char name = 'a';
const char number = '8';
const char print = ';';
const char quit = 'Q';

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
	Token buffer;

	public:
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
	char ch;
	cin >> ch;
	switch(ch)
	{
		case '(': case ')':
		case '+': case '-':
		case '*': case '/': case '%':
		case ';': case '=':
		{
			return Token(ch);
		};
		case '.': case '0':
		case '1': case '2': case '3':
		case '4': case '5': case '6':
		case '7': case '8': case '9':
		{
			cin.unget();		// used in place of cin.putback()
			double val;
			cin >> val;
			return Token(number,val);
		};
		default:
		{
			if(isalpha(ch))		//testes whether ch is a letter
			{
				string s;
				s += ch;
				while(cin.get(ch) && (isalpha(ch) || isdigit(ch)))	//why while ?
					s = ch;
				cin.unget();
				if(s == "let") 
					return Token(let);
				if(s == "quit") 
					return Token(name);
				return Token(name,s);
			}
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
	for(int i = 0; i < names.size(); ++i)	// why not range for loop ?
		if(names[i].name == s)
			return names[i].value;
	error("get: undefined name ",s);
}

void set_value(string s,double d)
{
	for(int i = 0; i <= names.size(); ++i)	// why not range for loop ?
		if(names[i].name == s)
		{
			names[i].value = d;
			return;
		}
	error("set: undefined name ",s);
}

bool is_declared(string s)
{
	for(int i = 0; i < names.size(); ++i)	// why not range for loop ?
		if(names[i].name == s)
			return true;
	return false;
}

Token_stream ts;

double expression();

double primary()
{
	Token prim_t = 
		ts.get();
	switch(prim_t.kind)
	{
		case '(':
		{
			double prim_d = 
				expression();		// wy d is not used anywhere?
			prim_t = 
				ts.get();
			if(prim_t.kind != ')') 
				error("'(' expected"); 
			else 
				return prim_d;
		}
		case '-':
			return -primary();
		case number:
			return prim_t.value;	// why not ts.unget(prim_t) ?
		case name:
			return get_value(prim_t.tokenName);
		default:
			error("primary expected");
	}
}

double term()
{
	double term_left = 
		primary();
	while(true)
	{
		Token term_t = 
			ts.get();
		switch(term_t.kind)
		{
			case '*':
			{
				term_left *= 
					primary();
				break;
			}
			case '/':
			{
				double term_d = 
					primary();
				if(term_d == 0) 
					error("divide by zero");
				term_left /= term_d;
				break;
			}
			default:
			{
				ts.unget(term_t);
				return term_left;
			}
		}
	}
}

double expression()
{
	double expr_left = 
		term();
	while(true)
	{
		Token expr_t = 
			ts.get();
		switch(expr_t.kind)
		{
			case '+':
			{
				expr_left += 
					term();
				break;
			}
			case '-':
			{
				expr_left -= 
					term();
				break;
			}
			default:
			{
				ts.unget(expr_t);
				return expr_left;
			}
		}
	}
}

double declaration()
{
	Token decl_t = 
		ts.get();
	if(decl_t.kind != 'a') 
		error("name expected in declaration");
	string name = 
		decl_t.tokenName;
	if(is_declared(name)) 
		error(name," declared twice");
	Token decl_t2 = 
		ts.get();
	if(decl_t2.kind != '=') 
		error("= missing in declaration of ",name);
	double decl_d = 
		expression();
	names.push_back(
		Variable(name,decl_d));
	return decl_d;
}


double statement()
{
	Token stat_t = 
		ts.get();
	switch(stat_t.kind)
	{
		case let: 
			return declaration();
		default:
		{
			ts.unget(stat_t);
			return expression();
		}
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while(true) try
	{
		cout << prompt;
		Token calc_t = 
			ts.get();
		while(calc_t.kind == print)
			calc_t = 
				ts.get();
		if(calc_t.kind == quit) 
			return;
		ts.unget(calc_t);
		cout 
			<< result
			<< statement()		// this is where we jump to grammar lower levels
			<< endl;
	}
	catch(runtime_error &e)
	{
		cerr 
			<< e.what() 
			<< endl;
		clean_up_mess();
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
			<< "exception: " 
			<< e.what() 
			<< endl;
		char c;
		while(cin >> c && c != ';'){};
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