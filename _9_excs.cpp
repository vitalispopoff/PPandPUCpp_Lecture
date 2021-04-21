#include "std_lib_facilities.h"
#include "_9_excs.h"

namespace ch09_exc02
{
	//	class Name_pairs

	Name_pairs::Name_pairs() : name(), age() {}

	void Name_pairs::read_users()
	{
		cout 
			<< "enter name, or 'exit'\n";
		string 
			s;
		double 
			d;
		while(cin >> s)
		{
			if(s == "exit")
				break;
			cout 
				<< "\tEnter age: ";
			cin 
				>> d;
			if(isInBase(s, d))				
			{
				cout
					<< "This one (the name with the age) is already in base";
				continue;
			}
			name.push_back(s);
			age.push_back(d);
			cout 
				<< "\n\t" 
				<< s 
				<< " is saved as " 
				<< d 
				<< " years old\n";
		}
	}


	void Name_pairs::read_ages()
	{
		cout 
			<< "Wanna edit everyone's age ('y') or just the missing ones ('n')?\t";
		char 
			c{' '};
		cin 
			>> c;
		double 
			d;
		switch(c)
		{
			case 'y':
			{
				for(int i = 0; i < name.size(); ++i)
				{
					cout 
						<< "\n\t" << name[i] << " , age: " << age[i] << " ;\t set it to :\t";
					cin 
						>> d;
					if(ageIsValid(d))
					{	
						double &
							target = age[i];
						target = d;
					}
					else continue;
				}
				break;
			}
			case 'n':
			{
				for(int i = 0; i < name.size(); ++i)
				{
					if(age[i] < 0)
					{
						cout
							<< "\n\t" << name[i] << " , age: " << age[i] << " ;\t set it to :\t";
						cin 
							>> d;		
						if(ageIsValid(d))
						{
							double &
								target = age[i];
							target = d;
						}
						else continue;
					}
				}
				break;
			}
		}
	}

	ostream& Name_pairs::print(ostream& os) const
	{
		os 
			<< "\n\tnames with ages:";
		for(int i = 0; i < name.size(); ++i)
			os
				<< "\n\tname: " 
				<< name[i]
				<< "\t, age: " 
				<< age[i];
		os 
			<< endl;
		return os;
	}

	bool Name_pairs::isInBase(string s, double d)
	{
		for(int i = 0; i < name.size(); ++i)
			if(s == name[i] && d == age[i])
				return true;
		return false;
	}

	bool Name_pairs::nameIsInBase(string s)
	{
		for(string n : name)
			if(s == n)
				return true;
		return false;
	}

	bool Name_pairs::ageIsValid(double d)
	{
		return 0 <= d && d < 1024;
	}

	void Name_pairs::sort()
	{
		vector<string> 
			&source = name,
			sorted = name;
		vector<double>
			&sortingAge = age;

		std::sort(sorted.begin(), sorted.end());

		for(int i = 0; i < name.size(); ++i)
		{
			for(int j = i + 1; j < name.size(); ++j)
			{
				if(sorted[i] == source[j])
				{
					double 
						tempAge = sortingAge[i];
					sortingAge[i] = sortingAge[j];
					sortingAge[j] = tempAge;
					string
						tempName = source[i];
					source[i] = source[j];
					source[j] = tempName;
				}
			}
		}
	}

	void Name_pairs::read_names()
	{
		cout 
			<< "enter name only, or 'exit'\n";
		string
			s;
		while(cin>>s)
		{
			if(s == "exit")
				break;
			if(nameIsInBase(s))
			{	
				cout 
					<< "This user is aldeady in base";
				continue;
			}
		name.push_back(s);
		age.push_back(-1);
		cout
			<< "\n\t"
			<< s 
			<< " is saved with age set as -1.\n";
		}
	}

	ostream& operator<<(ostream& os, Name_pairs np)
	{
		return np.print(os);
	}


		
	void exc02()
	{
		//using namespace ch09_exc02;

		Name_pairs np;

		np.read_users();
		//np.read_names();
		//np.read_pairs();
		//np.read_ages();

		cout << np;
	}
}

namespace ch09_exc04
{
	
	struct X 
	{
		// would return 1 but it's void, it doesn't change anything - not using a single global or variable passed by reference/poitnter
		void f(int x)	
		{
			struct Y 
			{
				int 
					m; 
				int f() 
				{ return 1; } 
			};

			Y 
				m2;
			int 
				m = x; 

			return f(m2.f());	// m2.f() == 1 ; f(m2.f()) == 1;
		}

		int 
			m; 

		void g (int m)
		{
			if (m) 
				f (m+2); // returns 1.
			else 
				g(m+2); // returns void
		}

		X() {}	// X default constructor

		void m3(){} // an empty function not even returning

		// rebranded main function - still inside the struct...
		void exc04() 
		{
			X a; 
			a.f(2);
		} 
	};
}

namespace ch09_exc05
{
	//	struct ISBN;

	ISBN::ISBN(string input)
	{
		string 
			s;
		int 
			index {0};
		for(char c : input) 
		{
			if(c != '-' && index < 3)
				s += c;
			else
			{
				switch (index)
				{
					case 0:
						state = stoi(s);
						break;
					case 1:
						publisher = stoi(s);
						break;
					case 2:
						number = stoi(s);
						break;
					case 3:
						controlSum = c;
				}
				s = "";
				++index;
			}
		}
	}

	string ISBN::toString()
	{
		string 
			result;
		result += numberToString(state) ;
		result += '-';
		result += numberToString(publisher);
		result += '-';
		result += numberToString(number);
		result += '-';
		result += controlSum;
		return result;
	}
	string ISBN::numberToString(int i)
	{
		stringstream ss;
		ss << i;
		string s;
		ss >> s;
		return s;
	}

	bool ISBN::isValid()
	{
		return isalpha(controlSum) || isdigit(controlSum);
	}

	bool operator==(const ISBN &c1,const ISBN &c2)
	{
		return
			c1.state == c2.state
			&& c1.publisher==c2.publisher
			&& c1.number == c2.number
			&& c1.controlSum == c2.controlSum;
	}
	bool operator!=(const ISBN &c1, const ISBN &c2)
	{
		return
			c1.state != c2.state
			|| c1.publisher != c2.publisher
			|| c1.number != c2.number
			|| c1.controlSum != c2.controlSum;
	}


	
	//	struct Author;

	Author::Author() {}
	Author::Author(string l, string f) 
		: lastName{l}, firstName{f} {} 

	ostream &operator<<(ostream &os,const Author & a)
	{
		os
			<< a.lastName 
			<< ' '
			<< a.firstName;
		return os;
	}



	string makeISBN(string s)
	{
		if(ISBN(s).isValid())
			return s;
		return "";
	}

	//	struct Book;

	Book::Book() 
		: genre{Genre::N_A}, copyrightDate{1, ch09_lib::Chronou::Month::Jan, 1} {}

	Book::Book(Author a, string code, string t, Genre g, ch09_lib::Chronou::Date d) 
		: author{a}, isbn(makeISBN(code)), title{t}, genre{g}, copyrightDate{d} {}

	bool operator==(const Book& b1, const Book& b2)
	{
		return ISBN(b1.isbn) == ISBN(b2.isbn);
	}
	bool operator!=(const Book& b1, const Book& b2)
	{
		return ISBN(b1.isbn) != ISBN(b2.isbn);
	}

	ostream & operator<<(ostream & os, const Book & b)
	{
		os
			<< endl
			<< b.author
			<< endl
			<< b.title
			<< endl
			<< b.isbn
			<< endl;
		return os;
	}



	//	class Patron;

	Patron::Patron() {}

	Patron::Patron(int number, string last, string first) 
		: CardNumber{number}, lastName{last}, firstName{first} {}

	double Patron::getFeeAccount()
	{
		return feeAccount;
	}
	void Patron::addToFeeAccount(double d)
	{
		feeAccount += d;
	}

	bool isPatronDue(Patron p)
	{
		return p.getFeeAccount() <= 0.;
	}



	//	struct Transactiun;

	Transaction::Transaction() 
		: date{1, ch09_lib::Chronou::Month::Jan, 1} {}



	//	class Library:

	Library::Library() {}

	void Library::addBook(Book & b)
	{
		books.push_back(b);
	}

	void Library::addPatron(Patron & p)
	{
		patrons.push_back(p);
	}

	//	tests, sketches, other

	void sketch01()
	{
		Book
			b1{
				Author("imie","naŸwisko"),
				"1-2-3-x",
				"tytu³",
				Genre::nonfiction,
				ch09_lib::Chronou::Date(1973, ch09_lib::Chronou::Month::Feb, 2)
			},
			b2{
				Author("imie","naŸwisko"),
				"1-2-3-x",
				"tytu³",
				Genre::nonfiction,
				ch09_lib::Chronou::Date(1973, ch09_lib::Chronou::Month::Feb, 2)
			};
		cout 
			<< (b1 == b2) 
			<< endl
			<< b1;
	}

	void sketch02()
	{
		Patron p{1,"zbyszek", "romek"};

		cout
			<< p.getFeeAccount()
			<< endl
			<< isPatronDue(p)
			<< endl;

		p.addToFeeAccount(-1);

		cout
			<< "\n subtracting from the fee account\n"
			<< p.getFeeAccount()
			<< endl
			<< isPatronDue(p)
			<< endl;

	}

	void sketch03()
	{

	}
}

void ch09Excercises()
{
	//ch09_exc02::exc02();

	using namespace ch09_exc05;

	sketch01();
	sketch02();
}