
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
			
			Date(int, int, int);

			void year	(int);
			void month	(int);
			void day	(int);

			int year	();
			int month	();
			int day		();

			void add_day	(int);
			bool is_valid	();

		private:
			int
				y,m,d;
	};

}