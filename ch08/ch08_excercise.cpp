#include "../_add/std_lib_facilities.h"
#include "ch08.h"

namespace ch08
{
	namespace excercise
	{
		namespace e01
		{
			//make the input stream an explicit paremeter
			//give the Token_stram constructor an istream& parameter
		
			double SymbolTable::get(string s)
			{
				for(const Variable & var : varTable)
					if(var.name == s)
						return var.value;
				error("undefined name for a variable: ",s);
				return 0;
			}
		
			void SymbolTable::set(string s, double d, bool b)
			{
				for(Variable & var : varTable)
				{
					if(var.readOnly)
					{
						cout 
							<< "\n\tThis variable is read-only.\n";
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
				for(const Variable & var : varTable)
					if(var.name == s)
						return true;
				return false;
			}
		
			void SymbolTable::declare(Variable v)
			{
				varTable.push_back(v);
			}
		
		
		
			istream & Token_stream::getInputStream()
			{
				return inputStream;
			}
		
			void Token_stream::unget(Token t)
			{
				this -> buffer = t;
				this -> full = true;
			}
		
			Token Token_stream::get()
			{
				if(full)
				{
					this -> full = false;
					return buffer;
				}
				char 
					c;
				inputStream 
					>> c;
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
							double 
								d;
							inputStream 
								>> d;
							return Token(number, d);
						};
		
						if(c == '_' || isalpha(c))
						{
							string 
								s;
							s += c;
							while(inputStream.get(c) && (isalpha(c) || isdigit(c) || c == '_'))					// this needs serious refactoring
								s += c;
		
							inputStream.unget();
							if (s == "let")
								return Token(let);
		
							if (s == "quit" || s == "exit")
								return Token(quit);
		
							if (s == "sqrt")
								return Token(root);
		
							if (s == "pow")
								return Token(power);
		
							return Token(name, s);
						};
						error("Bad token: ");
						return Token(' ');
					}
				}
			}
		
			void Token_stream::ignore(char c)
			{
				full = false;
				if (c == buffer.kind)
					return;
				char 
					input;
				while(inputStream >> input)
					if (input == c)
						return;
			}
		
		
		
			double primary(Token_stream & ts, SymbolTable & table)
			{
				Token 
					t = ts.get();
				switch(t.kind)
				{
					case '(':
					{
						double 
							d = expression(ts, table);	//innit fix?
						t = ts.get();
						if (t.kind != ')')
							error("')' expected");
						else return d;
					}
		
					case '-':
						return -primary(ts, table);
		
					case number:
						return t.value;
		
					case root:
					{
						double 
							d = primary(ts, table);
						if (d < 0)
							error("positive number for the root expected (imaginary numbers are not supported).");
						return sqrt(d);
					}
		
					case power:
					{
						t = ts.get();
						if (t.kind != '(')
							error("'(' expected");
		
						double 
							d1 = expression(ts, table);
						t = ts.get();
						if (t.kind != ';')	// temporarily into ';'
							error("';' expected");
		
						double 
							d2 = expression(ts, table);
						t = ts.get();
						if (t.kind != ')')
							error("')' expected");
		
						return pow(d1,d2);
					}
		
					case name:
						return table.get(t.tokenName);
		
					default:
						error("primary expected");
						return 0;
				}
			}
		
			double term(Token_stream & ts, SymbolTable & table)
			{
				double 
					d = primary(ts, table);
				while (true)
				{
					Token 
						t = ts.get();
					switch (t.kind)
					{
						case '*':
						{
							d *= primary(ts, table); 
							break;
						}
						case '/':
						{
							double 
								denominator = primary(ts, table);
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
		
			double expression(Token_stream & ts,SymbolTable & table)
			{
				double 
					d = term(ts, table);
				while (true)
				{
					Token
						t = ts.get();
					switch (t.kind)
					{
						case '+':
						{
							d += term(ts, table); 
							break;
						}
						case '-':
						{
							d -= term(ts, table); 
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
		
			double declaration(Token_stream & ts,SymbolTable & table)
			{
				vector<string>
					messages
					{
						"name expected in declaration",
						" declared twice",
						"= missing in declaration of ",
					};
				Token 
					t1 = ts.get();
		
				if (t1.kind != 'a')
					error(messages[0]);
				string 
					name = t1.tokenName;
		
				if (table.isDeclared(name))
					error(name,messages[1]);
				Token 
					t2 = ts.get();
		
				if (t2.kind != '=')
					error(messages[2],name);
				double 
					d = expression(ts, table);
				Variable 
					v = Variable(name,d);
				table.declare(v);
		
				return d;
			}
		
			double statement(Token_stream & ts,SymbolTable & table)
			{
				Token 
					t = ts.get();
				bool 
					b {false};
				while (true)
				{
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
							char 
								c;
							if(cin >> c && c == '=' && table.isDeclared(t.tokenName))
							{
								double 
									d = expression(ts, table);
								table.set(t.tokenName, d, b);
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
			}
		
		
		
			void setConstants(SymbolTable & table)
			{
				table.declare(Variable("pi", 3.141592628, true));
			}
		
			void calculate(Token_stream ts, SymbolTable & table)
			{
				while (true)
				{
					try
					{
						cout 
							<< prompt;
						Token 
							t = ts.get();
						while (t.kind == print)
							t = ts.get();
		
						if (t.kind == quit)
							return;
		
						ts.unget(t);
						cout
							<< result 
							<< statement(ts, table) 
							<< endl;
						ts.get();
					}
					catch (runtime_error & e)
					{
						cerr
							<< e.what() 
							<< endl;
						ts.ignore(print);
					}
				}
			}
		
			int calculatorMain()
			{
				try
				{
					Token_stream 
						ts;
					SymbolTable 
						table;
					setConstants(table);
					calculate(ts, table);
					return 0;
				}
				catch (exception & e)
				{
					cerr
						<< "exception: " 
						<< e.what() 
						<< endl;
					char 
						c;
					while(cin >> c && c != ';') 
					{};
					return 1;
				}
				catch (...)
				{
					cerr
						<< "exception\n";
					char 
						c;
					while (cin >> c && c != ';') 
					{};
					return 2;
				}
			}
		}

		const string 
			lineBreak{"\n\t"};

		namespace e02
		{
			void print(const vector<int> &fibonacciValues, string fibonacciName)
			{
				cout 
					<< lineBreak 
					<< fibonacciName 
					<< ';' 
					<< lineBreak;
				int 
					counter {0};	
				for (const int &value : fibonacciValues)
					cout 
						<< value
						<< (counter++ % 5 == 4 ? lineBreak : ", ");
				cout 
					<< endl;
			}
		}

		namespace e03
		{
			vector<int> fibonacci(int x, int y,vector<int> &v, int n)
			{
				// x, y - two consecutive values of the fibonacci sequence to start work with
				// v - vector to store the sequence
				// n - number of values to add to the sequence	
				v.push_back(x);
				v.push_back(y);
				int 
					z{0};
				for(int i = 0; i < n; ++i)
				{
					z = x + y;
					v.push_back(z);
					x = y;
					y = z;
				}
				return v;
			}
		
			void e03_main()
			{
				using e02::print;
		
				int 
					length = 43;
				vector<int> 
					v;
				fibonacci(0, 1, v, length);
				stringstream 
					ss;
				ss 
					<< "fibo(" 
					<< length 
					<< "): " ;
				string 
					s;
				ss 
					>> s;
				print(v, s);
			}
		}

		namespace ch04
		{
			using e02::print;
		
			vector<int> rangedFibonacci(int x, int y, vector<int> &v, int range)
			{
				v.push_back(x);
				v.push_back(y);
				int
					z{0};
				while(z <= range - y)
				{
					z = x + y;
					v.push_back(z);
					x = y;
					y = z;
				}
				return v;		
			}
		
			void e04_main()
			{
				vector<int>
					v;
				rangedFibonacci(0,1,v,INT_MAX);
				cout
					<< "\n\t"
					<< v.size()
					<< endl;
				print(v,"full fibonacci");
			}
		}

		namespace ch05
		{
			using e02::print;
		
			vector<int>getSwappedVector(vector<int>v)
			{
				int 
					length = narrow_cast<int>(v.size()) >> 1,
					last = narrow_cast<int>(v.size()) - 1;
				for (int i = 0; i < length ; ++i)
				{
					int 
						t = v[i];
					v[i] = v[last - i];
					v[last - i] = t;
				}
				return v;
			}
		
			void vectorSwap(vector<int> &v)
			{
				int
					length = narrow_cast<int>(v.size()) >> 1,
					last = narrow_cast<int>(v.size()) - 1;
				for(int i = 0; i < length ; ++i)
				{
					int 
						t = v[i];
					v[i] = v[last - i];
					v[last - i] = t;
				}
			}
		
			void e05_main()
			{
				vector<int> v;
				for(int i = 0; i < 100 ; ++i)
					v.push_back(i);
				print(getSwappedVector(v), "swapped copy");
				print(v, "original v");
				vectorSwap(v);
				print(v,"swapped original");		
			}
		}

		namespace e06
		{
			void print(const vector<string> &v,string name)
			{
				cout
					<< lineBreak
					<< name
					<< ';'
					<< lineBreak;
				int
					counter{0};
				for(const string &value : v)
					cout
					<< value
					<< (counter++ % 5 == 4 ? lineBreak : ", ");
				cout
					<< endl;
			}
		
			vector<string>getSwappedStrings(vector<string>v)
			{
				int
					length = narrow_cast<int>(v.size()) >> 1,
					last = narrow_cast<int>(v.size()) - 1;
				for (int i = 0; i < length; ++i)
				{
					string 
						s = v[i];
					v[i] = v[last - i];
					v[last - i] = s;
				}
				return v;
			}
		
			void stringsSwap(vector<string> &v)
			{
				int
					length = narrow_cast<int>(v.size()) >> 1,
					last = narrow_cast<int>(v.size()) - 1;
				for (int i = 0; i < length; ++i)
				{
					string s = v[i];
					v[i] = v[last - i];
					v[last - i] = s;
				}
			}
		
			string generateString()
			{
				string 
					result;
				for(int i = 0; i < 8; ++i)
				{
					int 
						charCode = (rand() % 26);
					char 
						c = char(charCode + 65 + (rand() & 1) * 32);
					result += c;
				}
				return result;
			}	
		
			void e06_main()
			{
				vector<string> 
					v;
				for (int i = 0; i < 100; ++i)
				{
					v.push_back(generateString());
				}
		
				print(getSwappedStrings(v), "swapped copy");
				print(v, "original");
				stringsSwap(v);
				print(v, "swapped original");
			}
		}

		namespace e07
		{
			void listUsers(const vector<string> &names, const vector<int> &ages)
			{
				vector<string>
					sortedNames = names;
				sort(sortedNames.begin(), sortedNames.end());
				for(string name : sortedNames)
				{
					cout << lineBreak << name << ", age: ";
					for(int i = 0; ; ++i)	
						if (name == names[i]) 
						{
							cout << ages[i];
							break;
						}
				}
				cout << endl;
			}
		
			void e07_main()
			{
				vector<string> 
					names;
				vector<int> 
					ages;	
				string 
					name;
				int
					age;
				while(cin >> name >> age && age >= 0)
				{	
					names.push_back(name);
					ages.push_back(age);
					if (names.size() >= 5)
						break;
				}
				listUsers(names, ages);
			}
		}

		//

		namespace e09
		{
			void print(const vector<double> &v,string name)
			{
				cout
					<< lineBreak
					<< name
					<< ';'
					<< lineBreak;
				int
					counter{0};
				for(const double &value : v)
					cout
					<< value
					<< (counter++ % 10 == 9 ? lineBreak : "\t");
				cout
					<< endl;
			}
		
			double generatePrice()
			{
				int 
					i = rand() % 10000;
				return double (i) / 100.;
			}
		
			double generateWeight()
			{
				int
					i = rand() % 10000;
				return double (i) / 1000.;
			}
		
			void e09_main()
			{
				int
					lengthOfVectors{50};
				vector<double>
					prices,
					weights;
				for(int i = 0; i < lengthOfVectors; ++i)
				{
					prices.push_back(generatePrice());
					weights.push_back(generateWeight());
				}
				double 
					sumOfIndices{0};
		
				for(int i = 0; i < lengthOfVectors; ++i)
					sumOfIndices += (prices[i] * weights[i]);
		
				print(prices, "prices");
				print(weights, "weights");
				cout 
					<< lineBreak 
					<< sumOfIndices 
					<< endl;
			}
		}

		namespace e10
		{
			using namespace e09;
		
			double maxV(vector<double> v)
			{
				double 
					result = -DBL_MAX;
				for(double d : v)
					result = max(result, d);
				return result;
			}
		
			void e10_main()
			{
				vector<double> 
					arguments;
				for(int i = 0; i < 100; ++i)
					arguments.push_back(generatePrice());
				print(arguments, "arguments");
				cout 
					<< lineBreak
					<< maxV(arguments)
					<< endl;
			}
		}

		namespace e11
		{
			void Statistics::print()
			{
				cout 
					<< lineBreak
					<< "min:\t" << minimum
					<< "\nmax:\t" << maximum
					<< "\nmean:\t" << mean
					<< "\nmedian:\t" << median
					<< endl;
			}
		
			vector<int> generateIntVector(int length)
			{
				vector<int> 
					v;
				for(int i = 0; i < length; ++i)
					v.push_back(rand() % 1000);
				return v;
			}
		
			Statistics getStatistics(vector<int> v)
			{
				Statistics
					result;		
				sort(v.begin(), v.end());
				int
					last = narrow_cast<int>(v.size()) - 1,
					middle = narrow_cast<int>(v.size()) >> 1;
				result.minimum = double (v[0]);
				result.maximum = double (v[last]);		
				result.median = last & 1 
					? 0.5 * (double(v[middle]) + double(v[middle - 1]))
					: double (v[middle]);
				result.mean = 0.;
				for(int i : v)
					result.mean += double(i);
				result.mean /= double(v.size());
		
				return result;
			}
		
			void e11_main()
			{
				using e02::print;
		
				vector<int>
					v {generateIntVector(100)};
				print(v, "original vector");
				Statistics
					s {getStatistics(v)};
				s.print();
				sort(v.begin(), v.end());
				print(v, "sorted vector");
			}
		}

		namespace e12
		{
			void print_until_s(const vector<string>&v, string quit)
			{
				int
					index {0};
				cout
					<< lineBreak 
					<< "'" << quit << "'";
				for(string s : v)
				{
					if(s == quit)
					{
						cout 
							<< " found at index "
							<< index << endl;
						return;
					}
					++index;
				}
				cout
					<< "not found in the vector.\n";
			}
		
			void print_until(const vector<string> &v, string quit, int occurrences)
			{
				int
					counter{0};
				cout
					<< lineBreak
					<< "'" << quit << "'";
				for(string s : v)
				{
					if(s == quit)
					{
						++counter;
						if(counter == occurrences)
							break;
					}
				}
				if (counter > 0)
				{
					cout
						<< " found "
						<< counter
						<< " times.\n";
					return;
				}
				cout
					<< " not found in the vector.\n";
			}
		
			void e12_main()
			{
				using e06::print;
		
				vector<string>
					v{
					"zbyszek",
					"czesiek",
					"romek",
					"wacek",
					"marek",
					"rysiek",
					"bo¿ena",
					"marzena",
					"gra¿yna",
					"renata",
					"andrzej",
					"romek",
					"janek",
					"romek"};
				print(v, "names");
				print_until_s(v, "rysiek");
				print_until(v, "romek", 4);
				print_until(v, "d¿esika", 1);
			}
		}

		namespace e13
		{
			void firstAndLast(vector<string> v)
			{
				sort(v.begin(), v.end());
				cout
					<< lineBreak
					<< "first:\t"
					<< v[0]
					<< lineBreak
					<< "last:\t"
					<< v[narrow_cast<unsigned int>(v.size()) - 1]
					<< endl;
			}
		
			void shortestAndLongest(const vector<string> v)
			{
				string
					shortest{v[0]},
					longest{v[0]};
				for(string s : v)
				{
					if(s.size() < shortest.size())
						shortest = s;
					else 
						if(s.size() > longest.size())
							longest = s;
				}
				cout
					<< lineBreak
					<< "shortest:\t"
					<< shortest
					<< lineBreak
					<< "longest\t"
					<< longest
					<< endl;
			}
		
			vector<int> & countLetters(const vector<string> & v)
			{
				vector<int>
					lengths,
					& result = lengths;
				for(string s : v)
					lengths.push_back(narrow_cast<int>(s.size()));
				
				return result;
			}

			void print(const vector<int> & v, string fibonacciName)
			{
				cout 
					<< lineBreak 
					<< fibonacciName 
					<< ';' 
					<< lineBreak;
				int 
					counter {0};	
				for (const int &value : v)
					cout 
						<< value
						<< (counter++ % 5 == 4 ? lineBreak : ", ");
				cout 
					<< endl;
			}
		
			void e13_main()
			{
				//using e02::print;

				vector<string>
					v
					{
						"zbyszek",
						"czesiek",
						"romek",
						"wacek",
						"marek",
						"rysiek",
						"bo¿ena",
						"marzena",
						"gra¿yna",
						"renata",
						"andrzej",
						"janek",
						"placek",
						"gacek",
						"tacek"
					};
				firstAndLast(v);
				shortestAndLongest(v);
				print(countLetters(v), "lengths");
			}
		}
	}
}
