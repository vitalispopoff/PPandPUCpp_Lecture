#include <string>

namespace ch09_exc02
{
using namespace std;

	class Name_pairs
	{
		public:
		Name_pairs();

		void addPair(string, double);


			vector<string>name;
			vector<double>age;
			const static vector<char> letters;

		private:			

			bool nameIsValid(string);
			bool ageIsValid(double);
	};
}