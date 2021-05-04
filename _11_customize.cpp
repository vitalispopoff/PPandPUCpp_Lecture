#include "std_lib_facilities.h"

namespace ch11
{
	namespace examples
	{
		char
			t {'\t'},
			n {'\n'};
			string
				tt {"\t\t"};

		void example01()
		{
			int
				i {1234};
			cout
				<< n << dec << i << t << "(decimal)" 
				<< n << hex << i << t << "(hexadecimal)" 
				<< n << oct << i << t << "(octal)" 
				<< n;
			cout
				<< n << (i >> 2)
				<< n;
		}

		void tryThis01()
		{
			int
				pastYear {2000},
				thisYear {2021},
				years {thisYear - pastYear};
			cout
				<< n 
				<< t << hex << years
				<< t << oct << years
				<< t << dec << years
				<< n;
		}

		void example02()
		{
			int
				i {1234};
			cout
				<< t << dec << i 
				<< t << hex << i 
				<< t << oct << i 
				<< n;
			cout 
				<< showbase;
			cout
				<< t << dec << i
				<< t << hex << i
				<< t << oct << i
				<< n;
			cout
				<< noshowbase
				<< dec;
			cout
				<< t << i
				<< t << 0x4d2
				<< t << 02322
				<< n;
		}

		void tryThis02()
		{
			int
				i1 {0},
				i2 {0},
				i3 {0};
			cin 
				>> dec >> i1 
				>> hex >> i2 
				>> oct >> i3;

			cout 
				<< dec
				<< t << i1
				<< t << i2
				<< t << i3
				<< n;
		}

		void example03()
		{
			cin.unsetf(ios::dec);
			cin.unsetf(ios::oct);
			cin.unsetf(ios::hex);
			int
				a,	b,	c,	d;
			cin 
				>> a
				>> b
				>> c;
			cin.setf(ios::dec);
			cin.setf(ios::oct);
			cin.setf(ios::hex);
			cin
				>> d;
			cout
				<< n
				<< t << a
				<< t << b
				<< t << c
				<< t << d
				<< n;
		}

		void example04()
		{
			double
				d {1234.56789};
			cout
				<< t << defaultfloat
					<< d << tt << "(default)" << n
				<< t << fixed 
					<< d << t << "(fixed)" << n
				<< t << scientific 
					<< d << t << "(scientific)" << n;
		}

		void tryThis03()
		{
			double
				d {1234567.89};
			cout
				<< t << defaultfloat	
				<< d << n
				<< t << scientific
				<< d << n
				<< t << fixed
				<< d << n;
		}

		void example05()
		{
			double
				d {1234.56789};
			int
				p1 {5},
				p2 {8},
				implicit {6};
			cout
				<< t 
					<< d << tt 
				<< fixed 
					<< d << tt 
				<< scientific 
					<< d << n;
			cout 
				<< t
				<< defaultfloat << setprecision(p1)
					<< d << tt
				<< fixed
					<< d << tt
				<< scientific
					<< d << n;
			cout 
				<< t
				<< defaultfloat << setprecision(p2)
					<< d << t
					<< fixed
					<< d << tt
					<< scientific
					<< d << n
					<< setprecision(implicit) << defaultfloat;	// default settings
		}

		void example06()
		{
			int
				i {123456},
				width1 {4},
				width2 {8};
			cout	
				<< t <<'|' 
					<< i << n
				<< t << '|' << setw(width1)
					<< i << n
				<< t << '|' << setw(width2)
					<< i << n;
		}

		void example07()
		{
			int
				width {8},
				i {123456};
			double
				d {1234.56789};
			cout			
				<< t << '|' << setw(width)		<< i << '|' << n
				<< t << '|' << setw(width)		<< d << '|' << n
				<< t << '|' << setw(width / 2)	<< i << '|' << n
				<< t << '|' << setw(width / 2)	<< d << '|' << n;
		}

		void example08()
		{
			int
				width {8};
			string
				s {"asdfg"};
			cout
				<< t << '|' << setw(width)		<< s << '|' << n
				<< t << '|' << setw(width / 2)	<< s << '|' << n;
		}

		void example09()
		{
			string
				s {"asdfg"};
			cout 
				<< t << '|' << setw(12)	<< s << '|' << n
				<< t << '|'				<< s << '|' << n;
		}

		void tryThis04()
		{
			vector<string>
				names {
					"zbyszek",
					"rysiek",
					"romek",
					"andrzej",
					"wacek",
					"marzena"
				};
			vector<double>
				ages {
					37,
					15,
					3,
					56,
					47,
					28
				};
			vector<int>
				phones {
					22'623'65'23,
					49'235'05'21,
					32'123'53'53,
					12'501'20'13,
					85'238'12'56,
					44'684'40'01
				};
			int
				col1 {16},
				col2 {3},
				col3 {12};
			string
				beginTop{"\t+"},
				begin	{"\t|"},
				wallTop {"-+-"},
				wall	{" | "},
				endTop	{"-+\n"},
				end		{" |\n"};

			auto drawLine = [](int length)
			{
				for(int i = 0 ; i < length ; ++i)
					cout << '-';
			};
			auto horizon = [&]
			{
				cout
					<< beginTop;
				drawLine(col1);
				cout 
					<< wallTop;
				drawLine(col2);
				cout
					<< wallTop;
				drawLine(col3);
				cout
					<< endTop;
			};

			horizon();
			for(int i = 0 ; i < names.size() ; ++i)
			{
				cout 
					<< begin
					<< setw(col1)	<< names[i]		<< wall 
					<< setw(col2)	<< ages[i]		<< wall 
					<< setw(col3)	<< phones[i]	<< end;
			}
			horizon();
		}

		void example10()
		{
			cout
				<< "enter input file name\n";
			string
				iname;
			cin
				>> iname;
			ifstream
				ifs {iname, ios_base::binary};
			if (!ifs)
				error("cant open input file ", iname);
			cout 
				<< "enter output file name\n";
			string
				oname;
			cin
				>> oname;
			ofstream
				ofs {oname, ios_base::binary};
			if (!ofs)
				error("can't open output file ", oname);
			vector<int>
				v;
			for (int x; ifs.read(as_bytes(x), sizeof(int)); )	// as_bytes() needs more explanation
				v.push_back(x);
			for (int x : v)
				ofs.write(as_bytes(x), sizeof(int));
		}

		void example11()
		{
			string
				address {"E:\\_LAB\\_C\\PPandPUCpp_Lecture\\_other\\"},
				name	{"ColdGrits_ItsYourThing.wav"};
			ifstream
				ifs	{address + name, ios_base::binary};
			if (!ifs)
				error("can't open ", name);
			int
				fileSize {0};
			ifs.seekg(4);
			ifs.read(as_bytes(fileSize), 4);
			char
				import[106];
			ifs.seekg(0);
			ifs.read(as_bytes(import), fileSize);
			ifs.close();

			vector<char>
				bytes {begin(import), end(import)};

			for(char byte : bytes)
				cout 
					<< byte;
		}

		void example12()
		{
			string
				s {"125937912"};
			istringstream
				iss {s};
			double
				d;
			iss 
				>> d;
			if (!iss)
				error("double format error ",s);
			if(iss.eof())
				cout
					<< "BOINK!\n";
			cout 
				<< fixed 
				<< d;
		}

		void example13()
		{
			string
				s {},
				input {"one two\nthree four"};
			stringstream
				ss {input};
			if (false)
			{
				ss 
					>> s;
				cout 
					<< s
					<< "|";
				ss
					>> s;
				cout
					<< s;
			}
			else
			{
			getline(ss, s);
			cout
				<< s;
			}
		}

		void example14()
		{
			string
				command {};
			getline(cin, command);
			stringstream
				ss {command};
			vector<string>
				words {};
			for (string s; ss >> s; )
				words.push_back(s);
		}

		void example15()
		{
			for (char ch; cin.get(ch); )
			{
				if (isspace(ch))
				{
					// ...
				}
				if (isdigit(ch))
				{
					// ...
				}
				else if (isalpha(ch))
				{
					// ...
				}
				else
				{
					// ...
				}
			}
		}

		void example16()
		{
			string
				input {"EGWEWrgewweQWgGWQ32Gt#Q4thjRtyESrg"};		
			cout 
				<< input;
			for(char & c : input)
				c = tolower(c);
			cout
				<< input;
		}

		// dealing with special characters
		namespace example17
		{
			//	bad solution 

			void initial()
			{
				string
					line {"As planned, the guests arrived; then,"};
				if (sizeof(line) == 0)
					getline(cin,line);

				for (char & c : line)
					switch (c)
					{
						case ';' : 
						case '.' : 
						case ',' : 
						case '?' : 
						case '!' :
							c = ' ';
					}
				stringstream 
					ss(line);
				vector<string> 
					vs;
				for (string word; ss >> word; )
					vs.push_back(word);
			}

			// better solution
		
			class Punct_stream
			{
				public:
					Punct_stream(istream & is)
						: source {is}, sensitive {true}
					{}

					void	whitespace			(const string & s)	{white = s; }
					void	add_white			(char c)			{white += c; }
					void	case_sensitive		(bool b)			{sensitive = b; }
					bool	is_case_sensitive	()					{return sensitive; }
					bool	is_whitespace		(char c);

					Punct_stream & operator >> (string & s);
					operator bool();

				private:
					istream 
						& source;
					istringstream
						buffer;
					string
						white;
					bool
						sensitive;
			};

			bool Punct_stream::is_whitespace(char c)
			{
				for (char ch : white)
					if (ch == c)
						return true;
				return false;
			}

			Punct_stream & Punct_stream::operator >> (string & s)
			{
				while (!(buffer >> s))					// fail reading from buffer
				{
					if (buffer.bad() || !source.good())	// fail in reading at all
						return * this;					// err C2102, C2440 : must be a lvalue (hence not passing by value E0461 or by reference E0158), or function designator (hence passing by the pointer)
				
					buffer.clear();						// reset buffer	 (because we're here due to the (buffer >> s) fail)
					string
						line;
					getline(source, line);				// intercept string from the other stream source - freezes as the cin input string gets to its end TODO.

					for (char & c : line)				// inspect string
					{
						if (c == ' ')					// skip the whitespace
							continue;
						if (is_whitespace(c))
							c = ' ';					// rewrite according to the whitespace list
						else if (!sensitive)			// this a bit unclear - converting to lowercase if stream is set to DGaF ?
							c = tolower(c);
					}
					buffer.str(line);					// copies string to the buffer
				}
				return * this;							// returns buffer
			}

			Punct_stream::operator bool()
			{
				bool											// can source be good and bad or failed simultanously?
					failOrBad = source.fail() || source.bad();
				return source.good() && !failOrBad;
			}

			void final()
			{
				Punct_stream 
					ps {cin};
				ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~");
				ps.case_sensitive(false);

				cout
					<< "please enter words\n";
				vector<string>
					vs {};
				for (string word; ps >> word; )
					vs.push_back(word);
				sort(vs.begin(), vs.end());

				for (int i = 0; i < vs.size(); ++i)
					if (i == 0 || vs[i] != vs[i - 1])
						cout
							<< vs[i]
							<< '\n';
			}
		}
	}

	namespace excercises
	{
		void exc01()
		{
			string
				inputFile {"E:\\_LAB\\_C\\PPandPUCpp_Lecture\\_other\\ch11_exc01_read.txt"};
			if (sizeof(inputFile) == 0)
				cin
					>> inputFile;
			ifstream
				ifs {inputFile, ios_base::binary};
			if(!ifs)
				error("can't read the input ", inputFile);
			string
				s {};
			for (char c; ifs.read(as_bytes(c), 1); )
			{
				if (isalpha(c))
					c = tolower(c);
				s += c;
			}
			ifs.close();
			
			cout 
				<< "\n\tread:\t"
				<< s
				<< endl;
			
			string
				outputFile {"E:\\_LAB\\_C\\PPandPUCpp_Lecture\\_other\\ch11_exc01_write.txt"};
			if (sizeof(outputFile) == 0)
				cin
					>> outputFile;
			ofstream
				ofs {outputFile, ios_base::binary};
			if(!ofs)
				error("can't opent the ouptut ", outputFile);
			for (char c : s)
				ofs << c;
			ofs.close();
		}

		void exc02()
		{		
			string
				inputFile {"E:\\_LAB\\_C\\PPandPUCpp_Lecture\\_other\\ch11_exc02_read.txt"};				
			ifstream
				ifs {inputFile};

			if (!ifs)
				error("can't open file ", inputFile);

			string
				bannedSigns {"!@#$%^&*(){}[]<>:;\",.?~`/"},
				keyword {"that"};
			int 
				lineNumber {1};

			for (string signs; getline(ifs, signs,'\n'); signs = "")
			{
				for (char & sign : signs)
					for (char & punctuation : bannedSigns)
						if (sign == punctuation)
							sign = ' ';

				stringstream
					ss {signs};

				for (string word; ss >> word; )
					if (word == keyword)
						cout 
							<< "line: " 
							<< lineNumber 
							<< endl;
				lineNumber++;					
			}		
		}

		void exc03()
		{
			string
				inputFile {"E:\\_LAB\\_C\\PPandPUCpp_Lecture\\_other\\ch11_exc02_read.txt"};
			ifstream
				ifs {inputFile, ios_base::binary};
			if(!ifs)
				error("can't open file ", inputFile);
			string
				vowels{"aeiouy"},
				cache;
			auto compare = [&](char & c)
			{
				for (char & v : vowels)
					if (c == v)
						return false;
				return true;
			};
			for (char c; ifs.read(as_bytes(c), 1); )
				if (compare(c))
					cache += c;
			cout
				<< cache;
		}	
	}
}

void ch11Main()
{
	//ch11::examples::example17::final();

	//ch11::excercises::exc01();
	//ch11::excercises::exc02();
	ch11::excercises::exc03();

}