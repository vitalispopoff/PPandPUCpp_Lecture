#include "../_add/std_lib_facilities.h"

#include "ch04.h"

namespace ch04
{
	namespace excercise
	{
		void e01() 
		{
			vector<double>
				temps;
			for (double temp; cin >> temp;)	
				temps.push_back(temp);
			int 
				length {narrow_cast<int>(temps.size())};
			if (length == 0) 
				return;
			sort(temps);
			cout 
				<< "\n\n\t";
			for (double t : temps) 
				cout 
					<< t 
					<< " , ";
			cout 
				<< endl
				<< "\n\tmedian = "
				<< ((length & 1) 
					? (temps[length / 2]) 
					: (temps[(length >> 1) - 1] + temps[length >> 1]) / 2.)
				<< endl;
		}

		void e03() 
		{
			int 
				numberOfCities = 11;
			vector<double> 
				distances;
			double 
				maxDist = 1000.;
			uniform_real_distribution<double> 
				unif(0., maxDist);
			default_random_engine 
				re;

			for (int i = 1; i < numberOfCities; ++i)
				distances.push_back(unif(re));

			cout 
				<< endl;
			for (double d : distances) 
				cout 
					<< d 
					<< " , ";
			cout 
				<< endl;

			sort(distances);
			cout 
				<< "\n\tthe smallest distance is " 
				<< distances[0];
			cout 
				<< "\n\tthe largest distance is  " 
				<< distances[narrow_cast<unsigned int>(distances.size()) - 1];

			double 
				average {0};
			for (double d : distances) 
				average += d;

			cout 
				<< "\n\taverage distances is " 
				<< average / distances.size() 
				<< endl;
		}

		void e04() 
		{
			int
				guess {50},
				margin {guess / 2};
			cout
				<< "\n\n\tThink of a number between 0 and " 
				<< guess * 2 
				<< endl;
			char
				answer {' '};
			while (answer != '=' && margin > 0) 
			{
				cout
					<< "\n\t if it's less than "	<< guess	<< " - enter '<',"
					<< "\n\t if t's more than "		<< guess	<< " - enter '>',"
					<< "\n\t and if it is "			<< guess	<< " - enter '='.\n";
				cin
					>> answer;

				if (answer == '<')
					guess -= margin;
				else if (answer == '>')
					guess += margin;

				if (margin > 1) 
					margin /= 2;
			}
			if (answer != '=')
				cout
				<< "\n\n\tc'mon! You've cheated...";
			else 
			{
				cout
					<< "\n\n\tSo, it was "
					<< guess
					<< " all along... Nice. Wanna play again ?"
					<< "\n\t('n' is nah, anything else is yay... almost)"
					<< endl;

				if (cin >> answer && answer != 'n')
					e04();
				else
					return;
			}
		}

		void e05() 
		{

			cout 
				<< "\n\n\tenter value1, operation (+ - * / ), and value2 - all separated with spaces.\t";
			double
				value1 {0},
				value2 {0},
				result {0};
			char
				operation {' '};
			string
				s {"+-:/*"};
			string	
				names[] 
				{
					"sum", 
					"subtraction", 
					"multiplication", 
					"division", 
					"division" 
				};

			while (cin >> value1 >> operation >> value2 && s.find(operation) < s.size()) 
			{

				switch (operation) 
				{
					case '+':
					{
						result = value1 + value2;
						break;
					}
					case'-':
					{
						result = value1 - value2;
						break;
					}
					case'*':
					{
						result = value1 * value2;
						break;
					}
					case'/':
					{};
					case':':
					{
						result = 
							value2 == 0 
							? narrow_cast<double>(NAN) 
							: double(value1) / double(value2);
						break;
					}
					default:
					{
						cout 
							<< "\n\n\tsomething went wrong with the operation sign, start all over again unles You've enough - then ctrl-z will is the solution./n";
					}
				}
				cout 
					<< "\n\n\t the " 
					<< names[s.find(operation)] 
					<< " of " 
					<< value1 
					<< " and " 
					<< value2 
					<< " is " 
					<< result 
					<< " .\n";
			}

		}

		void e06() 
		{

			vector<string> 
				names
				{ 
					"zero", 
					"one", 
					"two", 
					"three", 
					"four", 
					"five", 
					"six", 
					"seven", 
					"eight", 
					"nine" 
				};
			string 
				input;

			auto findDigit = [&]() -> int 
			{
				for (unsigned int i = 0; i < input.size(); ++i)
					if (input[i] >= '0' && input[i] <= '9')
						return input[i] - '0';

				return -1;
			};

			auto findName = [&]() ->int 
			{
				for (unsigned int i = 0; i < names.size(); ++i)
					if (input.find(names[i]) < input.size())
						return i;

				return -1;
			};

			while (cin >> input) 
			{
				int 
					foundDigit = findDigit();
				if (foundDigit >= 0) 
					cout 
						<< "\n\n\t" 
						<< names[foundDigit];

				int 
					foundName = findName();
				if (foundName >= 0) 
					cout 
						<< "\n\n\t" 
						<< foundName;
				cout << endl;
			}
		}

		void e07() 
		{

			vector<string> 
				digits
				{ 
					"zero", 
					"one", 
					"two", 
					"three", 
					"four", 
					"five", 
					"six", 
					"seven", 
					"eight", 
					"nine" 
				};
			string 
				input1, 
				input2;

			auto findDigit = [&](string input) -> int 
			{
				for (int i = 0; i < input.size(); ++i)
					if (input[i] >= '0' && input[i] <= '9')
						return input[i] - '0';

				return -1;
			};
			auto findName = [&](string input) ->int 
			{
				for (int i = 0; i < digits.size(); ++i)
					if (input.find(digits[i]) < input.size())
						return i;
		
			return -1;
			};
			auto decipher = [&](string input) -> int 
			{
				int 
					foundDigit = findDigit(input);
			
				if (foundDigit >= 0)
					return foundDigit;
				else 
				{
					int 
						foundName = findName(input);
					if (foundName >= 0)
						return foundName;
				}
				return 0;
			};

			int
				value1{ 0 },
				value2{ 0 },
				result{ 0 };
			char
				operation{ ' ' };
			string
				s {"+-:/*"};
			string
				names[]
				{ 
					"sum", 
					"subtraction", 
					"multiplication", 
					"division", 
					"division"
				};

			while (cin >> input1 >> operation >> input2 && s.find(operation) < s.size()) 
			{
				value1 = decipher(input1);
				value2 = decipher(input2);

				switch (operation) 
				{
					case '+':
					{
						result = value1 + value2;
						break;
					}
					case'-':
					{
						result = value1 - value2;
						break;
					}
					case'*':
					{
						result = value1 * value2;
						break;
					}
					case'/':
					{};
					case':':
					{
						result = narrow_cast<int>(value2 == 0 ? narrow_cast<double>(NAN) : double(value1) / double(value2));
						break;
					}
					default:
					{
						cout 
							<< "\n\n\tsomething went wrong with the operation sign, start all over again unles You've enough - then ctrl-z will is the solution./n";
					}
				}
				cout 
					<< "\n\n\t the " 
					<< names[s.find(operation)] 
					<< " of " 
					<< value1 
					<< " and " 
					<< value2 
					<< " is " 
					<< result 
					<< " .\n";
			}
		}

		void e08() 
		{
			int
				aimValue{ 0 };
			cin 
				>> aimValue;
			int 
				i = 0;

			for( ; narrow_cast<double>(int(1) << i) < aimValue / 2.; ++i)
				cout 
					<< "\n\t" 
					<< (1 << i);
			cout 
				<< "\n\n\t" 
				<< i;
		}

		void e09() 
		{

			//	The amount of all grains from the chessboard would be: (2^65) - 1;
			//double would lack a single bit to represent the number;

			float
				grains = (ULLONG_MAX * 2.) - 1.;

			cout
				<< "\n\t"	<< fixed		<< grains
				<< "\n\t"	<< scientific	<< grains
				<< endl;

			// -------------------------------------

			//What  is  the  largest  number  of  squares  for  which  you can calculate the approximate number of grains(using a double)

			//start with a signed floating-point;
			//MSb = sign
			//7bits = base;
			//24LSBs = significand

			//significand is a proper part of a fraction (stuff after the '.')
			//so a significand is 1 + (1 - (2^-24)) = 2 - (1 / 16 ,777, 216)

			//base is a (2^7)-1 = 127
			//assuming that unsigned floating point adds sign bit to the base we'get

			//(2-(1/16777216))^255,
			//which is almost 2^255;
		}

		void e10() 
		{
			cout
				<< "\n\t~\tpaper"
				<< "\n\tx\tscissors"
				<< "\n\to\trock"
				<< "\n\t";
			char
				input;
			int
				player1{ 0 },
				player2{ 0 };
			vector<string> 
				betNames
				{
					"rock",			// 0 : 0b00
					"paper",		// 1 : 0b01
					"scissors"		// 2 : 0b10
				};

			while (cin >> input) 
			{
				player2 = (rand() % 3);

				//converting player input to int
				switch (input)
				{
					case 'o':	player1 = 0;	break;
					case '~':	player1 = 1;	break;
					case 'x':	player1 = 2;	break;
					case '8':
					{
						cout 
						<< "Whoah! A shotgun! You win all the games!\n"; 
						return;
					}
					default:
					{};
				}

				if (player1 == player2)
					cout 
						<< "\n\tIt's a draw.\n";

				else {
					bool
						whosBigger = (player1 > player2),
						result = abs(player1 - player2) & 1;	//the bigger bid wins with LSb = 1; the smaller bid otherwise
					cout
						<< ((whosBigger == result) 
							? "\n\tWow. You won against the " 
							: "\n\tUgh. You lost against the ")
						<< betNames[player2] 
						<< "\n\t";
				}
			}
		}

		void e11() 
		{
			vector<int> 
				primes {2};

			auto isPrime = [&](int input) -> bool 
			{
				for (int i = 0; i < primes.size() && primes[i] <= 1 + (input >> 1); ++i)
					if (input % primes[i] == 0)
						return false;

				return true;
			};

			int 
				max;
			vector<string> 
				wtf 
				{ 
					"\t",
					"\n\t" 
				};

			while (cin >> max) 
			{
				for (int i = 3; i <= max; ++i)
					if (isPrime(i)) 
						primes.push_back(i);

				cout 
					<< "\n\t";
				for (int i = 0; i < primes.size(); ++i) 
					cout 
						<< primes[i] 
						<< wtf[i % 10 == 9];
				cout 
					<< endl;
			}
		}

		void e12() 
		{
			int 
				max {0};

			while (cin >> max) 
			{
				vector<int>
					primes{};								// list of results
				vector<char>
					candidates {0, 0};						// list of candidates

				for (int i = 2; i < max; ++i)						// populate candidate list
					candidates.push_back(1);

				for (int i = 2; i < max; ++i) 					// traverse the candidates
					if (candidates[i]) 							// qualify candidate
					{
						primes.push_back(i);						//add candidate to prime list
						for (int j = 2 * i; j <= max - i; j += i)
							candidates[j] = 0;						//disqualify all multiplications of a qualified candidate
					}

				for (int prime : primes) 
					cout 
						<< prime 
						<< " , ";
				cout 
					<< endl;
			}
		}

		void e13() 
		{
			int 
				population, 
				max;

			while (cin >> population) 
			{
				if (population == 1) 
					cout 
						<< "2 , \n";
				else 
				{
					//computing the search range.
					{
						double 
							temporal {1. + double(population)};
						max = int(ceil(1.2 * temporal * log(temporal)));
					}

					vector<int>
						primes{};								// list of results
					vector<char>
						candidates{ 0, 0 };						// list of candidates

					for (int i = 2; i < max; ++i)						// populate candidate list
						candidates.push_back(1);

					for (int i = 2; i < max && primes.size() < population; ++i)						// traverse the candidates
					{
						if (candidates[i])							// qualify candidate
						{
							primes.push_back(i);						//add candidate to prime list

							for (int j = 2 * i; j <= max - i; j += i)
								candidates[j] = 0;						//disqualify all multiplications of a qualified candidate
						}
					}
					for (int prime : primes) 
						cout 
							<< prime 
							<< " , ";
					cout 
						<< endl;
				}
			}
		}

		void e14() 
		{
			vector<int> 
				series;
			int
				size{ 20 },
				range{ 10 };
			for (int i = 0; i < size; ++i)
				series.push_back(rand() % (range - 1));

			sort(series);

			struct mode 
			{
				int 
					element, 
					appearances;

				mode(int element) 
				{
					this ->	element = element;
					appearances = element < 0 ? -1 : 1;
				}

				mode & operator ++ (int) 
				{
					appearances++;
					return * this;
				}
			};

			vector<mode> 
				modes {mode(-1)};

			for (int i : series) 
			{
				int 
					index {narrow_cast<int>(modes.size()) - 1};
				mode 
					& thisMode = (modes[index]);

				if (i == thisMode.element)
					thisMode++;
				else
					modes.push_back(mode(i));
			}

			mode 
				& theMode {modes[0]};
			for (mode m : modes) 	
				if (m.appearances > theMode.appearances)
					theMode = m;	

			for (int i : series) 
				cout 
					<< "\n\t" 
					<< i;
			cout 
				<< "\n\t";
			cout 
				<< "\n\t" 
				<< theMode.element 
				<< "/" 
				<< theMode.appearances;
			cout 
				<< endl;
		}

		void e15() 
		{
			int 
				length {8}, 
				population {16};
			vector<string> 
				strings;

			// populating the strings vector
			for (int i = 0; i < population; ++i) 
			{
				string 
					s{ "" };
				for (int j = 0; j < length; ++j) 
				{
					char 
						c = (rand() % ('z' - 'a')) + 'a';
					s += c;
				}
				cout 
					<< "\n\t" 
					<< s;
			}
			sort(strings);	
			cout 
				<< "\n\tmin " 
				<< strings[0] 
				<< "\t\tmax" 
				<< strings[narrow_cast<int>(strings.size()) - 1] 
				<< endl;

			//...
		}

		void e16() 
		{
			double 
				a, b, c;
			while (cin >> a >> b >> c) 
			{
				double 
					discriminant = (b * b) - 4 * a * c;
				cout 
					<< endl;
				switch ((discriminant > 0) - (discriminant < 0)) 
				{
					case 1: 
					{
						double 
							root = sqrt(discriminant), denominator = a * 2;
						cout 
							<< "\n\t" 
							<< ((-b + root) / denominator);
						cout 
							<< "\t" 
							<< ((-b - root) / denominator) 
							<< endl;
						break;
					}
					case 0: 
					{
						cout 
							<< "\n\t" 
							<< (-b / (a * 2)) 
							<< endl;
						break;
					}
					case -1:
						cout 
							<< "\n\t" 
							<< "no solutions in a real number domain" 
							<< endl;
				}
				cout 
					<< "\n\tagain ?\n";
			}

		}

		void e17() 
		{
			string 
				name {""};
			int 
				score;
			vector<string> 
				names;
			vector<int> 
				scores;
			auto nameIndex = [&]()-> int 
			{
				for (int i = 0; i < names.size(); ++i)
					if (names[i] == name) 
						return i;
				return -1;
			};
			auto breakPoint = [&]							// has to pass the reference in order to stay up-to-date
			{	
				return (name == "NoName") && (score == 0);
			};

			//fill the vectors
			while (cin >> name >> score && !breakPoint()) 
			{
				if (nameIndex() < 0) 
				{
					names.push_back(name);
					scores.push_back(score);
				}
				else break;
			}

			//query

			string 
				input {""};

			auto inputIsInt = [&] 
			{
				for (char c : input)
					if (c < '0' || c > '9')
						return false;
				return true;
			};
			auto scoreIndex = [&]()-> int 
			{
				for (int i = 0; i < scores.size(); ++i)
					if (scores[i] == score) 
						return i;
				return -1;
			};

			while (cin >> input) 
			{
				if (inputIsInt()) 
				{
					score = stoi(input);
					int 
						index = scoreIndex();

					//report a single score (prints the first on the list only), inform whether n/a 
					switch (index) 
					{
						case -1:
							cout 
								<< "\n\tScore not found.\n";
							break;

						default:
							cout 
								<< "\t: " 
								<< names[index]
								<< endl;
					}
				}
				else 
				{
					cout 
						<< "\n\t";
					name = input;
					int 
						index = nameIndex();

					// report everybody and exit
					if (name == "get_all") 
					{
						cout 
							<< endl;
						for (int i = 0; i < names.size(); ++i)
							cout 
								<< "\n\t" 
								<< names[i] 
								<< "\t: " 
								<< scores[i];
						cout 
							<< endl;
						return;
					}

					//report a single person, inform whether n/a 
					switch (index) 
					{
					case -1:
						cout 
							<< "\n\tName not found.\n";
						break;

					default:
						cout 
							<< "\t: " << scores[index] 
							<< endl;
					}
				}
			}

			//query

			while (cin >> name) 
			{}
		}
	}
}