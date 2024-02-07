#include <iostream>
#include <string>
using namespace std;

struct Renderer {
	virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer : Renderer {
	void render_circle(float x, float y, float radius) override {
		cout << "Drawing a vector circle with radius" << radius << endl;
	}
};

struct RasterRenderer : Renderer {
	void render_circle(float x, float y, float radius) override {
		cout << "Rasterizing circle with radius" << radius << endl;
	}
};

//bridge class
struct Shape {
protected:
	Renderer& renderer;
	Shape(Renderer& renderer): renderer{renderer}{}
public:
	virtual void draw() = 0;
	virtual void resize(float factor) = 0;
};

struct Circle : Shape {
	float x, y, radius;
	void draw() override {
		renderer.render_circle(x, y, radius);
	}

	void resize(float factor) override {
		radius *= factor;
	}

	Circle(Renderer& renderer, float x, float y, float radius) : Shape{renderer}, x{x}, y{y}, radius{radius}{}
};

int main() {
	RasterRenderer rr;
	Circle raster_circle{ rr,5,5,5 };
	raster_circle.draw();
	raster_circle.resize(2);
	raster_circle.draw();
}

/*	The bridge design pattern consist in a class/struct that connect two classes
	the main purpose of this class is to make sure that every class respect the principle of Single Responsibility
	for example in a drawing programm we shold have a class that draw and a class that hold infomation about shape
	the class that hold informations about shapes should not draw 
	the example simulate a class that can render in both vectorial and raster mode and a class that manage shapes

	the class Circle does not rendere but hold a reference to a class that can render
*/