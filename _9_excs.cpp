#include "std_lib_facilities.h"
#include "_9_excs.h"

namespace ch09_exc02
{
	//	class Name_pairs

	Name_pairs::Name_pairs() : name(), age() {}

	void Name_pairs::read_names()
	{
		cout 
			<< "enter name, or 'exit'\n";
		string 
			s;
		char 
			c;
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
		};
	}

	bool Name_pairs::isInBase(string s, double d)
	{
		for(int i = 0; i < name.size(); ++i)
			if(s == name[i] && d == age[i])
				return true;
		return false;
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

	np.read_names();

	for(string n : np.name)
		cout << "\n\t" << n;

}