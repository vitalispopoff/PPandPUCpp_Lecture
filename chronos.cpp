#include "std_lib_facilities.h"
#include "chronos.h"

namespace Chronos
{

	//	--------------------------------------------	class Year;

	Year::Year() 
		: year{0}{}
	Year::Year(int i)
		: year{i}
	{
		if(i < min || max <= i)
			throw Invalid();
	}

	istream & operator >> (istream &is,Year &y)
	{
		int i;
		is >> i;
		if(isValidYear(i))
			y.setValue(i);
		else
			throw Year::Invalid{};
		return is;
	}

	bool isValidYear(int i)
	{
		return Year::min <= i && i < Year::max &&i != 0;
	}

	bool isLeapYear	(int i)
	{
		return
			(i % 4 == 0 && i % 100 != 0)
			|| i % 400 == 0;
	}

	int countLeapYears(int begin,int end)
	{
		if(end == begin)
			return 0;
		int
			leapCandidates{(end / 4) - (begin / 4)},
			centuryExclusions{(end / 100) - (begin / 100)},
			quadCenturyInclusions{(end / 400) - (begin / 400)};
		return abs(leapCandidates - (centuryExclusions - quadCenturyInclusions));
	}

	int countLeapYears(int end)
	{
		if(end <= 1970)
			return 0;
		int
			leapCandidates{(end / 4) - 492},
			centuryExclusions{(end / 100) - 19},
			quadCenturyInclusions{(end / 400) - 4};
		return leapCandidates - (centuryExclusions - quadCenturyInclusions);
	}

	//	--------------------------------------------

	Month operator ++ (Month &m)
	{
		return int(m) > 0
			? (m == Month::Dec) ? Month::Jan : Month(int(m) + 1)
			: Month(0);
	}
	
	Month operator -- (Month &m)
	{
		return int(m) > 0
			? (m == Month::Jan) ? Month::Dec : Month(int(m) - 1)
			: Month(0);
	}

	bool isValidMonth	(int i)
	{
		return
			int(Month::Jan) <= i
			&& i <= int(Month::Dec);
	}

	Month int_to_month	(int i)
	{
		if(i < int(Month::Jan) || int(Month::Dec) < i)
			error("unavailable month value");
		return Month(i);
	}

	bool isValidDay(int i)
	{
		return 1 <= i && i <= 31;
	}

	//	--------------------------------------------	class Date; 

	Date::Date()
		: year{Year::defaultYear()},month{Month(0)},day{0} { }

	Date::Date(Year y,Month m,int d)
		: year{y},month{m},day{d}
	{
		if(!isValid())
			throw Invalid{};
	}

	bool	Date::isValid	() const
	{
		return
			int(Month::Jan) <= int(month)
			&& int(month) <= int(Month::Dec);
	}

	bool Date::isBiggerThan(const Date &date) const
	{
		if(year.getValue() > date.year.getValue())
			return true;
		else if(year.getValue() == date.year.getValue())		// the same year
		{
			if(int(month) > int(date.month))
				return true;
			else if(int(month) == int(date.month))						// the same year and month
				if(day > date.day)
					return true;
		}
		return false;
	}

	ostream &operator<<(ostream &os,const Date &d)
	{
		return
			os
			<< d.getYear().getValue()
			<< '.'
			<< int(d.getMonth())
			<< '.'
			<< d.getDay();
	}

	istream &operator>>(istream &is,Date &date)
	{
		int
			y,m,d;
		char
			c1{0},c2{0};
		auto
			separators = [&] { return c1 == '.' && c2 == '.'; };
		is
			>> y
			>> c1
			>> m
			>> c2
			>> d;
		if(isValidDate(y,m,d) && separators())
		{
			date.setYear(y);
			date.setMonth(Month(m));
			date.setDay(d);
		}
		else cout << "wrong data for date.\ndate set to" << endl;

		return is;
	}

	bool operator==(const Date &a,const Date &b)
	{
		return
			a.getYear().getValue() == b.getYear().getValue()
			&& int(a.getMonth()) == int(b.getMonth())
			&& a.getDay() == b.getDay();
	}

	bool operator!=(const Date &a,const Date &b)
	{
		return
			a.getDay() != b.getDay()
			|| int(a.getMonth()) != int(b.getMonth())
			|| a.getYear().getValue() != b.getYear().getValue();
	}

	bool operator>(const Date &a,const Date &b)
	{
		if(a.getYear().getValue() > b.getYear().getValue())
			return true;
		else if(a.getYear().getValue() == b.getYear().getValue())		// the same year
		{
			if(int(a.getMonth()) > int(b.getMonth()))
				return true;
			else if(a.getMonth() == b.getMonth())						// the same year and month
				if(a.getDay() > b.getDay())
					return true;
		}
		return false;
	}

	bool isValidDate(int y,int m,int d)
	{
		bool
			isYear{isValidYear(y)},
			isMonth{isValidMonth(m)};
		auto isDay = [&]
		{
			return 1 <= d && (
					(d <= int (isLeapYear(y) + 28) && m == 2)
					|| (d <= 30 && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12))
					|| (d <= 31 && (m == 4 || m == 6 || m == 19 || m == 11)));
		};
		return isYear && isMonth && isDay();
	}
}

//	--------------------------------------------------------------------------------------------

void chronosMain()
{


}