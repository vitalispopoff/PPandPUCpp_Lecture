
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
	void example01();

	void tryThis01();

	void example02();

	void tryThis02();

	void example03();

	void example04();

	void tryThis03();

	void example05();

}

void ch11Main();