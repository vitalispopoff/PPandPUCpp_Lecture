#include "../_add/std_lib_facilities.h"
#include "../ch05/ch05.h"

namespace ch05
{
	namespace drill
	{
		void d01() 
		{
			// err E0020, C2065
			// wrn C4018, C4101
			//Cout << "Success!\n";

			cout 
				<< "Success!\n";
		}

		void d02() 
		{
			// err E0008, E0065, C2001, C2143
			// wrn C4018, C4101
			//cout << "Success!\n;

			cout 
				<< "Success!\n";
		}

		void d03() 
		{
			// err E0007, E0008, E0065, C2017, C2001, C2065, C2143, C2142
			// wrn C4018, C4101
			//cout << "Success" << !\n"

			cout 
				<< "Success" 
				<< "!\n";
		}

		void d04() 
		{
			// err E0020, C2065
			// wrn C4018, C4101
			//cout << success << '\n';

			cout 
				<< "success" 
				<< '\n';
		}

		void d05() 
		{
			// err E0415, E0413, C2440, C2440
			// wrn C4018, C4101
			//string res = 7; vector<int>v(10); v[5] = res; cout << "Success!\n";

			//string res = 7;	//mustn't be string.
			int 
				res {7};
			vector<int> 
				v(10);
			v[5] = res;
			cout 
				<< "Success!\n";
		}

		void d06() 
		{
			// err E0980, E0980. C2064, C2064, C4018, C4101
			//vector<int>v(10); v(5) = 7; if (v(5) != 7)cout << "Success!\n";

			vector<int>
				v(10);

			//v(5) = 7;	//wrong brackets
			v[5] = 7;

			//if (v(5) != 7) cout << "Success!\n";	// wrong brackets here as well
			//if (v[5] != 7) cout << "Success!\n";	// gotta switch != to == to get "Success!" 

			if (v[5] == 7) 
				cout 
					<< "Success!\n";
		}

		void d07() 
		{
			// err E0020, C2065
			// wrn C4018, C4101

			//if (cond)cout << "Success!\n"; else cout << "Fail!\n"; // cond not declared, nor initialized.

			bool 
				cond = true;
			if (cond) 
				cout 
					<< "Success!\n";
			else 
				cout 
					<< "Fail!\n";
		}

		void d08() 
		{
			//bool c = false; if(c)cout << "Success!\n"; else cout << "Fail!\n"; // c needs being true, or if assertion changed to !

			bool 
				c = true;
			if (c) 
				cout 
					<< "Success!\n";
			else 
				cout 
					<< "Fail!\n";
		}

		void d09() 
		{
			// err E0020, C2374, C2065, C2146, C2065, C2065
			// wrn C4018, C4101
			//string s = "ape";boo c = "fool"<s;if(c)cout<<"Success!\n"; // no type 'boo'

			string 
				s {"ape"};
			bool 
				c {"fool" < s};			// had to rename c to c1 because of line 408
			if (!c) 
				cout 
					<< "Success!\n";	// to have it success gotta switch to !c1
		}

		void d10() 
		{
			//string s = "ape"; if (s == "fool")cout << "Success!\n";// this one needs != instead of ==

			string 
				s {"ape"};
			if (s != "fool") 
				cout 
					<< "Success!\n";
		}

		void d11() 
		{
			// err E0349, C2678
			// wrn C4018, C4101
			//string s="ape";if(s=="fool")cout<"Success!\n"; // assert : == to != ; also cout << rather than <

			string 
				s {"ape"};
			if (s != "fool") 
				cout 
					<< "Success!\n";
		}

		void d12() 
		{
			// err E0711, E0349, C2451, C2678
			// wrn C4018, C4101

			//string s="ape";if(s+"fool")cout<"Success!\n"; // assertion needs to be a proper expression, cout needs <<

			string 
				s {"ape"};
			s = "fool";		// was + a shift mistype?
			if (s == "fool") 
				cout 
					<< "Success!\n";
		}

		void d13() 
		{
			//vector<char>v(5);for(int i=0;0<v.size();++i);cout<<"Success!\n";	// for loop sustain condition is always true, and its code block is empty

			vector<char> 
				v(5);
			for (int i = 0; i < v.size(); ++i) // keeping it useless, but not infinite
			{};
			cout 
				<< "Success!\n";
		}

		void d14() 
		{
			//vector<char>v(5);for(int i=0;i<=v.size();++i);cout<<"Success!\n";//this works actually

			vector<char> 
				v(5);
			for (int i = 0; i < v.size(); ++i) // we should change <= into < . just in case
			{};
			cout << "Success!\n";
		}

		void d15() 
		{
			//string s = "Success!\n"; for (int i = 0; i < 6; ++i) cout << s[i]; // prints "Success" only

			string 
				s = "Success!\n";
			//for (int i = 0; i < s.size(); ++i) cout << s[i];

			for (char c : s) 
				cout 
					<< c;	// even safer.
		}

		void d16() {

			// err E0020
			// err E0065
			// err C2065
			// err C2146
			// err C2181
			// wrn C4018
			// wrn C4101
			// wrn C4018
			// wrn C4018

			//if (true)then cout << "Success!\n"; else cout << "Fail!\n"; // looks like Excel.

			if (true) 
				cout 
					<< "Success!\n";
			else 
				cout 
					<< "Fail!\n";

		}

		void d17() 
		{

			//int x = 2000; char c = x; if (c == 2000) cout << "Success!\n"; // 2000 exceeds char length

			int 
				x = 2000;
			char 
				c = (x % 256);

			if (c == char(2000)) 
				cout 
					<< "Success!\n"; // not sure if char(2000 % 256) wasn't better

		}

		void d18() 
		{
			//string s = "Success!\n"; for (int i = 0 ; i < 10; ++i) cout << s[i]; works but is not safe.

			string 
				s = "Success!\n";
			for (char c : s)
				cout 
					<< c;

		}

		void d19() 
		{
			// err E0441
			// err C2955
			// err C2514
			// err C2662
			// wrn C4018 
			// wrn C4101
			// wrn C4018 
			// wrn C4018

			//vector v(5); for (int i = 0; i <= v.size(); ++i); cout << "Success!\n"; // vector w/o type declaration, for loop sustaine condition not safe, for loop codeblock empty;

			int 
				vectorLength = 5;					// vector length moved outside the declaration - vector cannot be defined properly
			//vector</*...*/> v(vectorLength);		// no info on the vector type provided
			for (int i = 0; i < vectorLength; ++i)	// sustain condition based on a external variable instead of vector member
			{};
			cout 
				<< "Success!\n";

		}

		void d20() 
		{

			//int i = 0; int j = 9; while (i < 10) ++j; if (j < i) cout << "Success!\n"; // will never happen

			//int i = 0, j = 9;
			//while (i < 10) ++j;	// will never stop
			//if (j < i) cout << "Success!\n";	// will never be true


			int 
				i = 0, 
				j = 9;
			while (i < 10) 
				++i;	// it's the i to be asserted
			if (j < i) 
				cout 
					<< "Success!\n";

		}

		void d21() 
		{

			//int x = 2; double d = 5 / (x - 2); if (d == 2 * x + 0.5) cout << "Success!\n";

			int 
				x = 2;
			double 
				d = 5 / (double(x) - 2);					//this will yield 'inf.' but at least won't throw an exception
			if(d != (2 * x) + 0.5)	// put 2 * x in brackets - possible break of the original code
				cout 
					<< "Success!\n";		//it's rude, but effective

		}

		void d22() 
		{

			//string<char>s = "Success!\n"; for (int i = 0; i <= 10; ++i) cout << s[i];	// string doesn't accept this kind of declaration

			string 
				s = "Success!\n";						// removed the <char> thing
			for (char c : s) 
				cout 
					<< c;						// switched from for to range for loop, dumped the magic constant, and got safer

		}

		void d23() 
		{

			//int i = 0; while (i < 10) ++j; if (j < i)cout << "Success!\n"; // j not defined

			int
				i = 0,
				j = 0;						// added definition of j
			while (i < 10)
				++i;						// changed to i increment to break the while condition, and make the if condition true
			if (j < i)
				cout 
					<< "Success!\n";
		}

		void d24() 
		{
			//int x = 4; double d = 5 / (x - 2); if (d = 2 * x + 0.5) cout << "Success!\n"; // d reinitialized in the if condition ?

			int
				x = 2;
			double
				d = x == 2 ? 0 : 5 / (double(x) - 2);
			if(d = (2 * x) + 0.5)					// this is just true
				cout 
					<< "Success!\n";
		}

		void d25() 
		{
			//cin << "Success!\n"; cin requires >>, << requires cout

			cout 
				<< "Success!\n";
		}
	}
}