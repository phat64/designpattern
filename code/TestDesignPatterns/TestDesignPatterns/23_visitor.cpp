#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <assert.h>

using namespace std;
typedef std::string String;

namespace visitor
{
	namespace withoutvisitor
	{
		class Fruit {
		public:
			Fruit() {}
			virtual ~Fruit() {}
		};

		class Orange : public Fruit { };
		class Apple : public Fruit { };
		class Banana : public Fruit { };

		list<Fruit*> getFruits()
		{
			list<Fruit*> fruits = {
				new Orange(), new Apple(), new Banana(),
				new Banana(), new Banana(), new Orange() };
			return fruits;
		}


		void sort()
		{
			list<Fruit*> fruits = getFruits();

			list<Orange*> oranges;
			list<Apple*> apples;
			list<Banana*> bananas;
			
			for(Fruit* fruit : fruits)
			{
				if (Orange* orange = dynamic_cast<Orange*>(fruit))
					oranges.push_back(orange);
				else if (Apple* apple = dynamic_cast<Apple*>(fruit))
					apples.push_back(apple);
				else if (Banana* banana = dynamic_cast<Banana*>(fruit))
					bananas.push_back(banana);
			}

			/*
			It works, but there are lots of problems with this code:

			- For a start, its ugly.
			- Its not type - safe, we won't catch type errors until runtime.
			- Its not maintainable.If we add a new derived instance of Fruit,
				we need to do a global search for every place which performs a fruit type-test, otherwise we might miss types.
			*/
		}
	}

	namespace withvisitor{

		class Fruit;
		class Orange;
		class Apple;
		class Banana;

		class IFruitVisitor
		{
		public:
			virtual void Visit(Orange* fruit) = 0;
			virtual void Visit(Apple* fruit) = 0;
			virtual void Visit(Banana* fruit) = 0;
		};

		class Fruit { public: virtual void Accept(IFruitVisitor* visitor) = 0; };
		class Orange : public Fruit { public: void Accept(IFruitVisitor* visitor) { visitor->Visit(this); } };
		class Apple : public Fruit { public: void Accept(IFruitVisitor* visitor) { visitor->Visit(this); } };
		class Banana : public Fruit { public: void Accept(IFruitVisitor* visitor) { visitor->Visit(this); } };

		class FruitPartitioner : public IFruitVisitor
		{
		public:
			list<Orange*> Oranges;
			list<Apple*> Apples;
			list<Banana*> Bananas;
					
			
			FruitPartitioner() {}

			void Visit(Orange* fruit) { Oranges.push_back(fruit); }
			void Visit(Apple* fruit) { Apples.push_back(fruit); }
			void Visit(Banana* fruit) { Bananas.push_back(fruit); }
		};

		/*
		This has the advantages of:
		- Being relatively clean, easy to read code.
		- Type-safety, type errors are caught at compile time.
		- Maintainability. If I add a remove a concrete Fruit class, I could modify my IFruitVisitor interface to handle the type accordingly, and the compiler will immediately find all places where we implement the interface so we can make the appropriate modifications.
		*/
	}
}

using namespace visitor::withvisitor;

int main(int argc, char ** argv)
{
	list<Fruit*> fruits = {
		new Orange(), new Apple(), new Banana(),
		new Banana(), new Banana(), new Orange() };

	FruitPartitioner partitioner;
	for (Fruit* fruit : fruits)
	{
		fruit->Accept(&partitioner);
	}

	// result
	cout << "Oranges count "<< partitioner.Oranges.size() <<endl;
	cout << "Apples count " << partitioner.Apples.size() << endl;
	cout << "Bananas count " << partitioner.Bananas.size() << endl;

	// clear fruits
	for (Fruit* fruit : fruits)
	{
		delete fruit;
	}
	fruits.clear();

	return 0;
}

/* output :
Oranges count 2
Apples count 1
Bananas count 3
*/
