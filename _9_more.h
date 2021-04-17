
namespace ch9_lib
{
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
	class  Date
	{
		public:
			class Invalid { };		// class used as exception
			
			Date(Year, Month, int);

			void year	(Year);
			void month	(Month);
			void day	(int);

			Year year	();
			Month month	();
			int day		();

			void add_day	(int);
			bool is_valid	();

		private:
			Year	y;
			Month	m;
			int		d;
	};

	class Year
	{
		
		public:
			class Invalid{ };
			
			Year (int);
			
			int	year	();
			void year	(int);

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
		Spr,
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

	enum Day
	{
		mon,
		tue,
		wed,
		thu,
		fri,
		sat,
		sun
	};

}