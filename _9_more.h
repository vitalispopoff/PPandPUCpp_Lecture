
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
				class Invalid{ };
			
				Year (int);
			
				void setValue	(int);
				int	getValue	();

			private:
				static const int 
					min{1800},
					max{2200};
				int 
					y;
		};

		enum class Month
		{
			//Jan,	// by default starts with 0 obviously
			Jan = 1, // but a different value may be assigned;
			Feb,
			Mar,
			//Mar = 5, to every enum member
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

		Month int_to_month(int);
		Month operator++(Month&);
		Month operator--(Month&);

		class  Date
		{
			public:
				class Invalid { };		// class used as exception
			
				/*Default constructor secures declarations like for vectors*/
				Date	();

				Date	(Year, Month, int);

				void setYear	(Year);
				void setMonth	(Month);
				void setDay		(int);

				Year	getYear	()	const;	// 'const' declares a non invasive function
				Month	getMonth()	const;
				int		getDay	()	const;

				void addDay	(int);

				/*This one apparently has to be implemented inside the class declaration
					for whatever reason the function doesn't like returning 'const'
				*/
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
	}
}