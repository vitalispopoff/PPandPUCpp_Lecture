#include "std_lib_facilities.h"
#include <iostream>
#include "_2_io.h"

namespace ch10_examples
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
	/*
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

	struct Day
	{
		vector<double>
			hour{24,not_a_reading};
	};

	ostream & operator << (ostream & os, const Day & d)
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

	ofstream &print_day(ofstream & os,const Day & d)
	{
		for(double h : d.hour)
			os
				<< h;
		return os;
	}

	struct Month
	{
		int
			month{not_a_month};
		vector<Day>
			day{32};
	};
	
	ostream & operator << (ostream & os, const Month & m)
	{
		if(m.month == not_a_month)
			return os << " --- \n";
		os
			<< "Month: "
			<< m.month
			<< endl;
		for (Day d : m.day)
			os
				<< d;
		return os;
	}

	ofstream &print_month(ofstream &os,const Month &m)
	{
		os
			<< m.month
			<< endl;
		for(Day d : m.day)
			print_day(os,d);
		return os;
	}
	
	vector<string> 
		month_input {
			"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"
		};

	int month_to_int(string m)	// implementations is irrelevant for now
	{
		for (int i = 0 ; i < month_input.size(); ++i)
			if(month_input[i] == m)
				return i + 1;
		return 0;
	}
	string int_to_month(int i)
	{
		i--;
		if (i < 0 || 12 <= i)
			error("bad month index");
		return month_input[i];
	}

	constexpr int
		implausible_min = -200,
		implausible_max = 200;
	
	bool is_valid(Reading r)
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
		Year() : year{0}
		{}
	};

	ostream & operator << (ostream & os, const Year & y)
	{
		os
			<< "Year: "
			<< y.year
			<< endl;
		for(Month m : y.month)
			os 
				<< m;
		return os;
	}
	ofstream &print_year(ofstream &os,const Year &y)
	{
		os 
			<< y.year;
		for(Month m : y.month)
			print_month(os,m);
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
		y.year = yy;

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
			print_year(ost, y);		// TODO : check if the ofstream print functions cover output format the same way ifstream input functions do.
	}*/
}

namespace ch10_drill01
{	
	vector<Point>
		points;

	Point::Point() 
		: x{0}, y{0} 
		{}

	Point::Point(int i1, int i2)
		: x{i1}, y{i2} 
		{}

	Point & Point::addPoint(int x, int y)
	{
		points.push_back(Point(x, y));
		int
			index {narrow_cast<int>(points.size() - 1)};
		return points[index];
	}
		
	ostream & operator << (ostream & os, const Point & p)
	{
		os
			<< '('
			<< p.x
			<< ','
			<< p.y
			<< ')';
		return os;
	}

	istream & writePoint(istream & is)
	{
		int
			x,		y;
		is 
			>> x	>> y;
		Point::addPoint(x, y);
		return is;
	}
	
	string 
		filename{"E:\\_LAB\\_C\\PPandPUCpp_Lecture\\_other\\ch10_dril01.tmp"};

	void write()
	{
		cout 
			<< "enter points\t";
		for(int i = 0; i < 6; ++i)
			writePoint(cin);
		cout
			<< "\nenter file name.\n";
		string
			outputFileName;
		cin 
			>> outputFileName;
		ofstream
			ofs {outputFileName};
		if (!ofs)
			error("ofs no no.");
		for(Point point : points)
			ofs 
				<< '(' 
				<< point.x
				<< ','
				<< point.y
				<< ')'
				<< endl;
		if(filename == "")
			filename = outputFileName;
	}

	void read()
	{
		string
			inputFileName{};
		if (filename == "")
		{
			cout
				<< "enter file name.\n";
			cin 
				>> inputFileName;
		}
		else
			inputFileName = filename;
		ifstream
			ifs {inputFileName};
		if(!ifs)
			error("error in reading file ", inputFileName);
		while(ifs)
		{
			char
				c1,		c2,		c3;
			int
				x,		y;	
			ifs 
				>> c1 
				>> x 
				>> c2 
				>> y 
				>> c3;
			if(c1 =='(' && c2==',' && c3==')')		
				cout 
					<< Point(x,y)
					<< endl;
		}
		// read list point twice... hmmmm

	}
}

void IOStreamsMain()
{
	//ch10_drill01::write();
	ch10_drill01::read();

}