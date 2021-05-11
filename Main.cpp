#include<cstdlib>												//v/	delivers srand()
#include<ctime>													//v/	delivers time()
#include "main.h"

int main() 
{
	srand(int(time(NULL)));

	return 0;	
} 