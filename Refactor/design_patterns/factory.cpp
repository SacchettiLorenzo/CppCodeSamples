#include <iostream>
#include <string>

using namespace std;

/* A factory design pattern let specialized methods create objects
* the constructor is often set protected or private in order to force the use of the specialized methods
* 
*/

class Point {
	float x, y;
	friend class PointFactory;
private:
	Point(float x, float y): x(x), y(y){}
};

struct PointFactory {
	static Point NewCartesian(float x, float y) {
		return Point{ x,y };
	}

	static Point NewPolar(float r, float theta) {
		return Point{ r*cos(theta),r*sin(theta)};
	}
};

int main() {
	auto point = PointFactory::NewCartesian(3, 4);
	auto point2 = PointFactory::NewPolar(10, 30);
}

/*	Recap:
*	A factory method is a class member that act as a way of creating object. 
*	It typically replaces a constructor
* 
*	A factory is tipically a separate class that knowe how to construct objects
* 
*	An abstract factory is an abstract class that can be inherited by concrete classes that offer a family of types.
* 
*	A factory has advantages over a simple constructor call:
*		can return a nullptr
*		can make objects of different types
*		can implement caching and storage optimization
*		can make object of different types even if not related with each other
*/