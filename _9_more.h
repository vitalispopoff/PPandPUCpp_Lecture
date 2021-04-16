
namespace ch9_lib
{
class  Date
{
	public:
	Date(int,int,int);

	//void add_day(int n){}

	void year(int);
	void month(int);
	void day(int);

	int year();
	int month();
	int day();

	private:
	int
		y,m,d;
};

}