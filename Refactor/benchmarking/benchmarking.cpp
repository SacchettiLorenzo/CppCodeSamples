// Benchmarking.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <memory>
#include <chrono>
using namespace std;

void functionToPerform();

class Timer {
public: 
    
    //constructor and start of the chrono 
    Timer() {
        m_StartTimepoint = chrono::high_resolution_clock::now();
    }

    //destructor
    ~Timer() {
        Stop();
    }

    //stop the chrono
    void Stop() {
        auto endTimepoint = chrono::high_resolution_clock::now();

        auto start = chrono::time_point_cast<chrono::microseconds>(m_StartTimepoint).time_since_epoch().count(); // cast time to microsecond
        auto end = chrono::time_point_cast<chrono::microseconds>(endTimepoint).time_since_epoch().count(); // cast time to microsecond

        auto duration = end - start;
        
        std::cout << "duration: "<<duration << endl;

    }
private:
    chrono::time_point<chrono::high_resolution_clock>m_StartTimepoint;
};

int main()
{
    srand(time(0));
    
    //scope for performance analysis
    {
        Timer timer;
        functionToPerform();
        
    }
}

void functionToPerform() {

    for (size_t i = 0; i < 100; i++)
    {
    int number1 = rand() % 100;
    int number2 = rand() % 100;
    int number3 = rand() % 100;

    int result = number1 * number2 * number3;

    cout << result << endl;
    }

}