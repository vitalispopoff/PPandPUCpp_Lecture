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

	//	--------------------------------------------	

	enum class Genre
	{
		nan,
		fiction,
		nonfiction,
		periodical,
		biography,
		children
	};

	//	--------------------------------------------	

	struct Book
	{
		string
			authorLastName,
			authorFirstName,			
			title,
			isbn{"00-0000-000-0"};
		Date
			copyDate{};
		Genre
			genre{Genre::nan};
		bool
			isCheckedOut{false};

		Book();
		Book(string last, string first, string title);

		static Book & defaultBook()
		{
			static Book 
				db{"", "", ""};
			return db;
		}
	};

	bool		operator == (const Book &, const Book &);
	ostream &	operator << (ostream &, const Book &);

	bool isValidISBN(string);

	//	--------------------------------------------	

	class Patron
	{
		public:
			Patron();
			Patron(string last, string first);

			string	getLastName		()			{ return lastName;}
			string	getFirstName	()			{ return firstName;}
			double	getFeeAccount	()			{ return feeAccount;}
			void	addToAccount	(double d)	{ feeAccount += d;}
			bool	iou				()			{ return feeAccount < 0.;}

			static Patron & defaultPatron()
			{
				static Patron
					dp{};
				return dp;
			}

		private:
			string 
				lastName,
				firstName;
			double
				feeAccount{0.};
	};

	bool		operator == (const Patron & , const Patron & );
	ostream &	operator << (ostream & , const Patron &);
	
	//	--------------------------------------------	

	struct Transaction
	{
		Book 
			& book;
		Patron
			& patron;

		Transaction();
		Transaction(Book & , Patron &);

		static Transaction & defaultTransaction()
		{
			static Transaction 
				dt{};
			return dt;
		}
	};

	bool operator == (const Transaction &, const Transaction &);
	ostream &	operator << (ostream &, const Transaction &);

	//	--------------------------------------------	

	class Library
	{		
			vector<Transaction> transactions;
			vector<Patron> patrons;
			vector<Book> books;
		public:
			
			Library();

			void addBook(string last, string first, string title);
			void addPatron(string last, string first);
			void addTransaction(Book &, Patron &);

			Book & findBook(string last, string first, string title);
			Patron & findPatron(string last, string first);
			Transaction & findTransaction(Book &, Patron &);

			void checkout(string authLast,string authFirst,string title,string patronLast,string patronFirst);
	};

	//	--------------------------------------------	

	//	--------------------------------------------	
}

namespace ch09_exc13
{

	//	--------------------------------------------	

	class Rational
	{
		public:
			class Invalid{};

			Rational();
			Rational(long n,long d);

			double	getValue		() const ;
			long	getNumerator	() const	{ return numerator;}
			long	getDenominator	() const	{ return denominator;}
			void	setNumerator	(long n){ numerator = n;}
			void	setDenominator	(long d){ denominator = d;}

		private:
			long
				numerator{0},
				denominator{1};
		
			long denyZero(long);		
	};

	//	--------------------------------------------	

}

namespace ch09_exc14
{

	class Money
	{
		public:
			Money();
			Money(double);

			double	getMoney();
			void	setMoney(double);

		//private:
			long cents;

		/*
			converts long cents to double representation of money,
			doesn't care about previewing additional decimal places.
			does limit the min/max values to the length of double mantissa
			in order to meet the rounding rule requirement.
			For the exponent values exceeding length of the mantissa (52),
			the double cant't keep the increment of value within 0.5, 
			which breaks the rounding requirement.
			The accepted max/min range should be probably limited by another bit,
			to make sure the rounding process makes even sense...	
		*/
		double	centsToDouble(long);
		long	doubleToCents(double);
	};

}