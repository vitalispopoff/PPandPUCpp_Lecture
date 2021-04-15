
// example of a general comment containing inner grammar scheme

/* 
	Simple calculator
		
	Revision history : 
			Revised by Bjarne Stroustrup	November 2013
			Revised by Bjarne Stroustrup	May 2007
			Revised by Bjarne Stroustrup	August 2006
			Revised by Bjarne Stroustrup	August 2004
			
			Originally written by Bjarne Stroustrup
				(bs@cs.tamu.edu)			Spring 2004.
				
	This program implements a basic expression calculator.
	Input from cin; output to cout.

	The grammar for input is : 
	
		Calculation:
			Print
			Quit
			Calculation Stamement
			Statement

		Print:
			;

		Quit:
			quit

		Statement : 
			Declaration
			Expression

		Declaration
			let Name = Expression
			# Name = Expression
			Name = Expression

		Expression:
			Term
			Expression + Term
			Expression – Term
		
		Term : 
			Primary
			Term * Primary
			Term / Primary
			Term % Primary
		
		Primary : 
			Number
			(Expression)                    
			–  Primary 
			+ Primary
			sqrt(Primary)
			pow(Expression; Expression)

		
		Number : 
			floating-point-literal

			
		Input comes from cin through the Token_stream called ts.		
*/