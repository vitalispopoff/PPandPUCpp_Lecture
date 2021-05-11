#pragma once

namespace ch02
{
	namespace example
	{
		void f01();
	
		struct location 
		{
			double 
				x, 
				y;
	
			bool equals(location l) 
			{ 
				return x == l.x && y == l.y; 
			}
		};
	
		void f02();
	
		void f03(location, location);
	
		namespace cookbook
		{};
	}
	
	namespace drill
	{};
	
	namespace excercise
	{};
}
			
//void ch02_main()												/// causes err LNK2005, LNK1169
//{
//	//using namespace ch02::example;
//	
//	//f01();
//}