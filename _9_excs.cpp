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

/*
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
*/

namespace ch09_exc05
{
	using namespace ch09_lib::Chronou;

	//	--------------------------------------------	

	//	--------------------------------------------	struct Book;

	Book::Book() {}

	Book::Book(string last, string first, string t)
		: authorLastName{last}, authorFirstName{first}, title{t} {}

	bool		operator == (Book& b1, Book& b2)
	{
		Book
			* temp1 = & b1,
			* temp2 = & b2;
		return temp1 == temp2;
	}
	ostream &	operator << (ostream & os, const Book & b)
	{
		os
			<< endl
			<< b.authorLastName 
			<< ", "
			<< b.authorFirstName
			<< endl
			<< b.title
			<< endl;
		return os;
	}

	bool isValidISBN(string input)
	{
		if(input.size() != 13 /*|| input.size() != 17*/)			// we work with ISBN10 only now
			return false;											// 10 symbols + 3 dashes for ISBN10, and 13 symbols + 4 dashes for ISBN13
		string
			s,
			subS{s.substr(0,s.size() -2)};							// cut out the control sum with last dash
		//replace(subS.begin(), subS.end(), '-', ' ');
		//stringstream 
		//	ss{subS};
		//int
		//	numbers[4];
		//try
		//{
		//	for(int i{0}; i < 4; ++i)
		//		ss >> numbers[i];
		//}
		//catch(exception & e)
		//{
		//	cout << "\n\t something went wrong with numbers";
		//	return false;
		//}
		//remove(subS.begin(), subS.end(), ' ');
		subS.erase(remove(subS.begin(), subS.end(), '-'), subS.end());
		int
			result{0},
			i{10};
		for(char c : subS)
		{
			if (!isdigit(c))
				return false;
			result += ((c - '0') * i--);
		}
		result %= 11;
		char
			controlSum {input[input.size() - 1]};
		if(controlSum == 'X' || controlSum == 'x')
			controlSum = 58;
		
		return	result + 48 == controlSum;
	}

	//	--------------------------------------------	class Patron;

	Patron::Patron() {}

	Patron::Patron(string last, string first) 
		: lastName{last}, firstName{first} {}

	bool		operator == (Patron & p1, Patron & p2)
	{
		Patron
			* temp1 = & p1,
			* temp2 = & p2;
		return temp1 == temp2;
	}
	ostream &	operator << (ostream & os, Patron & patron)				// const referenced prohibits using get/set for private members 
	{
		os
			<< endl
			<< patron.getLastName()
			<< ", "
			<< patron.getFirstName()
			<< endl;
		return os;
	}

	//	--------------------------------------------	struct Transaction;

	Transaction::Transaction() 
		: book{Book::defaultBook()}, patron{Patron::defaultPatron()} {}

	Transaction::Transaction(Book & b, Patron & p) 
		: book{b}, patron{p} {}

	bool		operator == (Transaction & t1, Transaction & t2)
	{
		Transaction
			* temp1 = & t1,
			* temp2 = & t2;
		return temp1 == temp2;
	}
	ostream &	operator << (ostream & os, Transaction & transaction)
	{
		os
			<< "\n\ttransaction book:"
			<< transaction.book
			<< "\n\ttransaction patron:"
			<< transaction.patron;
		return os;
	}

	//	--------------------------------------------	class Library;

	Library::Library() {}

	void Library::addBook(string authLast, string authFirst, string bookTitle)
	{
		Book 
			& found {findBook(authLast,authFirst,bookTitle)};
		if (found == Book::defaultBook())
		{
			books.push_back(Book{});
			Book 
				& temp {books[books.size() - 1]};
			temp.authorLastName = authLast;
			temp.authorFirstName = authFirst;
			temp.title = bookTitle;
			return;
		}
		else cout << "BOINK!";
	}

	void Library::addPatron(string last, string first)
	{
		if(findPatron(last, first) == Patron::defaultPatron())
			patrons.push_back(Patron{last, first});
	}

	void Library::addTransaction(Book & book, Patron & patron)
	{
		if(findTransaction(book, patron) == Transaction::defaultTransaction())
		{
			transactions.push_back(Transaction(book, patron));
			return;
		}
		cout
			<< "Transaction already added.";
	}

	Book & Library::findBook(string last, string first, string title)
	{
		for(Book & b : books)
		{
			if(b.authorLastName == last && b.authorFirstName == first && b.title == title)
			{	
				return b;
			}
		}
		return Book::defaultBook();
	}

	Patron & Library::findPatron(string last, string first)
	{
		for(Patron & p : patrons)
			if(p.getLastName() == last && p.getFirstName() == first)
				return p;
		return Patron::defaultPatron();
	}

	Transaction & Library::findTransaction(Book & book, Patron & patron)
	{
		for(Transaction & t : transactions)
			if(t.book == book & t.patron == patron)
				return t;
		return Transaction::defaultTransaction();
	}

	void Library::checkout(string authorLast, string authorFirst, string title, string patronLast, string patronFirst)
	{
		Book 
			& book {findBook(authorLast, authorFirst, title)};
		if (book == Book::defaultBook())
		{
			cout << "No such a book in the library";
				return;
		}
		if (book.isCheckedOut)
		{
			cout << "Currently book is not available.";
			return;
		}

		Patron
			& patron{findPatron(patronLast, patronFirst)};
		if (patron == Patron::defaultPatron())
		{
			cout << "Not a member of the library.";
			return;
		}
		if (patron.getFeeAccount() < 0.)
		{
			cout
				<< "\n\tPatron account suspended due to fee overdraft\n";
			return;
		}
		//	TODO	if book account is above threshold.

		Transaction &
			transaction{findTransaction(book, patron)};
		if(!(transaction == Transaction::defaultTransaction()))
		{	
			cout 
				<< "\n\ttransaction found:\n"
				<< transaction;
			return;
		}
		addTransaction(book, patron);
		cout 
			<< "\n\ttransaction added:\n"
			<< transactions[transactions.size() -1];	
	}
	
	//	--------------------------------------------	
	
	//	--------------------------------------------	tests, sketches, other

	void sketch01()
	{
		std::cout
			<< "\n\t sketch01():\n";
		Book
			b1{
				"imie",
				"naŸwisko",
				"tytu³"
			},
			b2{
				"imie",
				"naŸwisko",
				"tytu³",
			};
		cout 
			<< (b1 == b2) 
			<< endl
			<< b1;
	}

	void sketch02()
	{
		std::cout
			<< "\n\t sketch02():\n";
		string
			firstName = "zbyszek",
			lastName = "nanazwiskoromek";
		Library 
			lib{};
		cout 
			<< (lib.findPatron(lastName,firstName) == Patron::defaultPatron())
			<< endl;
		lib.addPatron(lastName, firstName);
		cout 
			<< (lib.findPatron(lastName, firstName).getLastName())
			<< endl;
	}

	void sketch03()
	{
		cout
			<< "\n\t sketch03():\n";
		string
			patronFirst {"zbyszek"},
			patronLast {"nanaziwskoromek"},
			authorFirst {"twoja"},
			authorLast {"stara"},
			bookTitle {"yello pages"};
		Library
			lib;
		lib.addBook(authorLast,authorFirst,bookTitle);
		lib.addPatron(patronLast, patronFirst);
		Book 
			& book {lib.findBook(authorLast, authorFirst, bookTitle)}; 
		Patron
			& patron {lib.findPatron(patronLast, patronFirst)};
		cout 
			<< "\nlisting book and patron"
			<< book
			<< patron;

		lib.checkout(authorLast, authorFirst, bookTitle, patronLast, patronFirst);



		
	}

	void sketch04()
	{
		cout
			<< "\n\t sketch04():\n";
		string
			isbn_0{"00-0000-000-0"},
			isbn_1{"81-7525-766-0"};
		cout 
			<< isValidISBN(isbn_1);
	}
}

void ch09Excercises()
{
	//ch09_exc02::exc02();

	using namespace ch09_exc05;

	sketch01();
	sketch02();
	sketch03();
	sketch04();

}