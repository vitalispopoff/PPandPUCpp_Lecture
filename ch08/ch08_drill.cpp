#include "../_add/std_lib_facilities.h"

#include "ch08.h"

namespace ch08
{
	namespace drill
	{
		namespace d02
		{
			void swap_v(int a, int b)
			{
				int 
					temp;
				temp = a;
				a = b;
				b = temp;
			}

			void swap_r(int& a, int& b)
			{
				int 
					temp;
				temp = a;
				a = b;
				b = temp;
			}

			// highlighted by intellisense already
			//void swap_v(const int& a, const int& b)
			//{
			//	int temp;
			//	temp = a;
			//	a = b;
			//	b = temp;
			//}

			void d02_main()
			{
				int
					x = 7,
					y = 9;
				swap_v(x, y);
				cout 
					<< x 
					<< endl;
				swap_r(x, y);
				cout 
					<< x 
					<< endl;
			}
		}

		namespace d03
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

			void d03_main()
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
				print();
				X::print();
			}
		}		
	}
}