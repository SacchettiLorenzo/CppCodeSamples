#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    //basic file handling -------------------------------------------
    ofstream file; //creates and write to files
    ifstream file2; //reads from files
    fstream file3; // conmination of ofstream and ifstrfeam 

    ofstream Myfile("myfile.txt");
    Myfile << "write to the file" << endl;
    Myfile.close();

    string text;
    ifstream myreadfile ("myfile.txt");
    while (getline(myreadfile,text)) {
        cout << text << endl;
    }
    //---------------------------------------------------------------
    
    //using modes ---------------------------------------------------
    ofstream test("myfile.txt", ios_base::app); //append 
    test << "Appending some text" << endl;

    ifstream test2("myfile.txt", ios_base::in);
    while (getline(test2, text)) {
        cout << text << endl;
    }
    
}
/*
* c++ handles files via fstream library
* ofstream handle output
* ifstream handle input
* 
* it is possible to specify the mode of operation via ios_base class
* ios_base::in for input (default in ifstrem instance) 
* ios_base::out for output (default in ofstream instance)
* ios_base::binary for reading binary file instead of text files
* ios_base::ate the output position start at the end of the file
* ios_base::app all output operations happen at the end of the file appending to existing content
* ios_base::trunc any content that existed in the file before it is open are discarder
*/
