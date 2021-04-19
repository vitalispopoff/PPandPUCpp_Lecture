#include "std_lib_facilities.h"
#include "_9_excs.h"

//class Name_pairs;

namespace ch09_exc02
{

	//	class Name_pairs

	Name_pairs::Name_pairs() : name(), age() {}

	//void Name_pairs::addPair(string s, double d)
	//{
	//	auto notInBase = [&]
	//	{
	//		for(int i = 0; i < name.size(); ++i)
	//			if(s == name[i] && d == age[i])
	//				return false;
	//		return true;
	//	};

	//	if(nameIsValid(s) && ageIsValid(d) && notInBase())
	//	{
	//		name.push_back(s);
	//		age.push_back(d);
	//	}
	//	else
	//		cout << "wrong name, wrong age, or both already in the base\n";
	//}

	void Name_pairs::read_names()
	{
		string s;
		char c;
		while(cin >> c)
		{
			if (isalpha(c))
				s += c;
			else 
			{
				name.push_back(s);
				s = "";
				break;
			}
		}
	}

	bool Name_pairs::nameNotInBase(string s)
	{
		for(string n : name)
			if(s == n)
				return false;
		return true;
	}

	bool Name_pairs::nameIsValid(string s)
	{
		for(unsigned char c : s)
			if(!isalpha(c))
				return false;
		return true;
	}

	bool Name_pairs::ageIsValid(double d)
	{
		return 0 <= d && d < 1024;
	}
}
void ch09Excercises()
{
	using namespace ch09_exc02;

	Name_pairs np;
	//np.addPair("zbyszek", 47);
	//np.addPair("marzena", 56);
	//np.addPair("seba", 31);

	for(string n : np.name)
		cout << "\n\t" << n;

}