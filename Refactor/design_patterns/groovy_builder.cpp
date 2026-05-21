#include <iostream>
#include <vector>

using namespace std;

struct Tag {
	string name;
	string text;
	vector<Tag> children;
	vector<pair<string, string>> attributes;

	Tag& add_attribute(string attribute, string value) {
		attributes.emplace_back(make_pair(attribute, value));
		return *this;
	}

protected:
	Tag(const string& name, const string& text) : name{ name }, text{ text } {}; //constructor with name and text
	Tag(const string& name, const vector<Tag>& children) : name{ name }, children{ children } {}; //constructor with name and children
	Tag(const string& name, const string& text, const vector<Tag>& children) : name{ name }, text{text}, children { children } {}; // constructor with name, text and children
};

struct Div : Tag {
	explicit Div(const string& text) : Tag{ "div", text } {};//constructor with name and text
	Div(initializer_list<Tag> children) : Tag("div", children) {};//constructor with name and children
	Div(const string& text, initializer_list<Tag> children) : Tag("div", text,children) {};// constructor with name, text and children
};

struct Button : Tag {
	explicit Button(const string& text) : Tag{ "button", text } {};//constructor with name and text
};

struct IMG : Tag {
	explicit IMG(const string& url) : Tag{ "img", "" }//constructor with name
	{
		attributes.emplace_back(make_pair("src",url));
	}
};

int main() {
	//using groovy style pattern
	Div my_html_structure //extarnal structure 
	{"first div", //text
				{
				Button{"My first Button"}, //first child
				IMG{"http:/url.com"}.add_attribute("height","50 px").add_attribute("width","50 px"), //second child (with attributes)
				Div{"second div", //third child with children
								{
								Button{"My second Button"}.add_attribute("color","red").add_attribute("margin","50 px")
								}
					},
					Div{}
				}
	}; 

	//not using groovy style pattern
	Div my_html_structure2("first div");

	Button firstButton("My first Button");

	IMG img("http:/url.com");
	img.add_attribute("height", "50 px").add_attribute("width", "50 px");

	Div secondDiv("second div");

	Button secondButton("My second Button");
	secondButton.add_attribute("color", "red").add_attribute("margin", "50 px");

	Div anotherDiv("");

	secondDiv.children.push_back(secondButton);

	my_html_structure2.children.push_back(firstButton);
	my_html_structure2.children.push_back(img);
	my_html_structure2.children.push_back(secondDiv);
	my_html_structure2.children.push_back(anotherDiv);
	 

}

/* GROOVY STYLE BUILDER PATTERN
*  allow nested object initialization
*  an object can be initialized by itself or passing his child
* 
*  in the example the idea is to render an HTML structure like:
*  <div>
*		<button>
*       </button>
*		<img>
*  </div>
* 
*  a div can have children but button and img cannot.
*  a div and a button can have text but img cannot.
* 
*  using initializer_list and vectors of children is possible to build massive object without the extensive use of adding functions
* 
*  it is still possible to use the standard method that envolve the creation of object and the one by one assignement but it is more verbose and difficult to understand with big objects
* 
*  fluent builder is used to add attributes to the objects
* 
* initializer_list automatically construct a list of object
*/