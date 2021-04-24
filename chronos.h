

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

			void	setValue	(int i)		{ year = i; }
			int		getValue	()	const	{ return year; };

			static Year & defaultYear()
			{
				static Year
					dy{};
				return dy;
			}

		private:
			int year;
	};

	istream &operator>>(istream &,Year &);

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

	enum class Month
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

	Month	int_to_month	(int);
	bool	isValidMonth	(int);
	bool	isValidDay		(int);

	//	--------------------------------------------	

	class  Date
	{
		public:
			class Invalid {};

			Date	();
			Date	(Year,Month,int);

			Year	getYear		()		const { return year; }
			Month	getMonth	()		const { return month; }
			int		getDay		()		const { return day; }

			void	setYear		(Year y)	{ year = y; }
			void	setMonth	(Month m)	{ month = m; }
			void	setDay		(int d)		{ day = d; }

			void	addDay		(int i)		{ day += i; }

			bool	isBiggerThan(const Date &) const;

			static Date & defaultDate()
			{
				static Date
					dd{2001,Month::Jan,1};
				return dd;
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

	struct Day
	{
		int 
			number;
	};

	//	--------------------------------------------	

	struct Second
	{
		long
			number;

		Second();
		Second(long n);
	};

	//	--------------------------------------------	

}

void chronosMain();