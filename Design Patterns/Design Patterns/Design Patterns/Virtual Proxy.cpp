#include <iostream>

using namespace std;

struct Image {
	virtual void draw() = 0;
};

//normal non-lazy class
struct Bitmap : Image {
	Bitmap(const string& filename) {
		this->filename = filename;
		cout << "Loading image from " << filename << endl;
	}

	void draw() override {
		cout << "Drawing image" << filename << endl;
	}

private:
	string filename;
};

struct LazyBitmap : Image {
	LazyBitmap(const string& filename) : filename{filename}{}

	~LazyBitmap() { delete bmp; }

	void draw() override {
		if (!bmp) {
			bmp = new Bitmap(filename); //bmp constructed only after draw() call
		}
		bmp->draw();
	}

private:
	Bitmap* bmp{ nullptr };
	string filename;
};

int main() {
	//using non lazy image
	Bitmap img{ "pokemon.png" }; //image loaded here
	img.draw();

	LazyBitmap limg{ "pokemon.png" };
	limg.draw(); //image loaded here
}
/*	Virtual Proxy implement lazy instantiation.
*	the object is constructed only when it is accessed so it does not get allocated prematurely
*	this kind of design becomes handy when an object is used few times or in a late stage of the programm
*	this approach is helpfull at saving some memory
*	it is possible to interact with the object with his virtual instance before it is actually used and initialized
*	
*	in the example we suppose that an image is loaded when the constuctor is called and we want to create 
*	proxy that implement the lazy version of that functionality. the original class cannot be modified
*/