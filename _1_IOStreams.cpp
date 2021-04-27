#include "std_lib_facilities.h"
#include <iostream>

namespace ch10
{
	void example01()
	{		
		string
			inputFileName{"E:\\_LAB\\unpeak\\shortie\\1kHz_16_mono.wav"};
		if(inputFileName.size() ==0)
		{
			cout
				<< "Please enter input file name:\t";
			cin
				>> inputFileName;
		}
		ifstream
			ist{inputFileName};
		if (!ist)
			error("I can't open input file ", inputFileName);
		vector<unsigned char> 
			bytes;
		for (unsigned char byte; ist >> byte; )
			bytes.push_back(byte);
		int 
			index{0};
		for (unsigned char byte : bytes)
			cout 
				<< int(byte)
				<< (index++ % 8 == 7 ? '\n' : '\t');
	}	

	void example10_06(istream & ist, vector<int> & v, char terminator)
	{
		for (int i; ist >> i;)
			v.push_back(i);

		if (ist.eof())
			return;

		if (ist.bad())
			error("ist bad");

		if (ist.fail())
		{
			ist.clear();						// sets fail flag to false

			char
				c;
			ist
				>> c;							// intercepts the faulty byte
			if (c != terminator)				
			{
				ist.unget();					// gives it back to stream
				ist.clear(ios_base::failbit);	// sets fail flag back to true
			}
		}
	}



}

void IOStreamsMain()
{
	using namespace ch10;
}