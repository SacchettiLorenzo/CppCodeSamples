#include <stdio.h>
#include <string.h>

int main() {

	//Pointer Casting

	//depending on the machine this chunk of code could have different behaviour because of the endiannees
	//intel processor work on little endian (less significant byte first)

	int v_0 = 256;
	char* p;
	p = (char*)&v_0; // &v casted from ( int *) to ( char *) 
	*p = 1; // this is an assignment of a ( char ) at the first element of the pointer (less significant)
	printf(" % d \n", v_0);
	//in binary:
	// 256: 00000000 00000000 00000001 00000000
	// 257: 00000000 00000000 00000001 00000001

	int v_1[10] = { -1,1000,2 };
	int a;
	char* ptr = (char*)v_1+1;
	a = strlen(((char*)v_1 + 1));
	printf(" % d \n", a);
	//The arry looks as follow: (little endian has less significant on the left)
	//ffffffff E8030000 02000000
	//ptr is moved foreward by 1
	//strlen count ff ff ff E8 30 so it equals to 5
	 
	int v_2[10] = {-1,1000,2};
	int b;

	b = strlen((char*)(v_2 + 1));
	printf(" % d \n", b);
	//Same as the one above but the pointer in incremented before the casting so strlen count E8 30 so it equals to 2

	char s[8] = "12";
	int* q;

	q = (int*)s;
	printf("%d", *q);
	//after casting p will look at the first 4 bytes in the array that are 49 50 00 00 
	//the number 50 49 is equal to 12849 (looking from right to left for the conversion because more significant value on the right)

	int v_3[8] = { -1,0,8 };
	char* t;

	t = (char*)(v_3 + 1);
	memcpy(t + 2, t - 4, 4);
	printf("%i,%i,%i", v_3[0], v_3[1], v_3[2]);
	//v_3 : 
	//ffffffff 00000000 08000000
	// after the memcopy the situation is as follow:
	//ffffffff 0000ffff ffff0000
	// reading from right to left each byte ffffffff = -1, ffff0000 = -65536, 0000ffff = 65535

	

}