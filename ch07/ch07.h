#pragma once

#include "../_add/std_lib_facilities.h"

namespace ch07
{
	void getHelp();

	struct Variable
	{
		public:
			string 
				name;
			double 
				value;
			bool 
				readOnly;
		
			Variable(string n, double v) 
				: name(n), value(v), readOnly(false) 
			{}
			Variable(string n, double v, bool b) 
				: name(n), value(v), readOnly(b) 
			{}
	};

	class SymbolTable
	{
		private:
			vector<Variable> 
				varTable;

		public:
			double get(string);
			void set(string, double, bool);
			bool isDeclared(string);
			void declare(Variable);
	};

	struct Token
	{
		public:
			char 
				kind;
			double 
				value {0.};
			string 
				tokenName;

			Token(char ch) 
				: kind(ch) 
			{}
			Token(char ch,double val) 
				: kind(ch), value(val) 
			{}
			Token(char ch,string s) 
				: kind(ch), value{0}, tokenName(s) 
			{}
	};

	class Token_stream
	{
		private:
			bool 
				full;
			Token 
				buffer;

		public:
			Token_stream() 
				: full{false}, buffer(0) 
			{}

			void unget(Token);
			Token get();
			void ignore(char);
	};

	double expression(Token_stream);

	double primary(Token_stream);

	double term(Token_stream);

	double expression(Token_stream);

	double declaration(Token_stream);

	double statement(Token_stream);

	void setConstants();

	void calculate(Token_stream);

	int calculatorMain();
}