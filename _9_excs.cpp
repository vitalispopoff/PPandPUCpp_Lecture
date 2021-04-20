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


		


}



void ch09Excercises()
{
	using namespace ch09_exc02;

	Name_pairs np;

	np.read_users();
	//np.read_names();
	//np.read_pairs();
	//np.read_ages();

	cout << np;

}