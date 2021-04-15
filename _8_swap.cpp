#include "std_lib_facilities.h"
#include "_8_technicalities.h"

void swap_v(int a, int b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void swap_r(int& a, int& b)
{
	int temp;
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

void swapMain()
{
	int
		x = 7,
		y = 9;

	swap_v(x, y);
	cout << x << endl;

	swap_r(x, y);
	cout << x << endl;


}

