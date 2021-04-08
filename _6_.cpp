#include "std_lib_facilities.h"
#include "_6_programming.h"

// 01. 

//void calc_01() {
//
//	cout << "\n\tEnter the expression (we support + and - )\t";
//
//	int
//		lval{ 0 },
//		rval{ 0 },
//		result;
//	char
//		op;
//	cin >> lval >> op >> rval;
//
//	switch (op) {
//	case '+':
//		cout << "\n\n\t== " << lval + rval << endl; break;
//	case '-':
//		cout << "\n\n\t== " << lval - rval << endl; break;
//	default:
//		cout << "\n\n\tNo proper operation, no result.\n";
//	}
//}

// 02. 

//void calc_02() {
//
//	cout
//		<< "\n\tEnter the expression including operations: + - * / \t";
//	cout
//		<< "\n\tadd an x to end the expression (e.g. 1+2*3x)\t";
//	int
//		lval{ 0 },
//		rval{ 0 };
//	cin
//		>> lval;
//
//	if (!cin)
//		error("no first operand");
//
//	for (char op; cin >> op;) {
//
//		if (op != 'x')
//			cin >> rval;
//		if (!cin)
//			error("no second operand");
//
//		switch (op) {
//		case '+':
//			lval += rval;
//			break;
//		case '-':
//			lval -= rval;
//			break;
//		case '*':
//			lval *= rval;
//			break;
//		case '/':
//			if (rval == 0)
//				error("dividing by zero");
//			else lval /= rval;
//			break;
//		default:
//			cout
//				<< "\n\tResult:\t"
//				<< lval
//				<< endl;
//		}
//	}
//	error("bad expression");
//}

// 03. Tokens.

class Token {
public:
	char
		kind;
	double
		value;
};

// 05. Grammar.

//double expression01() {
//
//	double
//		//leftSide = expression01(); // infinite loop, gotta get the other way around
//		leftSide = term01();
//	Token
//		t = getToken01();
//	switch (t.kind) {
//	case'+':
//		//return leftSide + term01(); // changing the order of functions includes in this too
//		return leftSide + expression01();
//	case '-':
//		//return leftSide - term01(); // and in this as well
//		return leftSide - expression01();
//	default:
//		return leftSide;
//	}
//}

//double expression03() {
//
//	double
//		leftSide = term01();	// read the term
//	Token
//		t = getToken01();		// initialize token
//	while (true)				// the loop is virtually infinite
//	{
//		switch (t.kind)			// read the token
//		{
//		case'+':				// token is a proper operation
//			leftSide += term01();	// read to the right of the token
//			t = getToken01();		// search for another token
//			break;
//		case '-':				// just like above
//			leftSide -= term01();
//			t = getToken01();
//			break;
//		default:				// no proper token found
//			return leftSide;	// nothing more to read and calculate
//		}
//	}
//}

double term01() {
	double
		leftSide = primary01();
	Token
		t = getToken01();
	while (true) {
		switch (t.kind) {
		case '*':
			leftSide *= primary01();
			t = getToken01();
			break;
		case '/': {
			double
				d = primary01();
			if (d == 0)
				error("no division by zero allowed");
			leftSide /= d;
			t = getToken01();
			break;
		}
		default:
			return leftSide;
		}
	}
}

double primary01() {
	Token
		t = getToken01();
	switch (t.kind) {
	case '(': {						//primary starts with a bracket
		double
			d = expression03();		// which contains an expression
		t = getToken01();			// after which is a token
		if (t.kind != ')')			// which better be a closing bracket
			error("')' expected");
		return d;					// if so, the expression is to be dealt with by a designated function
	}
	case '8':			// '8' represents a number
		return t.value;
	default:
		error("primary expected");	// if token aint a bracket or a number symbol, then WTF
	}
}

class TokenStream{
public:
	//TokenStream();
	Token get();
	void putBack(Token);
private:
	bool 
		full{ false };
	Token 
		buffer;
};

void TokenStream::putBack(Token t) {
	if (full)
		error("putback() into a a full buffer");
	buffer = t;
	full = true;
}

Token TokenStream::get() {
	if (full) {
		full = false;
		return buffer;
	}
	char
		ch;
	cin
		>> ch;
	switch (ch) {
	case ';' :	// chosen as the print token
	case 'q' :	// chosen as the quit token
	case '(' : case ')' : 
	case '+' : case '-' : case '*' : case '/' :
		return Token{ ch };	// return so no need to break
	case'.':
	case '0' : case '1' : case '2' : case '3' : case '4' :
	case '5' : case '6' : case '7' : case '8' : case '9' : {
		cin.putback(ch);	// after reading and recognizing the cin input, we put it back to cin
		double
			val;
		cin
			>> val;
		return Token{ '8', val };
	}
	default:
		error("Bad token");
	}
}

double expression04() {
	double
		leftSide = term01();	// read the term
	Token
		t = getToken01();		// initialize token
	while (true)				// the loop is virtually infinite
	{
		switch (t.kind)			// read the token
		{
		case'+':				// token is a proper operation
			leftSide += term01();	// read to the right of the token
			t = getToken01();		// search for another token
			break;
		case '-':				// just like above
			leftSide -= term01();
			t = getToken01();
			break;
		default:				// no proper token found
			return leftSide;	// nothing more to read and calculate
		}
	}
}

typedef double (*funk)();
funk expression = expression04;

//void calcMk01() {
//
//	while (cin)
//		cout << "=" << expression() << endl;
//}



void calcProj() {

	while (cin)
		cout << "=" << expression() << endl;

}