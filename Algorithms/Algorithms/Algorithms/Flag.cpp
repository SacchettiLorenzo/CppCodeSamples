#include <iostream>
using namespace std;

enum color { rosso, bianco, verde };
typedef enum color Color;

void Bandiera(Color B[], int n)
{
    int g = 0;
    int r = n - 1;
    Color tmp;
    for (size_t i = 0; i < n; i++) {
        if (B[i] == verde) {
            tmp = B[g];
            B[g] = B[i];
            B[i] = tmp;
            g++;    
        }

        if (B[i] == rosso && i<=r) {
            tmp = B[r];
            B[r] = B[i];
            B[i] = tmp;
            r--;
            i--;
        }

        if (B[i] == bianco) {
            cout << endl;
        }

    }
    
}
int main()
{
	Color B1[] = { rosso, verde, rosso, bianco, verde, bianco };
    int dimB1 = sizeof(B1) / sizeof(int);
	Bandiera(B1,dimB1);

	
	cout << endl;
}


