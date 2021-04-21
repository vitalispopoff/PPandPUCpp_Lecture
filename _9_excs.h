#include <string>
#include "_9_more.h"

namespace ch09_exc02
{
	class Name_pairs
	{
		public:
		Name_pairs();

		/*
			writes names and ages to the respective vectors from keyboard input,
			filters out duplicates (both name and age must duplicate)
			concludes upon input "exit".
		*/
		void read_users();

		/*
			wites names to the name vector from the keyboard input,
			adds '-1' value for the respective index in age vector.
			filters out duplicates (checks name only)
			concludes on "exit"
		*/
		void read_names();

		/*
			enables editing the ages of names.
			lists names in order with the current name,
			overwrite age value only when valid value is entered.
			works in two modes:
			'y' - lists all the names,
			'n' - lists only names with invalid age values.
		*/
		void read_ages();

		/*
			sorts name vector alphabetically, and base on that shuffles the age vector.
		*/
		void sort();

		/*
			prints all names with the ages from respective vectors.
		*/
		ostream& print(ostream&) const;

		private:
			vector<string>name;
			vector<double>age;

			bool ageIsValid(double);
			bool nameIsInBase(string);
			bool isInBase(string, double);
	};

	/*
		cheapest reimplementation of the print() function possible
	*/
	ostream& operator<<(ostream&, Name_pairs);
}

namespace ch09_exc05
{
	using namespace ch09_lib::Chronou;

	struct ISBN
	{
		int
			state{0}, 
			publisher{0},
			number{0};
		char
			controlSum{'0'};
		ISBN (string);

		string toString();
		//static bool validate(string);
		string numberToString(int);
		bool isValid();
	};
	
	bool operator==(const ISBN &, const ISBN &);
	bool operator!=(const ISBN &, const ISBN &);
		
	enum class Genre
	{
		N_A,
		fiction,
		nonfiction,
		periodical,
		biography,
		chindren
	};

	struct Author
	{
		string
			lastName,
			firstName;
		
		Author();
		Author(string, string);
	};

	ostream & operator<<(ostream &, const Author &);

	struct Book
	{
		//Author
		//	author;
		string
			authorLastName,
			authorFirstName,			
			title,
			isbn;
		Genre
			genre;
		Date
			copyrightDate;
		bool
			isCheckedOut{true};

		Book();
		Book(string last, string first, string title, string isbn, Genre, Date);
		Book(string last, string first, string title);

		static Book & defaultBook()
		{
			Book 
				db{"", "", "", "", Genre::N_A, Date::defaultDate()};
			return db;
		}

	};

	bool operator==(const Book &, const Book &);
	bool operator!=(const Book &, const Book &);
	ostream & operator<<(ostream &, const Book &);

	class Patron
	{
		public:
			Patron();
			Patron(int, string, string);

			double getFeeAccount();
			void addToFeeAccount(double);
			string getLastName() { return lastName;}
			string getFirstName() { return firstName;}

			static Patron & defaultPatron()
			{
				static Patron
					dp{INT_MIN, "", ""};
				return dp;
			}

		private:
			int
				CardNumber;
			string 
				lastName,
				firstName;
			double
				feeAccount {0.};

			bool is(string, string);
			bool is(Patron & p);
			bool is(int);
	};

	bool operator==(Patron & , Patron & );
	


	bool userOwesAFee(const Patron &);

	struct Transaction
	{
		Book 
			book;
		Patron
			patron;
		Date
			date;

		Transaction();
	};

	class Library
	{		
		public:
		vector<Transaction> transactions;
		vector<Patron> patrons;
		vector<Book> books;
			
			Library();

			void addBook(string authorLastName, string authorFirstName, string title);
			void addPatron(string last, string first);			
			void checkOut(Book &,Patron &, Date &);

			Book & findBook(string authorLastName, string AuthorFirstName, string title);
			Patron & findPatron(string last, string first);

			

			
	};



	

}