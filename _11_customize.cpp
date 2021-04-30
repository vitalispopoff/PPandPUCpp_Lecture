#include "std_lib_facilities.h"

namespace ch11
{
	char
		t{'\t'},
		n{'\n'};
		string
			tt{"\t\t"};

	//	bases and cout malipunators

	void example01()
	{
		int
			i{1234};
		cout
			<< n << dec << i << t << "(decimal)" 
			<< n << hex << i << t << "(hexadecimal)" 
			<< n << oct << i << t << "(octal)" 
			<< n;
		cout
			<< n << (i >> 2)
			<< n;
	}

	void tryThis01()
	{
		int
			pastYear{2000},
			thisYear{2021},
			years{thisYear - pastYear};
		cout
			<< n 
			<< t << hex << years
			<< t << oct << years
			<< t << dec << years
			<< n;
	}

	void example02()
	{
		int
			i{1234};
		cout
			<< t << dec << i 
			<< t << hex << i 
			<< t << oct << i 
			<< n;
		cout 
			<< showbase;
		cout
			<< t << dec << i
			<< t << hex << i
			<< t << oct << i
			<< n;
		cout
			<< noshowbase
			<< dec;
		cout
			<< t << i
			<< t << 0x4d2
			<< t << 02322
			<< n;
	}

	// bases and cin matilunapors

	void tryThis02()
	{
		int
			i1{0},
			i2{0},
			i3{0};
		cin 
			>> dec >> i1 
			>> hex >> i2 
			>> oct >> i3;

		cout 
			<< dec
			<< t << i1
			<< t << i2
			<< t << i3
			<< n;
	}

	// ios_base::fmtflags

	void example03()
	{
		cin.unsetf(ios::dec);
		cin.unsetf(ios::oct);
		cin.unsetf(ios::hex);
		int
			a,	b,	c,	d;
		cin 
			>> a
			>> b
			>> c;
		cin.setf(ios::dec);
		cin.setf(ios::oct);
		cin.setf(ios::hex);
		cin
			>> d;
		cout
			<< n
			<< t << a
			<< t << b
			<< t << c
			<< t << d
			<< n;
	}

	//	floating-point outpoop

	void example04()
	{
		double
			d{1234.56789};
		cout
			<< t << defaultfloat
				<< d << tt << "(default)" << n
			<< t << fixed 
				<< d << t << "(fixed)" << n
			<< t << scientific 
				<< d << t << "(scientific)" << n;
	}

	// floating-point precission

	void tryThis03()
	{
		double
			d{1234567.89};
		cout
			<< t << defaultfloat	
			<< d << n
			<< t << scientific
			<< d << n
			<< t << fixed
			<< d << n;
	}

	void example05()
	{
		double
			d{1234.56789};
		int
			p1{5},
			p2{8},
			implicit{6};
		cout
			<< t 
				<< d << tt 
			<< fixed 
				<< d << tt 
			<< scientific 
				<< d << n;
		cout 
			<< t
			<< defaultfloat << setprecision(p1)
				<< d << tt
			<< fixed
				<< d << tt
			<< scientific
				<< d << n;
		cout 
			<< t
			<< defaultfloat << setprecision(p2)
				<< d << t
				<< fixed
				<< d << tt
				<< scientific
				<< d << n
				<< setprecision(implicit) << defaultfloat;	// default settings
	}

	// precission equivalent for integrals

	void example06()
	{
		int
			i{123456},
			width1{4},
			width2{8};
		cout	
			<< t <<'|' 
				<< i << n
			<< t << '|' << setw(width1)
				<< i << n
			<< t << '|' << setw(width2)
				<< i << n;
	}

	// but not necessarily since set width function works with floating points too
	void example07()
	{
		int
			i{123456};
		double
			d{1234.56789};
		cout
			<< setw(4)
			<< t << '|' << i << n
			<< t << '|' << d << n;
	}
}

void ch11Main()
{
	//ch11::example01();
	//ch11::tryThis01();
	//ch11::example02();
	//ch11::tryThis02();
	//ch11::example03();
	//ch11::example04();
	//ch11::tryThis03();
	//ch11::example05();
	//ch11::example06();
	ch11::example07();

}