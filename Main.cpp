#include "std_lib_facilities.h"
#include "main.h"
//#include <stdlib.h>
//#include <time.h>

int main() {

	//errors();

	//try {
	//	//helloWorld();
	//	//objectsTypesValues();
	//	//computation();
	//	return 0;
	//}
	//catch (...) {
	//	cerr << "\n\tunknown exception occured\n";
	//	keep_window_open();
	//	return 2;
	//}


	//drill

	try {
	
		errors();

		keep_window_open();
		return 0;
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << endl;
		keep_window_open();
		return 1;
	}
	catch (...) {

		cerr << "unknown exception.\n";
		keep_window_open();
		return 2;
	}



}