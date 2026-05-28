#include <iostream>

using namespace std;

class Entity {
private:
    string n_name;
    mutable int m_debugCount = 0;
public:
    const string& GetName() const {
        m_debugCount++;
        return n_name;
    }
};

int main()
{
    const Entity e;
    e.GetName();

    int x = 0;

    auto f = [=]() mutable {
        x++;
        cout << x << endl;
        };
}

//mutable allow const functions to update non-const variable
//in lambda every variable passed by reference or value cannot be modified unles the lambda expression is mutable
