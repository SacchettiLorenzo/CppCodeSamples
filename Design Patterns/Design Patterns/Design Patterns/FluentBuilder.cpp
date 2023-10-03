#include <iostream>
#include <string>

using namespace std;

struct StringBuilder {
    string root;
    int number;

    StringBuilder(string r) {
        root = r;
    }

    //the function return a pointer to the struct itself
    StringBuilder& add_string_piece(string s) {
        root = root + s;
        return *this;
    }

    StringBuilder& define_number(int n) {
        number = n;
        return *this;
    }

};


int main()
{
    StringBuilder s("ciao");
    s.add_string_piece(" ciao").add_string_piece(" ciao").define_number(5);
    cout << s.root << endl;

}

/* Fluent builder design pattern
*  By returning a reference to the struct or class itself the calls can now be chained.
*  This should be used when a concatenation is neded and when the function work with member accessible by functions.
*  this design pattern is usefull when creating big objects.
*  
*/

