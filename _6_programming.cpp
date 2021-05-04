#include "std_lib_facilities.h"

namespace ch06
{

	// excerice 04  ------------------------------------------------

	class NameValue 
	{
		public:
			string 
				name;
			int 
				score;

			NameValue(string s, int i)
				: name(s), score(i) 
			{}
	};

	void programming_exc04() 
	{
		string
			name {""};
		int 
			score;
		vector<NameValue>
			ranking;

		auto nameIndex = [&]()-> int								// searching for the name duplicates in the ranking
		{
			int 
				output = 0;

			for (NameValue player : ranking)
				if (name == player.name)
					return output;
				else 
					output++;

			return -1;
		};

		auto breakPoint = [&]()->bool								// has to pass the reference in order to stay up-to-date
		{
			return (name == "NoName") && (score == 0);
		};

		while (cin >> name >> score && !breakPoint())				//fill the vectors
		{
			if (nameIndex() < 0)
				ranking.push_back(NameValue(name, score));
			else
			{
				cout 
					<< "\n\tname's already on the list.\n";
				break;
			}
		}

		//query
		string 
			input {""};
		char 
			c;

		while (cin >> c) 
		{
			bool 
				missing {true};

			if (c >= '0' && c <= '9')								//writing down a number
			{
				cin.putback(c);
				cin 
					>> score;

				for (NameValue player : ranking) 
				{
					if (score == player.score) 
					{
						cout 
							<< "\n\t" 
							<< player.name 
							<< "\t:\t" 
							<< player.score 
							<< endl;
						missing = false;
					}
				}
			}
			else if ((c > 32 && c < '0') || (c > '9' && c < 127))	//writing down a name
			{
				cin.putback(c);
				cin 
					>> input;

				for (NameValue player : ranking) 
				{
					if (name == player.name) 
					{
						cout 
							<< "\n\t" 
							<< player.name 
							<< "\t:\t" 
							<< player.score 
							<< endl;
						missing = false;
					}
				}
			}
			if (missing)
				cout 
				<< "\n\trecord not found.\n";
		}
	}

	// excerice 05  ------------------------------------------------

	/*
	Exemplary english grammar:

		Sentence:
			Noun Verb
			Pronoun Noun Verb
			Sentence Conjunction Sentence
		Conjunction:
			"and"
			"or"
			"but"
		Pronoun:
			"the"
		Noun:
			"birds"
			"fish"
			"C++"
		Verb:
			"rules"
			"fly"
			"swim"

	*/

	// excerice 08  ------------------------------------------------

	class num 
	{
		public:
			char
				answer,
				guess;

			num(char a)
				:answer(a) 
			{};

	};

	void programming_exc08() 
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
				letter = (rand() % 26) + 97;

			auto compare = [&]()->bool 
			{
				for (num s : sequence)
					if (letter == s.answer)
						return false;
				return true;
			};

			if (compare()) 
			{
				sequence.push_back(num(letter));
				++i;
			}
		}

		//printing the answers
		for (num n : sequence)
			cout 
				<< n.answer 
				<< ' ';
		int
			bulls {0},
			cows {0};

		// the round
		while (bulls < sequenceLength) 
		{
			bulls = cows = 0;

			// player writing his guess
			for (num& i : sequence) 
			{
				char 
					tmp;
				cin 
					>> tmp;
				i.guess = tmp;
			}

			// comparing guesses with anwswers

			for (int i = 0; i < sequenceLength; ++i) 
			{
				if (sequence[i].answer == sequence[i].guess)
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

	// excerice 09  ------------------------------------------------

	// read digits ind write as a sentence like ("123") -> "123 is 1 hundred and 2 tens and 3 ones."

	void programming_exc09() 
	{
		vector<string>
			powers
			{
				"one",
				"ten",
				"hundred",
				"thousand"
			};
		char 
			input {' '};
		string
			digits {""},
			output {""};
		int	
			value {0};

		while (input != 'q') 
		{
			int 
				counter {3};
			while (cin >> input && input >= '0' && input <= '9') 
			{
				digits = input + digits;
				(value *= 10) += (input - '0');
				if (0 == counter--) 
					break;
			}
			
			for (int i = digits.size() - 1; i >= 0; --i) 
			{
				if (output.size() > 0) 
					output += " and";
				if (digits[i] > '0') 
				{
					// this is just unreadable bullshit
					//((((output += ' ') 
					//	+= digits[i]) 
					//	+= ' ')
					//	+= powers[i])
					//	+= (digits[i] > '1') ? "s"  : "";			

					output += ' ';
					output += digits[i];
					output += ' ';
					output += powers[i];
					
					output += 
						(digits[i] > '1') 
							? "s" 
							: "";
				}
			}
			cout 
				<< "\n\t" 
				<< value 
				<< " is" 
				<< output 
				<< ".\n";
		}
	}

	// excerice 09  ------------------------------------------------

	// permutaion and combination calculator

	void programming_exc10() 
	{
		int 
			a {0},
			b {0},
			c {0};
		char 
			type {' '};

		while (cin >> b >> a >> type && a >= b) 
		{
			c = a - b;
			double
				a_factorial {1}, 
				b_factorial {1}, 
				c_factorial {1};

			for (double i = 2; i <= a; ++i) 
			{
				a_factorial *= i;
				if (i == b)
					b_factorial = a_factorial;
				if (i == c)
					c_factorial = a_factorial;
			}
			cout << fixed << setprecision(0);

			if (type == 'p')
				cout 
					<< a_factorial / c_factorial;
			else if (type == 'c')
				cout 
					<< a_factorial / c_factorial / b_factorial;
		}
		cout 
			<< scientific 
			<< setprecision(6);
	}

	void programming() 
	{
		programming_exc10();
	}

}