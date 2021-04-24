

namespace Chronos
{
	//	--------------------------------------------	

	//	--------------------------------------------	

	class Year
	{
		public:
			class Invalid {};

			static const int
				min {-5000},
				max {2200};

			Year();
			Year (int);

			void	setValue	(int i)		{ value = i; }
			int		getValue	()	const	{ return value; };

			static Year & implicit()
			{
				static Year
					impl{0};
				return impl;
			}

		private:
			int value;
	};

	istream & operator >> (istream &,Year &);

	bool	isValidYear	(int);
	bool	isLeapYear	(int);
	
	/*
	calculates a number of leap years 
	between two certain year dates.
	*/ 
	int		countLeapYears	(int, int);

	/*
	number of leap years since 1970 for a given year date
	for the input date before 1970 returns 0
	*/
	int		countLeapYears	(int);

	//	--------------------------------------------	

	enum struct Month
	{
		Jan = 1,
		Feb,
		Mar,
		Apr,
		May,
		Jun,
		Jul,
		Aug,
		Sep,
		Oct,
		Nov,
		Dec
	};

	Month 	operator ++ (Month &);
	Month 	operator -- (Month &);

	Month	int_to_month(int);
	bool	isValidMonth(int);
	bool	isValidDay	(int);

	//	--------------------------------------------	

	/*
	List of days of the week, starts at Monday (index == 1)
	index == 0 reserved for the implicit value: Week_implicit function (TODO)
	*/
	enum struct Week
	{
		Mon = 1,
		Tue,
		Wed,
		Thu,
		Fri,
		Sat,
		Sun
	};

	/*
	returns Week value for Jan 1 1970;
	*/
	Week Week_implicit();

	//	--------------------------------------------	
	
	struct Day
	{
		long 
			value;

		Day		();
		Day		(long);

		int		getValue	()		{ return value;}
		void	setValue	(long l) { value = l;}

		static	Day & implicit()
		{
			static Day
				impl{0};
			return impl;		
		}
	};

	/*
		calculates day of the year from the epoch format day,
		doesn't account for certain scenarios:
			+ number of day (before ajusting for the Leap Years) is lower than ammount of leap years. (TODO)
	*/
	int dayOfYear(Day);

	/*
	converts day-since-epoch-time to year of that same format
	corrects for a leap years, but doesn't account for certain scenarios:
		+ number dayOfTheYear (before adjusting for leap years) is lower than number of leap Years. (TODO)

	*/
	Year &	dayToYear	(Day);

	Week dayToWeek(Day);

	//	--------------------------------------------	

	class Second
	{
		public:
			Second	();
			Second	(long l);
			Second	(long l, bool b);

			long	getValue		()			{ return value;}
			bool	getIsNonTrivial	()			{ return nonTrivial;}
			void	setValue		(long l)	{ value = l;}
			void	setIsNonTrivial	(bool b)	{ nonTrivial = b;}
			
			static	Second & implicit()
			{
				static Second
					impl{0};
				return impl;
			}
		
		private:
			long
				value;
			bool
				nonTrivial;
	};

	/*
	converts epoch time into number of day since 1970.1.1
	doesn't bother with non-trivial seconds (TODO)
	*/
	Day &	secondToDay	(Second);

	//	--------------------------------------------	

	class  Date
	{
		public:
			class Invalid {};

			Date	();
			Date	(Year,Month,int);

			Year	getYear		()		const { return year;}
			Month	getMonth	()		const { return month;}
			int		getDay		()		const { return day;}

			void	setYear		(Year y)	{ year = y;}
			void	setMonth	(Month m)	{ month = m;}
			void	setDay		(int d)		{ day = d;}

			void	addDay		(int i)		{ day += i;}

			bool	isBiggerThan(const Date &) const;

			static	Date & implicit()
			{
				static Date
					impl{Year::implicit(),Month(0),Day::implicit().getValue()};
				return impl;
			};

		private:
			Year	year;
			Month	month;
			int		day;

			bool	isValid	()	const;
	};

	ostream &	operator <<	(ostream &,const Date &);
	istream &	operator >>	(istream &,Date &);
	bool		operator ==	(const Date &,const Date &);
	bool		operator !=	(const Date &,const Date &);

	bool		isValidDate	(int, int, int);

	//	--------------------------------------------	

}

void chronosMain();