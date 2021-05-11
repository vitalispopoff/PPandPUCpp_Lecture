#pragma once

namespace ch05
{
	namespace sample
	{
		void s05();

		namespace s06
		{
			int area(int, int);

			int framedArea(int, int);
		}

		void s07();

		void s08();

		namespace s09
		{
			int framedArea(int, int);
		}

		namespace s10
		{
			int area(int, int);

			int framedArea(int, int);
		}

		namespace s11
		{
			class BadArea										///BadArea - exception type dedicated to area();
			{};

			int area (int, int);

			int framedArea (int, int);

			void s06_main();			
		}

		void s12();

		void s13();

		void s14();

		void s15();

		void s16();

		void s17();

		void s18();

		void s19();

		void s20();

		void s21();
	}

	namespace drill
	{		
		void d01();
		
		void d02();
		
		void d03();
		
		void d04();
		
		void d05();
		
		void d06();
		
		void d07();
		
		void d08();
		
		void d09();
		
		void d10();
		
		void d11();
		
		void d12();
		
		void d13();
		
		void d14();
		
		void d15();
		
		void d16();
		
		void d17();
		
		void d18();
		
		void d19();
		
		void d20();
		
		void d21();
		
		void d22();
		
		void d23();
		
		void d24();
		
		void d25();
	}

	namespace excercise
	{
		namespace e02
		{
			double CelsiusToKelvin(double);

			void e02_main();
		}

		namespace e04
		{
			double CelsiusToKelvin(double);

			void e04_main();
		}

		namespace e05
		{
			double CelsiusToKelvin(double, char);

			void e05_main();
		}

		namespace e06
		{
			double CelsiusToFahrenheit(double, char);

			void e06_main();
		}

		void e07();
		void e08();
		void e09();
		void e10();
		void e11();
		
		namespace e12
		{
			struct num 
			{
				int
					answer,
					guess;
				//bool
				//	status{ false };	// cow == true

				num(int a) :
					answer {a}
				{}
				bool bull() 
				{
					return answer == guess;
				}
			};

			void e12_main();
		}

		void e14();
	}
}