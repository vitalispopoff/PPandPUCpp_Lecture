#include "../_add/std_lib_facilities.h"

namespace ch04
{
	namespace example
	{
		void f01() 
	{
		constexpr double
			phi = 1.618039887,
			pi = 3.14159265359;

		//this results in
		//err E0137 : expressoin must be a modifiable lvalue
		//err C2105 : '++' needs l-value

		//++phi; // disabled due to the errors
	}

		void f02() 
		{
			int 
				input {0};
			cout 
				<< "\n\n\twhat is current year ?\t";
			cin 
				>> input;
			bool
				every4Years		{bool (input & 4)},
				everyCentury	{bool (input & 100)},
				every4Centuries	{bool (input & 400)},
				leapYear		{every4Years && (!everyCentury || every4Centuries)};
			const int
				daysThisYear {365 + leapYear};
			cout 
				<< "\n\n\thow many day current year has? " 
				<< daysThisYear 
				<< endl;

			//this line results in
			//err E0137 : expression must be a modifiable lvalue
			//err C3892 : 'daysThisYear': you cannot assign to a variable that is const

			//daysThisYear++; // disabled due to the errors
		}

		void f03() 
		{
			int 
				i {-1};
			float 
				f {0};
			cout 
				<< "\n\n\t" 
				<< -i 
				<< endl;

			//narrowing conversion (casting >_>)
			cout 
				<< "\n\tcast: type(variable)\t" 
				<< typeid(double(i)).name();
			cout 
				<< "\n\tcast: (type)variable\t" 
				<< typeid((double)i).name();

			//non narrowing conversion (available since C++11 ?)
			cout 
				<< "\n\n\tcast: type{variable}\t" 
				<< typeid(long{ i }).name();
			cout 
				<< "\n\tcast: type{varialbe}\t" 
				<< typeid(double{ f }).name() 
				<< endl;

			//neither of these will compile: as the conversion would risk in data loss
			//which is prevented by the {} conversion.
			//err C2397

			//cout << double{ i };
			//cout << long{ f };
		}

		void f04() 
		{
			[]() {};

			// wrn C4390 : ';' : empty controlled statement found; is this the intent ?
			//if (true);

			//assembly: xor, je, jmp, jmp
			while (false)
				break;

			return;
		}

		void f05() 
		{
			int 
				i  {0};
			cin 
				>> i;
			if (i) 
				cout 
					<< "\n\n\tTRUE\n\n";
			else 
				cout 
					<< "\n\n\tnot so true as it could have been if it was TRUE, just like intended in first place...\n";
		}

		void f06() 
		{
			constexpr double
				cmToInch {2.54};
			double
				length {0};
			char
				unit {'c'};
			cout
				<< "\n\n\tEnter a length followed by a unit: cm:('c'), in:('i').\t";
			cin
				>> length
				>> unit;
			cout
				<< "\n\t";
			if (unit == 'i')
				cout 
					<< length << "in == " 
					<< length * cmToInch 
					<< "cm.\n";
			else
				if (unit == 'c')
					cout 
						<< length 
						<< "cm == " 
						<< length / cmToInch 
						<< "in.\n";
				else
					cout 
						<< "Unit must be either cm ('c') or in ('i'), and it's neither. Can't convert. Bye.\n";
		}

		void f07() 
		{
			constexpr double
				cmToInch {2.54};
			double
				length {0};
			char
				unit {'c'};
			cout
				<< "\n\n\tEnter a length followed by a unit:"
				<< "\n\t c\tcm"
				<< "\n\t i\tinch"
				<< "\n\t";
			cin
				>> length
				>> unit;
			cout
				<< "\n\t";
			switch (unit) {

				case 'c' : 
					cout 
						<< length 
						<< "in == " 
						<< length * cmToInch 
						<< "cm.\n";
					break;

				case 'i' : 
					cout 
						<< length 
						<< "cm == " 
						<< length / cmToInch 
						<< "in.\n";
					break;

				default :
					cout 
						<< "Unit must be either cm ('c') or in ('i'), and it's neither. Can't convert.\n\tBye.\n";
					break;

			}
		}

		void f08() 
		{
			const double
				eur2usd {1.17},
				jpy2usd {0.00904},
				gbp2usd {1.37},
				chf2uds {1.06};
			cout
				<< "\n\tenter currency:"
				<< "\n\t 'e'\tEUR"
				<< "\n\t 'y'\tJPY"
				<< "\n\t 'p'\tGBP"
				<< "\n\t 'f'\tCHF"
				<< "\n\twhitespace and a value to convert into USD.\n\tConfirm with 'Enter'.\t";
			char
				currency{0};
			string
				currencyCode;
			double
				value {0},
				result {0};
			cin
				>> currency
				>> value;
			auto attach = [&](double rate, string code) 
			{
				result = value * rate;
				currencyCode = code;
			};
			if (currency == 'e')
				attach(eur2usd, "EUR");
			else
				if (currency == 'y')
					attach(jpy2usd, "JPY");
				else
					if (currency == 'p')
						attach(gbp2usd, "GPB");
					else
						if (currency == 'f')
							attach(chf2uds, "CHF");
						else {
							cout
								<< "\n\n\tNone of currencies available for a conversion were chosen."
								<< "\n\tBetter luck next time."
								<< "\n\tBye."
								<< endl;
							return;
						}
			cout
				<< "\n\n\t" 
				<< fixed 
				<< setprecision(2) 
				<< currencyCode 
				<< ' ' 
				<< value 
				<< " equals to USD " 
				<< result
				<< endl;
		}

		void f09() 
		{
			char
				currency{0};
			double
				eur2usd {1.17},
				jpy2usd	{0.00904},
				gbp2usd	{1.37},
				chf2usd	{1.06},
				value	{0.},
				result	{0.};
			string
				currencyCode;
			cout
				<< "\n\tenter currency:"
				<< "\n\t 'e'\tEUR"
				<< "\n\t 'y'\tJPY"
				<< "\n\t 'p'\tGBP"
				<< "\n\t 'f'\tCHF"
				<< "\n\twhitespace and a value to convert into USD.\n\tConfirm with 'Enter'.\t";
			cin
				>> currency
				>> value;

			auto attach = [&](double rate, string code) 
			{
				result = value * rate;
				currencyCode = code;
			};

			switch (currency) 
			{
				case 'e' :
					attach(eur2usd, "EUR");
					break;
			
				case 'y' :
					attach(jpy2usd, "JPY");
					break;

				case 'p' :
					attach(gbp2usd, "GBP");
					break;

				case 'f' :
					attach(chf2usd, "CHF");
					break;

				default :
					cout
						<< "\n\n\tNone of currencies available for a conversion were chosen."
						<< "\n\tBetter luck next time."
						<< "\n\tBye."
						<< endl;
					return;
			}
			cout
				<< "\n\n\t" 
				<< fixed 
				<< setprecision(2) 
				<< currencyCode 
				<< ' ' 
				<< value 
				<< " equals to USD " 
				<< result
				<< endl;
		}

		void f10() 
		{
			//Zbyszek
			//Czesiek
			//Rysiek
			//Marzena
			//Bo¿ena
			//Gra¿yna

			char
				input{};
			cin
				>> input;
			cout
				<< "\n\n\t";
			switch (input) 
			{
				//doesn't work - adding a filter variable to the case (e.g. 'c':) causes multiple errors
				//err E0065 : expected a ';'
				//err C2143 : syntax error: missing ';' ':'
				//err C2059 : syntax error ':'

				case 'z' :
					cout 
						<< "male in general";
					break;

				case 'c' :
					cout 
						<< "c case";
					break;

				case 'm' :
					break;

				default :
					cout 
						<< "moustache at will";
					break;

			}
			cout 
				<< endl;
		}

		void f11() 
		{
			//idea: implement switch using a hashcode of certain strings.
			//the problem tho: is it possible to set the case filtering value to be not hardcoded... ?

			const unsigned int 
				cases[3]
				{
					4126860097,
					261001112,
					2054715501,
				};
			string
				selectorIn;
			cin
				>> selectorIn;

			auto stringToUnInt = [](string s)
			{ 
				return (hash<string>()(s));
			};

			switch (stringToUnInt(selectorIn)) 
			{
				case 4126860097: 
					cout 
						<< "\n\n\t this is Zbyszek.\n";
					break;

				case 261001112: 
					cout 
						<< "\n\n\t this is Rysiek.\n";
					break;

				case 2054715501: 
					cout 
						<< "\n\n\t this is Andrzej.\n";
					break;

				default: 
					cout 
						<< "User not recognized. Access denied.\n";
			}
		}

		void f12() 
		{
			int
				i	{0},
				max	{0};
			cin
				>> max;
			while (i < max)
				cout
					<< "\n\t" << ++i
					<< "\t" << i * i;
			cout
				<< endl;
		}

		void f13() 
		{
			auto drawACoin = [] 
			{
				int
					counter {0};
				bool
					flag {true};
				while (flag) 
				{
					counter++;
					flag = rand() & 1;
				}
				cout
					<< "\n\t" 
					<< counter;
			};
			char
				again{'y'};
			while (again == 'y') 
			{
				drawACoin();
				cout
					<< "\n\tagain ?\t(y/n)\t";
				cin
					>> again;
			}
			cout
				<< endl;
		}

		void f14() 
		{
			int
				c {32};
			while (++c < 256)
				cout 
					<< "\n\t" 
					<< char(c)
					<< "\t" 
					<< unsigned int(c);
			cout
				<< endl;
		}

		void f15() 
		{
			//while loop w/ the counter increment inside the sustain statement

			int
				i {0};
			while (i++ < 100) 
			{
				cout
					<< "\n\t"
					<< (rand() & 1) 
						? "yay" 
						: "";
			}
			cout
				<< endl;
		}

		void f16() 
		{
			for (int i = 32; i < 256; ++i) 	
				cout
					<< "\n\t" 
					<< char(i)
					<< "\t" 
					<< i;		
			cout
				<< endl;
		}

		void f17() 
		{
			int
				in		{0},
				result	{0};
			cin
				>> in;
			for (int i = 0; i < in; ++i)
				result += in;
			cout
				<< "\n\t" 
				<< result
				<< endl;
		}

		void f18() 
		{
			vector<int> 
				v { 0, 1, 2, 3 };
			cout 
				<< "\n\tvector v: ";
			for (int i : v)
				cout 
					<< i 
					<< " , ";
			//cout 
			//	<< endl;
			//cout 
			//	<< ' , ';		/// this produces something strange : 2108448210844821084482108448

			vector <int> 
				w (4);
			cout 
				<< "\n\tvector w: ";
			for (int i : w)
				cout 
					<< i 
					<< " , ";
			vector<int> 
				u(5);
			cout 
				<< "\n\tvector u: ";

			for (unsigned int i = 0; i < u.size(); ++i) 
			{
				u[i] = i;
				cout 
				<< (i > 0 
					? " , " 
					: "") 
				<< u[i];
			}

			//to be correctly initialized vector needs at least a stated size, even 0 works.
			vector<int> 
				t(0);
			cout
				<< "\n\tvector t:"
				<< "\n\t\tsize = " 
				<< t.size()
				<< "\n\t\tlocation = " 
				<< & t;
			t.push_back(0);
			cout
				<< "\n\t\tsize = " 
				<< t.size()
				<< "\n\t\tlocation = " 
				<< & t;
			cout
				<< endl;
		}

		void f19() 
		{
			vector<char> 
				txt(16);
			for (char & c : txt) 
				cin 
					>> c;
			cout 
				<< "\n\t";
			for (char c : txt) 
				cout 
				<< c;
			cout 
				<< endl;
		}

		void f20() 
		{
			//declaration is enough to make the vector work.
			vector<double>
				dd;
			for (double input; cin >> input; ) 
				dd.push_back(input);

			cout 
				<< "\n\n\t";
			for (double d : dd) 
				cout 
					<< d 
					<< " , ";
			cout 
				<< endl;
		}

		void f21() 
		{
			vector<string> 
				words;
			for (string input; cin >> input; ) 
			{
				transform(input.begin(), input.end(), input.begin(), :: tolower);
				words.push_back(input);
			}
			cout 
				<< "\n\twordcounter:\t" 
				<< words.size() 
				<< endl;
			sort(words);
			for (unsigned int i = 1; i < words.size(); ++i) 
				if (words[i] != words[i - 1]) 
					cout 
						<< words[i] 
						<< ",\n";
			cout 
				<< endl;
		}

		void f22() 
		{
			vector<string>
				blackList	{"broccoli"};
			string
				input;
			while (cin >> input) 
			{
				bool
					approved {true};
				for (string listed : blackList)
					if (input == listed)
						approved = false;
				if (approved)
					cout 
					<< "\n\n\t" 
					<< input 
					<< endl;
			}
		}
	}
}