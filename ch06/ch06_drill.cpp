#include "../_add/std_lib_facilities.h"
#include "ch06.h"

namespace ch06
{
	namespace drill
	{
		namespace d01
		{					
			//This file is known as calculator02buggy.cpp
			//
			//I have inserted 5 errors that should cause this not to compile
			//I have inserted 3 logic errors that should cause the program to give wrong results
			//
			//First try to find an remove the bugs without looking in the book.
			//If that gets tedious, compare the code to that in the book (or posted source code)
			//
			//Happy hunting!
																	
			//Token_stream::Token_stream() :					// The constructor just sets full to indicate that the buffer is empty:
			//	full (false),	buffer (0)					// no Token in buffer
			//{}
															
			//void Token_stream::putback(Token t)				// The putback() member function puts its argument back into the Token_stream's buffer:
			//{
			//	if (full) 
			//		error("putback() into a full buffer");
			//	buffer = t;									// copy t to buffer
			//	full = true;								// buffer is now full
			//}

			//Token Token_stream::get()						/// error #2
			//{
			//	if (full)									// do we already have a Token ready?
			//	{       
			//		full = false;							// remove token from buffer
			//		return buffer;
			//	}
			//	char 
			//		ch {0};
			//	cin 
			//		>> ch;									// note that >> skips whitespace (space, newline, tab, etc.)
			//	switch (ch) 
			//	{
			//		case ';':								// for "print"
			//		case 'q':								// for "quit"
			//		case '(': case ')': 
			//		case '+': case '-': 
			//		case '*': case '/':
			//			return Token(ch);					// let each character represent itself
			//
			//		case '.':
			//		case '0': case '1': case '2': case '3': case '4':
			//		case '5': case '6': case '7': case '8': case '9':		/// error #3
			//			cin.putback(ch);					// put digit back into the input stream
			//			double 
			//				val {0};
			//			cin 
			//				>> val;							// read a floating-point number
			//			return Token('8', val);				// let '8' represent "a number"
			//
			//		default:
			//			error("Bad token");
			//	}
			//}

			//Token_stream 
			//	ts;											// provides get() and putback() 

			//double expression();							// declaration so that primary() can call expression()
			//
			
			//double primary()								// deal with numbers and parentheses
			//{
			//	Token 
			//		t {ts.get()};
			//	switch (t.kind) 
			//	{
			//		case '(':								// handle '(' expression ')'
			//			double 
			//				d {expression()};
			//			t = ts.get();
			//			if (t.kind != ')') 
			//				error("')' expected");			/// error #4
			//				return d;
			//
			//		case '8':								// we use '8' to represent a number
			//			return t.value;						// return the number's value
			//
			//		default:
			//			error("primary expected");
			//	}
			//}

			//double term()									// deal with *, /, and %
			//{
			//	double 
			//		left {primary()};
			//	Token 
			//		t {ts.get()};							// get the next token from token stream
			//	while (true) 
			//	{
			//		switch (t.kind) 
			//		{
			//			case '*':
			//				left *= primary();
			//				t = ts.get();
			//
			//			case '/':
			//				double 
			//					d {primary()};
			//				if (d == 0) 
			//					error("divide by zero");
			//				left /= d;
			//				t = ts.get();
			//				break;
			//
			//			default:
			//				ts.putback(t);					// put t back into the token stream
			//				return left;
			//		}
			//	}
			//}
			
			//double expression()								// deal with + and -
			//{
			//	double										// read and evaluate a Term
			//		left {term()};							/// error #5 
			//	Token										// get the next token from token stream
			//		t {ts.get()};
			//	while (true) 
			//	{
			//		switch (t.kind) 
			//		{
			//			case '+':
			//				left += term();						// evaluate Term and add
			//				t = ts.get();
			//				break;
			//
			//			case '-':
			//				left += term();						// evaluate Term and subtract
			//				t = ts.get();
			//				break;
			//
			//			default:
			//				ts.putback(t);						// put t back into the token stream
			//				return left;						// finally: no more + or -: return the answer
			//		}
			//	}
			//}

			//int main()
			//{														/// error #7
			//	try
			//	{
			//		while (cin) 
			//		{
			//			Token 
			//				t {ts.get()};
			//			double 
			//				val {0};								/// error #6
			//			if (t.kind == 'q') 
			//				break;									// 'q' for quit
			//			if (t.kind == ';')							// ';' for "print now"
			//				cout 
			//					<< "=" 
			//					<< val 
			//					<< '\n';
			//			else
			//				ts.putback(t);
			//			val = expression();
			//		}
			//		keep_window_open();
			//	}
			//	catch (exception& e) 
			//	{
			//		cerr 
			//			<< "error: " 
			//			<< e.what() 
			//			<< '\n';
			//		keep_window_open();
			//		return 1;
			//	}
			//	catch (...) 
			//	{
			//		cerr 
			//			<< "Oops: unknown exception!\n";
			//		keep_window_open();
			//		return 2;
			//	}
			//}
		}
	}
}