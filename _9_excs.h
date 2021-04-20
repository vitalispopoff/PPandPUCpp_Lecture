#include <string>

namespace ch09_exc02
{
using namespace std;

	class Name_pairs
	{
		public:
		Name_pairs();

		void read_users();
		void read_names();
		void read_ages();
		void read_pairs();

		private:
			vector<string>name;
			vector<double>age;

			bool ageIsValid(double);
			bool nameIsInBase(string);
			bool isInBase(string, double);

	};
}