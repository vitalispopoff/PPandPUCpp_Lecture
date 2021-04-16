#include "std_lib_facilities.h"

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



	struct Date
	{
		int
			y,
			m,
			d;

		Date(int y, int m, int d){};
		void init_day(Date &dd, int y, int m, int d){};
		void add_day(int n){}; 



	};

	void ch9_3()
	{



	}

}

void ch09Main()
{
	using namespace ch9_lib;


}