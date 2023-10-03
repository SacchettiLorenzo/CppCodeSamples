// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };


struct Product {
    string name;
    Color color;
    Size size;
};

//Base struct of the Filter specifications
template <typename T>
struct Specification {
    virtual bool is_satisfied(T* item) = 0;
};

//Base struct of the Filter, the filter function accept a dataset and a filter specification
template <typename T>
struct Filter {
    virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

//sub struct of filter that return a vector of product
struct BetterFilter : Filter<Product>
{
    vector<Product*> filter(vector<Product*> items, Specification<Product>& spec)override
    {
        vector<Product*> result;
        for (auto& p : items)
            if (spec.is_satisfied(p))
                result.push_back(p);
        return result;
    }
};

//color specification for the filter
struct ColorSpecification : Specification<Product> {
    Color color;
    explicit ColorSpecification(const Color color) : color{ color } {}

    bool is_satisfied(Product* item) override {
        return item->color == color;
    }
};

//size specification for the filter
struct SizeSpecification : Specification<Product> {
    Size size;
    explicit SizeSpecification(const Size size) : size{ size } {}

    bool is_satisfied(Product* item) override {
        return item->size == size;
    }
};

//AndSpecification return the a list of element that match both Specification
template <typename T>
struct AndSpecification :Specification<T> {
    Specification<T>& first;
    Specification<T>& second;

    AndSpecification(Specification<T>& first, Specification<T>& second) : first{ first }, second{ second } {}

    bool is_satisfied(T* item) override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

//OrSpecification return the a list of element that match at least one specification
template <typename T>
struct OrSpecification :Specification<T> {
    Specification<T>& first;
    Specification<T>& second;

    OrSpecification(Specification<T>& first, Specification<T>& second) : first{ first }, second{ second } {}

    bool is_satisfied(T* item) override {
        return first.is_satisfied(item) || second.is_satisfied(item);
    }
};
int main()
{
    Product apple{ "Apple", Color::Green, Size::Small };
    Product tree{ "Tree", Color::Green, Size::Large };
    Product house{ "House", Color::Blue, Size::Large };
    Product r{ "r", Color::Red, Size::Medium };

    vector<Product*> all{&apple, & tree, & house, & r};

    BetterFilter bf;

    //Specification for filtering green element
    ColorSpecification green(Color::Green);

    auto green_things = bf.filter(all, green);
    for (auto& x : green_things) {
        cout << x->name << " is green" << endl;
    }

    //Specification for filtering large element
    SizeSpecification large(Size::Large);

    //Specification for filtering green and large element
    AndSpecification<Product> green_and_large{large, green};

    ColorSpecification red(Color::Red);

    OrSpecification<Product> red_or_green_and_large{green_and_large, red};

    //OrSpecification and AndSpecification are substruct of Specification so they can be concatanated to perform complex filtering 
    //A&&(B||C) for example

    auto big_green_thing = bf.filter(all, red_or_green_and_large);
    for (auto& x : big_green_thing) {
        cout << x->name << endl;
    }

}


