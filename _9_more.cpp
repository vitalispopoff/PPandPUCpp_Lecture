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

	void Date::year	(int i)	{ y = i; }
	void Date::month(int i) { m = i; }
	void Date::day	(int i)	{ d = i; }

	int Date::year	()	{ return y; }
	int Date::month	()	{ return m; }
	int Date::day	()	{ return d; }

	void Date::add_day	(int i)	{ d += i;}
	bool Date::is_valid	()		{ return 1 <= m && m <= 12; }
	


	void ch9_4	()	{ Date d {1972, 2, 21}; }

	void ch9_4_6(int x,int y)
	{
		try
		{
			Date 
				dxy {2004, x, y};
			cout
				//<< dxy	// operand not implemented.
				<< endl;
			dxy.add_day(2);
		}
		catch (Date::Invalid)
		{
			error("invalid date");
		}
	}
}

ch9_lib::Date::Date(int iy,int im,int id) : y{iy}, m{im}, d{id} 
{ 
	if (!is_valid())
	{	
		cout << "BOINK!";
		throw Invalid{};
	}	
}



void ch09Main()
{
	using namespace ch9_lib;
	
	ch9_4();


}