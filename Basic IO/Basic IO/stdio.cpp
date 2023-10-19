
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
	tmp = sprintf_s(buffer, "This is the string for snprintf: %s", "ciao");
	tmp = snprintf(buffer, bufferSize, "This is the string for snprintf: %s", "ciao");
}

void fileAccess() {
	//file management
	char buffer[1024];
	FILE* file;
	file = fopen("filename.txt", "r");
	fclose(file);
	freopen("myfile.txt", "w", file);
	fflush(file);
	setbuf(file, buffer);
	setvbuf(file, buffer, _IOFBF, 1024);
	//file positioning
	fpos_t pos;
	fgetpos(file, &pos);
	pos++;
	fsetpos(file, &pos);
	fseek(file, 9, SEEK_SET);
	long size = ftell(file);
	rewind(file);
}

void characterStream() {
	int c;
	char ch;
	const int stringLength = 100;
	char s[stringLength];
	c = fgetc(stdin);
	fgets(s, stringLength, stdin);
	fputc(c, stdout);
	fputs(s, stdout);
	ch = getc(stdin);
	ch = getchar();
	gets_s(s);
	putc(c, stdout);
	putchar('c');
	puts(&ch);
	if (c == '#') ungetc('@', stdout);
}

int main() {
	//formattedStream();
	characterStream();
}

/*
* stdio.h have function for accessing input and output on file, formatted stream, character stream
* it can deal with file position and files errors handling
* 
* _s at the end of some function involve the use of the safe version (it is possible to use the unsafe version if wanted)
* 
* Formatted Stream:
* printf : print the provided string to the standard output
* fprintf: the same as printf but it is possible to specify another stream output (a file for example)
* scanf : read from standard input
* fscanf: the same as scanf but it is possible to specify another stream input
* sprintf: Write formatted data to buffer, return the total number of characters written. The size of the buffer should be large enough to contain the entire string
* snprintf: Write formatted output to sized buffer, return the number of characters that would have been written if n had been sufficiently large. (all the surplus character are discarded) (safer that sprintf)
* the above functions have a version that can manage a variable number of arguments but needs to be treated accordingly (see variadic functions)
* 
* Character Stream:
* fgetc: Get character from stream. can specify the stream
* fgets: Get string from stream
* fputc: Write character to stream
* fputs: Write string to stream
* getc: Get character from stream
* getchar: Get character from stdin
* gets: Get string from stdin
* putc: Write character to stream
* putchar: Write character to stdout
* puts: Write string to stdout with newline \n
* ungetc: Unget character from stream, replace the last read character with provided character. in the example if the last read character == # it replace it with @ in the stream
*
* File Access
* fopen: Opens the file whose name is specified in the parameter filename and associates it with a stream
* fclose: close the stream
* freopen: Reopen stream with different file or mode
* fflush: If the given stream was open for writing  any unwritten data in its output buffer is written to the file.
* setbuf: Specifies the buffer to be used by the stream
* setvbuff: Specifies a buffer for stream. The function allows to specify the mode and size of the buffer (in bytes).
* fgetpos: Retrieves the current position in the stream.
* fsetpos: Restores the current position in the stream to pos.
* fseek: Reposition stream position indicator
* ftell: Returns the current value of the position indicator of the stream. return a long int
* rewind: Set position of stream to the beginning
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

/* fopen mode
* r : read : Open file for input operations. The file must exist.
* w : write : Create an empty file for output operations
* a : append
* r+: read/update: Open a file for update (both for input and output). The file must exist.
* w+: write/update: Create an empty file and open it for update
* a+: 	append/update: Open a file for update (both for input and output) with all output operations writing data at the end of the file.
* 
*/

/* buffer mode
* _IONBF, stream is unbuffered (every single byte is written/read immediately)
* _IOLBF, the buffer is written as soon as newline is found
* _IOFBF, write to disk only whe buffer is full
*/

/* fseek position used as reference
* SEEK_SET	Beginning of file
* SEEK_CUR	Current position of the file pointer
* SEEK_END	End of file *
*/