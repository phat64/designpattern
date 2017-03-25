#include <iostream>
#include <map>
#include <vector>
#include <assert.h>

using namespace std;
typedef std::string String;
namespace flyweight {
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
	private:
		String color;
		int x;
		int y;
		int radius;

	public:
		Circle(const String &color)
		{
			this->x = 0;
			this->y = 0;
			this->radius = 0;
			this->color = color;
		}

		virtual ~Circle() {	}

		void setX(int x) {
			this->x = x;
		}

		void setY(int y) {
			this->y = y;
		}

		void setRadius(int radius) {
			this->radius = radius;
		}

		virtual void draw() {
			cout << "Circle: Draw() [Color : " << color.c_str()
				<< ", x : " << x << ", y :" << y
				<< ", radius :" << radius << endl;
		}
	};

	// Create a factory to generate object of concrete class based on given information
	class ShapeFactory {
	private:
		static map<String, Shape*> circleMap;

	public:
		static Shape* getCircle(const String& color) {
			Circle* circle = (Circle*)circleMap[color];
			if (circle == nullptr) {
				circle = new Circle(color);
				circleMap[color] = circle;
				cout << "Creating circle of color : " << color.c_str() << endl;
			}
			return circle;
		}

		static void clean()
		{
			for (auto iter : circleMap)
			{
				delete iter.second;
			}
			circleMap.clear();
		}
	};
	map<String, Shape*> ShapeFactory::circleMap;
}

using namespace flyweight;

const String& getRandomColor();
int getRandomX();
int getRandomY();



void main18(int argc, char ** argv) {

	for (int i = 0; i < 20; ++i) {
		Circle* circle = (Circle*)ShapeFactory::getCircle(getRandomColor());
		circle->setX(getRandomX());
		circle->setY(getRandomY());
		circle->setRadius(100);
		circle->draw();
	}

	ShapeFactory::clean();
}

int random(int max)
{
	return rand() % max;
}

const String& getRandomColor() {
	static vector<String> colors = { "Red", "Green", "Blue", "White", "Black" };
	return colors[random((int)colors.size())];
}

int getRandomX() {
	return random(100);
}

int getRandomY() {
	return random(100);
}

/* Output:
Creating circle of color : Black
Circle: Draw() [Color : Black, x : 36, y :71, radius :100
Creating circle of color : Green
Circle: Draw() [Color : Green, x : 27, y :27, radius :100
Creating circle of color : White
Circle: Draw() [Color : White, x : 64, y :10, radius :100
Creating circle of color : Red
Circle: Draw() [Color : Red, x : 15, y :44, radius :100
Circle: Draw() [Color : Green, x : 19, y :10, radius :100
Circle: Draw() [Color : Green, x : 94, y :32, radius :100
Circle: Draw() [Color : White, x : 69, y :98, radius :100
Creating circle of color : Blue
Circle: Draw() [Color : Blue, x : 13, y :4, radius :100
Circle: Draw() [Color : Green, x : 21, y :21, radius :100
Circle: Draw() [Color : Blue, x : 55, y :86, radius :100
Circle: Draw() [Color : White, x : 90, y :70, radius :100
Circle: Draw() [Color : Green, x : 78, y :3, radius :100
Circle: Draw() [Color : Green, x : 64, y :89, radius :100
Circle: Draw() [Color : Blue, x : 3, y :91, radius :100
Circle: Draw() [Color : Blue, x : 62, y :82, radius :100
Circle: Draw() [Color : Green, x : 97, y :61, radius :100
Circle: Draw() [Color : Green, x : 86, y :12, radius :100
Circle: Draw() [Color : Green, x : 38, y :93, radius :100
Circle: Draw() [Color : Red, x : 76, y :82, radius :100
Circle: Draw() [Color : Blue, x : 95, y :82, radius :100
*/