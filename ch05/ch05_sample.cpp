#include "../_add/std_lib_facilities.h"
#include "../ch05/ch05.h"

namespace ch05
{
	namespace sample
	{
		namespace s01
		{
			//int s1 = area(7;					// err E0018, C2143, C2660
			//int s2 = area()					// err E0165, E0065, C2660, C2144
			//Int s3 = area(7);					// err E0020, E0165, C2660, C2144
			//int s4 = area('7);				// err E0008, E0018, C2660, C2144
		}

		namespace s02
		{
			//int x0 = arena(7);				// err E0020, C3861
			//int x1 = area(7);					// err E0165, C2660
			//int x2 = area("seven", 2);		// err E0167, C2664
		}

		namespace s03
		{
			//int area(int x, int y) 
			//{ 
			//	return x * y;					/// orginal implementation, non secure;
			//}	
			// 
			//int x4 = area(10, -7);			// 	
			//int x5 = area(10.7, 9.3);			//
			//char x6 = area(100, 9999);		//
		}

		namespace s04
		{
			//int f(int i1, int i2);
			//int f(double d1, double d2) { return 0; };
			//int f(int i1, int i2);
			//int x = f(2, 3);					// err LNK2019, LNK1120
		}

		void s05()
		{
			string 
				s;
			while (cin >> s) 
				throw runtime_error("because we can");
		}

		namespace s06
		{			 
			int area (int length, int width) 
			{
				return length * width;
			}

			int framedArea (int x, int y) 
			{
				return area(x - 2, y - 2);
			}
		}

		void s07()
		{
			using namespace s06;

			int
				x	{-1},
				y	{2},
				z	{4},
				ar1 {area(x, y)},								/// -1 * 2 == -2
				ar2 {framedArea(1, z)},							/// -1 * (4-2) == -2
				ar3 {framedArea(y, z)};							/// (2-2) * (4-2) == 0
		double
			ratio	{double(ar1) / ar3};							/// -2 : 0 == -inf.
		}

		void s08()
		{
			using namespace s06;
			int 
				x, 
				y, 
				z;
			{
				x = -1; y = 2; z = 4;
			}

			if (x <= 0 || y <= 0) 
				throw runtime_error("non-positive area() argument");
			int 
				ar1 {area(x, y)};

			if (z <= 2) 
				throw runtime_error("non positive area() width called by framedArea()");
			int 
				ar2 {framedArea(1, z)};

			if (y <= 2 || z <= 2) 
				throw runtime_error("non-positive area() argument called bye framedArea()");
			int 
				ar3 {framedArea(y, z)};
		}

		namespace s09
		{
			using namespace s06;

			constexpr int 
				frameWidth {2};

			int framedArea(int x, int y) 
			{
				return area(x - frameWidth, y - frameWidth);
			}
		}

		namespace s10
		{
			int area(int x, int y)
			{
				return x * y;
			}
			int framedArea(int x, int y) 
			{
				constexpr int 
					frameWidth {2};
				if (x <= frameWidth || y <= frameWidth)
					throw runtime_error("non-positive area() arguments intercepted by framedArea()");
				return area(x - frameWidth, y - frameWidth);
			}

		}

		namespace s11
		{							
			int area(int length, int width)						/// area() handling by throwing an exception
			{
				if (length <= 0 || width <= 0) 
					throw BadArea{};
				return length * width;
			}

			int framedArea(int x, int y)						/// framedArea() - non secure 
			{
				return area(x - 2, y - 2);
			}

			void s06_main()									///main scope secured with try-catch focused on BadArea type
			{
				try 
				{
					int 
						x, y, z;
					{
						x = -1; 
						y = 2; 
						z = 4;
					}
					int 
						ar1 {area(x, y)},
						ar2 {framedArea(1, z)},
						ar3 {framedArea(y, z)};
					double 
						ratio	{double(ar1) / double(ar3)};
				}
				catch (BadArea) 
				{ 
					cout 
						<< "\n\tGotcha!\n"; 
				}
			}
		}

		void s12()
		{
			vector<int>	
				v;
			for (int i; cin >> i; )
				v.push_back(i);
		}

		void s13()
		{
			vector<int>	
				v;
			for (int i = 0; i < v.size(); ++i)
				cout
					<< "v["
					<< i
					<< "]=="
					<< v[i]
					<< 'n';
		}

		void s14()
		{
			vector<int>	
				v;
			s13();
			int
				counter	{0};
			for (int i : v)
				cout
					<< "v["
					<< counter++
					<< "]=="
					<< i
					<< '\n';
		}

		void s15()
		{				
			vector<int>	
				v;
			s13();
			try 
			{
				for (int i = 0; ; ++i)
					cout 
						<< "\n\tv[" 
						<< i 
						<< "] == " 
						<< v[i];
			}
			catch (out_of_range) 
			{
				cerr 
					<< "\n\tWhooops.\n";
			}
			catch (...) 
			{
				cerr 
					<< "\n\tSomething completely different.\n";
			}
		}

		void s16() 
		{
			double 
				d;
			while (true) 
			{
				cin 
					>> d;
				if (!cin) 
					throw runtime_error("cin error - couldn't read a double");
			}
		}

		void s17() 
		{
			vector <int> 
				v {0};
			try 
			{
				for (int i = 0; ; ++i)
					v[i];
			}
			catch (out_of_range & e) 
			{
				cerr 
					<< "oops...\n";
			}
		}

		void s18() 
		{
			//Exception thrown at 0x00085344 in PPandPUCpp_Lecture.exe: 0xC0000094 : Integer division by zero.
			//Unhandled exception at 0x00085344 in PPandPUCpp_Lecture.exe : 0xC0000094 : Integer division by zero.

			int 
				i;
			cin 
				>> i;
			try 
			{
				i = 2 / i;
			}
			catch (runtime_error & e) 
			{
				cerr 
					<< "runtime error: " 
					<< e.what() 
					<< '\n';
			}
			cout 
				<< "\n\twe good" 
				<< endl;
		}

		void s19() 
		{
			//Exception thrown at 0x00983EC1 in PPandPUCpp_Lecture.exe: 0xC0000094 : Integer division by zero.
			//Unhandled exception at 0x00983EC1 in PPandPUCpp_Lecture.exe : 0xC0000094 : Integer division by zero.

			int 
				i;
			cin 
				>> i;
			i = 1 / i;
		}

		void s20() 
		{
			double 
				d = 2.9;

			//Exception thrown at 0x76A2A8B2 in PPandPUCpp_Lecture.exe: Microsoft C++ exception : std::runtime_error at memory location 0x007AF874.
			//Unhandled exception at 0x76A2A8B2 in PPandPUCpp_Lecture.exe: Microsoft C++ exception : std::runtime_error at memory location 0x007AF874.
			//int x1 = narrow_cast<int>(d);

			int 
				x2 {narrow_cast<int>(floor(d))},
				i {1066};

			//Exception thrown at 0x76A2A8B2 in PPandPUCpp_Lecture.exe: Microsoft C++ exception : std::runtime_error at memory location 0x0079F508.
			//Unhandled exception at 0x76A2A8B2 in PPandPUCpp_Lecture.exe: Microsoft C++ exception : std::runtime_error at memory location 0x0079F508.
			//char c1 = narrow_cast<char>(i);

			char 
				c2 {narrow_cast<char>(i % 256)};
		}

		void s21() 
		{
			vector < double> 
				temperatures;

			for (double temp; cin >> temp; temperatures.push_back(temp))
			{};

			//double sum = 0, highTemp = 0 , lowTemp= 0;	

			double 
				sum {0}, 
				highTemp, 
				lowTemp;
			highTemp = lowTemp = temperatures[0];

			//for (int x : temperatures)

			if (temperatures.size() > 0) 
			{
				for (double x : temperatures)
				{
					highTemp = max(highTemp, x);
					lowTemp = min(lowTemp, x);
					sum += x;
				}
				cout
					<< "\n\tHigh temperature:\t"	
					<< highTemp
					<< "\n\tLow tempererature:\t"	
					<< lowTemp
					<< "\n\tAverage temperature:\t"	
					<< sum / temperatures.size()
					<< endl;
			}
			else 
				cout 
					<< "no data provided.";
		}
	}
}
