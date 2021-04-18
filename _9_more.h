
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
				Year (int);
			
				void setValue	(int);
				int	getValue	()		const;

				class Invalid{ };

			private:
				static const int 
					min{1800},
					max{2200};
				int y;
		};

		enum class Month
		{
			Jan = 1,	Feb,		Mar,		Apr,		May,		Jun,
			Jul,		Aug,		Sep,		Oct,		Nov,		Dec
		};

		Month int_to_month(int);
		Month operator++(Month&);
		Month operator--(Month&);

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

			friend ostream& operator<<(ostream&, Date&);	// friend function - we're way ahead here

			private:
				Year	y;
				Month	m;
				int		d;

				bool	isValid	()	const;
		};
	}

	void ch9_4_6(int, int);
	void example_07();
	void example_08();
	void example_09(Chronou::Date&,const Chronou::Date&);


}