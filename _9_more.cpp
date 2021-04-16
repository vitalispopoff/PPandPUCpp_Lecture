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



	//class Date
	//{
	//	public:
	//		Date(int, int, int);

	//		//void add_day(int n){}
	//		
	//		void year(int);
	//		void month(int);
	//		void day(int);
	//		
	//		int year();
	//		int month();
	//		int day();
	//	
	//	private:
	//		int
	//			y, m, d;		
	//};

	//Date::Date(int iy,int im,int id) : y(iy), m(im), d(id) {};
	void Date::year(int i) { y = i; }
	void Date::month(int i) { m = i; }
	void Date::day(int i) { d = i; }

	int Date::year() { return y; }
	int Date::month() { return m; }
	int Date::day() { return d; }



	void ch9_3()
	{
		Date d{1972, 2, 21};


	}

}

ch9_lib::Date::Date(int iy,int im,int id) : y(iy),m(im),d(id) {};

void ch09Main()
{
	using namespace ch9_lib;


}