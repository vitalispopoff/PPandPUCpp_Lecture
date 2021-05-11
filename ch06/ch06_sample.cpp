#include "../_add/std_lib_facilities.h"
#include "ch06.h"

namespace ch06
{
	namespace sample
	{
		namespace s01
		{
			void calc()
			{
				cout 
					<< "\n\tEnter the expression (we support + and - )\t";				
				int
					lval {0},
					rval {0},
					result;
				char
					op {0};
				cin 
					>> lval 
					>> op 
					>> rval;				
				switch (op) 
				{
					case '+':
						cout 
							<< "\n\n\t== " 
							<< lval + rval 
							<< endl; 
						break;

					case '-':
						cout 
							<< "\n\n\t== " 
							<< lval - rval 
							<< endl; 
							break;

					default:
						cout 
							<< "\n\n\tNo proper operation, no result.\n";
				}
			}
		}

		namespace s02
		{
			void calc()
			{
				cout
					<< "\n\tEnter the expression including operations: + - * / \t"
					<< "\n\tadd an x to end the expression (e.g. 1+2*3x)\t";
				int
					lval {0},
					rval {0};
				cin
					>> lval;			
				if (!cin)
					error("no first operand");
			
				for (char op; cin >> op; ) 
				{			
					if (op != 'x')
						cin 
							>> rval;
					if (!cin)
						error("no second operand");
			
					switch (op) 
					{
						case '+':
							lval += rval;
							break;

						case '-':
							lval -= rval;
							break;

						case '*':
							lval *= rval;
							break;

						case '/':
							if (rval == 0)
								error("dividing by zero");
							else 
								lval /= rval;
							break;

						default:
							cout
								<< "\n\tResult:\t"
								<< lval
								<< endl;
					}
				}
				error("bad expression");
			}
		}

		namespace s05
		{							
			//void TokenStream::putBack(Token t) 
			//{
			//	if (full)
			//		error("putback() into a a full buffer");
			//	buffer = t;
			//	full = true;
			//}

			//Token TokenStream::getToken() 
			//{
			//	if (full) 
			//	{
			//		full = false;
			//		return buffer;
			//	}
			//	char
			//		ch {0};
			//	cin
			//		>> ch;
			//	switch (ch) 
			//	{
			//		case ';' :									// chosen as the print token
			//		case 'q' :									// chosen as the quit token
			//		case '(' : case ')' : 
			//		case '+' : case '-' : 
			//		case '*' : case '/' :
			//			return Token {ch};						// return so no need to break
			//
			//		case'.':
			//		case '0' : case '1' : case '2' : case '3' : case '4' :
			//		case '5' : case '6' : case '7' : case '8' : case '9' : 
			//			cin.putback(ch);						// after reading and recognizing the cin input, we put it back to cin
			//			double
			//				val {0};
			//			cin
			//				>> val;
			//			return Token {'8', val};
			//
			//		default:
			//			error("Bad token");
			//	}
			//}

			//double expression()									/// expression01
			//{			
			//	double
			//		leftSide {term()};
			//		//leftSide = expression();					/// infinite loop, gotta get the other way around
			//	Token
			//		t {getToken()};
			//	switch (t.kind) 
			//	{
			//		case'+':
			//			return leftSide + expression();
			//			//return leftSide + term01();			/// changing the order of functions includes in this too
			//	
			//		case '-':
			//			return leftSide - expression();
			//			//return leftSide - term01();			/// and in this as well
			//	
			//		default:
			//			return leftSide;
			//	}
			//}
			
			//double term()										///term01
			//{
			//	double
			//		leftSide {primary()};
			//	Token
			//		t {getToken()};
			//	while (true) 
			//	{
			//		switch (t.kind) 
			//		{
			//			case '*':
			//				leftSide *= primary();
			//				t = getToken();
			//				break;
			//
			//			case '/':
			//				double
			//					d {primary()};
			//				if (d == 0)
			//					error("no division by zero allowed");
			//				leftSide /= d;
			//				t = getToken();
			//				break;
			//
			//			default:
			//				return leftSide;
			//		}
			//	}
			//}
			
			//double primary()									///	primary01
			//{
			//	Token
			//		t = getToken();
			//	switch (t.kind) 
			//	{
			//		case '(': 										///	primary starts with a bracket
			//			double
			//				d {expression()};						/// which contains an expression
			//			t = getToken();								/// after which is a token
			//			if (t.kind != ')')							/// which better be a closing bracket
			//				error("')' expected");
			//
			//			return d;									/// if so, the expression is to be dealt with by a designated function		
			//		case '8':										/// '8' represents a number
			//			return t.value;
			//	
			//		default:
			//			error("primary expected");					/// if token aint a bracket or a number symbol, then WTF
			//	}
			//}
		}

		namespace s06
		{
			//using s03::Token;
			//using s05::getToken;
			//using s05::term;

			//double expression04() {
			//	double
			//		leftSide = term();	// read the term
			//	Token
			//		t = getToken();		// initialize token
			//	while (true)				// the loop is virtually infinite
			//	{
			//		switch (t.kind)			// read the token
			//		{
			//		case'+':				// token is a proper operation
			//			leftSide += term();	// read to the right of the token
			//			t = getToken();		// search for another token
			//			break;
			//		case '-':				// just like above
			//			leftSide -= term();
			//			t = getToken();
			//			break;
			//		default:				// no proper token found
			//			return leftSide;	// nothing more to read and calculate
			//		}
			//	}
			//}
		}
	}	
}