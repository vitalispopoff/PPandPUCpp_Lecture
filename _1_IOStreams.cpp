#include "std_lib_facilities.h"
#include <iostream>

namespace ch10
{
	void example01()
	{		
		string
			inputFileName{"E:\\_LAB\\unpeak\\shortie\\1kHz_16_mono.wav"};
		if(inputFileName.size() ==0)
		{
			cout
				<< "Please enter input file name:\t";
			cin
				>> inputFileName;
		}
		ifstream
			ist{inputFileName};
		if (!ist)
			error("I can't open input file ", inputFileName);
		vector<unsigned char> 
			bytes;
		for (unsigned char byte; ist >> byte; )
			bytes.push_back(byte);
		int 
			index{0};
		for (unsigned char byte : bytes)
			cout 
				<< int(byte)
				<< (index++ % 8 == 7 ? '\n' : '\t');
	}	

	//	----------------------------	Example 02

	void end_of_loop(istream & ist, char term, const string & message)
	{
		if (ist.fail())
		{
			ist.clear();
			char
				ch;
			if (ist >> ch && ch == term)
				return;
			error(message);
		}
	}

	const int
		not_a_reading = -7777,
		not_a_month = -1;

	struct Day
	{
		vector<double>
			hour{24,not_a_reading};
	};

	ostream & print_day(ostream & os, const Day & d)
	{
		int 
			index{0};
		for (int i = 0; i < d.hour.size(); ++i)
			if (d.hour[i] != not_a_reading)
			{
				index ++;
				os
					<< "\n\t\t"
					<< i
					<< '.\t'
					<< d.hour[i];
			}
		if(index > 0)
			os << endl;
		return os;
	}

	
	struct Month
	{
		int
			month{not_a_month};
		vector<Day>
			day{32};
	};
	
	ostream & print_month(ostream & os, const Month & m)
	{
		if(m.month == not_a_month)
			return os << " --- \n";
		os
			<< "Month: "
			<< m.month
			<< endl;
		for (Day d : m.day)
			print_day(os, d);
		return os;
	}

	int month_to_int(string m)	// implementations is irrelevant for now
	{
	return 0;
	}

	constexpr int
		implausible_min = -200,
		implausible_max = 200;
	
	bool is_valid(Reading r)	// implementations is irrelevant for now
	{
		if (r.day < 1 || 31 < r.day)
			return false;
		if (r.hour < 0 || 23 < r.hour)
			return false;
		if (r.temperature < implausible_min || implausible_max < r.temperature)
			return false;
		return true;
	}

	istream & operator >> (istream & is, Month& m)
	{
		char
			ch = 0; // why '=' instead of '{}' ?
		if (is >> ch && ch != '{')
		{
			is.unget();
			is.clear(ios_base::failbit);
			return is;
		}

		string
			month_marker,
			mm;
		is 
			>> month_marker		>> mm;

		if (!is || month_marker != "month")
			error("bad start of month");
		m.month = month_to_int(mm);

		int
			duplicates = 0,		invalids = 0;

		for(Reading r; is >> r; )
		{
			if (is_valid(r))
			{
				if (m.day[r.day].hour[r.hour] != not_a_reading)
					++duplicates;
				m.day[r.day].hour[r.hour] = r.temperature;
			}
			else
				++ invalids;
		}
		if (invalids)
			error("invalid readeings in month", invalids);
		if (duplicates)
			error("duplicate readings in month", duplicates);
		end_of_loop(is, '}', "bad oend of month");
		return is;
	}

	struct Year
	{
		int
			year;
		vector<Month>
			month{12};
	};

	ostream & print_year(ostream & os, const Year & y)
	{
		os
			<< "Year: "
			<< y.year
			<< endl;
		for(Month m : y.month)
			print_month(os, m);
		return os;
	}


	istream & operator >> (istream & is, Year & y)
	{
		char
			ch;
		is
			>> ch;
		if (ch != '{')
		{
			is.unget();
			is.clear(ios::failbit);
			return is;
		}
		string
			year_marker;
		int
			yy;
		is 
			>> year_marker	
			>> yy;
		if (!is || year_marker != "year")
			error("bad start of year");
		y.year == yy;

		while(true)
		{
			Month
				m;
			if (!(is >> m))
				break;
			y.month[m.month] = m;	// y.month is a vector<Month>, and m.month is defind int index
		}
		end_of_loop(is, '}', "bad end of year");
		return is;	
	}

	struct Reading
	{
		int
			day,
			hour;
		double
			temperature;
	};

	istream & operator >> (istream & is, Reading & r)
	{ 
		char 
			ch1;
		if (is >> ch1 && ch1 != '(')
		{
			is.unget();
			is.clear(ios_base::failbit);
			return is;
		}
		char
			ch2;
		int
			d,	h;
		double
			t;
		is
			>> d	>> h	>> t	>> ch2;

		if (!is || ch2 != ')')
			error("bad reading");

		r.day = d;
		r.hour = h;
		r.temperature = t;
		return is;
	}


	void example02()
	{
		string
			iname{};
		if (iname.size() == 0)
			cout
				<< "Enter input file name\n";
		cin
			>> iname;
		ifstream 
			ist {iname};
		if (!ist)	// originally written as "ifs"
			error("can't open input file ", iname);
		ist.exceptions(ist.exceptions() | ios_base::badbit);	// exceptions gets the error bit mask (four errors in a single byte?), and sets its value.

		string
			oname{};
		if (oname.size() == 0)
			cout
				<< "Enter output file name\n";
		cin	
			>> oname;
		ofstream 
			ost {oname};
		if (!ost)	// originally written as "ofs"
			error("can't open output file ", oname);

		vector<Year>
			ys;
		while(true)
		{
			Year
				y;
			if (!(ist >> y))
				break;
			ys.push_back(y);
		}
		cout
			<< "read "
			<< ys.size()
			<< " years of readings\n";
		for (Year & y : ys)
			print_year(ost, y);
	}
}

void IOStreamsMain()
{
	//using namespace ch10;

}