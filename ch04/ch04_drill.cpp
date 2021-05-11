#include "../_add/std_lib_facilities.h"

#include "ch04.h"

namespace ch04
{
	namespace drill
	{
		void d01() 
		{
			//Write a program that consists of a while-loop
			//that (each time around the loop) reads in two ints
			//and then prints them.
			//Exit the program when a terminating '|' is entered.

			cout 
				<< "\n\t";
			int 
				input1	/*{0}*/, 
				input2	/*{0}*/;
			while (cin >> input1 >> input2)	
				cout 
					<< input1 
					<< " , " 
					<< input2 
					<< "\n\t";
		}

		void d02() 
		{
			//make 01 printout the smaller value

			cout 
				<< "\n\t";
			int 
				input1	{0}, 
				input2	{0};
			while (cin >> input1 >> input2)
				cout
					<< "\n\tthe smaller value is: " 
					<< min(input1, input2)
					<< "\n\tthe larger value is: " 
					<< max(input1, input2);
			cout 
				<< endl;
		}

		void d03() 
		{
			//make it respond to an equal values

			cout
				<< "\n\t";
			int
				input1	{0},
				input2	{0};
			while (cin >> input1 >> input2)
				if (input1 == input2)
					cout
					<< "\n\tnumbers are equal"
					<< endl;
				else 
					cout
						<< "\n\tthe smaller value is: " 
						<< min(input1, input2)
						<< "\n\tthe larger value is: " 
						<< max(input1, input2)
						<< endl;
		}

		void d04() 
		{
			//change it to doubles

			double
				input1 {0},
				input2 {0};
			cout
				<< "\n\t";
			while (cin >> input1 >> input2)
				if (input1 == input2)
					cout
						<< "\n\tnumbers are equal"
						<< endl;
				else 
					cout
						<< "\n\tthe smaller value is: " 
						<< min(input1, input2)
						<< "\n\tthe larger value is: " 
						<< max(input1, input2)
						<< endl;
		}

		void d05() 
		{
			//add the "almost equal" printout  for the non-equal case with a diff < 0.01

			double
				input1 {0},
				input2 {0};
			cout
				<< "\n\t";
			while (cin >> input1 >> input2)
				if (input1 == input2)
					cout
						<< "\n\tnumbers are equal"
						<< endl;
				else 
				{
					cout
						<< "\n\tthe smaller value is: " 
						<< min(input1, input2)
						<< "\n\tthe larger value is: " 
						<< max(input1, input2)
						<< endl;
					if (abs(input1 - input2) < 0.01)
						cout
							<< "\n\tthe numbers are almost equal"
							<< endl;
				}
		}

		void d06() 
		{
			// make while write just one int each iteration; add min and max. report upon reaching either of 'em

			double
				minimum {std::numeric_limits<double>::max()},
				maximum {std::numeric_limits<double>::min()},
				input[2];
			bool
				switcher {false};
			cout
				<< "\n\t";

			while (cin >> input[switcher]) 
			{
				if (input[switcher] > maximum) 
				{
					cout
						<< "\tis the largest value so far" 
						<< endl;
					maximum = input[switcher];
				}

				if (input[switcher] < minimum) 
				{
					cout
						<< "\tis the smallest value so far" 
						<< endl;
					minimum = input[switcher];
				}

				if (switcher) 
				{
					if (input[0] == input[1])
						cout
							<< "\n\tnumbers are equal"
							<< endl;
					else 
					{
						cout
							<< "\n\tthe smaller value is: " 
							<< min(input[0], input[1])
							<< "\n\tthe larger value is: " 
							<< max(input[0], input[1])
							<< endl;

						if (abs(input[0] - input[1]) < 0.01)
							cout
							<< "\n\tthe numbers are almost equal"
							<< endl;
					}
				}
				switcher = !switcher;
			}
		}

		void d07() 
	{
		double
			minimum {numeric_limits<double>::max()},
			maximum {numeric_limits<double>::min()},
			values[2];
		bool 
			switcher {false};
		vector<string> 
			unitCodeBook {"cm", "in", "ft", "m"};
		vector<double> 
			unitConversionBook 
			{
				1, 
				2.54, 
				(2.54 * 12), 
				100.
			};
		string 
			input;
		int	
			unitIndex;

		auto allowedUnit = [&]
		{
			for (unitIndex = 0; unitIndex < unitCodeBook.size(); ++unitIndex)
				if (input.find(unitCodeBook[unitIndex]) < input.size())
					return true;
			return false;
		};

		while (cin >> input && allowedUnit()) 
		{
			values[switcher] = stod(input) * unitConversionBook[unitIndex];

			if (values[switcher] < minimum) 
			{
				minimum = values[switcher];
				cout 
					<< "\n\t" 
					<< values[switcher] 
					<< " is the smallest so far.";
			}
			if (values[switcher] > maximum) 
			{
				maximum = values[switcher];
					cout 
						<< "\n\t" 
						<< values[switcher] 
						<< " is the largest so far.";
			}
			if (switcher) 
			{
				if (values[0] == values[1]) 
					cout 
						<< "\n\tlengths are equal.\n";
				else 
				{
					cout 
						<< "\n\tthe smaller value is " 
						<< min(values[0], values[1]) 
						<< "\n\tthe larger values is " 
						<< max(values[0], values[1]);
				
					if (abs(values[0] - values[1]) < 0.01) 
						cout 
							<< "\n\tthe values are almost equal.\n";
				}
			}
			switcher = !switcher;
		}
	}

		void d09() 
		{
			double
				minimum {numeric_limits<double>::max()},
				maximum {numeric_limits<double>::min()},
				values[3]{};
			bool 
				switcher {false};
			vector<string> 
				unitCodeBook {"cm", "in", "ft", "m"};
			vector<double> 
				unitConversionBook 
				{
					1, 
					2.54, 
					2.54 * 12., 
					100.
				},
				allValues {};
			string 
				input;
			int	
				unitIndex;

			auto allowedUnit = [&]() -> bool 
			{
				for (unitIndex = 0; unitIndex < unitCodeBook.size(); ++unitIndex)
					if (input.find(unitCodeBook[unitIndex]) < input.size())
						return true;
				return false;
			};

			while (cin >> input && allowedUnit()) 
			{

				values[switcher] = (stod(input) * unitConversionBook[unitIndex]) / 100.;
				values[2] += values[switcher];
				allValues.push_back(values[switcher]);

				if (values[switcher] < minimum) 
				{
					minimum = values[switcher];
					cout 
						<< "\n\t" 
						<< values[switcher] 
						<< " is the smallest so far.";
				}
				if (values[switcher] > maximum) 
				{
					maximum = values[switcher];
					cout 
						<< "\n\t" 
						<< values[switcher] 
						<< " is the largest so far.";
				}
				if (switcher) 
				{
					if (values[0] == values[1]) 
						cout 
							<< "\n\tlengths are equal.\n";
					else 
					{
						cout 
							<< "\n\tthe smaller value is " 
							<< min(values[0], values[1]) 
							<< "\n\tthe larger values is " 
							<< max(values[0], values[1]);

						if (abs(values[0] - values[1]) < 0.01) 
							cout 
								<< "\n\tthe values are almost equal.\n";
					}
				}
				switcher = !switcher;
			}
			sort(allValues);
			cout
				<< "\n\tthe smallest value : " 
				<< minimum
				<< "\n\tthe largest value : " 
				<< maximum
				<< "\n\tThe sum of all values : " 
				<< values[2]
				<< "\n\tall entered values (sorted, and converted to meters):\n";

			for (double d : allValues)
				cout 
					<< "\n\t" << d;
			cout 
				<< "\n\n\tBye.\n";
		}
	}
}