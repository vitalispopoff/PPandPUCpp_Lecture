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
	}



	void example_01()
	{
		X	x;
		int	y = x.f(2);		
	}

	void example_02()
	{
		Chronou::Date
			d{1972, Chronou::Month(2), 21};					//Month moved from 'int' to 'enum'
			//d{1972, static_cast<Chronou::Month>(2), 21};	//it might be cast as well... just leaving it here/
	}

	void example_03(int x, int y)
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
			cout 
				<< d 
				<< endl;
	}

	void example_09(Chronou::Date &d, const Chronou::Date &statOfTerm)
	{
		int a	{d.getDay()};
		//int b {startOfTerm.getDay()}; // can't directly process 'const', but can't declare a non-member function 'const' either, so...
		Chronou::Date 
			tmp{statOfTerm};
		int	b	{tmp.getDay()};
	}

	void example_10(Chronou::Date &startOfTerm)
	{
		int a {startOfTerm.getDay()};
	}


}

void ch09Main()
{
	using namespace ch9_lib;
	
	Chronou::Date 
		d {};

	//example_01();
	example_02();
	//example_03(1, 2);
	//example_07();
	//example_08();
	//example_09(d, Chronou::Date{});	// reference to non-const must be lvalue, hence 'd'.
	//example_10(d);

}