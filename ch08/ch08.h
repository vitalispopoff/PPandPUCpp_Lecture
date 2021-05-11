#pragma once

namespace ch08
{
	namespace drill
	{
		namespace d02
		{
			void swap_v(int, int);

			void swap_r(int &, int &);

			//void swap_v(const int &, const int & );

			void d02_main();
		}

		namespace d03
		{
			void d03_main();
		}
	}

	namespace excercise
	{
		namespace e01
		{
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
		
			const char 
				let			{'L'},
				name		{'a'},
				number		{'8'},
				print		{';'},
				power		{'P'},
				quit		{'Q'},
				remember	{'#'},
				root		{'R'};
		
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
					Token(char ch, double val)
						: kind(ch), value(val) 
					{}
					Token(char ch, string s)
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
					istream 
						& inputStream;
		
				public:
					Token_stream()
						: full{false}, buffer(0), inputStream(cin)
						{}
		
					istream & getInputStream();
					void unget(Token);
					Token get();
					void ignore(char);
			};
		
			const string 
				prompt = "> ",
				result = "= ";
		
		
			double primary(Token_stream &, SymbolTable &);
		
			double term(Token_stream &, SymbolTable &);
		
			double	expression(Token_stream &, SymbolTable &);
			
			double declaration(Token_stream &, SymbolTable &);
		
			double statement(Token_stream &, SymbolTable &);
		}

		namespace e02
		{
			void print(const vector<int> &, string);
		}

		namespace e03
		{
			vector<int> fibonacci(int, int, vector<int> &, int);
		
			void e03_main();
		}

		namespace e04
		{
			vector<int> rangedFibonacci(int, int, vector<int> &, int);
		
			void e04_main();
		}

		namespace e05
		{
			vector<int>getSwappedVector(vector<int>);
		
			void vectorSwap(vector<int> &);
		
			void e05_main();
		}

		namespace e06
		{
			void print(const vector<string> &, string);
		
			vector<string>getSwappedStrings(vector<string>);
		
			void stringSwap(vector<string> &);
		
			string generateString();
		
			void e06_main();
		}

		namespace e07
		{
			void listUsers(const vector<string> &, const vector<int> &);
		
			void e07_main();
		}

		namespace e09
		{
			void print(const vector<double> &, string);
		
			double generatePrice();
		
			double generateWeight();
		
			void e09_main();
		}

		namespace e10
		{
			double maxV(vector<double>);
		
			void e10_main();
		}

		namespace e11
		{
			struct Statistics
			{
				double
					minimum {NAN},
					maximum {NAN},
					mean {NAN},
					median{NAN};
		
					void print();		
			};
		
			vector<int> generateIntVector(int length);
		
			Statistics getStatistics(vector<int>);
		
			void e11_main();
		}

		namespace e12
		{
			void print_until_s(const vector<string> &, string);
			
			void print_until(const vector<string> &, string, int);
		
			void e12_main();
		}

		namespace e13				
		{
			void firstAndLast(vector<string>);
		
			void shortestAndLongest(const vector<string>);
		
			vector<int> & countLetters(const vector<string &>);
		
			void e13_main();
		}	 
	}
}