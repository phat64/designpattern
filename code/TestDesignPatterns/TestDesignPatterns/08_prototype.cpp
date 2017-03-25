#include <iostream>
#include <map>
#include <assert.h>

using namespace std;
typedef std::string String;

#define SafeDelete(ptr) if (ptr){ delete ptr; ptr = nullptr; }


// Create an interface
class Cloneable
{
public:
	virtual void* clone() = 0;
};

// Create an abstract class implementing Clonable interface.
class Shape : public Cloneable {
private:
	String id;
	String type;

public:
	Shape():id(), type() {}

	virtual void draw() {}

	const String& getType() {
		return type;
	}

	void setType(const String & type) {
		this->type = type;
	}

	const String& getId() {
		return id;
	}

	void setId(const String & id) {
		this->id = id;
	}

	void* clone() {
		Shape* clone = nullptr;

		clone = new Shape;
		clone->setId(id);
		clone->setType(type);

		return (void*)clone;
	}
};

// Create 3 concrete classes

class Rectangle : public Shape {

public:
	Rectangle() {
		setType("Rectangle");
	}

	void draw() {
		cout << "Inside Rectangle::draw() method." << endl;
	}
};

class Square : public Shape {

public:
	Square() {
		setType("Square");
	}

	void draw() {
		cout << "Inside Square::draw() method." << endl;
	}
};


class Circle : public Shape {
public:
	Circle() {
		setType("Circle");
	}

	void draw() {
		cout << "Inside Circle::draw() method." << endl;
	}
};

// Create a class to get concrete classes from database
// and store them in a Hashtable.
class ShapeCache {
private:
	static map<String, Shape*> shapeMap;

public:
	static Shape* getShape(const String & shapeId) {
		Shape* cachedShape = shapeMap[shapeId];
		return (Shape*)cachedShape->clone();
	}

	// for each shape run database query and create shape
	// shapeMap.put(shapeKey, shape);
	// for example, we are adding three shapes
	static void loadCache() {
		Circle* circle = new Circle();
		circle->setId("1");
		shapeMap[circle->getId()] = circle;

		Square* square = new Square();
		square->setId("2");
		shapeMap[square->getId()] = square;

		Rectangle* rectangle = new Rectangle();
		rectangle->setId("3");
		shapeMap[rectangle->getId()] = rectangle;
	}
};
map<String, Shape*> ShapeCache::shapeMap;

// example
int main8(int argc, char ** argv) {
	ShapeCache::loadCache();

	Shape* clonedShape = (Shape*)ShapeCache::getShape("1");
	cout << "Shape : " << clonedShape->getType().c_str() << endl;

	Shape* clonedShape2 = (Shape*)ShapeCache::getShape("2");
	cout << "Shape : " << clonedShape2->getType().c_str() << endl;

	Shape* clonedShape3 = (Shape*)ShapeCache::getShape("3");
	cout << "Shape : " << clonedShape3->getType().c_str() << endl;

	SafeDelete(clonedShape);
	SafeDelete(clonedShape2);
	SafeDelete(clonedShape3);

	return 0;
}

/*
Shape : Circle
Shape : Square
Shape : Rectangle
*/