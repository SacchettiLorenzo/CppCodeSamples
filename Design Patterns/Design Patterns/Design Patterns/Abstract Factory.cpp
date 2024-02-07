#include <iostream>
#include <string>
#include <map>

using namespace std;

/* The abstract factory focus on the creation of multiple object in the same factory
* 
*
*/

struct HotDrink {
	virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink {
	void prepare(int volume) override {
		cout << "Take tea bag, boil water, pour" << volume << "ml, add some lemon" << endl;
	}

	unique_ptr<HotDrink> make_drink(string type) {
		unique_ptr<HotDrink> drink;
		if (type == "tea") {
			drink = make_unique<Tea>();
			drink->prepare(200);
		}
		return drink;
	}
};

struct Coffee : HotDrink {
	void prepare(int volume) override {
		cout << "take coffee powder, boil water" << volume << "ml" << endl;
	}

	unique_ptr<HotDrink> make_drink(string type) {
		unique_ptr<HotDrink> drink;
		if (type == "coffee") {
			drink = make_unique<Coffee>();
			drink->prepare(100);
		}
	}
};

struct HotDrinkFactory {
	virtual unique_ptr<HotDrink> make() const = 0;
};

struct CoffeeFactory : HotDrinkFactory {
	unique_ptr<HotDrink> make() const override {
		return make_unique<Coffee>();
	}
};

struct TeaFactory : HotDrinkFactory {
	unique_ptr<HotDrink> make() const override {
		return make_unique<Tea>();
	}
};

class DrinkFactory {
	map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
	DrinkFactory() {
		hot_factories["coffee"] = make_unique<CoffeeFactory>();
		hot_factories["tea"] = make_unique<TeaFactory>();
	}

	unique_ptr<HotDrink> make_drink(const string& name) {
		auto drink = hot_factories[name]->make();
		drink->prepare(200);
		return drink;
	}
};

int main() {
	DrinkFactory factory;
	auto d1 = factory.make_drink("tea");
	auto d2 = factory.make_drink("coffee");
	
}