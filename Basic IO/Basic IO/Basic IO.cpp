#include <iostream>     // standard input - output stream

int main()
{
    int age;
    char line1[50];
    char line2[50];
    char line3[50];

    wchar_t line4[50];


    std::cin.getline(line1, 50); // read 50 char even with spaces
    std::cout << line1 << std::endl;
    std::cout << "---------------------------------" << std::endl;

    std::cin >> line2; // read char util user press enter but read until the end of the line, it read a single word
    std::cout << line2 << std::endl;
    std::cout << "---------------------------------" << std::endl;

    std::cin.ignore(10); // Ignore the next 10 characters of std::cin
    std::cin.getline(line3, 50);
    std::cout << line3 << std::endl;
    std::cout << "---------------------------------" << std::endl;

    std::wcin >> line4;
    std::wcout << line4 << std::endl;
    std::cout << "---------------------------------" << std::endl;

    std::cout << "enter your age" << std::endl; //output data
    std::cin >> age;                //input data
    if (age < 18) {
        std::cerr << "you are too young!!"; // standard error stream 
        std::clog << "An error occurred";
    }



}

/* NOTE ------------------------------------------
*   '<<' IS THE INSERTION OPERATOR
*   'std' STANDARD
*   'cerr' has no buffer, the message is displayed but is not stored.
*   'clog' the behavior is the same as cout but is not intended to be used as output for the user
*   'cin' use char as character type so it can ber used for ASCII and ANSI characters.
*   'wcin' wide cin. it use wchar_t character type so is usable with UNICODE for better internationalization. in alternatitve to wchar_t it is possible to use char16_t and char32_t to be more specific. Same with wcout;
*   'cout' and 'wcout' has a series of Member functions to acces the buffer or to set options for data display.
*   'wcerr' and 'wclog' has the same behavior of cerr and clog
*
*
*
*
*
* */


