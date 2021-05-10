#include "std_lib_facilities.h"


namespace Ch8_lib
{
	const string 
		lineBreak{"\n\t"};

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

	void ch8_exc2()
	{
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

	void exc04()
	{
		vector<int>
			v;
		Ch8_lib::rangedFibonacci(0,1,v,INT_MAX);
		cout
			<< "\n\t"
			<< v.size()
			<< endl;
		Ch8_lib::print(v,"full fibonacci");
	}



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

	void exc05()
	{
		vector<int> v;
		for(int i = 0; i < 100 ; ++i)
			v.push_back(i);
		print(getSwappedVector(v), "swapped copy");
		print(v, "original v");
		vectorSwap(v);
		print(v,"swapped original");
		
	}



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

	void exc06()
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

	void exc07()
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

	void exc09()
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

	double maxV(vector<double> v)
	{
		double 
			result = -DBL_MAX;
		for(double d : v)
			result = max(result, d);
		return result;
	}

	void exc10()
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
		


	struct Statistics
	{
		double
			minimum {NAN},
			maximum {NAN},
			mean {NAN},
			median{NAN};
		
		void print()
		{
			cout 
				<< lineBreak
				<< "min:\t" << minimum
				<< "\nmax:\t" << maximum
				<< "\nmean:\t" << mean
				<< "\nmedian:\t" << median
				<< endl;
		}
	};

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

	void exc11()
	{
		vector<int>
			v {generateIntVector(100)};
		print(v, "original vector");
		Statistics
			s {getStatistics(v)};
		s.print();
		sort(v.begin(), v.end());
		print(v, "sorted vector");
	}


	
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

	void exc12()
	{
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



	void firstAndLast(vector<string>v )
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

	vector<int> countLetters(const vector<string> &v)
	{
		vector<int>
			lengths;
		for(string s : v)
			lengths.push_back(narrow_cast<int>(s.size()));
		return lengths;
	}
		
	void exc13()
	{
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
			"janek",
			"placek",
			"gacek",
			"tacek"};
		firstAndLast(v);
		shortestAndLongest(v);
		print(countLetters(v), "lengths");
	}

}

void ch8_exc2sqq_Main()
{
	//Ch8_lib::exc05();
	//Ch8_lib::exc06();
	//Ch8_lib::exc07();
	//Ch8_lib::exc09();
	//Ch8_lib::exc10();
	//Ch8_lib::exc11();
	//Ch8_lib::exc12();
	//Ch8_lib::exc13();
}
