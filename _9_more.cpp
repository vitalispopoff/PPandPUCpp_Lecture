#include "std_lib_facilities.h"
#include "_9_more.h"

namespace ch9_lib
{

	class X
	{	
		int 
			m;
		int mf(int v)
		{
			int old = m;
			m = v;
			return old;
		}

		public:
			int f(int i)
			{
				m = 1;
				return mf(i);
			}
	};

	void ch9_2()
	{
		X 
			x;
		int
			y = x.f(2);		
	}


	
	class Date;		// declaration of the class moved to the header file.

	Date::Date(Year i1, Month i2,int i3) : y{i1}, m{i2}, d{i3}
	{ 
		if (!is_valid())
		{	
			cout << "BOINK!";
			throw Invalid{};
		}	
	}

	void Date::year	(Year y)	{ this -> y = y; }
	void Date::month(Month m)	{ this -> m = m; }
	void Date::day	(int d)		{ this -> d = d; }

	Year Date::year	()		{ return y; }
	Month Date::month	()	{ return m; }
	int Date::day	()		{ return d; }

	void Date::add_day	(int i)	{ d += i;}
	bool Date::is_valid	()		{ return 1 <= int(m) && int(m) <= 12; }
	


	class Year;

	Year::Year(int i) : y{i}
	{
		if( i < min || max <= i)
			throw Invalid();
	}

	void Year::year	(int i)	{ y = i; }
	
	int Year::year	()		{ return y; }





	enum Month;

	Month int_to_month(int i)
	{
		if (i < int(Month::Jan) || int(Month::Dec) < i)
			error("unavailable month value");
		return Month(i);
	}

	Month operator++(Month &m)
	{
		m = (m == Month::Dec) ? Month::Jan : Month(int(m) + 1);
		return m;
	}

	Month operator--(Month &m)
	{
		m = (m == Month::Jan) ? Month::Dec : Month(int(m) - 1);
		return m;
	}

	//void ch9_4_6(int x,int y)
	//{
	//	try
	//	{
	//		Date 
	//			dxy {2004, x, y};
	//		cout
	//			//<< dxy	// operand not implemented.
	//			<< endl;
	//		dxy.add_day(2);
	//	}
	//	catch (Date::Invalid)
	//	{
	//		error("invalid date");
	//	}
	//}
}




void ch09Main()
{
	using namespace ch9_lib;
	
	//ch9_4();

	

}