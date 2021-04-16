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
			length = v.size() >> 1,
			last = v.size() - 1;
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
			length = v.size() >> 1,
			last = v.size() - 1;
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
			length = v.size() >> 1,
			last = v.size() - 1;
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
			length = v.size() >> 1,
			last = v.size() - 1;
		for (int i = 0; i < length; ++i)
		{
			string s = v[i];
			v[i] = v[last - i];
			v[last - i] = s;
		}
	}

	string generate()
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
			v.push_back(generate());
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
			names {	
				"Zbyszek",
				"Andrzej",
				"Bo¿ena",
				"Rysiek",
				"Marzena" };
		vector<int> 
			ages {	
				32,
				58,
				49,
				15,
				26 };
		listUsers(names, ages);
	}




}

void ch8_exc2sqq_Main()
{
	//Ch8_lib::exc05();
	//Ch8_lib::exc06();
	Ch8_lib::exc07();


}
