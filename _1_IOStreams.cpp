#include "std_lib_facilities.h"
#include <iostream>
#include "_2_io.h"

namespace p2_ch10
{

	void enterString(string &s,string name)
	{
		if(s == "")
		{
			cout
				<< "enter " << name;
			cin
				>> s;
		}
	}

	namespace ch10_examples
	{

		void example01()
		{
			string
				inputFileName{"E:\\_LAB\\unpeak\\shortie\\1kHz_16_mono.wav"};
			if(inputFileName.size() == 0)
			{
				cout
					<< "Please enter input file name:\t";
				cin
					>> inputFileName;
			}
			ifstream
				ist{inputFileName};
			if(!ist)
				error("I can't open input file ",inputFileName);
			vector<unsigned char>
				bytes;
			for(unsigned char byte; ist >> byte; )
				bytes.push_back(byte);
			int
				index{0};
			for(unsigned char byte : bytes)
				cout
				<< int(byte)
				<< (index++ % 8 == 7 ? '\n' : '\t');
		}

		//	----------------------------	Example 02

		void end_of_loop(istream &ist,char term,const string &message)
		{
			if(ist.fail())
			{
				ist.clear();
				char
					ch;
				if(ist >> ch && ch == term)
					return;
				error(message);
			}
		}

		const int
			not_a_reading = -7777,
			not_a_month = -1;

		struct Reading
		{
			int
				day,
				hour;
			double
				temperature;
		};

		istream &operator >> (istream &is,Reading &r)
		{
			char
				ch1;
			if(is >> ch1 && ch1 != '(')
			{
				is.unget();
				is.clear(ios_base::failbit);
				return is;
			}
			char
				ch2;
			int
				d,h;
			double
				t;
			is
				>> d >> h >> t >> ch2;

			if(!is || ch2 != ')')
				error("bad reading");

			r.day = d;
			r.hour = h;
			r.temperature = t;
			return is;
		}

		struct Day
		{
			vector<double>
				hour{24,not_a_reading};
		};

		ostream &operator << (ostream &os,const Day &d)
		{
			int
				index{0};
			for(int i = 0; i < d.hour.size(); ++i)
				if(d.hour[i] != not_a_reading)
				{
					index++;
					os
						<< "\n\t\t"
						<< i
						<< '.\t'
						<< d.hour[i];
				}
			if(index > 0)
				os << endl;
			return os;
		}

		ofstream &print_day(ofstream &os,const Day &d)
		{
			for(double h : d.hour)
				os
				<< h;
			return os;
		}

		struct Month
		{
			int
				month{not_a_month};
			vector<Day>
				day{32};
		};

		ostream &operator << (ostream &os,const Month &m)
		{
			if(m.month == not_a_month)
				return os << " --- \n";
			os
				<< "Month: "
				<< m.month
				<< endl;
			for(Day d : m.day)
				os
				<< d;
			return os;
		}

		ofstream &print_month(ofstream &os,const Month &m)
		{
			os
				<< m.month
				<< endl;
			for(Day d : m.day)
				print_day(os,d);
			return os;
		}

		vector<string>
			month_input{
			"jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"
		};

		int month_to_int(string m)	// implementations is irrelevant for now
		{
			for(int i = 0 ; i < month_input.size(); ++i)
				if(month_input[i] == m)
					return i + 1;
			return 0;
		}
		string int_to_month(int i)
		{
			i--;
			if(i < 0 || 12 <= i)
				error("bad month index");
			return month_input[i];
		}

		constexpr int
			implausible_min = -200,
			implausible_max = 200;

		bool is_valid(Reading r)
		{
			if(r.day < 1 || 31 < r.day)
				return false;
			if(r.hour < 0 || 23 < r.hour)
				return false;
			if(r.temperature < implausible_min || implausible_max < r.temperature)
				return false;
			return true;
		}

		istream &operator >> (istream &is,Month &m)
		{
			char
				ch = 0; // why '=' instead of '{}' ?
			if(is >> ch && ch != '{')
			{
				is.unget();
				is.clear(ios_base::failbit);
				return is;
			}

			string
				month_marker,
				mm;
			is
				>> month_marker >> mm;

			if(!is || month_marker != "month")
				error("bad start of month");
			m.month = month_to_int(mm);

			int
				duplicates = 0,invalids = 0;

			for(Reading r; is >> r; )
			{
				if(is_valid(r))
				{
					if(m.day[r.day].hour[r.hour] != not_a_reading)
						++duplicates;
					m.day[r.day].hour[r.hour] = r.temperature;
				}
				else
					++invalids;
			}
			if(invalids)
				error("invalid readeings in month",invalids);
			if(duplicates)
				error("duplicate readings in month",duplicates);
			end_of_loop(is,'}',"bad oend of month");
			return is;
		}

		struct Year
		{
			int
				year;
			vector<Month>
				month{12};
			Year(): year{0}
			{}
		};

		ostream &operator << (ostream &os,const Year &y)
		{
			os
				<< "Year: "
				<< y.year
				<< endl;
			for(Month m : y.month)
				os
				<< m;
			return os;
		}
		ofstream &print_year(ofstream &os,const Year &y)
		{
			os
				<< y.year;
			for(Month m : y.month)
				print_month(os,m);
			return os;
		}

		istream &operator >> (istream &is,Year &y)
		{
			char
				ch;
			is
				>> ch;
			if(ch != '{')
			{
				is.unget();
				is.clear(ios::failbit);
				return is;
			}
			string
				year_marker;
			int
				yy;
			is
				>> year_marker
				>> yy;
			if(!is || year_marker != "year")
				error("bad start of year");
			y.year = yy;

			while(true)
			{
				Month
					m;
				if(!(is >> m))
					break;
				y.month[m.month] = m;	// y.month is a vector<Month>, and m.month is defind int index
			}
			end_of_loop(is,'}',"bad end of year");
			return is;
		}


		void example02()
		{
			string
				iname{};
			if(iname.size() == 0)
				cout
				<< "Enter input file name\n";
			cin
				>> iname;
			ifstream
				ist{iname};
			if(!ist)	// originally written as "ifs"
				error("can't open input file ",iname);
			ist.exceptions(ist.exceptions() | ios_base::badbit);	// exceptions gets the error bit mask (four errors in a single byte?), and sets its value.

			string
				oname{};
			if(oname.size() == 0)
				cout
				<< "Enter output file name\n";
			cin
				>> oname;
			ofstream
				ost{oname};
			if(!ost)	// originally written as "ofs"
				error("can't open output file ",oname);

			vector<Year>
				ys;
			while(true)
			{
				Year
					y;
				if(!(ist >> y))
					break;
				ys.push_back(y);
			}
			cout
				<< "read "
				<< ys.size()
				<< " years of readings\n";
			for(Year &y : ys)
				print_year(ost,y);		// TODO : check if the ofstream print functions cover output format the same way ifstream input functions do.
		}
	}

	namespace ch10_drill01
	{
		vector<Point>
			points;

		Point::Point()
			: x{0},y{0}
		{}

		Point::Point(int i1,int i2)
			: x{i1},y{i2}
		{}

		Point &Point::addPoint(int x,int y)
		{
			points.push_back(Point(x,y));
			int
				index{narrow_cast<int>(points.size() - 1)};
			return points[index];
		}

		ostream &operator << (ostream &os,const Point &p)
		{
			os
				<< '('
				<< p.x
				<< ','
				<< p.y
				<< ')';
			return os;
		}

		istream &writePoint(istream &is)
		{
			int
				x,y;
			is
				>> x >> y;
			Point::addPoint(x,y);
			return is;
		}

		string
			filename{"E:\\_LAB\\_C\\PPandPUCpp_Lecture\\_other\\ch10_dril01.tmp"};

		void write()
		{
			cout
				<< "enter points\t";
			for(int i = 0; i < 6; ++i)
				writePoint(cin);
			cout
				<< "\nenter file name.\n";
			string
				outputFileName;
			cin
				>> outputFileName;
			ofstream
				ofs{outputFileName};
			if(!ofs)
				error("ofs no no.");
			for(Point point : points)
				ofs
				<< '('
				<< point.x
				<< ','
				<< point.y
				<< ')'
				<< endl;
			if(filename == "")
				filename = outputFileName;
		}

		void read()
		{
			string
				inputFileName{};
			if(filename == "")
			{
				cout
					<< "enter file name.\n";
				cin
					>> inputFileName;
			}
			else
				inputFileName = filename;
			ifstream
				ifs{inputFileName};
			if(!ifs)
				error("error in reading file ",inputFileName);

			bool flag{true};
			int index{0};
			while(true)
			{
				char
					c1,c2,c3;
				int
					x,y;

				ifs
					>> c1
					>> x
					>> c2
					>> y
					>> c3;

				if(ifs.eof())
					break;			// returns true only if ifstream attempted read already exceeded file area in memory.

				if(c1 == '(' && c2 == ',' && c3 == ')')
					cout
					<< c1 << x << c2 << y << c3
					<< endl;
			}
		}
	}

	namespace ch10_exc01
	{
		// generate number

		int generate(int range)
		{
			return (rand() % range * 2) - range;
		}

		//void enterString(string & s, string name)
		//{
		//	if(s == "")
		//	{
		//		cout 
		//			<< "enter " << name;
		//		cin 
		//			>> s;
		//	}
		//}

		string
			fileAddress{"E:\\_LAB\\_C\\PPandPUCpp_Lecture\\_other\\"},
			fileName{"ch10_exc01.txt"};

		void enterFileName()
		{
			enterString(fileAddress,"file address");
			enterString(fileName,"file name");
		}

		void writeFile()
		{
			enterFileName();

			string
				ofName{fileAddress};
			ofName += fileName;
			ofstream
				ofs{ofName};
			if(!ofs)
				error("file can't be opened: ",ofName);
			int
				lenght{abs(generate(50)) + 50};
			for(int i = 0 ; /*i < lenght */; ++i)
			{
				ofs
					<< generate(100);
				if(i == lenght - 1)
				{
					ofs
						<< char(0);
					break;
				}
				ofs
					<< ' ';
			}
		}

		int sumFile()
		{
			enterFileName();

			string
				ifName{fileAddress};
			ifName += fileName;
			ifstream
				ifs{ifName};
			if(!ifs)
				error("file can't be opened: ",ifName);
			int
				result{0};
			while(ifs.peek() > 0)	// this works only based on the last space changed into NULL
			{
				int
					i{0};
				ifs
					>> i;
				result += i;
			}
			return result;
		}
	}

	struct Reading
	{
		int
			hour;
		char
			scale;
		double
			temperature;
		Reading()
			: hour{-1},scale{'f'},temperature{-460.}
		{}
		Reading(int h,double t)
			: hour{h},scale{'f'},temperature{t}
		{}
		Reading(int h,char s,double t)
			: hour{h},scale{s},temperature{t}
		{}
	};

	vector<Reading>
		dailyReadings;

	namespace ch10_exc02
	{
		void fillDailyReadings()
		{
			for(int hour{0}; hour < 24; ++hour)
			{
				double
					temp{(narrow_cast<double>(rand() % 15000) - 5000.) / 100.};
				dailyReadings.push_back(Reading{hour,temp});
			}
		}

		string
			fileAddress{"E:\\_LAB\\_C\\PPandPUCpp_Lecture\\_other\\"},
			fileName{"ch10_exc02.txt"};

		void enterFileName()
		{
			enterString(fileAddress,"file address");
			enterString(fileName,"file name");
		}

		void saveToFile()
		{
			enterFileName();
			string
				file{fileAddress};
			file += fileName;
			ofstream
				ofs{file};
			if(!ofs)
				error("can't read: ",file);
			for(Reading r : dailyReadings)
			{
				ofs << r.hour << ' ' << r.temperature << (r.hour == 23 ? char(0) : '\n');
			}
		}

		void readFile()
		{
			enterFileName();
			string
				file{fileAddress};
			file += fileName;
			ifstream
				ifs{file};
			if(!ifs)
				error("can't open file ",file);
			while(true)
			{
				int
					hour;
				double
					temperature;
				ifs
					>> hour
					>> temperature;
				dailyReadings.push_back(Reading{hour,temperature});

				if(ifs.peek() == char(0))
					break;
			}
		}
		vector<double> extractTemperatures()
		{
			vector<double>temperatures;
			for(Reading r : dailyReadings)
				temperatures.push_back(r.temperature);
			return temperatures;
		}

		double getMedian(vector<double> &temperatures)
		{
			sort(temperatures);
			return 0.5 * (temperatures[11] + temperatures[12]);
		}

		double getMean(vector<double> &temperatures)
		{
			double
				result{0};
			for(double t : temperatures)
				result += t;
			return result / narrow_cast<double>(temperatures.size());
		}
	}

	void excercise02sqq()
	{
		auto checkSize = [&]
		{
			cout
				<< "\n\t dailyReadings size:\t"
				<< dailyReadings.size()
				<< endl;
		};
		auto printContent = [&]
		{
			for(Reading r : dailyReadings)
				cout
				<< '\t'
				<< r.hour
				<< '\t'
				<< r.temperature
				<< endl;
		};

		using namespace ch10_exc02;

		if(false)		// disable as the file is there already.
		{
			checkSize();
			fillDailyReadings();
			checkSize();
			printContent();

			saveToFile();
			dailyReadings.clear();
			checkSize();
		}

		readFile();
		checkSize();
		printContent();

		cout
			<< "\n\t* * *\n";

		vector<double>
			temp = extractTemperatures(),
			&temperatures = temp;
		cout
			<< "\n\tmedian:\t" << getMedian(temperatures)
			<< "\n\tmean:\t" << getMean(temperatures)
			<< endl;
	}

	namespace ch10_exc04
	{

		void fillDailyReadings()
		{
			for(int hour{0}; hour < 24; ++hour)
			{
				double
					temp{(narrow_cast<double>(rand() % 12000) - 6000.) / 100.};
				char
					scale { (rand() & 1) ? 'c' : 'f'};
				if(scale == 'f')
				{
					temp -=32;
					temp *= 5./9.;
				}
				dailyReadings.push_back(Reading{hour, scale, temp});
			}
		}

		string
			fileAddress{"E:\\_LAB\\_C\\PPandPUCpp_Lecture\\_other\\"},
			fileName{"ch10_exc02.txt"};

		void enterFileName()
		{
			enterString(fileAddress,"file address");
			enterString(fileName,"file name");
		}

		void saveToFile()
		{
			enterFileName();
			string
				file{fileAddress};
			file += fileName;
			ofstream
				ofs{file};
			if(!ofs)
				error("can't read: ",file);
			for(Reading r : dailyReadings)
			{
				ofs << r.hour << ' ' << r.scale << ' ' << r.temperature << (r.hour == 23 ? char(0) : '\n');
			}
		}

		void readFile()
		{
			enterFileName();
			string
				file{fileAddress};
			file += fileName;
			ifstream
				ifs{file};
			if(!ifs)
				error("can't open file ",file);
			while(true)
			{
				int
					hour{-1};
				char
					scale{' '};
				double
					temperature{-460};
				ifs
					>> hour
					>> scale
					>> temperature;

				if (scale == 'c')
				{
					temperature *= 5 /9;
					temperature += 32;
				}
				dailyReadings.push_back(Reading{hour, 'f', temperature});

				if(ifs.peek() == char(0))
					break;
			}
		}
		vector<double> extractTemperatures()
		{
			vector<double>
				temperatures;
			for(Reading r : dailyReadings)
				temperatures.push_back(r.temperature);
			return temperatures;
		}

		double getMedian(vector<double> &temperatures)
		{
			sort(temperatures);
			return 0.5 * (temperatures[11] + temperatures[12]);
		}

		double getMean(vector<double> &temperatures)
		{
			double
				result{0};
			for(double t : temperatures)
				result += t;
			return result / narrow_cast<double>(temperatures.size());
		}
	}

	void excercise04()
	{
		using namespace ch10_exc04;

		auto printContent = [&]
		{
			for(Reading r : dailyReadings)
				cout
				<< '\t'
				<< r.hour
				<< '\t'
				<< r.scale
				<< ' '
				<< r.temperature
				<< endl;
		};

		if(false)					// disable call as the file is already written;
			fillDailyReadings();

		readFile();
		printContent();


	}

		void IOStreamsMain()
		{
			//ch10_drill01::write();
			//ch10_drill01::read();

			//ch10_exc01::writeFile();
			//cout << ch10_exc01::sumFile();

			//excercise02sqq();
			excercise04();

		}

}