#include <iostream>
#include <string>

using namespace std;

//normal enumaration
enum numbers  {one, two, three};

//normal enumarations cannot have names already taken by other enumerations, scoped enumarations can
enum class CircleColors { red, blue, green };
enum class SquareColors { red, blue, green };

//enum numberss { one, two, three }; this will not compile

//enum elements can have an assigned values 
enum Foo { a, b, c = 10, d, e = 1, f, g = f + c };
enum direction { left = 'l', right = 'r' };

//it is possible to specify the type of the enum and force the conversion with static cast (in the char is described with and integer for example)
enum withtype : char { l = 'a'};
char val = static_cast<char>(l);

int main()
{
    //the name of the enum can be omitted, this will make the enumeration valid only for his scope and therefore the elements names are reusable
    {
        enum { a, b, c };
    }

    enum sameAsBefore{a,b,c};
}


