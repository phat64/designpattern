#include <iostream>
#include <list>
#include <assert.h>

using namespace std;
typedef std::string String;

class Packing;

// Create an interface Item representing food item and packing.

class Item {
public:
	virtual const char* name() = 0;
	virtual Packing* packing() = 0;
	virtual float price() = 0;
};

class Packing {
public:
	virtual const char* pack() = 0;
};

// Create concrete classes implementing the Packing interface.
class Wrapper : public Packing {
public:
	const char* pack() {
		return "Wrapper";
	}
};

class Bottle : public Packing {
public:
	const char* pack() {
		return "Bottle";
	}
};

// Create abstract classes implementing the item interface providing default functionalities.
class Burger : public Item {
	Wrapper wrapper;
public:
	Packing* packing() {
		return &wrapper;
	}

	virtual float price() = 0;
};

class ColdDrink:  public Item {
	Bottle bottle;
public:
	Packing* packing() {
		return &bottle;
	}

	virtual float price() = 0;
};

// Create concrete classes extending Burger and ColdDrink classes
class VegBurger : public Burger {
public:
	float price() {
		return 25.0f;
	}

	const char*  name() {
		return "Veg Burger";
	}
};

class ChickenBurger : public Burger {
public:
	float price() {
		return 50.5f;
	}

	const char* name() {
		return "Chicken Burger";
	}
};

class Coke : public ColdDrink {
public:
	float price() {
		return 30.0f;
	}

	const char* name() {
		return "Coke";
	}
};

class Pepsi : public ColdDrink {
public:
	float price() {
		return 35.0f;
	}

	const char* name() {
		return "Pepsi";
	}
};

// Create a Meal class having Item objects defined above.

class Meal {
private:
	std::list<Item*> items;

public:
	virtual ~Meal()
	{
		for (Item* item : items) {
			delete item;
		}
		items.clear();
	}

	void addItem(Item* item) {
		items.push_back(item);
	}

	float getCost() {
		float cost = 0.0f;

		for (Item* item : items) {
			cost += item->price();
		}
		return cost;
	}

	void showItems() {
		for (Item* item : items) {
			cout << "Item : " << item->name();
			cout << ", Packing : " << item->packing()->pack();
			cout << ", Price : " << item->price();
			cout << endl;
		}
	}
};

// Create a MealBuilder class, the actual builder class responsible to create Meal objects.
class MealBuilder {

public:
	Meal* prepareVegMeal() {
		Meal* meal = new Meal();
		meal->addItem(new VegBurger());
		meal->addItem(new Coke());
		return meal;
	}

	Meal* prepareNonVegMeal() {
		Meal* meal = new Meal();
		meal->addItem(new ChickenBurger());
		meal->addItem(new Pepsi());
		return meal;
	}
};

// BuiderPatternDemo uses MealBuider to demonstrate builder pattern.

void main13(int argc, char ** argv) {

	MealBuilder* mealBuilder = new MealBuilder();

	Meal* vegMeal = mealBuilder->prepareVegMeal();
	cout << "Veg Meal" << endl;
	vegMeal->showItems();
	cout << "Total Cost: " << vegMeal->getCost() << endl;
	delete vegMeal;

	cout << endl;
	cout << endl;

	Meal* nonVegMeal = mealBuilder->prepareNonVegMeal();
	cout << "Non-Veg Meal" << endl;
	nonVegMeal->showItems();
	cout << "Total Cost: " << nonVegMeal->getCost() << endl;
	delete nonVegMeal;

	delete mealBuilder;
}

/*
Veg Meal
Item : Veg Burger, Packing : Wrapper, Price : 25.0
Item : Coke, Packing : Bottle, Price : 30.0
Total Cost : 55.0


Non - Veg Meal
Item : Chicken Burger, Packing : Wrapper, Price : 50.5
Item : Pepsi, Packing : Bottle, Price : 35.0
Total Cost : 85.5
*/