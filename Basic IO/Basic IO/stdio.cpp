
#include <stdio.h> //The C Standard Library <stdio.h> header.

void formattedStream() {
	int number;
	int tmp;
	const int bufferSize = 100;
	char buffer[bufferSize];
	printf("%s\n", "ciao");
	fprintf(stdout, "%s\n", "ciao");
	scanf_s("&d\n", &number);
	fscanf_s(stdin, "%d\n", &number);
	tmp = sprintf(buffer, "This is the string for snprintf: %s", "ciao");
	tmp = snprintf(buffer, bufferSize, "This is the string for snprintf: %s", "ciao");
}

void fileAccess() {

}

void characterStream() {

}

int main() {
	formattedStream();
	/*
	char s[20];
	fgets(s, sizeof(s), stdin);
	*/
}

/*
* stdio.h have function for accessing input and output on file, formatted stream, character stream
* it can deal with file position and files errors handling
* 
* Formatted Stream:
* printf : print the provided string to the standard output
* fprintf: the same as printf but it is possible to specify another stream output (a file for example)
* scanf : read from standard input
* fscanf: the same as scanf but it is possible to specify another stream input
* sprintf: Write formatted data to buffer, return the total number of characters written. The size of the buffer should be large enough to contain the entire string
* snprintf: Write formatted output to sized buffer, return the number of characters that would have been written if n had been sufficiently large. (all the surplus character are discarded) (safer that sprintf)
* the above functions have a version that can manage a variable number of arguments but needs to be treated accordingly (see variadic functions)
*/

/*  SPECIFIERS
* 
d or i	Signed decimal integer	392
u	Unsigned decimal integer	7235
o	Unsigned octal	610
x	Unsigned hexadecimal integer	7fa
X	Unsigned hexadecimal integer (uppercase)	7FA
f	Decimal floating point, lowercase	392.65
F	Decimal floating point, uppercase	392.65
e	Scientific notation (mantissa/exponent), lowercase	3.9265e+2
E	Scientific notation (mantissa/exponent), uppercase	3.9265E+2
g	Use the shortest representation: %e or %f	392.65
G	Use the shortest representation: %E or %F	392.65
a	Hexadecimal floating point, lowercase	-0xc.90fep-2
A	Hexadecimal floating point, uppercase	-0XC.90FEP-2
c	Character	a
s	String of characters	sample
p	Pointer address	b8000000
n	Nothing printed.
n	The corresponding argument must be a pointer to a signed int.
n	The number of characters written so far is stored in the pointed location.	
%	A % followed by another % character will write a single % to the stream.	%

it is possible to add format specifiers for precision, print width and lenght sub-specifier
*/