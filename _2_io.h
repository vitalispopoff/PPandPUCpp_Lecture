
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
