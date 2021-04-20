#include <string>

namespace ch09_exc02
{
using namespace std;

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
			prints all names with the ages from respective vectors.
		*/
		void read_pairs();

		/*
			sorts name vector alphabetically, and base on that shuffles the age vector.
		*/
		void sort();

		private:
			vector<string>name;
			vector<double>age;

			bool ageIsValid(double);
			bool nameIsInBase(string);
			bool isInBase(string, double);

	};
}