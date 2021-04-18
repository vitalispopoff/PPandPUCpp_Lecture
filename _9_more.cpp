#include "std_lib_facilities.h"
#include "_9_more.h"

namespace ch9_lib
{	
	class X
	{	
		int	m;
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
		X	x;
		int	y = x.f(2);		
	}


	
	namespace Chronou
	{
		class Date;

		Date::Date() :
			y {defaultDate().getYear()},
			m {defaultDate().getMonth()},
			d {defaultDate().getDay()}
			{ }

		Date::Date(Year i1, Month i2,int i3) : y{i1}, m{i2}, d{i3}
		{ 
			if (!isValid())
				throw Invalid{};
		}

		void Date::setYear	(Year y)	{ this -> y = y; }
		void Date::setMonth	(Month m)	{ this -> m = m; }
		void Date::setDay	(int d)		{ this -> d = d; }
		void Date::addDay	(int i)		{ d += i; }

		Year	Date::getYear	() const { return y; } 
		Month	Date::getMonth	() const { return m; }
		int		Date::getDay	() const { return d; }
		bool	Date::isValid	() const 
		{ 
			return 
				int(Month::Jan) <= int(m) 
				&& int(m) <= int(Month::Dec); 
		}
		
		ostream& operator<<(ostream& os, Date & d)
		{
			os 
				<< d.getYear().getValue()
				<< '.'
				<< int(d.getMonth())
				<< '.'
				<< d.getDay();
			return os;
		}



		class Year;

		Year::Year(int i) : y{i}
		{
			if( i < min || max <= i)
				throw Invalid();
		}

		void Year::setValue	(int i)	{ y = i; }
	
		int Year::getValue	() const{ return y; }

		Month int_to_month(int i)
		{
			if (i < int(Month::Jan) || int(Month::Dec) < i)
				error("unavailable month value");
			return Month(i);
		}

		Month operator++(Month &m)
		{
			return 
				(m == Month::Dec) ? Month::Jan : Month(int(m) + 1);
		}

		Month operator--(Month &m)
		{
			return 
				(m == Month::Jan) ? Month::Dec : Month(int(m) - 1);
		}

		//void ch9_4_6(int x,int y)
		//{
		//	try
		//	{
		//		Date 
		//			dxy{};
		//		cout
		//			<< dxy
		//			<< endl;
		//		dxy.addDay(2);
		//	}
		//	catch (Date::Invalid)
		//	{
		//		error("invalid date");
		//	}
		//}

		//void example_7()
		//{
		//	Date
		//		d1{},
		//		d2{};

		//	d1.setYear(2021);
		//	d1.setMonth(Month::Apr);

		//	int
		//		i1 = d1.getYear().getValue(),
		//		i2 = d2.getYear().getValue();
		//	bool
		//		b = i1 == i2;

		//	cout << b;
		//}

//		/*declaring vector<Date> because default constructor*/
		//void example_8()
		//{
		//	/*use of () instead {} in the vector definition is by convention rather*/
		//	vector<Date>
		//		birthdays(10);
		//	cout 
		//		<< "\n\tsize of the vector: " 
		//		<< birthdays.size();
		//	for(Date d : birthdays)
		//		cout 
		//			<< "\n\tyear: " << d.getYear().getValue()
		//			<< "\tmonth: " << int(d.getMonth())
		//			<< "\tday: " << d.getDay();
		//	cout 
		//		<< endl;
		//}

//		/* 'startOfTerm' refuses to pass its member to 'b' directly - 'const' prevents	
//		it has no problem with passing itself tho, so it's rather a 'const' vs 'getDay()' */
		//void example_09(Date &d, const Date &startOfTerm)
		//{
		//	int a	{d.getDay()};
		//	Date tmp{startOfTerm};
		//	int b	{tmp.getDay()};
		//}

		// making 'tmp' const prevents it from passing its member to 'b'
		//void example_09(Date &d,Date &startOfTerm)
		//{
		//	int a{d.getDay()};
		//	const Date tmp{startOfTerm};
		//	int b{tmp.getDay()};
		//}
		void example_10(Date &startOfTerm)
		{
			int a {startOfTerm.getDay()};
		}
	}

	void ch9_4_6(int x, int y)
	{
		try
		{
			Chronou::Date
				dxy{};
			cout
				<< dxy
				<< endl;
			dxy.addDay(2);
		}
		catch (Chronou::Date::Invalid)
		{
			error("invalid date");
		}
	}

	void example_07()
	{
		using namespace Chronou;

		Date
			d1{},
			d2{};
		d1.setYear(2021);
		d2.setMonth(Month::Apr);		
		int
			i1 {d1.getYear().getValue()},
			i2 {d2.getYear().getValue()};
		bool
			b {i1 == i2};
		cout
			<< b;
	}

	void example_08()
	{
		using namespace Chronou;
		vector<Date>
			birthdays(10);
		cout
			<< "\n\tsize of the vector: "
			<< birthdays.size();
		for(Date d : birthdays)
			cout << d;
		cout << endl;
	}

	/* 'startOfTerm' refuses to pass its member to 'b' directly - 'const' prevents
		it has no problem with passing itself tho, so it's rather a 'const' vs 'getDay()' 
		solution is to declare the function 'const'.
		but - only class member functions may be declared 'const'
	*/
	void example_09(Chronou::Date &d, const Chronou::Date &statOfTerm)
	{
		int a	{d.getDay()};
		//int b {startOfTerm.getDay()}; // can't directly process 'const', but can't declare a non-member function 'const' either, so...
		Chronou::Date 
			tmp{statOfTerm};
		int	b	{tmp.getDay()};
	}

	/* it is the 'const' that secures the input, by authorizing only processing the functions clearly declared non-invasive.*/
	void example_10(Chronou::Date &startOfTerm)
	{
		int a {startOfTerm.getDay()};
	}


}

void ch09Main()
{
	using namespace ch9_lib;
	

	//ch9_4();
	//example7();
	//example_8();


}