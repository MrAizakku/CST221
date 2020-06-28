/*	Programmer: Isaac Tucker
	CST-211 : MMU
	06/27/2020
	Description: This program will take a decimal number between 0 and 4095 as input from a user and it will output the number as a 32-bit binary number, a 32-bit hex number, and it will transform the input by shifting the number 16 bits to the left and masking out the bottom 16 bits to finally represent the number as a hex number. Modularized functions will be utilized as well.		*/
#include <stdio.h>
#include <stdlib.h>

void printBinary(int n) {	//convert given int to binary with least sig. bit on right
	int a[32] = {0}, i, j;
	for(i = 0; n > 0; i++) {
		a[i] = n % 2;
		n = n / 2;
	}
	printf("\nBinary: ");
	for (j = (sizeof(a)/sizeof(int)) -1; j > -1; j--) {
		printf("%i", a[j]);
		if(j % 8 == 0) {printf(" ");}
	}
}

void printHex(int n) {		//convert given int to hexidecimal
	printf("\nHexidecimal: 0x%08x\n", n);
}

void displayDeci(int n) {	//Display inputted number as decimal, binary and hex.
	printf(" \nYou entered the base-10 number: %i", n);
	printBinary(n);
	printHex(n);
}

void displayShifted(int n) {	//display inputted number shifted 16 bits as decimal, binary and hex
	n = n << 16;
	printf(" \nNumber when shifted by 16 bits : %i", n);
	printBinary(n);
	printHex(n);

}
//display inputted number shifted 16 bits and masked btm 16 bits as decimal, binary and hex
void displayShiftedMasked(int n) {
	n = (n << 16) & ~0xFFFF;
	printf("\nNumber when shifted by 16 bits and masking bottom 16 bits : %d", n);
	printBinary(n);
	printHex(n);
}
//display number shifted 16 bits, masked btm 16 bits with added 0x07ff as decimal, binary and hex
void displayShiftedMaskedAdd(int n) {
	n = ((n << 16) & ~0xFFFF) | 0x07ff;
	printf("\nNumber when shifted by 16 bits, masking bottom 16 bits with 0x07ff : %d", n);
	printBinary(n);
	printHex(n);
}

void displayResults(int n) {	//group all display methods
	displayDeci(n);
	displayShifted(n);
	displayShiftedMasked(n);
	displayShiftedMaskedAdd(n);
}

int main() {
	int n;
	printf("Hello and welcome to this number converter. \n");
	printf("Please provide a base-10 whole number between 0 - 4095. \n");
	scanf("%i", &n);
	if(n < 0 || n > 4095) {
		printf("\nYou have entered an invalid selection. Please try again. \n");
		return 1;
	} else {
		displayResults(n);
		return 0;
	}
}
