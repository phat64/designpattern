#include <iostream>
#include <assert.h>

using namespace std;
typedef std::string String;

class Shape
{
public:
	//virtual ~Shape() = 0;
	virtual void draw() = 0;
};

class Circle : public Shape
{
public:
	Circle() {}
	virtual ~Circle() {}
	void draw(){cout << "draw circle" << endl;}
};

class Rectangle : public Shape
{
public:
	Rectangle() {}
	virtual ~Rectangle() {}
	void draw() { cout << "draw rectangle" << endl; }
}; 

class Square : public Shape
{
public:
	Square() {}
	virtual ~Square() {}
	void draw() { cout << "draw square" << endl; }
};

class ShapeFactory {

	//use getShape method to get object of type shape 
public:
	static Shape* getShape(const String & shapeType) {

		if (shapeType == "CIRCLE") {
			return new Circle();

		}
		else if (shapeType == "RECTANGLE") {
			return new Rectangle();

		}
		else if (shapeType == "SQUARE") {
			return new Square();
		}

		return nullptr;
	}
};

int main2(int argc, char** argv)
{
	Circle* circle = (Circle*) ShapeFactory::getShape("CIRCLE");
	circle->draw();

	Rectangle* rectangle = (Rectangle*)ShapeFactory::getShape("RECTANGLE");
	rectangle->draw();

	Square* square = (Square*)ShapeFactory::getShape("CIRCLE");
	square->draw();

	delete circle;
	delete rectangle;
	delete square;

	return 0;
}

/*output :
draw circle
draw rectangle
draw square
*/