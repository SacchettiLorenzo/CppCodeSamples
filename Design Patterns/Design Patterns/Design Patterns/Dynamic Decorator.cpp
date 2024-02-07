#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*	The idea is to enhance existing types without modifying the original type
	and without causing an increase in the number of derived types

	in the example we want to enhance a class called Shape with
	Colored Shape and TransparentShape
	every time we define a new class for a particular kind of shape we need to create the class that "merge" the two behaviuor
	ColoredTransparentShape
	In this way the number of derived classes increase with a huge ratio so we need to use the Decorator design pattern

	In this example it is used the Dynamic Composition Decorator that allow the composition of something at runtime
	it gives flexibility because the composition can happen in response of some input

	compose mean to create an object using a reference to a parent class and not only by inheriting his members
*/

struct Shape {
	virtual string str() const = 0;
};

struct Circle : Shape {
	float radius;

	explicit Circle(const float radius)  : radius{radius}{}

	void resize(float factor) { 
		radius *= factor; 
	}

	string str() const override {
		ostringstream oss;
		oss << "circle with radius " << radius << endl;
		return oss.str();
	}
};

//composing enhanched shape
struct ColoredShape : Shape {
	Shape& shape; //composing 
	string color;

	ColoredShape(Shape& shape, const string& color ) : shape{shape}, color{color}{}

	string str() const override {
		ostringstream oss;
		oss << shape.str() << "has the color " << color << endl;
		return oss.str();
	}
};

struct TransparentShape : Shape {
	Shape& shape;
	uint8_t transparency;

	TransparentShape(Shape& shape, const uint8_t transparency) : shape{ shape },transparency{transparency}{}

	string str() const override {
		ostringstream oss;
		oss << shape.str() << "has " << static_cast<float>(transparency) / 255.f * 100.f << "% transparency" << endl;
		return oss.str();
	}
};

int main() {
	Circle circle{ 0.5f };
	ColoredShape redCircle{ circle,"red" };
	cout << redCircle.str();

	TransparentShape tCircle{ circle,85 };
	cout << tCircle.str();

	//merging TransparentShape and ColoredShape

	Circle C{ 2.5f };
	ColoredShape blueCircle{ C,"blue" };
	TransparentShape MyCircle{
		blueCircle,64
	};
	cout << MyCircle.str();

	//or
	Circle CC{ 3.0f };
	TransparentShape ttCircle{ CC,25 };
	ColoredShape MyCircle2{
		ttCircle,"green"
	};

	cout << MyCircle2.str();

}