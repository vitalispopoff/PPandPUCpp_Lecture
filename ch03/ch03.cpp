#include "../_add/std_lib_facilities.h"

namespace ch03
{
	namespace excercise
	{
		void f01() 
		{
			cout 
				<< "\n\tPlease enter your first name and hit 'Enter'.\n\t";
			string 
				firstName;
			cin 
				>> firstName;
			cout 
				<< "\n\n\tHello, " 
				<< firstName 
				<< ". Please to meet You.\n";
		}

		void f02() 
		{
			cout 
				<< "\n\tPlease enter your first name (and age).";
			string 
				firstName;
			int 
				age {0};
			cin 
				>> firstName
				>> age;
			cout 
				<< "\n\n\tHey, " 
				<< firstName 
				<< ".\n\tWow. You definitely don't look like " 
				<< age 
				<< ".\n\n\tYou look like " 
				<< int(age * 1.4) 
				<< ".\n";
		}

		void f03() 
		{
			int 
				i	{0};
			string 
				s;
			cin 
				>>	i
				>>	s;
			int 
				i2	{i + 2};
			string 
				s2	{s + " Jr. "};								/// concatenation
			int 
				i3	{i - 2};
			//string											/// subtractive kind of concatenation doesn't exist tho
			//	s3	{s2 - " Jr. "};								///disabled due to the error : E0349
		}

		void f04() 
		{
			int 
				i {500};
			auto gen = [=]										/// lambda function, passing by value;
			{				
				return i + (rand() % (i << 1)); 
			};
			int 
				a	{gen()}, 
				b	{gen()};
			auto result = [=]()-> int							/// lambda function, by default passing variables from parent scope, explicit int output
			{
				return a / b * b + a % b; 
			};

			cout 
				<< "\n\n\t" 
				<< (result() == a);
		}

		void f05() 
		{
			string 
				first, 
				second;
			cin 
				>> first 
				>> second;
			cout 
				<< "\n\n\t";
			if (first == second) 
				cout 
					<< "these are the same";
			else 
				cout 
					<< first 
					<< ((first < second) 
						? " is before " 
						: " is after ") 
					<< second;
			cout 
				<< ".\n";
		}

		void f06() 
		{
			auto letters = [](string & s)															/// input explicitly: string passed by reference
			{
				int 
					string_len {(rand() % 9) + 3};													/// name length randomizer			
				cout 
					<< "\ndbg: " 
					<< string_len;
				for (int i = 0; i < string_len; ++i) 
				{
					int 
						//x {(rand() % 25) + 65 + 32 * (i != 0)};									/// due to obscurity rewritten as follows;
						alphabet_len	{'z' - 'a'},
						up_low_shift	{('a' - 'A') * (i > 0)},									/// uppercase for the first initial, after all we generate names.
						letter			{'A' + (rand() % alphabet_len) + up_low_shift};
					s.append(1, char(letter));
				}
			};
			string 
				s1, 
				s2;
			letters(s1);
			letters(s2);
			cout 
				<< "\n\n\t";
			if (s1 == s2) 
				cout 
					<< s1 
					<< " and " 
					<< s2 
					<< " are the same";
			else 
				cout 
					<< s1 
					<< ((s1 < s2) 
						? " is before " 
						: " is after ") 
					<< s2;
			cout 
				<< ".\n";
		}

		void f07() 
		{
			string 
				previous {" "}, 
				current;
			int 
				repeated {0};

			while (cin >> current) 
			{
				if (previous == current)
					cout 
						<< "\n\t\'" 
						<< current 
						<< "\' repeated " 
						<< repeated 
						<< (++repeated == 1 
							? " time\n" 
							: " times\n");			
				else 
					repeated = 0;
				previous = current;
			}
		}

		namespace f08
		{
			//int x, y = x, z = y + 2;
		}

		void f09() 
		{
			bool 
				truth	{true};
			char 
				c		{truth};
			int 
				i		{c};
			float 
				//f		{i};									/// requires narrowing conversion
				f		{float(i)};				

			double 
				//d		{f};									/// requires narrowing conversion
				d		{double (f)};

			double 
				phi		{1.6180339887498948482};
			float 
				//fi		{phi};								/// requires narrowing conversion
				fi		{float(phi)};
			long 
				//lie		{fi};								/// requires narrowing conversion
				lie		{long(fi)};								
			int 
				//big		{0x80000001};						/// unsigned int to int requires narrowing conversion
				big		{int(0x80000001)};
			char 
				//small	{big};									/// requires narrowing conversion
				small	{char(big)};

			auto check = [](auto v1, auto v2) 
			{
				string
					type1 {typeid(v1).name()},
					type2 {typeid(v2).name()},
					result[]
					{ 
						"changed.", 
						"remained." 
					};
				bool
					comparison {v1 == v2};
				cout
					<< "\n\tcast " 
					<< type1
					<< " to " 
					<< type2
					<< " - value has " 
					<< result[comparison]
					<< endl;
			};
		}

		void f10() 
		{
			int 
				i	{0};
			char 
				c	{0};
			while (cin >> i) 
			{
				c = i;
				int 
					result {i - c};
				cout
					<< "\n\tint " 
					<< i
					<< " cast to char (" 
					<< int(c)
					<< "), difference in value is " 
					<< result
					<< endl;
			}
		}

		void f11() 
		{
			//using c++11 universal & uniform initialization syntax prevents narrowing conversion:
			//	C2397 : conversion from 'int' to 'char' requires a narrowing conversion.
			//using pre-C++11 notation convention would result in
			//	C4244 : 'initializing': conversion from 'int' to 'char', possible loss of data
			//but the compilator would proceed anyways.			
			int 
				i {0};
			while (cin >> i) 
			{
				char 
					c {char (i)};								/// required narrowing conversion
				int 
					result{i - c};
				cout
					<< "\n\tint " 
					<< i
					<< " cast to char (" 
					<< int(c)
					<< "), difference in value is " 
					<< result
					<< endl;
			}
		}
	}

	namespace drill
	{
		void d01() 
		{
			cout 
				<< "\n\n\tEnter the names of the recipient and sender separated with whitespace.\t";
			string 
				recipient, 
				sender;
			cin 
				>> recipient 
				>> sender;
			cout 
				<< "\n\tEnter 'f' for female or other character for male and age separated with whitespace.\t";
			char 
				fem;
			int 
				age;
			cin 
				>> fem 
				>> age;
			cout
				<< "\n\n\t\tDear " 
				<< recipient
				<< ",\n\n\tIn these first words of sympathy I'd like You to ask You to stop writing your code at once."
				<< "\n\t Your recent software development activities have already shown as a damaging factor to a emotional health to all the "
				<< (fem == 'f' 
					? "fe" 
					: "") 
				<< "males in our office, and the authorities were already adviced to intervene with no hesistation."
				<< "\n\tBeing " 
				<< age 
				<< (abs(age) == 1 
					? " year" 
					: " years") 
				<< " of age is certainly not a proper moment in life to dedicate oneself to become a Dev."
				<< "\n\n\t\tSincerely, \n\n\t\t" 
				<< sender 
				<< "\n\n";
		}
	}

	namespace excercise
	{
		void e01() 
		{
			double 
				input;
			int 
				i	{0};
			while (cin >> input) 
			{
				if (input == double(NAN))							/// casting NAN to double ? not sure of this idea TBH
					i = 0;											/// actually this should return kinda NaN or out of range exception.
				else 
					if (input < int(INT_MIN)) 
						i = int(INT_MIN);
					else 
						if (input > int(INT_MAX)) 
							i = int(INT_MAX);
						else 
							i = input;
				cout 
					<< "\n\n\t" 
					<< i 
					<< endl;
			}
		}

		void e02() 
		{
			double 
				miles	{0},
				types[]	
				{
					1.609344,									/// imperial
					1.85166,									/// nautic
				};
			string
				names[]
				{
					" imperial ",
					" nautical "
				};
			int 
				type	{0};
			cout 
				<< "\n\n\t enter distance (in miles) and mile type (0: imperial, 1 : nautical).\t";
			cin 
				>> miles 
				>> type;
			type = int(type > 0);								/// ruling out the possible user caused errors
			cout 
				<< "\n\n\t" 
				<< miles 
				//<< (bool(type) ? " nautical" : " imperial")	/// replaced by branchless
				<< ' '
				<< names[type]
				<< " is about " 
				<< miles * types [type] 
				<< " kilometers in distance.\n";
		}

		void e03() 
		{			
			///err E0084
			///err C2632
			///wrn C4901			
			//int double;

			///err E0040
			///err C2059
			//double 3three;

			///wrn C4101
			//bool _main;

			///err E0065
			///err C2143
			///err C2059
			//char H4><0R;
		}

		void e04() 
		{
			int
				val1 {0},
				val2 {0};
			cout 
				<< "\n\n\tEnter two integrals.\t";
			cin 
				>> val1 
				>> val2;
			if (val1 == val2)
				cout 
					<< "\n\n\t the integrals provided are equal.\n";
			else 
			{
				int
					smaller {min (val1, val2)},
					bigger	{max (val1, val2)},
					sum		{val1 + val2};
				cout 
					<< "\n\n\t" 
					<< smaller 
					<< " is smaller than " 
					<< bigger 
					<< " by " 
					<< bigger - smaller;
				cout 
					<< "\n\t which is " 
					<< 100. * double(bigger - smaller) / bigger
					<< "% of the bigger of them.";

				cout 
					<< "\n\n\t Together they are equal " 
					<< sum 
					<< " , and on average " 
					<< sum * 0.5;
			}
		}

		void e05() 
		{
			double
				val1 {0.},
				val2 {0.};
			cout 
				<< "\n\n\tEnter two numbers.\t";
			cin 
				>> val1 
				>> val2;
			if (val1 == val2)
				cout 
					<< "\n\n\t the integrals provided are equal.\n";
			else 
			{
				double
					smaller	{min	(val1, val2)},
					bigger	{max	(val1, val2)},
					sum		{val1 + val2};
				cout 
					<< "\n\n\t" 
					<< smaller 
					<< " is smaller than " 
					<< bigger << " by " 
					<< bigger - smaller;
				cout 
					<< "\n\t which is " 
					<< 100. * double(bigger - smaller) / bigger << "% of the bigger of them.";
				cout 
					<< "\n\n\t Together they are equal " 
					<< sum 
					<< " , and on average " 
					<< sum * 0.5;
			}
		}

		void e06() 
		{
			int 
				i[3] {0};
			cin 
				>> i[0] 
				>> i[1] 
				>> i[2];
			auto swap = [&] (int i1, int i2) 
			{				
				if (i[i1] > i[i2] && i1 < i2)				/// the order of values doesn't translate into values
				{
					int 
						temp = i[i1];
					i[i1] = i[i2];
					i[i2] = temp;
				}
			};
			swap(0, 1);
			swap(1, 2);
			swap(0, 1);
			cout 
				<< "\n\n\t" 
				<< i[0] 
				<< " , " 
				<< i[1] 
				<< " , " 
				<< i[2] 
				<< endl;
		}

		void e07() 
		{
			string 
				//s[3]	{" "};						/// since string is by default initialized empty, array declaration doesn't need an init val
				s[3];			
			if(true)								/// added just to provide alternatives in cin process part
				cin									/// cin is hardcoded to an exact number of s array elements
					>> s[0] 
					>> s[1] 
					>> s[2];
			else
				for (string str : s)				/// cin is independent on the s array length, and will provide data for all of em.
					cin 
						>> str;
						
			auto swap = [&] (int i1, int i2) 
			{
				if (s[i1] > s[i2] && i1 < i2) 
				{
					string 
						temp {s[i1]};
					s[i1] = s[i2];
					s[i2] = temp;
				}
			};
			swap(0, 1);
			swap(1, 2);
			swap(0, 1);
			cout 
				<< "\n\n\t" 
				<< s[0] 
				<< " , " 
				<< s[1] 
				<< " , " 
				<< s[2] 
				<< endl;
		}

		void e08()												/// Debug > Window > Disassembly
		{
			string answer[]{ "odd", "even" };
			int 
				i {0};											/// initializing... just in case
			cin 
				>> i;
			bool 
				result1	{bool (i & 1)},							///	bit masking in assembly:			mov, and, mov
				result2	{i % 2 == 0},							///	modulo with equation in assembly:	mov, and, jns, dec, or, inc, test, jne, mov, jmp, mov, mov, mov
				result3	{bool (i % 2)};							///	modulo								mov, and, jns, dec, or, inc, test, je, mov, jmp, mov, mov, mov
			cout 
				<< "\n\n\t" 
				<< i 
				<< " is " 
				//<< ((i & 1) ? "odd.\n" : "even.\n");			/// better make it branchless
				<< answer[i & 1] 
				<< ".\n";
		}

		void e09() 
		{
			cout
				<< "write a word representing a digit.\t";
			string
				s,
				answers []
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
			cin 
				>> s;
			bool
				unanswered {true};
			for (int i = 0; i < 10 && unanswered; ++i)
			{
				if (s == answers[i]) 
				{
					unanswered = false;
					cout 
						<< "\n\n\t" 
						<< s 
						<< " is equal to " 
						<< i 
						<< endl;
				}
			}
			if (unanswered) 
				cout 
					<< "\n\n\tDon't ask me, what You know - is true...\n";
		}

		void e10() 
		{
			char 
				type	{0};
			double 
				val1	{0},
				val2	{0};
			cin 
				>> val1 
				>> type 
				>> val2;
			double 
				& result	{val1};

			switch (type) 
			{
				case '+' : 
					result += val2;
					break;

				case '-' :
					result -= val2;
					break;

				case '*' : 
					result *= val2;
					break;

				case '/' :
				case ':' : 
					if(val2 == 0) 
						return;
					else 
						result /= val2;
					break;
			}
			cout 
				<< "\n\n\t result: " 
				<< result 
				<< endl;	
		}

		void e11() 
		{
			double 
				v1	{0}, 
				v2	{0}, 
				res	{0};
			string 
				operation;
			cin 
				>> v1 
				>> operation 
				>> v2;
			if (operation == "+" || operation == "add" || operation == "plus") 
				res = v1 + v2;
			else 
				if (operation == "-" || operation == "sub" || operation == "minus") 
					res = v1 - v2;
				else 
					if (operation == "*" || operation == "mul" || operation == "times") 
						res = v1 * v2;
					else 
						if (operation == "/" || operation == ":" || operation == "div" || operation == "by") 
							res = v1 / v2;
						else 
							cout 
								<< "\n\n\t we don't do that here\n";
			cout 
				<< "\n\n\t" 
				<< res 
				<< endl;
		}

		void e12() 
		{
			unsigned int
				pennies		{0},
				nickles		{0},
				dimes		{0},
				quarters	{0},
				halves		{0},
				dollars		{0};

			cout 
				<< "write us about your pennies, nicklez, dimes, quartaz, havz and bucks...\t";
			cin 
				>> pennies 
				>> nickles 
				>> dimes 
				>> quarters 
				>> halves 
				>> dollars;

			string
				p = pennies == 1 ? "penny" : "penny",
				n = nickles == 1 ? "nickle" : "nickles",
				d = dimes == 1 ? "dime" : "dimes",
				q = quarters == 1 ? "quarter" : "quarters",
				h = halves == 1 ? "50-cent" : "505-cents",
				b = dollars == 1 ? "dollar" : "dollars";

			auto bulletCoins = [](unsigned int val, string name) 
			{
				if (val > 0) 
					cout 
						<< "\n\t" 
						<< val 
						<< "\t" 
						<< name;
			};

			cout 
				<< "\n\n\tYou've said to have on you:\n";
	
			bulletCoins(pennies, p);
			bulletCoins(nickles, n); 
			bulletCoins(dimes, d);
			bulletCoins(quarters, q);
			bulletCoins(halves, h);
			bulletCoins(dollars, b);
			cout 
				<< "\n\n\t which gives a neatly round sum of " 
				<< (pennies + 5. * nickles + 10. * dimes + 25. * quarters + 50. * halves + dollars) / 100. 
				<< " dollaz.\n";
		}
	}
}