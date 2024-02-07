#include <iostream>
#include <string>

using namespace std;

/* the same as the normal factory pattern but the actual factory is brought inside the class that is generated
* exposing the factory from the original object drastically improves the usability of the AAPI;
*/

class Point {
private:
	Point(float x, float y) : x(x), y(y) {}
	struct PointFactory {
		static Point NewCartesian(float x, float y) {
			return Point{ x,y };
		}

		static Point NewPolar(float r, float theta) {
			return Point{ r * cos(theta),r * sin(theta) };
		}
	};

public:
	float x, y;
	static PointFactory Factory;
};


int main() {
	auto point = Point::Factory.NewCartesian(3, 4);
	auto point2 = Point::Factory.NewPolar(10, 30);
}