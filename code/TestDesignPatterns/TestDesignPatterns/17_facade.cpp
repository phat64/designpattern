#include <iostream>
#include <assert.h>

using namespace std;
typedef std::string String;
namespace facade {


// Create an "interface"
class Shape
{
public:
	virtual ~Shape() {}
	virtual void draw() = 0;
};

// Create concrete classes implementing the same interface
class Circle : public Shape
{
public:
	Circle() {}
	virtual ~Circle() {	}
	virtual void draw() { cout << "draw circle" << endl; }
};

class Rectangle : public Shape
{
public:
	Rectangle() {}
	virtual ~Rectangle() {}
	virtual void draw() { cout << "draw rectangle" << endl; }
};

class Square : public Shape
{
public:
	Square() {}
	virtual ~Square() {}
	virtual void draw() { cout << "draw square" << endl; }
};

// Create a facade class
class ShapeMaker {
private:
	Shape* circle;
	Shape* rectangle;
	Shape* square;

public:
	ShapeMaker() {
		circle = new Circle();
		rectangle = new Rectangle();
		square = new Square();
	}

	virtual ~ShapeMaker()
	{
		delete circle;
		delete rectangle;
		delete square;
	}

	void drawCircle() {
		circle->draw();
	}
	void drawRectangle() {
		rectangle->draw();
	}
	void drawSquare() {
		square->draw();
	}
};

};

using namespace facade;

// Use the facade to draw various types of shapes.
void main17(int argc, char ** argv) {
	ShapeMaker* shapeMaker = new ShapeMaker();

	shapeMaker->drawCircle();
	shapeMaker->drawRectangle();
	shapeMaker->drawSquare();

	delete shapeMaker;
}