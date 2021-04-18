
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
		//jan = 1,	// sets the value assigned to the literal;
		Jan,	// by default starts with 0 obviously
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
			void setDay	(int);

			Year getYear	();
			Month getMonth	();
			int getDay		();

			void add_day	(int);
			bool is_valid	();


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

	};


}