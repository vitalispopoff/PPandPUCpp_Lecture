
/* in-class implementations 
* (called inlined functions) force compiler to
* generate code at each call separately
* which boosts the performance, but
* require a full recompilation of entire code
* with each
* change of the implementation.
* reasonable for tiny simple functions
* that get used a lot
*/

namespace ch9_lib
{
	
	namespace Chronou
	{
	
	class Year
		{	
			public:			
				static const int 
					min{-5000},	// extended due to use in ch09.exc05 sqq
					max{2200};

				Year (int);
			
				void setValue	(int);
				int	getValue	()		const;

				class Invalid{ };

			private:
				int y;
		};

		istream& operator>>(istream&, Year&);

		bool isValidYear(int);
		bool isLeapYear	(int);

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

		Month operator++(Month&);
		Month operator--(Month&);

		bool isValidMonth(int);
		Month int_to_month(int);

		bool isValidDay	(int);

		class  Date
		{
			public:
				class Invalid { };
			
				Date	();
				Date	(Year, Month, int);

				void setYear	(Year);
				void setMonth	(Month);
				void setDay		(int);

				Year	getYear	()	const;
				Month	getMonth()	const;
				int		getDay	()	const;

				void addDay	(int);

				static Date& defaultDate()
				{
					static Date
						dd{2001, Month::Jan, 1};
					return dd;
				};

			private:
				Year	y;
				Month	m;
				int		d;
				
				bool	isValid	()	const;
		};

		ostream& operator	<<	(ostream &, const Date &);
		istream& operator	>>	(istream &, Date&);
		bool	operator	==	(const Date &, const Date &);
		bool	operator	!=	(const Date &, const Date &);
		
		bool isValidDate	(int, int, int);		

	}

	using namespace Chronou;

	/* 9.2:
		declaring class,
		access modifiers,
	*/
	void example_01();
	
	/* ch9_4
		initialization of a class object,
		passing an enum member as an input variable
		keeping in mind the namespace structure.
	*/
	void example_02();

	/* ch9_4_6
	*/
	void example_03(int, int);
	
	
	void example_07();
	
	
	void example_08();

	/* 'startOfTerm' refuses to pass its member to 'b' directly - 'const' prevents
	it has no problem with passing itself tho, so it's rather a 'const' vs 'getDay()'
	solution is to declare the function 'const'.
	but - only class member functions may be declared 'const'
	*/
	void example_09(Date&,const Date&);

	/* it is the 'const' that secures the input, by authorizing only processing the functions clearly declared non-invasive.
	*/
	void example_10(Date&);
}