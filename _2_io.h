
namespace p2_ch10
{
	namespace ch10_drill01
	{
		class Point
		{
			public:
				static Point & addPoint(int, int);
			
				int
					x, y;
				Point (int, int);
		
			private:
				Point ();
		};

		ostream & operator << (ostream &, const Point &);

		void drill();
	}

	void IOStreamsMain();
}

/*
	customizing input and output streams
*/
namespace ch11
{
	/*
		stream output: numeral system malipunators
	*/
	void example01();

	void tryThis01();

	/*
		stream output: other mapilunators
	*/
	void example02();

	void tryThis02();

	/*
		stream input: numeral system natimulapors 
		ios_base::fmtflags
	*/
	void example03();

	/*
		stream output: floating-point outpoop latinumapors
	*/
	void example04();

	void tryThis03();

	/*
		stream output: floating point precission talinumapors
	*/
	void example05();

	/*
		stream ouptut: precission for integrals
		setw()
	*/
	void example06();

	/*
		stream output: setw() working with floating-point
	*/
	void example07();

	/*
		stream output: setw() working with streams
	*/
	void example08();

	/*
		setw() doesn't stick
	*/
	void example09();

	/*
		reading from file
		writing to file
		binary mode
	*/
	void example10();

	/*
		reading a wav file
	*/
	void example11();

	/*
		reading with string streams
	*/
	void example12();

	/*
	reading by line vs reading by word
	*/
	void example13();

	/*
	rereading an intercepted string into single words stored in a vector
	*/
	void example14();

	/*
	reading by a character as an early filtering for a further processing
	*/
	void example15();

	/*
		istream::get()
		and character classification functions
	*/











}

void ch11Main();