#include "../_add/std_lib_facilities.h"
#include "../ch05/ch05.h"

namespace ch05
{
	namespace excercise
	{
		namespace e02
		{
			//inspect and fix the code:
			//
			//double ctok(double c)		//shortening the names not a good idea
			//{
			//	int k = c + 273.15;		// int instead of double, 'k' is never referred to in the local scope
			//	return int				// no ';' , returned type instead of variable
			//}
			//
			//int tempFunction01()
			//{		
			//	double c = 0;			// would be nice to have '0.0' rather than '0'
			//	cin >> d;				// 'd' was never declared
			//	double k = ctok("c");	//	ctok accepts doubles, this is string, declaring 'k; in the scope is confusing, as ctok already has the variable called 'k',
			//	Cout << k << '\n';		// cout should be written with small caps
			//}

			/// CelsiusToKelvin02
			double CelsiusToKelvin(double temperature) 
			{
				return temperature + 273.15;
			}

			void e02_main() 
			{
				double
					input{ 0. };
				cin
					>> input;
				double
					tempInKelvin = CelsiusToKelvin(input);
				cout
					<< tempInKelvin
					<< endl;
			}
		}

		namespace e04
		{
			/// CelsiusToKelvin03
			double CelsiusToKelvin(double temperature) 
			{
				//branchless - if temperature is less then 0K, returns 0;
				return (temperature >= -273.15) * (temperature + 273.15);
			}

			void e04_main() 
			{
				double
					input{ 0. };
				cin
					>> input;
				double
					tempInKelvin = CelsiusToKelvin(input);
				cout
					<< tempInKelvin
					<< endl;
			}
		}

		namespace e05
		{
			//converts temperature value between different scales.
			//@var temperature - value
			//@var scale - scale to which temperature is to be converted

			///CelsiusToKelvin05
			double CelsiusToKelvin(double temperature, char scale) 
			{
				//branchless - if temperature is less then 0K, returns 0;
				switch (scale) 
				{
					case 'k': case 'K':
						return (temperature >= -273.15) * (temperature + 273.15);

					case 'c': case 'C':
						return (temperature >= 0) * (temperature - 273.15);

					default:
						cout 
							<< "No accepted scale was chosen. Returning 0.";
						return 0.;
				}
			}

			void e05_main() 
			{
				double
					input {0.};
				char 
					scale{'k'};
				cin
					>> input
					>> scale;
				double
					tempInKelvin = CelsiusToKelvin(input, scale);
				cout
					<< tempInKelvin
					<< endl;
			}
		}

		namespace e06
		{
				///CelsiusToFahrenheit06
			double CelsiusToFahrenheit(double temperature, char scale) 
			{
				switch (scale) 
				{
					case 'f': 
					case'F':
						return 32. + temperature * 1.8;
			
					case 'c':
					case'C':
						return (temperature - 32) * 0.5555555555555;
			
					default:
						cout 
							<< "No accepted scale was chosen. Returning 0.";
						return 0;
				}
			}

			void e06_main() 
			{
				double
					input {0.};
				char
					scale {'f'};
				while (cin >> input >> scale) 
				{
					double
						tempInFahrenheit = CelsiusToFahrenheit(input, scale);
					cout
						<< tempInFahrenheit
						<< endl;
				}
			}
		}

		void e07() 
		{

			// a * x^2 + b * x + c == 0
			double
				a {0.},
				b {0.},
				c {0.};
			auto discriminant = [&]() -> double 
			{
				return (b * b) - (4 * a * c);
			};

			while (cin >> a >> b >> c) 
			{
				if (discriminant() < 0)
					cout 
						<< "\n\tNo solution available.";
				else if (discriminant() == 0)
					cout 
					<< "\n\tx: " 
					<< (0 - b) / (2 * a); // we don't want a '-0'
				else 
				{
					cout
						<< "\n\tx1: " 
						<< (-b + sqrt(discriminant())) / (2 * a)
						<< "\tx2: " 
						<< -(b + sqrt(discriminant())) / (2 * a);
				}
				cout 
					<< endl;
			}
		}

		void e08() 
		{
			for (int input; cin >> input; ) 
			{
				vector<int>
					numbers(input);
				cout
					<< "\n\tEnter "
					<< numbers.size()
					<< " integrals then.\t";
				for (int& i : numbers)
					cin 
						>> i;
				int
					result = 0;
				for (int i : numbers)
					result += i;
				cout
					<< "\n\tSum of those "
					<< input
					<< " integrals of your choice is "
					<< result
					<< endl;
			}
		}

		void e09() 
		{
			for (int input; cin >> input; ) 
			{
				vector<int>
					numbers(input);
				cout
					<< "\n\tEnter "
					<< numbers.size()
					<< " integrals then.\t";
				for (int& i : numbers)
					cin 
						>> i;
				double
					result = 0;
				for (int i : numbers)
					result += i;

				if (result - floor(result) == 0.)
					cout
						<< "\n\tSum of those "
						<< input
						<< " integrals of your choice is "
						<< round(result)
						<< endl;
				else
					cout
						<< "\n\tResult is not a proper integral.\n";
			}
		}

		void e10() 
		{
			for (int input; cin >> input; ) 
			{
				vector<double>
					numbers(input),
					differentials(narrow_cast<double>(input - 1));
				cout
					<< "\n\tEnter "
					<< numbers.size()
					<< " integrals then.\t";
				for (double& i : numbers)
					cin 
						>> i;
				for (int i = 0; i < differentials.size(); ++i)
					differentials[i] = numbers[i + 1] - numbers[i];
				double
					result = 0;
				for (double i : numbers)
					result += i;
				cout
					<< "\n\tSum of those "
					<< input
					<< " values of your choice is "
					<< result
					<< "\n\n\tDifferentials of the provided numbers:\t";
				for (double d : differentials)
					cout 
						<< d 
						<< " , ";
				cout
					<< endl;
			}
		}

		void e11() 
		{

			//nth of the fibonacci sequence. 
			//implemented with int - no concurrency

			vector<int> 
				numbers {0, 1};
			int 
				nth {0};
			while (cin >> nth && nth > 0 && nth < 47) // F47 exceeds int range.
			{

				if (nth >= numbers.size())
					for (int i = numbers.size(); i <= nth; ++i)
						numbers.push_back(numbers[i - 1] + numbers[i - 2]);
				cout 
					<< "\n\t Fibonacci's nth: " 
					<< numbers[nth] 
					<< endl;
			}
		}

		namespace e12
		{		
			void e12_main() 
			{
				// bulls and cows
				int
					sequenceLength = 4;
				vector<num>
					sequence;

				// generating sequence
				for (int i = 0; i < sequenceLength; ) 
				{
					int
						number = rand() % 10;
			
					auto compare = [&]()->bool 
						{
						for (num s : sequence)
							if (number == s.answer)
								return false;
						return true;
					};

					if (compare()) 
					{
						sequence.push_back(num(number));
						++i;
					}
				}
				int
					bulls{ 0 },
					cows{ 0 };

				// the round

				while (bulls < sequenceLength) 
				{

					bulls = cows = 0;

					// player writing his guess
					for (num & i : sequence) 
					{
						int
							tmp;
						if (cin >> tmp && tmp >= 0 && tmp < 10)
							i.guess = tmp;
					}

					// comparing guesses with anwswers

					for (int i = 0; i < sequenceLength; ++i) 
					{
						bool
							temp = sequence[i].bull();

						if (temp)
							bulls++;
						else 
						{
							for (int j = 0; j < sequenceLength; ++j) 
							{
								if (i != j && sequence[i].guess == sequence[j].answer) 
								{
									cows++;
									break;
								}
							}
						}
					}
					cout 
						<< "\n\tbulls: " 
						<< bulls 
						<< " , cows: " 
						<< cows 
						<< endl;
				}
			}
		}

		void e14() 
		{
			vector<int>
				rejected, 
				monday, 
				tuesday, 
				wednesday, 
				thursday, 
				friday, 
				saturday, 
				sunday;
			string
				s {""};
			int
				value {0};
			vector<string>
				glossary
				{ 
					"monday", 
					"tuesday", 
					"wednesday",
					"thursday", 
					"friday", 
					"saturday", 
					"sunday", 
					"mon", 
					"tue", 
					"wed", 
					"thu", 
					"fri", 
					"sat", 
					"sun"
				};

			auto searchGlossary = [&]()-> int 
			{
				for (int i = 0; i < glossary.size(); ++i)
					if (s == glossary[i])
						return 1 + (i % 7);
				return -1;
			};

			while (cin >> s >> value) 
			{
				auto toLower = [&] 
					{
					for (char& c : s) {
						c = tolower(c);
					}
				};

				toLower();
			
				int
					switcher = searchGlossary();

				switch (switcher) 
				{
					case 1:		monday.push_back(value);	break;
					case 2:		tuesday.push_back(value);	break;
					case 3:		wednesday.push_back(value); break;
					case 4:		thursday.push_back(value);	break;
					case 5:		friday.push_back(value);	break;
					case 6:		saturday.push_back(value);	break;
					case 7:		sunday.push_back(value);	break;
					default:	rejected.push_back(value);
				}
				if (s == "_end")
					break;
			}
			auto sumDay = [&](vector<int> day) -> int 
			{
				int
					result{ 0 };
				for (int i : day)
					result += i;

				return result;
			};

			cout 
				<< "\n\tmonday:\t"		<< sumDay(monday)
				<< "\n\ttuesday:\t"		<< sumDay(tuesday)
				<< "\n\twednesday:\t"	<< sumDay(wednesday)
				<< "\n\tthursday:\t"	<< sumDay(thursday)
				<< "\n\tfriday:\t"		<< sumDay(friday)
				<< "\n\tsaturday:\t"	<< sumDay(saturday)
				<< "\n\tsunday:\t"		<< sumDay(sunday)
				<< "\n\n\trejected data entries:\t"		<< rejected.size()
				<< endl;
			}
	}
}