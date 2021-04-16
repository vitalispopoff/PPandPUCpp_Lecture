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

	void temp()
	{
		X 
			x;
		int
			y = x.f(2);		
	}
}

void ch09Main()
{
	using namespace ch9_lib;


}