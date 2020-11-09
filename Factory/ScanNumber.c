//Extra function of getting the number

#ifndef Including
#define Including

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#endif

int ScanNumber() {
	//Initialising the input number
	int requestedNumber;
	//Initialising dump parameter
	char dumper[256];
	while (!scanf_s("%d", &requestedNumber)) {
		printf_s("Input the number, please try again...\n");
		//"Clearing" the buffer
		gets(dumper);
	}
	//Checking for lower limit
	if (requestedNumber <= 0) {
		printf_s("I accept only natural numbers, please try again...\n");
		requestedNumber = ScanNumber();
	}
	return requestedNumber;
}