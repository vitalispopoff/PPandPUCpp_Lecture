
/*
*/
void calcProj();

// 01.

/*basic concept of a calculator:
text inteface,
two most basic operations
int input
switch based logic
*/
//void calc_01();

// 02.

/*code developed to 
include for basic arithmetic operations
enable longer chains of operands
special character to end the expression and start calculation
basic error management

switch based logic uses two modes:
a) proper operators filtered accordingly
b) execution character filtered by default case

recognition of datay types is given to the cin function
*/
//void calc_02();

// 03. Tokens.

/*
*/
class Token;

// 05. Grammar.

/*
expression grammar:
	term
	expression '+' term
	expression '-' term

	the implementations fails tho: 
	recursion must follow the actual part of the code 
	this however is said to implement an opposite grammar
*/
//double expression01();

/*due to the problems with grammar implementations,
switch is replaces with an if-else cascade,
and recursion is completely removed.

but the only it does now is printing out every 3rd token
*/
//double expression03();

/*term grammar:
	primary
	term '*' primary
	term '/' primary
	term '%' primary - apparently it doesn't compile - no % for the doubles; its implementation is postponed
 
 which similar to the expression grammar
*/
double term01();

/* primary grammar:
	number
	'('expression')'


*/
double primary01();

/* fixing the 
*/
double expression04();

/**/
//Token getToken01();

