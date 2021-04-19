#include <string>

namespace ch09_exc02
{
using namespace std;

	class Name_pairs
	{
		public:
		Name_pairs();

		void addPair(string, double);

		void read_names();


			vector<string>name;
		private:
			vector<double>age;
			const static vector<char> letters;


			bool nameIsValid(string);
			bool ageIsValid(double);
			bool nameNotInBase(string);

	};
}