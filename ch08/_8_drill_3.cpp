#include "_8_technicalities.h"
#include <iostream>

namespace ch08
{
	namespace Y
	{
		int 
			var {0};
		void print()
		{
		std::cout 
			<< var;
		}
	};

	namespace Z
	{
		int 
			var;
		void print()
		{
			std::cout 
				<< "\n\t" 
				<< var;
		}
	};

	namespace X
	{
		int 
			var;
		void print()
		{
			std::cout 
				<< "\t" 
				<< var 
				<< std::endl;
		}
	};

	void ch_8_dr_3()
	{
		X::var = 7;
		X::print();
	
		using namespace Y;

		var = 9;
		Y::print(); // doesn't work without explicit directive : err E0308, C2668
	
		{
			using Z::var;
			using Z::print;
			var=11;
			print();
		}
	}
}