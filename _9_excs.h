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

	struct Book
	{
		string
			authorLastName,
			authorFirstName,			
			title;
		bool
			isCheckedOut{true};

		Book();
		Book(string last, string first, string title);

		static Book & defaultBook()
		{
			Book 
				db{"", "", ""};
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
			Patron(string last, string first);

			string getLastName() { return lastName;}
			string getFirstName() { return firstName;}

			static Patron & defaultPatron()
			{
				static Patron
					dp{};
				return dp;
			}

			string 
				lastName,
				firstName;
	};

	bool operator==(Patron & , Patron & );
	


	bool userOwesAFee(const Patron &);

	struct Transaction
	{
		Book 
			book;
		Patron
			patron;

		Transaction();
		Transaction(Book & , Patron &);

		static Transaction & defaultTransaction()
		{
			static Transaction 
				dt{};
			return dt;
		}
	};

	bool operator==(Transaction &, Transaction &);

	class Library
	{		
		public:
			vector<Transaction> transactions;
			vector<Patron> patrons;
			vector<Book> books;
			
			Library();

			void addBook(string last, string first, string title);
			void addPatron(string last, string first);
			void addTransaction(Book &, Patron &);

			Book & findBook(string last, string first, string title);
			Patron & findPatron(string last, string first);
			Transaction & findTransaction(Book &, Patron &);
	};
}